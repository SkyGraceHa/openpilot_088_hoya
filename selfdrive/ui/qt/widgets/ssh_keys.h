#pragma once

#include <QPushButton>
#include <QSoundEffect> // opkr

#include "selfdrive/hardware/hw.h"
#include "selfdrive/ui/qt/widgets/controls.h"
#include "selfdrive/ui/ui.h" // opkr
#include <QComboBox>
#include <QAbstractItemView>

// SSH enable toggle
class SshToggle : public ToggleControl {
  Q_OBJECT

public:
  SshToggle() : ToggleControl("SSH 접속 사용", "", "", Hardware::get_ssh_enabled()) {
    QObject::connect(this, &SshToggle::toggleFlipped, [=](bool state) {
      Hardware::set_ssh_enabled(state);
    });
  }
};

// SSH key management widget
class SshControl : public ButtonControl {
  Q_OBJECT

public:
  SshControl();

private:
  Params params;

  QLabel username_label;

  void refresh();
  void getUserKeys(const QString &username);
};

class SwitchOpenpilot : public ButtonControl {
  Q_OBJECT

public:
  SwitchOpenpilot();

private:
  Params params;

  QString githubid;
  QString githubrepo;
  QString githubbranch;

  void refresh();
  void getUserID(const QString &userid);
  void getRepoID(const QString &repoid);
  void getBranchID(const QString &branchid);
};

class SshLegacyToggle : public ToggleControl {
  Q_OBJECT

public:
  SshLegacyToggle() : ToggleControl("기존 공개KEY 사용", "SSH 접속시 기존 공개KEY(0.8.2이하)를 사용합니다.", "", Params().getBool("OpkrSSHLegacy")) {
    QObject::connect(this, &SshLegacyToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrSSHLegacy", status);
    });
  }
};

class GetoffAlertToggle : public ToggleControl {
  Q_OBJECT

public:
  GetoffAlertToggle() : ToggleControl("운행종료시 이온탈착 알림 사용", "운행종료 후 이온을 분리하라는 알림을 보냅니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrEnableGetoffAlert")) {
    QObject::connect(this, &GetoffAlertToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrEnableGetoffAlert", status);
    });
  }
};

class AutoResumeToggle : public ToggleControl {
  Q_OBJECT

public:
  AutoResumeToggle() : ToggleControl("자동출발 기능 사용", "SCC 사용중 정차시 자동출발 기능을 사용합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrAutoResume")) {
    QObject::connect(this, &AutoResumeToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrAutoResume", status);
    });
  }
};

class VariableCruiseToggle : public ToggleControl {
  Q_OBJECT

public:
  VariableCruiseToggle() : ToggleControl("가변 크루즈 사용", "SCC 사용중 크루즈 버튼을 이용하여 가감속을 보조합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrVariableCruise")) {
    QObject::connect(this, &VariableCruiseToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrVariableCruise", status);
    });
  }
};

class CruiseGapAdjustToggle : public ToggleControl {
  Q_OBJECT

public:
  CruiseGapAdjustToggle() : ToggleControl("정차시 크루즈 갭 자동변경", "정차시 빠른 출발을 위해 크루즈갭을 1칸으로 변경하며, 출발후 일정조건에 따라 다시 원래의 크루즈갭으로 돌아갑니다.", "../assets/offroad/icon_shell.png", Params().getBool("CruiseGapAdjust")) {
    QObject::connect(this, &CruiseGapAdjustToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("CruiseGapAdjust", status);
    });
  }
};

class AutoEnabledToggle : public ToggleControl {
  Q_OBJECT

public:
  AutoEnabledToggle() : ToggleControl("자동 인게이지 활성", "디스인게이지 상태에서 크루즈 버튼상태가 대기상태(CRUISE표시만 나오고 속도 지정이 안된상태)일 경우 자동 인게이지를 활성화 합니다.", "../assets/offroad/icon_shell.png", Params().getBool("AutoEnable")) {
    QObject::connect(this, &AutoEnabledToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("AutoEnable", status);
    });
  }
};

class CruiseAutoResToggle : public ToggleControl {
  Q_OBJECT

public:
  CruiseAutoResToggle() : ToggleControl("자동RES 사용", "크루즈 사용중 브레이크를 밟아 대기모드 상태로 변한경우(CANCEL은 해당없음) 브레이크 페달 해제/가속페달조작 시 다시 이전 속도로 세팅합니다. 크루즈 속도가 세팅되어 있고 차량속도가 30km/h 이상 혹은 앞차가 인식될 경우 작동합니다.", "../assets/offroad/icon_shell.png", Params().getBool("CruiseAutoRes")) {
    QObject::connect(this, &CruiseAutoResToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("CruiseAutoRes", status);
    });
  }
};

