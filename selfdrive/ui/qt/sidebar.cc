#include "selfdrive/ui/qt/sidebar.h"

#include <QMouseEvent>

#include "selfdrive/ui/qt/util.h"

#include <QProcess>
#include <QSoundEffect>

void Sidebar::drawMetric(QPainter &p, const QString &label, const QString &val, QColor c, int y) {
  const QRect rect = {30, y, 240, val.isEmpty() ? (label.contains("\n") ? 124 : 100) : 148};

  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(c));
  p.setClipRect(rect.x() + 6, rect.y(), 18, rect.height(), Qt::ClipOperation::ReplaceClip);
  p.drawRoundedRect(QRect(rect.x() + 6, rect.y() + 6, 100, rect.height() - 12), 10, 10);
  p.setClipping(false);

  QPen pen = QPen(QColor(0xff, 0xff, 0xff, 0x55));
  pen.setWidth(2);
  p.setPen(pen);
  p.setBrush(Qt::NoBrush);
  p.drawRoundedRect(rect, 20, 20);

  p.setPen(QColor(0xff, 0xff, 0xff));
  if (val.isEmpty()) {
    configFont(p, "Open Sans", 35, "Bold");
    const QRect r = QRect(rect.x() + 30, rect.y(), rect.width() - 40, rect.height());
    p.drawText(r, Qt::AlignCenter, label);
  } else {
    configFont(p, "Open Sans", 58, "Bold");
    p.drawText(rect.x() + 50, rect.y() + 71, val);
    configFont(p, "Open Sans", 35, "Regular");
    p.drawText(rect.x() + 50, rect.y() + 50 + 77, label);
  }
}

Sidebar::Sidebar(QWidget *parent) : QFrame(parent) {
  home_img = QImage("../assets/images/button_home.png").scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  settings_img = QImage("../assets/images/button_settings.png").scaled(settings_btn.width(), settings_btn.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

  connect(this, &Sidebar::valueChanged, [=] { update(); });

  setAttribute(Qt::WA_OpaquePaintEvent);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  setFixedWidth(300);
}

void Sidebar::mousePressEvent(QMouseEvent *event) {
  if (settings_btn.contains(event->pos())) {
    QUIState::ui_state.scene.setbtn_count = QUIState::ui_state.scene.setbtn_count + 1;
    if (QUIState::ui_state.scene.setbtn_count > 1) {
      QUIState::ui_state.scene.setbtn_count = 0;
      emit openSettings();
    }
    return;
  }
  // OPKR 
  if (home_btn.contains(event->pos())) {
      QUIState::ui_state.scene.homebtn_count = QUIState::ui_state.scene.homebtn_count + 1;
    if (QUIState::ui_state.scene.homebtn_count > 2) {
      QUIState::ui_state.scene.homebtn_count = 0;
      QProcess::execute("/data/openpilot/run_mixplorer.sh");
    }
    return;
  }
  // OPKR map overlay
  if (overlay_btn.contains(event->pos()) && QUIState::ui_state.scene.started) {
    QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile("/data/openpilot/selfdrive/assets/sounds/warning_1.wav"));
    //effect.setLoopCount(1);
    //effect.setLoopCount(QSoundEffect::Infinite);
    //effect.setVolume(0.1);
    float volume = 0.5f;
    if (QUIState::ui_state.scene.nVolumeBoost < 0) {
      volume = 0.0f;
    } else if (QUIState::ui_state.scene.nVolumeBoost > 1) {
      volume = QUIState::ui_state.scene.nVolumeBoost * 0.01;
    }
    effect.setVolume(volume);
    effect.play();
    QProcess::execute("am start --activity-task-on-home com.opkr.maphack/com.opkr.maphack.MainActivity");
    QUIState::ui_state.scene.map_on_top = false;
    QUIState::ui_state.scene.map_on_overlay = !QUIState::ui_state.scene.map_on_overlay;
  }
}

