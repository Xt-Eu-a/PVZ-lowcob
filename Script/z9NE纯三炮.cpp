#include <avz.h>
#include <dsl/shorthand.h>
#include "xt.h"

void AScript() {
  // 鼠标右键:高级暂停,原速→暂停,暂停→原速
  AConnect(VK_RBUTTON, [] {Paused = !Paused; ASetAdvancedPause(Paused, false, 0);});
  // X:0.1倍速,任意倍速→0.1倍速,0.1倍速→原速
  AConnect('X', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 100 ? 10 : 100;});
  // C:10倍速,任意倍速→10倍速,10倍速→原速
  AConnect('C', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 1 ? 10 : 1;});
  // 出怪13怪极红
  ASetZombies("气矿梯跳 橄丑篮杆 白红 普障门 偷");
  // 选卡 伞嘴盆魅高 双冰 樱辣核
  AXtSelectCards("UDVMH II AJN",5);
  // 3门炮列表
  aCobManager.AutoSetList();
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  /////////////////////////////////////////////////////////////////////////////////////////
  // C4u:I-P-PN I1-P-J/PA
  // 垫材逻辑
  // WASD在鼠标处放魅伞嘴盆,F在鼠标处铲除植物
  At('W') Do { ACard(AMHG_12, AMouseRow(), AMouseCol()); };
  At('A') Do { ACard(AYZBHS_37, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(ADZH_6, AMouseRow(), AMouseCol()); };
  At('D') Do { ACard(AHP_33, AMouseRow(), AMouseCol()); };
  At('F') Do { AShovel(AMouseRow(), AMouseCol()); };
  /////////////////////////////////////////////////////////////////////////////////////////
  // w1特化
  OnWave(1){
    At(-599) Card({{AGJG_23,1,2},{AYZBHS_37,4,3},{AHP_33,1,3},{ADZH_6,1,3}}),
    At(152) Card({{AYZBHS_37,3,3},{AHP_33,1,4},{ADZH_6,1,4}}),
    At(3001-599) Card(AGJG_23,2,2),
  };
  // 循环主体
  ATimeline I_P_PN = {
      // 1 3 5 7 9 |10 12 14 16 18 19. 20.
      At(185) I(2, 6, false), // I 落地冰A激活的小鬼
      At(1324) P(1, 8.375), // P可以收跳
      At(2301-373-1) Do{RightFullDamageSmartCob(4, 7.75, ATime(ANowWave(),2301-373), ALADDER_ZOMBIE, 70, true, true, true, 178.0f, 193.0f, 189.0f);},
      // P                                      整数行、浮点数列、ATime结构体、         僵尸类型、 预测前进距离、上中下是否考虑、      上中下炮右距
      At(2501) N({{2, 4}, {2, 5}, {2, 3}, {3, 3}}),
      // N [168,203]尽量晚生效多收1路小鬼 229有伤，3-3晚于168可拦345晚于228可拦12345，2-5早于203可拦345
      At(2501 + 185) I(1, 1, true), // I'
  };

  ATimeline I1_P_PA = {
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(1324) P(1, 8.375), // P可以收跳
      At(2301-373-1) Do{RightFullDamageSmartCob(4, 7.0875, ATime(ANowWave(),2301-373), AQQ_16, 83, true, true, true, 181.0f, 193.0f, 187.0f);},
      // P                                   整数行、浮点数列、ATime结构体、         僵尸类型、 预测前进距离、上中下是否考虑、      上中下炮右距
      At(2301+108) A(4, 7), // A
  };
  ATimeline J1 = {
      // 2 6 9. | 13 17 20
      At(1) Do{aPainter.Draw(AText(std::format("辣椒烧1路7列"), 90, 100), 2500);},
      At(2301) J(1,7), // J1
  };
  ATimeline J2 = {
      // 4 8 | 11 15 19
      At(1) Do{aPainter.Draw(AText(std::format("辣椒烧2路1列"), 90, 200), 2500);},
      At(2301) J(2,1), // J2
  };
  OnWave(1_9 % 1, 10_19 % 1,20_20 % 2) I_P_PN | I1_P_PA;
  OnWave(2,6,13,17,20) J1;
  OnWave(4,8,11,15,19) J2;
  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9.
  At(ATime(9, 2501)){
    At(1) Do{aPainter.Draw(AText(std::format("辣椒烧1路7列"), 90, 100), 2500);},
    At(1324) P(2, 7.5), // P可以收跳
    At(2301-373-1) Do{RightFullDamageSmartCob(4, 7.0875, ATime(ANowWave(),2301-373), AQQ_16, 83, true, true, true, 181.0f, 193.0f, 187.0f);},
    // P                                   整数行、浮点数列、ATime结构体、         僵尸类型、 预测前进距离、上中下是否考虑、      上中下炮右距
    At(2301+108) A(4, 7), // A
    At(2301) J(1,7), // J1
  };
  // w19.
  At(ATime(19, 2501)){
      At(185) I(2, 6, false), // I 落地冰A激活的小鬼
      At(1324) P(2, 7.5), // P可以收跳
      At(2301-373-1) Do{RightFullDamageSmartCob(4, 7.75, ATime(ANowWave(),2301-373), ALADDER_ZOMBIE, 70, true, true, true, 178.0f, 193.0f, 189.0f);},
      // P                                      整数行、浮点数列、ATime结构体、         僵尸类型、 预测前进距离、上中下是否考虑、      上中下炮右距
      At(2501) N({{2, 4}, {2, 5}, {2, 3}, {3, 3}}),
      // N [168,203]尽量晚生效多收1路小鬼 229有伤，3-3晚于168可拦345晚于228可拦12345，2-5早于203可拦345
      At(2501 + 243 +185) I(1, 1, true), // I'
  };
  // w20.
  At(ATime(20, 2501)){
      At(185) I(2, 6, false), // I 落地冰A激活的小鬼
      // 手动 P-PN
  };
}