class BatteryChargingControlToggle : public ToggleControl {
  Q_OBJECT

public:
  BatteryChargingControlToggle() : ToggleControl("배터리 충전 제어기능 사용", "배터리 충전제어 기능을 사용합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrBatteryChargingControl")) {
    QObject::connect(this, &BatteryChargingControlToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrBatteryChargingControl", status);
    });
  }
};

class BlindSpotDetectToggle : public ToggleControl {
  Q_OBJECT

public:
  BlindSpotDetectToggle() : ToggleControl("후측방 감지 아이콘 표시", "후측방에 차가 감지되면 화면에 아이콘을 띄웁니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrBlindSpotDetect")) {
    QObject::connect(this, &BlindSpotDetectToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrBlindSpotDetect", status);
      if (state) {
        QUIState::ui_state.scene.nOpkrBlindSpotDetect = true;
      } else {
        QUIState::ui_state.scene.nOpkrBlindSpotDetect = false;
      }
    });
  }
};

class MadModeEnabledToggle : public ToggleControl {
  Q_OBJECT

public:
  MadModeEnabledToggle() : ToggleControl("MainSW 오픈파일럿 ON/OFF", "크루즈 MainSW를 이용하여 오파를 활성화 합니다.", "../assets/offroad/icon_shell.png", Params().getBool("MadModeEnabled")) {
    QObject::connect(this, &MadModeEnabledToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("MadModeEnabled", status);
    });
  }
};

class WhitePandaSupportToggle : public ToggleControl {
  Q_OBJECT

public:
  WhitePandaSupportToggle() : ToggleControl("화이트판다 지원", "화이트판다 사용시 기능을 켜십시오", "../assets/offroad/icon_shell.png", Params().getBool("WhitePandaSupport")) {
    QObject::connect(this, &WhitePandaSupportToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("WhitePandaSupport", status);
    });
  }
};

class SteerWarningFixToggle : public ToggleControl {
  Q_OBJECT

public:
  SteerWarningFixToggle() : ToggleControl("조향경고 해제", "차량에서 조향에러가 발생하여 오파 실행이 불가능할 때 기능을 켜십시오(일부 차량 Only). 주행 중 정상적인 에러환경에서 발생시에는 기능을 켜지 마십시오.", "../assets/offroad/icon_shell.png", Params().getBool("SteerWarningFix")) {
    QObject::connect(this, &SteerWarningFixToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("SteerWarningFix", status);
    });
  }
};

class SteerWindDownToggle : public ToggleControl {
  Q_OBJECT

public:
  SteerWindDownToggle() : ToggleControl("Steer Wind Down", "Steer Warning 시 토크를 서서히 다운시킵니다. 일부 차량의 경우 조향각 제한등이 나타날 수 있으니 에러상관없이 최대조향각을 쓰려면 기능을 끄십시오.", "../assets/offroad/icon_shell.png", Params().getBool("SteerWindDown")) {
    QObject::connect(this, &SteerWindDownToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("SteerWindDown", status);
    });
  }
};

class AutoScreenDimmingToggle : public ToggleControl {
  Q_OBJECT

public:
  AutoScreenDimmingToggle() : ToggleControl("주행화면 Dimming 제어", "주행시 최소한의 밝기를 유지하여 배터리 소모량 및 발열을 줄이며, 이벤트 발생 시 밝기를 높여 일시적으로 가시성을 확보합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrAutoScreenDimming")) {
    QObject::connect(this, &AutoScreenDimmingToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrAutoScreenDimming", status);
    });
  }
};

class LiveSteerRatioToggle : public ToggleControl {
  Q_OBJECT

public:
  LiveSteerRatioToggle() : ToggleControl("Live SteerRatio 사용", "가변/고정 SR 대신 Live SteerRatio를 사용합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrLiveSteerRatio")) {
    QObject::connect(this, &LiveSteerRatioToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrLiveSteerRatio", status);
    });
  }
};

