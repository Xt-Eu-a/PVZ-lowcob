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
  // 选卡 盆喷 叶刺 高 双冰 樱辣核（阻塞时间至w1的-599）
  AXtSelectCards("Vc B_ T II AJN", 15);
  // 6门炮列表
  aCobManager.AutoSetList();
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  //ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  //  关闭报错
  //AGetInternalLogger()->SetLevel({});

  /////////////////////////////////////////////////////////////////////////////////////////
  // C4u:I3Pd-B2-B4cN I3Pd-B2-cA1P4(445+3+4)

  // 垫材逻辑
  // 热键ASW在鼠标处放大蒜,D在鼠标处铲除植物
  At('A') Do { ACard(AHP_33, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(AXPG_8, AMouseRow(), AMouseCol()); };
  At('D') Do { AShovel(AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(ADC_21, AMouseRow(), AMouseCol()); };
  At('E') Do { ACard(AGJG_23, AMouseRow(), AMouseCol()); };

  // 垫材逻辑
  ATimeline CC1 = {
    At(2299-751-751) Card(ASYC_27,1,8),
    At(2299-751) Card<36>({{ADC_21,2,9},{ASYC_27,3,9}}),
    At(2299) Card<134>({{AXPG_8,2,9},{ADC_21,3,9},{AHP_33,4,8},{ASYC_27,4,9}}),
  };
  OnWave(1_20) CC1;

  aPlantFixer.Start(AGJG_23, {{1, 4}, {5, 2}}, 3500);// 平均最高效自动补高坚果6000-6000/2=3000

  /*ATimeline CC2 = { //核波
    At(2299-751) Card<753>({AXPG_8,AHP_33},{{5,4},{5,5},{1,4},{1,5}}),
  };
  OnWave(1, 3, 5, 7, 9, 10, 12, 14, 16, 18) CC2;
  ATimeline CC3 = { //樱波
    At(2299-751) Card<753>({{AXPG_8,4,6},{AHP_33,4,7}}),
  };
  OnWave(2 ,4 ,6 ,8 ,11 ,13 ,15 ,17 ,19 ,20) CC3;*/

  /////////////////////////////////////////////////////////////////////////////////////////
  //w1特化
  OnWave(1){
      At(-599) Card({{ADC_21,1,1},{AHP_33,2,1},{AXPG_8,3,1}}),
      At(751-599) Card({{ADC_21,1,2},{AHP_33,4,1},{AXPG_8,5,3}}),
      At(751+751-599) Card({{AHP_33,5,4},{AXPG_8,5,4}}),

      At(110) J(5,7),//J5
      At(112) I(1, 7, false), // I3
      At(400) P(2,8.6) & P(4,8.6), // BB特化

      At(1730) P(4, 7.3625), // B4
      At(2199) P(2, 6.6625), // B2
      TrigAt(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}), // N
  };

  // 循环主体
  ATimeline JI3Pd_B4_B2cN = { //核波
      // 1 3 5 7 9 |10 12 14 16 18 19. 20.
      At(110) J(5,7),//J5
      At(112) I(1, 7, false), // I3
      At(712) P(3, 8.2875) & D<337>(3,2.5), // Pd P最晚850 delay337~346

      At(1730) P(4, 7.3625), // B4
      At(2199) P(2, 6.6625), // B2
      TrigAt(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}), // N
  };

  ATimeline I3Pd_B4_cA1P4 = { //樱波
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(112) I(5, 1, true), // I'3
      At(712) P(3, 8.2875) & D<337>(3,2.5), // Pd P最晚850 delay337~346

      At(2199) P(2, 6.6625), // B2

      TrigAt(2301) A(1, 8) & P(4, 7.725) , // A1P4
  };
  OnWave(2_9 % 2, 11_19 % 2) JI3Pd_B4_B2cN | I3Pd_B4_cA1P4;
  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9.
  At(ATime(9, 2501)){ //樱波
      At(112) I(5, 1, true), // I'3
      At(712) P(3, 8.2875) & D<337>(3,2.5), // Pd P最晚850 delay337~346

      At(2199) P(2, 6.6625), // B2

      TrigAt(2301) A(3, 8) & P(4, 7.725) , // A3P4
  };
  // w10
  OnWave(10){ //核波
      At(110) J(5,7),//J5
      At(112) I(1, 8, false), // I3
      At(430) P(2,6.5) & P(4,6.5), // BB特化

      At(1730) P(4, 7.3625), // B4
      At(2199) P(2, 6.6625), // B2
      TrigAt(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}), // N
  };
  // w19.
  At(ATime(19, 2501)){ //核波
      At(110) J(5,7),//J5
      At(112) I(1, 7, false), // I3
      At(712) P(3, 8.2875) & D<337>(3,2.5), // Pd P最晚850 delay337~346

      At(1730) P(4, 7.3625), // B4
      At(2199) P(2, 6.6625), // B2
      TrigAt(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}), // N
  };
  // w20
  OnWave(20){ //樱波
      At(112) I(5, 1, true), // I'3
      At(532) P(2,6) & P(4,6), // BB特化

      At(2199) P(2, 6.6625), // B2

      TrigAt(2301) A(1, 8) & P(4, 7.725) , // A1P4
  };
  At(ATime(20, 2501)){ //核波
      At(1) Do{aPlantFixer.Stop();}, //停止补高坚果
      At(110) J(5,7),//J5
      At(112) I(1, 8, false), // I3
      At(712) P(3, 8.2875) & D<337>(3,2.5), // Pd P最晚850 delay337~346

      At(1730) P(4, 7.3625), // B4
      At(2199) P(2, 6.6625), // B2
      TrigAt(2301) N({{2, 6}, {3, 6}, {2, 7}, {3, 7}}), // N
      At(2301) Shovel({{2, 1}, {3, 1}, {4, 1}}),
      At(2301) Shovel({{2, 1}, {3, 1}, {4, 1}}),
  };

}
/*
N4：I3Pd-B2-B4cN I3Pd-B2-cA1P4
鸣的屑六炮的优化版本,通过延后小鬼投掷的时间来减小尾炸炮伤，单波炮伤仅有0.025，全部来自3列炮的Pd尾炸小鬼，样本量为20 0000，总伤为0.025*20=0.5
运算分析：
445+3+4，不缺运算，樱波垫4路扶梯顺便垫巨人，2-6核坑漏5路红眼，5路要存垫
问题：
1、一路没有多余运算尾炸，要偷地刺处理矿工小鬼
操作：
1、w20开始前 2-9 3-9 4-6 4-7 4-9 提前存个植物(如果可以)，不要让墓碑出现在这个位置
*/