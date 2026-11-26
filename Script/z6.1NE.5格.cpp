#include <avz.h>
#include <dsl/shorthand.h>
#include <nb30.h>
#include "xt.h"

void AScript() {
  // Z:高级暂停,原速→暂停,暂停→原速（开关高级暂停;关闭音效;暂停时的透明度+颜色0~255是透明度,0是完全透明）
  AConnect('Z', [] {Paused = !Paused; ASetAdvancedPause(Paused, false, 0);});
  // X:0.1倍速,任意倍速→0.1倍速,0.1倍速→原速（tick原为10,10ms即1cs运行1帧,改成100为0.1倍速,100ms即10cs运行1帧）
  AConnect('X', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 100 ? 10 : 100;});
  // C:2倍速,任意倍速→2倍速,2倍速→原速
  AConnect('C', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 5 ? 10 : 5;});
  // 出怪12怪极红
  ASetZombies("矿梯跳 橄丑篮杆 白红 普障门");
  // 选卡 高 叶蒜 炮套 双冰 樱辣核（阻塞时间至w1的-599）
  AXtSelectCards("T BS YZ II AJN", 15);
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  // 关闭报错
  AGetInternalLogger()->SetLevel({});
  /////////////////////////////////////////////////////////////////////////////////////////
  // C4u:I-B"-N I1-B'-PAJ
  // 垫材逻辑
  // 热键ASW在鼠标处放三叶草大蒜玉米投手,D在鼠标处铲除植物
  At('A') Do { ACard(ASYC_27, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(ADS_36, AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(AYMTS_34, AMouseRow(), AMouseCol()); };
  At('D') Do { AShovel(AMouseRow(), AMouseCol()); };

  // 垫材逻辑
  ATimeline CC1 = {

  };
  OnWave(1_20) CC1;
  /////////////////////////////////////////////////////////////////////////////////////////
  //w1特化
  OnWave(1){
      At(-599) Card(AGJG_23,3,1) & Card(ADS_36,1,1) & Card(AYMTS_34,2,2),
      At(751-599) Card(ADS_36,5,1) & Card(AYMTS_34,1,4),
      At(751+751-599) Card(ADS_36,1,3) & Card(AYMTS_34,1,5),
      At(751+751+751-599) Card(ADS_36,5,3) & Card(AYMTS_34,5,5),
      At(3001-599) Card(AGJG_23,1,2),
      At(6002-599) Card(AGJG_23,5,2),
  };
  // 循环主体
  ATimeline I1_2Bl_3PAJ = {
      //4 8 | 11 15 19
      At(305) I(2, 1, true), //I'
      At(1325) RP(2,4,2,7.4125),//2-4 B
      At(1325-373+206) Shovel(2, 4) & Card(AYMTS_34, 2, 4),
      At(1325-373+206+751) Card({{AYMTS_34, 2, 5},{AYMJNP_47, 2, 4}}),
      At(2200) Shovel(5,4),
      At(2301) A(2,8) & RP(3,4,3,7.7) & J(5,4),//3-4 P
  };
  ATimeline I_2Bll_N = {
      // 1 5 9 |12 16 19.
      At(204) Shovel(1,6),
      At(305) I(1, 6, false), //I 
      At(1325) RP(2,4,3,7.4125),//2-4 B3
      At(2301) N({{3, 6},{3, 7}}),
  };
  ATimeline I1_3Bl_2PAJ = {
      // 2 6 9. | 13 17 20
      At(305) I(2, 1, true), //I'
      At(1325) RP(3,4,2,7.4125),//3-4 B
      At(1325-373+206) Shovel(3, 4) & Card(AYMTS_34, 3, 4),
      At(1325-373+206+751) Card({{AYMTS_34, 3, 5},{AYMJNP_47, 3, 4}}),
      At(2200) Shovel(5,4),
      At(2301) A(2,8) & RP(2,4,3,7.7) & J(5,4),//2-4 P
  };
  ATimeline I_3Bll_N = {
      // 3 7 |10 14 18 20.
      At(204) Shovel(1,6),
      At(305) I(1, 6, false), //I 
      At(1325) RP(3,4,2,7.4125),//3-4 B3
      At(2301) N({{2, 6}, {2, 7}}),
  };
  OnWave(1_9 % 2, 11_19 % 1) I1_2Bl_3PAJ | I_2Bll_N | I1_3Bl_2PAJ | I_3Bll_N;
  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9.
  At(ATime(9, 2501)){
      At(305) I(2, 1, true), //I'
      At(1325) RP(3,4,2,7.4125),//3-4 B
      At(1325-373+206) Shovel(3, 4) & Card(AYMTS_34, 3, 4),
      At(1325-373+206+751) Card({{AYMTS_34, 3, 5},{AYMJNP_47, 3, 4}}),
      At(2200) Shovel(5,4),
      At(2301) A(2,8) & RP(2,4,3,7.7) & J(5,4),//2-4 P
  };
  // w10
  OnWave(10){
      At(204) Shovel(1,6),
      At(305) I(1, 6, false), //I 
      At(1325) RP(3,4,2,7.8),//3-4 B3
      At(2301) N({{2, 6}, {2, 7}}),
  };
  // w19.
  At(ATime(19, 2501)){
      At(204) Shovel(1,6),
      At(305) I(1, 6, false), //I 
      At(1325) RP(2,4,3,7.4125),//2-4 B3
      At(2301) N({{3, 6},{3, 7}}),
  };
  // w20
  OnWave(20){
      At(305) I(2, 1, true), //I'
      //手动预判炸实一炮B 或 At(533) RP(3,4,2,8.6),//3-4 B
      At(1325-373+206) Shovel(3, 4) & Card(AYMTS_34, 3, 4),
      At(1325-373+206+751) Card({{AYMTS_34, 3, 5},{AYMJNP_47, 3, 4}}),
      At(2200) Shovel(5,4),
      At(2301) A(2,8) & RP(2,4,3,7.7) & J(5,4),//2-4 P
      At(2501)
        (At(204) Shovel(1,6)) &
        (At(305) I(1, 6, false)) &//I 
        //手动炸实56路w19和w20的巨人 或者 (At(1325) RP(3,4,4,6.5)) &//3-4
        (At(2301) N({{2, 6}, {2, 7}})),
  };
}