class VariableSteerMaxToggle : public ToggleControl {
  Q_OBJECT

public:
  VariableSteerMaxToggle() : ToggleControl("가변 SteerMax 사용", "곡률에 따른 가변 SteerMax을 사용합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrVariableSteerMax")) {
    QObject::connect(this, &VariableSteerMaxToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrVariableSteerMax", status);
    });
  }
};

class VariableSteerDeltaToggle : public ToggleControl {
  Q_OBJECT

public:
  VariableSteerDeltaToggle() : ToggleControl("가변 SteerDelta 사용", "곡률에 따른 가변 SteerDelta를 사용합니다.( DeltaUp ~ 5까지 변화, DeltaDown ~ 10까지 변화", "../assets/offroad/icon_shell.png", Params().getBool("OpkrVariableSteerDelta")) {
    QObject::connect(this, &VariableSteerDeltaToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrVariableSteerDelta", status);
    });
  }
};

class ShaneFeedForward : public ToggleControl {
  Q_OBJECT

public:
  ShaneFeedForward() : ToggleControl("Shane FeedForward 사용", "Shane의 FeedForward를 사용합니다. 조향각에 따라 직선주로에서는 토크를 낮추고, 곡선주로에서는 동적으로 조정합니다.", "../assets/offroad/icon_shell.png", Params().getBool("ShaneFeedForward")) {
    QObject::connect(this, &ShaneFeedForward::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("ShaneFeedForward", status);
    });
  }
};

class DrivingRecordToggle : public ToggleControl {
  Q_OBJECT

public:
  DrivingRecordToggle() : ToggleControl("자동 화면녹화 기능 사용", "운전 중 화면 녹화/중지를 자동으로 수행합니다. 출발 후 녹화가 시작되며 차량이 정지하면 녹화가 종료됩니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrDrivingRecord")) {
    QObject::connect(this, &DrivingRecordToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrDrivingRecord", status);
      if (state) {
        QUIState::ui_state.scene.driving_record = true;
      } else {
        QUIState::ui_state.scene.driving_record = false;
      }
    });
  }
};

class TurnSteeringDisableToggle : public ToggleControl {
  Q_OBJECT

public:
  TurnSteeringDisableToggle() : ToggleControl("턴시그널 사용시 조향해제 사용", "차선변경속도 이하로 주행할 때 턴시그널을 사용시 자동조향을 일시해제 합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrTurnSteeringDisable")) {
    QObject::connect(this, &TurnSteeringDisableToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrTurnSteeringDisable", status);
    });
  }
};

class HotspotOnBootToggle : public ToggleControl {
  Q_OBJECT

public:
  HotspotOnBootToggle() : ToggleControl("부팅시 핫스팟 자동실행", "부팅 후 핫스팟을 자동으로 실행합니다.", "", Params().getBool("OpkrHotspotOnBoot")) {
    QObject::connect(this, &HotspotOnBootToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrHotspotOnBoot", status);
    });
  }
};

class CruiseOverMaxSpeedToggle : public ToggleControl {
  Q_OBJECT

public:
  CruiseOverMaxSpeedToggle() : ToggleControl("설정속도를 초과속도에 동기화", "현재속도가 설정속도를 넘어설 경우 설정속도를 현재속도에 동기화합니다.", "../assets/offroad/icon_shell.png", Params().getBool("CruiseOverMaxSpeed")) {
    QObject::connect(this, &CruiseOverMaxSpeedToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("CruiseOverMaxSpeed", status);
    });
  }
};

class DebugUiOneToggle : public ToggleControl {
  Q_OBJECT

public:
  DebugUiOneToggle() : ToggleControl("DEBUG UI 1", "", "../assets/offroad/icon_shell.png", Params().getBool("DebugUi1")) {
    QObject::connect(this, &DebugUiOneToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("DebugUi1", status);
      if (state) {
        QUIState::ui_state.scene.nDebugUi1 = true;
      } else {
        QUIState::ui_state.scene.nDebugUi1 = false;
      }
    });
  }
};

class DebugUiTwoToggle : public ToggleControl {
  Q_OBJECT

public:
  DebugUiTwoToggle() : ToggleControl("DEBUG UI 2", "", "../assets/offroad/icon_shell.png", Params().getBool("DebugUi2")) {
    QObject::connect(this, &DebugUiTwoToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("DebugUi2", status);
      if (state) {
        QUIState::ui_state.scene.nDebugUi2 = true;
      } else {
        QUIState::ui_state.scene.nDebugUi2 = false;
      }
    });
  }
};

