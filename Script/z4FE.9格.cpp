#include <avz.h>
#include <dsl/shorthand.h>
#include <nb30.h>
#include "xt.h"

void AScript() {
  // Z:高级暂停,原速→暂停,暂停→原速（开关高级暂停;关闭音效;暂停时的透明度+颜色0~255是透明度,0是完全透明）
  AConnect('Z', [] {Paused = !Paused; ASetAdvancedPause(Paused, false, 0);});
  // X:0.1倍速,任意倍速→0.1倍速,0.1倍速→原速（tick原为10,10ms即1cs运行1帧,改成100为0.1倍速,100ms即10cs运行1帧）
  AConnect('X', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 100 ? 10 : 100;});
  // C:2倍速,任意倍速→10倍速,10倍速→原速
  AConnect('C', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 3 ? 10 : 3;});
  // 出怪14怪
  ASetZombies("矿气梯跳车 豚潜 橄丑篮杆 白红 普 偷",ASetZombieMode::INTERNAL);
  // 选卡 喷阳 窝坚 荷 双冰 樱辣核（阻塞时间至w1的-599）
  AXtSelectCards("cc WZ L II AJN", 15);
  // 2门炮列表
  aCobManager.AutoSetList();
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  //  关闭报错
  //AGetInternalLogger()->SetLevel({});

  /////////////////////////////////////////////////////////////////////////////////////////

  // N4:I--Nd I'-A-JB I-/B-N I'-A/d-JB（本质上是100s 2复用3）
    /*w1首代~w4
    I-B-Nd I'-A-JB I-/B-N I'-A/d-JB
    w5~w8
    I-~-Nd I'-A-JB I-/B-N I'-A/d-JB

    w9特化
    I--Nd(矿) I'-PA-J
    2路Na_B
    下半场NPA

    w10~w13
    I-B(偷)-Nd I'-A-JB I-/B-N I'-A/d-JB
    w14~w17
    I-~-Nd I'-A-JB I-/B-N I'-A/d-JB
    w18
    I--Nd

    w19特化
    I'-AP935-J I-/P1059-N
    2路AN_B
    下半场PPN

    w20特化
    I'-B(偷)394A/-/B1790-J I-P1368/-N-/d2764
    2路APN
    下半场BNa*/


  // 垫材逻辑
  // 热键ASW在鼠标处放小喷菇阳光菇窝瓜,D在鼠标处铲除植物
  At('A') Do { ACard(AXPG_8, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(AYGG_9, AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(AWG_17, AMouseRow(), AMouseCol()); };
  At('D') Do { AShovel(AMouseRow(), AMouseCol()); };

  //
  ATimeline CC1 = {

  };
  OnWave(1_20) CC1;
  //均匀出怪
  //At(ATime(1, -599))[] { AAverageSpawn(); };
  /////////////////////////////////////////////////////////////////////////////////////////

  //w1特化
  OnWave(1){
      At(-599) Card({AHY_16,AJG_3},3,5) & Card(AYGG_9,2,4),
      At(152) Card({AHY_16,AYGG_9},3,6),
      At(903) Card({AHY_16,AYGG_9},4,6),
      At(3001-599) Card(AJG_3,2,1),
      At(6002-599) Card(AJG_3,4,5),
      At(4105) Card(AHY_16,4,5),
      At(950) P(3,9), //B
  };
  
  // 循环主体
  ATimeline I__Nd = {
      // 1 5 | 10 14 18
      At(50) I(1, 1, false), //I 
      At(2301) N({{3, 8}, {4, 8}, {3, 7}, {4, 7}}) & D<284>(5, 3.05),
      At(2501+50) I(1, 1, true), //I'
  };
  ATimeline Il_A_JB = {
      // 2 6 | 11 15
      At(950) A(3,9),
      At(2301) J(1,2) & P(5, 6.025),
  };
  ATimeline I_B_N = {
      // 3 7 |12 16
      At(50) I(1, 1, false), //I 
      At(1325) P(5, 7.675), //B收5路小丑
      At(2301) N({{3, 8}, {4, 8}, {3, 7}, {4, 7}}),
      At(2501+50) I(1, 1, true), //I'
  };
  ATimeline Il_Ad_JB = {
      //4 8 | 13 17
      At(950) A(3,9),
      At(405) Do{RightFullDamageSmartCob(5, 2.5, ATime(ANowWave(),779-373), AXG_24,     //整数行、浮点数列、ATime结构体、僵尸类型
        31,false,true,true,178.0f, 193.0f, 189.0f);},   //373cs内的前进预测、上中下炸点判定选择
      At(2301) J(1,2) & P(5, 6.025),
  };
  OnWave(1_8 % 1, 10_18 % 1) I__Nd | Il_A_JB | I_B_N | Il_Ad_JB;

  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9 I--Nd(矿) I'-AP-J
  // 2路NA_Bio(a)
  // 下半场NP
  OnWave(9){
      At(50) I(1, 1, false), //I 
      At(2301) N({{3, 8}, {4, 8}, {3, 7}, {4, 7}}) & D<262>(5, 3.3625),
      At(2501+50) I(1, 1, true), //I'
      At(2501)  (At(1193) A(5,6)) &
                (At(980) P(5, 6.925)) &
                (At(2301) J(1,2)),
  };

  // w10 B炸小偷
  OnWave(10){
      At(799) P(3, 4),
  };

  // w19 I'-AP950-J I-/P1060-N
  // 2路AN_B
  // 下半场PPN_
  OnWave(19){
      At(950) A(3,9) & P(5, 7.2),
      At(2301) J(1,2),
      At(2501)  (At(50) I(1, 1, false)) & //I 
                (At(2301) N({{3, 8}, {4, 8}, {3, 7}, {4, 7}})),
      At(5245+1) I(1, 1, true), //I'
  };

  // w20 I'-B(偷)394A/-/B1792-J I-P1369/-N-/P2764
  // 2路APN
  // 下半场BNa
  OnWave(20){
      At(394) P(3, 4),
      At(1300) A(3,9),
      At(2301) J(1,2),
      At(2501)  (At(1) I(1, 1, false)) & //I 
                (At(2301) N({{3, 8}, {4, 8}, {3, 7}, {4, 7}})) ,
  };
}
