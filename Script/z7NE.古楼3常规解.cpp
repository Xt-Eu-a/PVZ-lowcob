#include <avz.h>
#include <dsl/shorthand.h>
#include <nb30.h>
#include "xt.h"
//#include "LeonHelper/myTasUI.h"

void AScript() {
  //lh::tasUi();
  // VK_RBUTTON:高级暂停,原速→暂停,暂停→原速（开关高级暂停;关闭音效;暂停时的透明度+颜色0~255是透明度,0是完全透明）
  AConnect(VK_RBUTTON, [] {Paused = !Paused; ASetAdvancedPause(Paused, false, 0);});
  // X:0.1倍速,任意倍速→0.1倍速,0.1倍速→原速（tick原为10,10ms即1cs运行1帧,改成100为0.1倍速,100ms即10cs运行1帧）
  AConnect('X', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 100 ? 10 : 100;});
  // C:10倍速,任意倍速→10倍速,10倍速→原速
  AConnect('C', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 1 ? 10 : 1;});
  // 出怪12怪极红
  ASetZombies("矿梯跳气 橄丑篮杆 白红 普桶 偷");
  //均匀出怪
  At(ATime(1, -599))[] { AAverageSpawn(); };
  // 选卡 叶喷 南高 窝 双冰 樱辣核（阻塞时间至w1的-599）
  AXtSelectCards("Bc PT W II AJN", 15);
  // 6门炮列表
  aCobManager.AutoSetList();
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  //ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  //  关闭报错
  AGetInternalLogger()->SetLevel({});

  /////////////////////////////////////////////////////////////////////////////////////////
  // C4u:I-B3D1-NS3d I-B1B4-P2Aa4J15d(5565+4)

  // 垫材逻辑
  // 热键ASW在鼠标处放大蒜,D在鼠标处铲除植物
  At('A') Do { ACard(ASYC_27, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(AXPG_8, AMouseRow(), AMouseCol()); };
  At('D') Do { AShovel(AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(ANGT_30, AMouseRow(), AMouseCol()); };
  At('E') Do { ACard(AGJG_23, AMouseRow(), AMouseCol()); };

  // 垫材逻辑 樱波 核波
  ATimeline CC1 = {
    At(719) Card(ASYC_27,5,8),
    At(1470) Card<2>(ASYC_27,4,9),
    At(2268) Card(ASYC_27,{{5,6},{5,7},{5,8}}),
  };
  OnWave(2 ,4 ,6 ,8 ,11 ,13 ,15 ,17 ,19 ,20) CC1;
  ATimeline CC2 = {
    At(919) Card(ASYC_27,5,8),
    At(1670) Card(ASYC_27,5,7),
    At(2468) Card<200>(ASYC_27,{{5,7},{5,8}}),
  };
  OnWave(1, 3, 5, 7, 9, 10, 12, 14, 16, 18) CC2;
  //aPlantFixer.Start(AGJG_23, {{1, 4}, {5, 2}}, 3500);// 平均最高效自动补高坚果6000-6000/2=3000

  /////////////////////////////////////////////////////////////////////////////////////////
  //w1特化
  OnWave(1){
      /*At(-599) Card({{AGJG_23,2,1},{ANGT_30,4,1},{AXPG_8,3,1}}),
      At(751-599) Card({{ADC_21,1,2},{AHP_33,4,1},{AXPG_8,5,3}}),
      At(751+751-599) Card({{AHP_33,5,4},{AXPG_8,5,4}}),
      At(3001-599) Card({{AGJG_23,2,1},{ANGT_30,4,1},{AXPG_8,3,1}}),*/

      At(305) I(1, 8, false), // I3
      At(305) P(1,8.225) & P(4,8.225), // BB特化
      At(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}) & P(3, 7.725) & D<239>(3,2.325), // NS3d
  };

  // 循环主体
  ATimeline JI_B3D1_NS3d = { //核波
      // 1 3 5 7 9 |10 12 14 16 18 19. 20.
      At(305) I(1, 8, false), // I3
      At(1325) P(3, 7.4125) & D<213>(1,7), // B3D1
      At(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}) & P(3, 7.725) & D<239>(3,2.325), // NS3d
  };

  ATimeline I_B1B4_P2Aa4d = { //樱波
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(305) I(4, 1, true), // I'3
      At(1325) P(1, 7.4125) & P(4, 7.4125), // B1B4
      At(2301-414) Card(AWG_17,4,9), // a4
      At(2301) P(2, 7.725) & A(4, 8) & D<246>(3,2.325), // P2A4d
  };
    ATimeline J5  = { //核波
      // 1 5 9 |12 16 19.
      At(120) J(5,8),//J5
  };
  ATimeline J1  = { //核波
      // 3 7 |10 14 18 20.
      At(120) J(1,8),//J1
  };
  OnWave(1,5,9,12,16) J5;
  OnWave(3,7,10,14,18) J1;
  OnWave(2_9 % 2, 11_19 % 2) JI_B3D1_NS3d | I_B1B4_P2Aa4d;
  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9.
  At(ATime(9, 2501)){ //樱波
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(305) I(4, 1, true), // I'3
      At(1325) P(1, 7.4125) & P(4, 7.4125), // B1B4
      At(2301-414) Card(AWG_17,4,9), // a4
      At(2301) P(2, 7.725) & A(4, 8) & D<246>(4,2.325), // P2A4d4特化
  };
  // w10
  OnWave(10){ //核波
      At(305) I(1, 8, false), // I3
      At(1325) P(4, 7.4125) & D<245>(2,7.3), // BB特化
      At(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}) & P(3, 7.725) & D<239>(3,2.325), // NS3d
  };
  // w19.
  At(ATime(19, 2501)){ //核波
      At(120) J(5,8),//J5
      At(305) I(1, 8, false), // I3
      At(1325) P(3, 7.4125) & D<213>(1,7), // B3D1
      At(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}) & P(3, 7.725) & D<239>(3,2.325), // NS3d
  };
  // w20
  OnWave(20){ //樱波
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(305) I(4, 1, true), // I'3
      At(1325) P(4, 7.4125) & D<238>(2,7.3125), // BB特化
      At(2301-414) Card(AWG_17,4,9), // a4
      At(2301) P(2, 7.725) & A(4, 8) & D<246>(3,2.325), // P2A4d
  };
  At(ATime(20, 2501)){ //核波
      At(120) J(1,8),//J1
      At(305) I(1, 8, false), // I3
      At(1325) P(3, 7.4125) & D<213>(1,7), // B3D1
      At(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}) & P(2, 7.725) & D<239>(4,2.325), // 特化NS2d4
  };

}
/*
N4：I-B3D1-NS3d3 I-B1B4-P2Aa4J15d3
非常常规的解法，这个解不用垫扶梯，尾炸伤比较高，打这个单纯是展示一下常规思路
运算分析：
5565+4，稍微垫一下5路即可
操作：
1、需要注意窝瓜可能当演员，压不全4路，这时候需要辣椒2301烧4路补运算，视频中为了减压延迟到120烧跳跳，其实压力没那么大，提早到2301就行。
*/