class LongLogToggle : public ToggleControl {
  Q_OBJECT

public:
  LongLogToggle() : ToggleControl("LONG LOG 표시", "화면에 가변크루즈 로그 대신 롱 튜닝 디버그용 로그를 표시합니다.", "../assets/offroad/icon_shell.png", Params().getBool("LongLogDisplay")) {
    QObject::connect(this, &LongLogToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("LongLogDisplay", status);
    });
  }
};

class PrebuiltToggle : public ToggleControl {
  Q_OBJECT

public:
  PrebuiltToggle() : ToggleControl("Prebuilt 파일 생성", "Prebuilt 파일을 생성하며 부팅속도를 단축시킵니다. UI수정을 한 경우 기능을 끄십시오.", "../assets/offroad/icon_shell.png", Params().getBool("PutPrebuiltOn")) {
    QObject::connect(this, &PrebuiltToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("PutPrebuiltOn", status);
    });
  }
};

class LDWSToggle : public ToggleControl {
  Q_OBJECT

public:
  LDWSToggle() : ToggleControl("LDWS 차량 설정", "", "../assets/offroad/icon_shell.png", Params().getBool("LdwsCarFix")) {
    QObject::connect(this, &LDWSToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("LdwsCarFix", status);
    });
  }
};

class FPTwoToggle : public ToggleControl {
  Q_OBJECT

public:
  FPTwoToggle() : ToggleControl("FingerPrint 2.0 설정", "핑거프린트2.0을 활성화 합니다. ECU인식으로 차량을 활성화 합니다.", "../assets/offroad/icon_shell.png", Params().getBool("FingerprintTwoSet")) {
    QObject::connect(this, &FPTwoToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("FingerprintTwoSet", status);
    });
  }
};

class GearDToggle : public ToggleControl {
  Q_OBJECT

public:
  GearDToggle() : ToggleControl("드라이브기어 강제인식", "기어인식문제로 인게이지가 되지 않을 때 사용합니다. 근본적으로 CABANA데이터를 분석해야 하지만, 임시적으로 해결합니다.", "../assets/offroad/icon_shell.png", Params().getBool("JustDoGearD")) {
    QObject::connect(this, &GearDToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("JustDoGearD", status);
    });
  }
};

class ComIssueToggle : public ToggleControl {
  Q_OBJECT

public:
  ComIssueToggle() : ToggleControl("프로세스간 통신오류 알람 끄기", "화이트판다 사용시 프로세스간 통신오류 알람을 끄기 위해 이옵션을 켜십시오.", "../assets/offroad/icon_shell.png", Params().getBool("ComIssueGone")) {
    QObject::connect(this, &ComIssueToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("ComIssueGone", status);
    });
  }
};

class RunNaviOnBootToggle : public ToggleControl {
  Q_OBJECT

public:
  RunNaviOnBootToggle() : ToggleControl("네비 자동 실행", "부팅 후 주행화면 전환 시 네비게이션(맵피)을 자동 실행합니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrRunNaviOnBoot")) {
    QObject::connect(this, &RunNaviOnBootToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrRunNaviOnBoot", status);
    });
  }
};

class BattLessToggle : public ToggleControl {
  Q_OBJECT

public:
  BattLessToggle() : ToggleControl("배터리리스 사용", "배터리리스 이온용 토글입니다. 관련 설정이 적용됩니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrBattLess")) {
    QObject::connect(this, &BattLessToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrBattLess", status);
    });
  }
};

class LiveTunePanelToggle : public ToggleControl {
  Q_OBJECT

public:
  LiveTunePanelToggle() : ToggleControl("라이브튠 사용 및 UI 표시", "화면에 라이브 튜닝 관련 UI를 표시합니다. 각종 튜닝 수치를 주행화면에서 라이브로 조정가능합니다. 조정 시 파라미터에 반영되며 토글을 끈 후 재부팅 해도 값이 유지됩니다.", "../assets/offroad/icon_shell.png", Params().getBool("OpkrLiveTunePanelEnable")) {
    QObject::connect(this, &LiveTunePanelToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("OpkrLiveTunePanelEnable", status);
      if (state) {
        QUIState::ui_state.scene.live_tune_panel_enable = true;
        QUIState::ui_state.scene.opkr_livetune_ui = true;
      } else {
        QUIState::ui_state.scene.live_tune_panel_enable = false;
        QUIState::ui_state.scene.opkr_livetune_ui = false;
      }
    });
  }
};

