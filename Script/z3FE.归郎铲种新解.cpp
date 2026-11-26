#include <avz.h>
#include <dsl/shorthand.h>
#include <nb30.h>
#include "xt.h"

void AScript() {
  // 高级暂停Z
  AConnect('Z', [] {
    Paused = !Paused;//点一下'Z',Paused值变成true,开启高级暂停
    PausedSlowed = false;
    ASetAdvancedPause(Paused, false, 0);//开关高级暂停;关闭音效;暂停时的透明度+颜色0~255是透明度,0是完全透明
  });
  // 出怪13怪极红
  ASetZombies({
      AKG_17, /*矿*/ AFT_21, /*梯*/ ATT_18, /*跳*/ ABC_12, /*车*/
      AHT_14, /*豚*/ 
      AGL_7,  /*橄*/ AXC_15, /*丑*/ ATL_22, /*篮*/ ACG_3,  /*杆*/
      ABY_23, /*白*/ AHY_32, /*红*/
      ABJ_20, /*偷*/ ALZ_2,  /*障*/ ATM_6,  /*门*/
  });
  // 选卡  双冰 辣 炮套 核 荷 窝叶刺
  ASelectCards({AM_HBG_14,AHBG_14,AHBLJ_20,AYMJNP_47,AYMTS_34,
                AHMG_15,AHY_16,AWG_17,ASYC_27,ADC_21}, 15);
  // 4门炮列表
  aCobManager.SetList({{3, 2}, {3, 4}, {4, 2}, {4, 4}});
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
  // 关闭报错
  //AGetInternalLogger()->SetLevel({});

  // C4u:BI'-BD"-P BI-d-JNd'/d 
  // 垫材逻辑
  // 热键ASDW在鼠标处放玉米三叶草地刺窝瓜
  At('A') Do { ACard(AYMTS_34, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(ASYC_27, AMouseRow(), AMouseCol()); };
  At('D') Do { ACard(ADC_21, AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(AWG_17, AMouseRow(), AMouseCol()); };

  // 地刺扎冰车,智能
  C.SetCards({ADC_21});
  ATimeline CC1 = {
    At(292) C.TriggerBy(ABC_12 & PosIn(700, 750, 134, 136))(50,APosition{2,9}),
  };
  OnWave(1,3,5,7,9,10,12,14,16,18) CC1;

  // 循环主体
  //w1特化
  OnWave(1){
    At(-599) Card({{ADC_21,1,1},{AYMTS_34,2,6}}),
    At(-599+751) Card(AYMTS_34,2,7),
  };

  ATimeline BI_d_JNdl2d = {
      // 1 5 9 |12 16 19.
      At(264-100) Shovel(2, 8),
      At(265) I(2, 8, false), //I 
      At(265) P(4, 8.2625), //B
      At(1220) P(5, 2.5), //d

      At(2199-100) Shovel({{2, 1},{2, 6},{2, 7},{2, 8}}),
      At(2200) J(2,1),
      At(2301) N({{3, 8}, {3, 7}, {3, 6}, {4, 7}}),

      At(2507) RP(2,2,1,3.6),//2-2 d1
      At(2507-373+206) Shovel(2, 2) & Card(AYMTS_34, 2, 2),
      At(2507-373+206+751) Card({{AYMTS_34, 2, 3},{AYMJNP_47, 2, 2}}),

      At(2515) P(5, 3.15), //d
  };
  ATimeline B4Il_BDll2_P = {
      // 2 6 9. | 13 17 20
      At(265) I(2, 1, true), //I'

      At(265) RP(2,4,3,8.35),//2-4 B3

      At(1377) P(1, 7.4125),
      At(1590) RP(2,2,1,5.6625),//2-2 D1

      At(2301) P(5,6.025),
  };
  ATimeline BI_d_JNdl4d = {
      // 3 7 |10 14 18 20.
      At(264-100) Shovel(2, 8),
      At(265) I(2, 8, false), //I 
      At(265) P(4, 8.2625), //B
      At(1220) P(5, 2.5), //d

      At(2199-100) Shovel({{2, 1},{2, 6},{2, 7},{2, 8}}),
      At(2200) J(2,1),
      At(2301) N({{3, 8}, {3, 7}, {3, 6}, {4, 7}}),

      At(2507) RP(2,4,1,3.6),//2-4 d1
      At(2507-373+206) Shovel(2, 4) & Card(AYMTS_34, 2, 4),
      At(2507-373+206+751) Card({{AYMTS_34, 2, 5},{AYMJNP_47, 2, 4}}),

      At(2515) P(5, 3.15), //d
  };
  ATimeline B2Il_BDll4_P = {
      //4 8 | 11 15 19
      At(265) I(2, 1, true), //I'

      At(265) RP(2,2,3,8.35),//2-2 B3

      At(1377) P(1, 7.4125),
      At(1590) RP(2,4,1,5.6625),//2-4 D1

      At(2301) P(5,6.025),
  };
  OnWave(1_9 % 1, 11_19 % 4) BI_d_JNdl2d | B4Il_BDll2_P | BI_d_JNdl4d | B2Il_BDll4_P;

  // 中场收尾特化
  // w9.
  At(ATime(9, 2501)){
      At(265) I(2, 1, true), //I'

      At(265) RP(2,4,2,7.5),//2-4 B2

      At(1377) P(1, 7.4125),
      At(1590) RP(2,2,1,5.6625),//2-2 D1

      At(2301) P(5,6.025),
  };
  // w10
  OnWave(10){
      At(264-100) Shovel(2, 8),
      At(265) I(2, 8, false), //I 
      At(265) P(4, 9), //B
      At(1220) P(5, 2), //d

      At(2199-100) Shovel({{2, 1},{2, 6},{2, 7},{2, 8}}),
      At(2200) J(2,1),
      At(2301) N({{3, 8}, {3, 7}, {3, 6}, {4, 7}}),

      At(2507) RP(2,4,1,3.6),//2-4 d1
      At(2507-373+206) Shovel(2, 4) & Card(AYMTS_34, 2, 4),
      At(2507-373+206+751) Card({{AYMTS_34, 2, 5},{AYMJNP_47, 2, 4}}),

      At(2515) P(5, 3.15), //d
  };
  // w19. 
  At(ATime(19, 2501)){
      At(264-100) Shovel(2, 8),
      At(265) I(2, 8, false), //I 
      At(265) P(5, 7.5), //B
      At(1220) P(5, 2.5), //d

      At(2199-100) Shovel({{2, 1},{2, 6},{2, 7},{2, 8}}),
      At(2200) J(2,1),
      At(2301) N({{3, 8}, {3, 7}, {3, 6}, {4, 7}}),

      At(2507) RP(2,2,1,3.6),//2-2 d1
      At(2507-373+206) Shovel(2, 2) & Card(AYMTS_34, 2, 2),
      At(2507-373+206+751) Card({{AYMTS_34, 2, 3},{AYMJNP_47, 2, 2}}),

      At(2515) P(5, 3.15), //d
  };
  // w20 手动
  OnWave(20){
      At(198) I(2, 1, true), //I'
  };
}

// 手动介入：