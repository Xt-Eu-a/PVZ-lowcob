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
  AConnect('C', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 2 ? 10 : 2;});
  // 出怪12怪
  ASetZombies("矿气梯跳车 橄丑篮杆舞 白红 偷");
  // 选卡 南高 玉炮 辣樱 豆双冰核（阻塞时间至w1的-599）
  AXtSelectCards("PH YZ JA KIIN", 15);
  // 均匀出怪
  At(ATime(1, -599))[] { AAverageSpawn(); };
  OnWave(9,19,20) EnsureExist({AGARGANTUAR, AGIGA_GARGANTUAR}, {1, 2, 3, 4});
  //女仆秘籍
  AMaidCheats::CallPartner();

  // 4门炮列表
  aCobManager.SetList({{3, 5}, {4, 5}, {5, 2}, {5, 5}});
  //自动存冰 先用模仿冰,从后往前使用
  aIceFiller.Start({{5, 4},{4, 4},{2, 5},{1, 5},{1, 4}});
  for(int wave:{9}){
    AConnect(ATime(wave,900),[]{aIceFiller.SetList({{5, 4},{4, 4},{4, 1},{5, 1}});});
  };
  for(int wave:{11}){
    AConnect(ATime(wave,1),[]{aIceFiller.SetList({{5, 4},{4, 4},{2, 5},{1, 5},{1, 4}});});
  };
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  //  关闭报错
  //AGetInternalLogger()->SetLevel({});

  /////////////////////////////////////////////////////////////////////////////////////////

  // I6:I3N(2-4)-PPD' I-PPD"J I-A-PP (1766连续冰波)
    /*w1 839 w2w3（-337）(3-4)
    PPd' I-PPD"J I-A-PP
    w4w5w6（383）743-298=445
    I3N(2-4)-PPD' I-PPD"J I-A-PP
    w7w8（86）762-298=464
    I3N(3-3)-PPD' I-PPD"
    w9w9（1555）
    I-N(3-4)-J3PSN(3-7)-A-PSd'
    1766*3=5298


    w10  674w11（637）
    PPJd" I-J-PP
    w12w13w14（340）770-298=472
    I3N(2-3)-PPD'J I-PPD" I-A-PP
    w15w16w17（43）743-298=445
    I3N(2-4)-PPD'J I-PPD" I-A-PP
    w18 770-298=472
    I3N(3-3)-PPD'
    w19w19（1512）
    I-J3-P"PSN(3-7)-A-Pd-b

    w20（1268）
    I-P'dI-JN(3-8)D"-A-Pd-P-P*/

  // 热键ASW在鼠标处放地刺玉米高坚果,D在鼠标处铲除植物
  At('A') Do { ACard(ADC_21, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(AYMTS_34, AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(AGJG_23, AMouseRow(), AMouseCol()); };
  At('D') Do { AShovel(AMouseRow(), AMouseCol()); };

  // 垫材逻辑
  ATimeline CC1 = {

  };
  OnWave(2_9,11_20) CC1;

  /////////////////////////////////////////////////////////////////////////////////////////

  //w1特化
  OnWave(1){
      At(-599) Card(AYMTS_34,1,3) & Card(AGJG_23,3,3),

      At(3001-599) Card(AGJG_23,1,2),
      At(6002-599) Card(AGJG_23,2,2),

      TrigAt(549) P(14,8.475),
      At(775) RP(4,2,4,4) & Do{AShovel(4,2); aCobManager.Plant(4,2);},
  };
  OnWave(2){
      At(1735) Card(AYMTS_34,1,4),
  };

  // 辣椒逻辑
  OnWave(2,5,15) {
    At(1779) J(2,6),
  };
  OnWave(11) {
    At(635) J(2,6),
  };
  //毁灭菇逻辑
  OnWave(1){At(-337) Card(AHMG_15,3,2),};
  OnWave(4){
      At(383) Card(AHMG_15,2,4),
      At(464) Card(AKFD_35,2,4),//冰cd晚恢复
  };
  OnWave(7){
      At(86) Card(AHMG_15,3,4),
      At(464) Card(AKFD_35,3,4),
  };
  OnWave(9){
      At(680) Card(AKFD_35,3,2),
      At(1555) Card({AHMG_15,AKFD_35},3,7),//1521上炸下需要护核
  };
  OnWave(11){
      At(637) Card(AHMG_15,2,3),
      At(1766+472) Card(AKFD_35,2,3),
  };
  OnWave(14){
      At(340) Card(AHMG_15,2,4),
      At(1766+464) Card(AKFD_35,2,4),//冰cd晚恢复
  };
  OnWave(17){
      At(43) Card(AHMG_15,3,4),
      At(1766+464) Card(AKFD_35,3,4),
  };

  OnWave(19){
      At(1512) Card({AHMG_15,AKFD_35},3,7),
  };
  OnWave(20){
      At(1268) Card(AHMG_15,3,8),
      At(1386) Card(AKFD_35,3,8),

  };

  // 循环主体I3N(2-4)-PPD' I-PPD"J I-A-PP （1766）
  ATimeline I3N_PPDl = {
      // 4 7 | 12 15 18
      At(11) I(), //I 
      TrigAt(1566) PP(8.525),
      At(1780) RP(4,2,4,7.4),
      At(1613) Do{AShovel(4, 2); aCobManager.Plant(4, 2);},
  };
  ATimeline I_PPDll = {
      // 2 5 8 | 13 16
      At(14) I(), //I 
      TrigAt(1566) PP(8.525),
      At(1780) RP(4,2,4,7.4),
  };
  ATimeline I_A_PP = {
      // 3 6 | 14 17
      At(14) I(), //I 
      At(1044) A(4,1),
      TrigAt(1566) PP(8.525),
  };
  OnWave(2_8 % 2, 12_18 % 1) I3N_PPDl | I_PPDll |I_A_PP;

  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9 I--Nd(矿) I'-AP-J
  // 2路NA_Bio(a)
  // 下半场NP
  OnWave(9){
      At(14) I(), //I 

      At(1525) J(3,1),
      At(1573) P(44,8.425),

      At(3276) P(22,6.3375),
      At(3489) RP(4,2,2,3) & Do{AShovel(4, 2); aCobManager.Plant(4, 2);},
  };

  // w10
  OnWave(10){
      TrigAt(474) P(14,8.475),
      At(733) RP(4,2,4,4),
      At(675) I(), //I 
  };
  //w11
  OnWave(11){
      TrigAt(1566) PP(8.4375),
  };

  // w19 I'-AP950-J I-/P1060-N
  // 2路AN_B
  // 下半场PPN_
  OnWave(19){
      At(1510) J(3,1),
      At(14) I(), //I 

      At(1530) P(44,8.5375),
      At(1596) RP(4,2,1,8.5),

      At(3276) P(1,6.15),
      At(3576) P(2,3),

      At(5005) P(4,1),
  };

  // w20 I'-B(偷)394A/-/B1792-J I-P1369/-N-/P2764
  // 2路APN
  // 下半场BNa
  OnWave(20){
      At(440) I(),
      At(1266) J(2,6),

      At(332) RP(4,2,4,8.5875),
      At(165) Do{AShovel(4, 2); aCobManager.Plant(4, 2);},
      At(571) P(4,5.3375),

      At(1914) RP(4,2,4,8.1),

      At(1506) P(2,8.15),
      At(2400) P(2,2.8),

      At(3235) P(2,8),
      At(4046) P(2,6.5),
  };
}