class KRDateToggle : public ToggleControl {
  Q_OBJECT

public:
  KRDateToggle() : ToggleControl("주행화면 날짜 표시", "주행화면에 현재 날짜를 표시합니다.", "../assets/offroad/icon_shell.png", Params().getBool("KRDateShow")) {
    QObject::connect(this, &KRDateToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("KRDateShow", status);
      if (state) {
        QUIState::ui_state.scene.kr_date_show = true;
      } else {
        QUIState::ui_state.scene.kr_date_show = false;
      }
    });
  }
};

class KRTimeToggle : public ToggleControl {
  Q_OBJECT

public:
  KRTimeToggle() : ToggleControl("주행화면 시간 표시", "주행화면에 현재 시간을 표시합니다.", "../assets/offroad/icon_shell.png", Params().getBool("KRTimeShow")) {
    QObject::connect(this, &KRTimeToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("KRTimeShow", status);
      if (state) {
        QUIState::ui_state.scene.kr_time_show = true;
      } else {
        QUIState::ui_state.scene.kr_time_show = false;
      }
    });
  }
};

class LeadCustomToggle : public ToggleControl {
  Q_OBJECT

public:
  LeadCustomToggle() : ToggleControl("선행차 인식 Custom 이미지 표시", "주행화면에 선행차 Custom 이미지를 표시합니다.", "../assets/offroad/icon_shell.png", Params().getBool("LeadCustom")) {
    QObject::connect(this, &LeadCustomToggle::toggleFlipped, [=](int state) {
      char value = state ? '1' : '0';
      Params().put("LeadCustom", &value, 1);
    });
  }
};

class RadarLongHelperToggle : public ToggleControl {
  Q_OBJECT

public:
  RadarLongHelperToggle() : ToggleControl("레이더 롱 보조 사용", "비전 SCC 사용 중 근거리(25m이하)에서 레이더값+콤마비전롱(보간)을 사용합니다. 비전SCC가 충분히 멈추지 못하는 상황에서 레이더 값을 이용해 확실히 멈출 수 있게 합니다. 레이더가 앞차 인식시만 사용되며, 앞차인식을 못할 시(녹색쉐브론)는 콤마비전롱으로만 감속됩니다. 이 기능을 끄면 항상 콤마 비전롱을 사용하는것을 의미합니다.(레이더인식시 앞차거리 3m 이하는 안전을 위해 레이더값을 강제로 사용함)", "../assets/offroad/icon_shell.png", Params().getBool("RadarLongHelper")) {
    QObject::connect(this, &RadarLongHelperToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("RadarLongHelper", status);
    });
  }
};

class FCATypeToggle : public ToggleControl {
  Q_OBJECT

public:
  FCATypeToggle() : ToggleControl("FCA11 사용(전방추돌관련)", "전방 추돌 신호를 SCC12 대신 FCA11을 사용합니다. 인게이지 혹은 부팅시 전방충돌오류가 날 때 사용합니다.", "../assets/offroad/icon_shell.png", Params().getBool("FCAType")) {
    QObject::connect(this, &FCATypeToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("FCAType", status);
    });
  }
};

class GitPullOnBootToggle : public ToggleControl {
  Q_OBJECT

public:
  GitPullOnBootToggle() : ToggleControl("부팅 시 Git Pull 자동실행", "부탕 후 업데이트가 있는 경우에 Git Pull을 자동 실행 후 재부팅합니다.", "", Params().getBool("GitPullOnBoot")) {
    QObject::connect(this, &GitPullOnBootToggle::toggleFlipped, [=](int state) {
      bool status = state ? true : false;
      Params().putBool("GitPullOnBoot", status);
    });
  }
};

// 오픈파일럿 미리보기
class OpenpilotView : public AbstractControl {
  Q_OBJECT

public:
  OpenpilotView();

private:
  QPushButton btn;
  Params params;
  
  void refresh();
};

// 차량 강제등록
class CarRecognition : public AbstractControl {
  Q_OBJECT

public:
  CarRecognition();

private:
  QPushButton btn;
  QString carname;
  QLabel carname_label;
  Params params;
  
  void refresh(QString carname);
};

class CarSelectCombo : public AbstractControl 
{
  Q_OBJECT

public:
  CarSelectCombo();

private:
  QPushButton btn;
  QComboBox combobox;
  Params params;