void Sidebar::updateState(const UIState &s) {
  auto &sm = *(s.sm);

  auto deviceState = sm["deviceState"].getDeviceState();
  setProperty("netType", network_type[deviceState.getNetworkType()]);
  int strength = (int)deviceState.getNetworkStrength();
  setProperty("netStrength", strength > 0 ? strength + 1 : 0);

  ItemStatus connectstatus;
  auto last_ping = deviceState.getLastAthenaPingTime();
  if (last_ping == 0) {
    connectstatus = ItemStatus{"네트워크\n오프라인", warning_color};
  } else {
    connectstatus = nanos_since_boot() - last_ping < 80e9 ? ItemStatus{"네트워크\n온라인", good_color} : ItemStatus{"네트워크\n오류", danger_color};
  }
  setProperty("connectStatus", QVariant::fromValue(connectstatus));

  QColor tempColor = danger_color;
  auto ts = deviceState.getThermalStatus();
  if (ts == cereal::DeviceState::ThermalStatus::GREEN) {
    tempColor = good_color;
  } else if (ts == cereal::DeviceState::ThermalStatus::YELLOW) {
    tempColor = warning_color;
  }
  setProperty("tempStatus", QVariant::fromValue(ItemStatus{QString("%1°C").arg((int)deviceState.getAmbientTempC()), tempColor}));

  ItemStatus pandaStatus = {"차량\n연결됨", good_color};
  if (s.scene.pandaType == cereal::PandaState::PandaType::UNKNOWN) {
    pandaStatus = {"차량\n연결안됨", danger_color};
  } else if (s.scene.started && !sm["liveLocationKalman"].getLiveLocationKalman().getGpsOK() && s.scene.gpsAccuracyUblox != 0.00) {
    pandaStatus = {"차량연결됨\nGPS검색중", warning_color};
  } else if (s.scene.satelliteCount > 0) {
  	pandaStatus = {QString("차량연결됨\nSAT : %1").arg(s.scene.satelliteCount), good_color};
  }
  setProperty("pandaStatus", QVariant::fromValue(pandaStatus));

  // opkr
  QString iPAddress = "N/A";
  QString sSID = "---";
  if (network_type[deviceState.getNetworkType()] != "--") {
    std::string m_strip = s.scene.deviceState.getWifiIpAddress();
    std::string m_strssid = s.scene.deviceState.getWifiSSID();
    iPAddress = QString::fromUtf8(m_strip.c_str());
    sSID = QString::fromUtf8(m_strssid.c_str());
  }
  QString bATStatus = "DisCharging";
  std::string m_battery_stat = s.scene.deviceState.getBatteryStatus();
  bATStatus = QString::fromUtf8(m_battery_stat.c_str());

  setProperty("iPAddress", iPAddress);
  setProperty("sSID", sSID);
  setProperty("bATStatus", bATStatus);
  setProperty("bATPercent", (int)deviceState.getBatteryPercent());
}

void Sidebar::paintEvent(QPaintEvent *event) {
  QPainter p(this);
  p.setPen(Qt::NoPen);
  p.setRenderHint(QPainter::Antialiasing);

  p.fillRect(rect(), QColor(0, 0, 0));
  // static imgs
  p.setOpacity(0.65);
  p.drawImage(settings_btn.x(), settings_btn.y(), settings_img);
  p.setOpacity(1.0);
  p.drawImage(60, 1080 - 180 - 40, home_img);

  // network
  int x = 58;
  const QColor gray(0x54, 0x54, 0x54);
  for (int i = 0; i < 5; ++i) {
    p.setBrush(i < net_strength ? Qt::white : gray);
    p.drawEllipse(x, 196, 27, 27);
    x += 37;
  }

  configFont(p, "Open Sans", 35, "Regular");
  p.setPen(QColor(0xff, 0xff, 0xff));
  const QRect r = QRect(50, 243, 100, 50);
  p.drawText(r, Qt::AlignHCenter, net_type);

  // metrics
  drawMetric(p, "시스템온도", temp_status.first, temp_status.second, 378);
  drawMetric(p, panda_status.first, "", panda_status.second, 558);
  drawMetric(p, connect_status.first, "", connect_status.second, 716);

  // atom - ip
  if( bat_Percent <= 1) return;
  const QRect r2 = QRect(35, 295, 230, 50);
  configFont(p, "Open Sans", 28, "Bold");
  p.setPen(Qt::yellow);
  p.drawText(r2, Qt::AlignHCenter, wifi_IPAddress);

  // opkr - ssid
  const QRect r3 = QRect(35, 335, 230, 45);
  configFont(p, "Open Sans", 25, "Bold");
  p.setPen(Qt::white);
  p.drawText(r3, Qt::AlignHCenter, wifi_SSID);

  // atom - battery
  QRect  rect(160, 247, 76, 36);
  QRect  bq(rect.left() + 6, rect.top() + 5, int((rect.width() - 19) * bat_Percent * 0.01), rect.height() - 11 );
  QBrush bgBrush("#149948");
  p.fillRect(bq, bgBrush);
  p.drawImage(rect, battery_imgs[bat_Status == "Charging" ? 1 : 0]);

  p.setPen(Qt::white);
  configFont(p, "Open Sans", 25, "Regular");

  char temp_value_str1[32];
  snprintf(temp_value_str1, sizeof(temp_value_str1), "%d%%", bat_Percent );
  p.drawText(rect, Qt::AlignCenter, temp_value_str1);
}