  void refresh();
};


// UI 설정
class AutoShutdown : public AbstractControl {
  Q_OBJECT

public:
  AutoShutdown();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class ForceShutdown : public AbstractControl {
  Q_OBJECT

public:
  ForceShutdown();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class AutoScreenOff : public AbstractControl {
  Q_OBJECT

public:
  AutoScreenOff();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class VolumeControl : public AbstractControl {
  Q_OBJECT

public:
  VolumeControl();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  QSoundEffect effect;
  
  void refresh();
  void playsound();
};

class BrightnessControl : public AbstractControl {
  Q_OBJECT

public:
  BrightnessControl();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class BrightnessOffControl : public AbstractControl {
  Q_OBJECT

public:
  BrightnessOffControl();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};


class ChargingMin : public AbstractControl {
  Q_OBJECT

public:
  ChargingMin();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};
class ChargingMax : public AbstractControl {
  Q_OBJECT

public:
  ChargingMax();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};


// 주행 설정
class CruisemodeSelInit : public AbstractControl {
  Q_OBJECT

public:
  CruisemodeSelInit();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class VariableCruiseProfile : public AbstractControl {
  Q_OBJECT

public:
  VariableCruiseProfile();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class LaneChangeSpeed : public AbstractControl {
  Q_OBJECT

public:
  LaneChangeSpeed();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class LaneChangeDelay : public AbstractControl {
  Q_OBJECT

public:
  LaneChangeDelay();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class LeftCurvOffset : public AbstractControl {
  Q_OBJECT

public:
  LeftCurvOffset();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};
class RightCurvOffset : public AbstractControl {
  Q_OBJECT

public:
  RightCurvOffset();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class MaxAngleLimit : public AbstractControl {
  Q_OBJECT

public:
  MaxAngleLimit();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SpeedLimitOffset : public AbstractControl {
  Q_OBJECT

public:
  SpeedLimitOffset();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

// 튜닝 설정
class CameraOffset : public AbstractControl {
  Q_OBJECT

public:
  CameraOffset();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class PathOffset : public AbstractControl {
  Q_OBJECT

public:
  PathOffset();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SRBaseControl : public AbstractControl {
  Q_OBJECT

public:
  SRBaseControl();

private:
  QPushButton btndigit;
  QPushButton btnminus;
  QPushButton btnplus;
  QLabel label;
  Params params;
  float digit = 0.01;
  
  void refresh();
};
class SRMaxControl : public AbstractControl {
  Q_OBJECT

public:
  SRMaxControl();

private:
  QPushButton btndigit;
  QPushButton btnminus;
  QPushButton btnplus;
  QLabel label;
  Params params;
  float digit = 0.01;
  
  void refresh();
};

class SteerActuatorDelay : public AbstractControl {
  Q_OBJECT

public:
  SteerActuatorDelay();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerRateCost : public AbstractControl {
  Q_OBJECT

public:
  SteerRateCost();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerLimitTimer : public AbstractControl {
  Q_OBJECT

public:
  SteerLimitTimer();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class TireStiffnessFactor : public AbstractControl {
  Q_OBJECT

public:
  TireStiffnessFactor();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerMaxBase : public AbstractControl {
  Q_OBJECT

public:
  SteerMaxBase();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerMaxMax : public AbstractControl {
  Q_OBJECT

public:
  SteerMaxMax();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerMaxv : public AbstractControl {
  Q_OBJECT

public:
  SteerMaxv();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerDeltaUpBase : public AbstractControl {
  Q_OBJECT

public:
  SteerDeltaUpBase();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerDeltaUpMax : public AbstractControl {
  Q_OBJECT

public:
  SteerDeltaUpMax();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerDeltaDownBase : public AbstractControl {
  Q_OBJECT

public:
  SteerDeltaDownBase();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerDeltaDownMax : public AbstractControl {
  Q_OBJECT

public:
  SteerDeltaDownMax();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};


// 제어 설정
class LateralControl : public AbstractControl {
  Q_OBJECT

public:
  LateralControl();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class PidKp : public AbstractControl {
  Q_OBJECT

public:
  PidKp();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class PidKi : public AbstractControl {
  Q_OBJECT

public:
  PidKi();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class PidKd : public AbstractControl {
  Q_OBJECT

public:
  PidKd();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class PidKf : public AbstractControl {
  Q_OBJECT

public:
  PidKf();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class IgnoreZone : public AbstractControl {
  Q_OBJECT

public:
  IgnoreZone();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class OuterLoopGain : public AbstractControl {
  Q_OBJECT

public:
  OuterLoopGain();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class InnerLoopGain : public AbstractControl {
  Q_OBJECT

public:
  InnerLoopGain();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class TimeConstant : public AbstractControl {
  Q_OBJECT

public:
  TimeConstant();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class ActuatorEffectiveness : public AbstractControl {
  Q_OBJECT

public:
  ActuatorEffectiveness();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class Scale : public AbstractControl {
  Q_OBJECT

public:
  Scale();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class LqrKi : public AbstractControl {
  Q_OBJECT

public:
  LqrKi();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class DcGain : public AbstractControl {
  Q_OBJECT

public:
  DcGain();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerAngleCorrection : public AbstractControl {
  Q_OBJECT

public:
  SteerAngleCorrection();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class MaxSteer : public AbstractControl {
  Q_OBJECT

public:
  MaxSteer();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class MaxRTDelta : public AbstractControl {
  Q_OBJECT

public:
  MaxRTDelta();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class MaxRateUp : public AbstractControl {
  Q_OBJECT

public:
  MaxRateUp();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class MaxRateDown : public AbstractControl {
  Q_OBJECT

public:
  MaxRateDown();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class SteerThreshold : public AbstractControl {
  Q_OBJECT

public:
  SteerThreshold();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class RecordCount : public AbstractControl {
  Q_OBJECT

public:
  RecordCount();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class RecordQuality : public AbstractControl {
  Q_OBJECT

public:
  RecordQuality();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class GitHash : public AbstractControl {
  Q_OBJECT

public:
  GitHash();

private:
  QLabel local_hash;
  QLabel remote_hash;
  Params params;
};

class RESChoice : public AbstractControl {
  Q_OBJECT

public:
  RESChoice();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class MonitoringMode : public AbstractControl {
  Q_OBJECT

public:
  MonitoringMode();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class MonitorEyesThreshold : public AbstractControl {
  Q_OBJECT

public:
  MonitorEyesThreshold();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class NormalEyesThreshold : public AbstractControl {
  Q_OBJECT

public:
  NormalEyesThreshold();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class BlinkThreshold : public AbstractControl {
  Q_OBJECT

public:
  BlinkThreshold();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class FanSpeedGain : public AbstractControl {
  Q_OBJECT

public:
  FanSpeedGain();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class CruiseGapTR : public AbstractControl {
  Q_OBJECT

public:
  CruiseGapTR();

private:
  QPushButton btn1;
  QPushButton btn2;
  QPushButton btn3;
  QPushButton btn4;
  QLabel label1;
  QLabel label2;
  QLabel label3;
  QLabel label4;
  QLabel label1a;
  QLabel label2a;
  QLabel label3a;
  QLabel label4a;
  Params params;
  
  void refresh1();
  void refresh2();
  void refresh3();
  void refresh4();
};

class DynamicTR : public AbstractControl {
  Q_OBJECT

public:
  DynamicTR();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class LCTimingFactor : public AbstractControl {
  Q_OBJECT

public:
  LCTimingFactor();

private:
  QPushButton btn1;
  QPushButton btn2;
  QPushButton btn3;
  QPushButton btn4;
  QLabel label1;
  QLabel label2;
  QLabel label3;
  QLabel label4;
  QLabel label1a;
  QLabel label2a;
  QLabel label3a;
  QLabel label4a;
  Params params;

  void refresh1();
  void refresh2();
  void refresh3();
  void refresh4();
};

class LCTimingFactorUD : public AbstractControl {
  Q_OBJECT

public:
  LCTimingFactorUD();

private:
  QPushButton btn;
  QPushButton btn2;
  Params params;
  
  void refresh();
  void refresh2();
};

class AutoResCondition : public AbstractControl {
  Q_OBJECT

public:
  AutoResCondition();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class AutoEnableSpeed : public AbstractControl {
  Q_OBJECT

public:
  AutoEnableSpeed();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class CamDecelDistAdd : public AbstractControl {
  Q_OBJECT

public:
  CamDecelDistAdd();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};

class LiveSRPercent : public AbstractControl {
  Q_OBJECT

public:
  LiveSRPercent();

private:
  QPushButton btnplus;
  QPushButton btnminus;
  QLabel label;
  Params params;
  
  void refresh();
};