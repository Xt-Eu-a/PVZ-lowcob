#include <avz.h>
#include <dsl/shorthand.h>

static bool Paused = false;
static bool PausedSlowed = false;

void AScript() {
  // 高级暂停
  AConnect('Z', [] {
    Paused = !Paused;
    PausedSlowed = false;
    ASetAdvancedPause(Paused, false, 0);
  });
  // 下一帧
  AConnect('X', [] {
    Paused = false;
    PausedSlowed = false;
    ASetAdvancedPause(Paused, false, 0);
    AConnect(ANowDelayTime(1), [] {
      Paused = !Paused;
      ASetAdvancedPause(Paused, false, 0);
    });
  });
  // 0.25倍速
  // 脱离倍速和高级暂停
  AConnect('C', [] {
    if (Paused) {
      Paused = false;
      PausedSlowed = true;
      ASetAdvancedPause(Paused, false, 0);
      AGetPvzBase()->TickMs() = 40;
    } else if (PausedSlowed) {
      Paused = true;
      PausedSlowed = false;
      ASetAdvancedPause(Paused, false, 0);
      AGetPvzBase()->TickMs() = 10;
    } else {
      AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 10 ? 40 : 10;
    }
  });
  // 十倍速
  // AConnect('R', [] { AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 1 ?
  // 10 : 1; });
  // 卡槽置顶
  // AConnect('V', [] { AMRef<int>(0x416DBE) = AMRef<int>(0x416DBE) == 699999 ?
  // 100001 : 699999; });

  ASetZombies({
      ABC_12, // 冰车
      AKG_17, // 矿工
      // AQQ_16, // 气球

      AFT_21, // 扶梯
      ATT_18, // 跳跳

      AHT_14, // 海豚
      AQS_11, // 潜水

      AGL_7,  // 橄榄
      AXC_15, // 小丑
      ATL_22, // 投篮
      ACG_3, // 撑杆

      ABY_23, // 白眼
      AHY_32, // 红眼

      // APJ_0,  // 普僵
      ALZ_2,  // 路障
      //ATT_4, // 铁桶

      ABJ_20, // 蹦极
  });

  //均匀出怪 女仆秘籍
  At(ATime(1, -599))[] {
      AAverageSpawn();
      AMaidCheats::Dancing();
  };

  // 选卡 双核 南叶 荷 樱辣 刺 蒜盆
  ASelectCards("NN PB L AJ _", {ADS_36,AHP_33}, 10);

  // 自动补南瓜头
  aPlantFixer.Start(ANGT_30,{{1, 2},{1, 3},{2, 2},{2, 3},{4, 8},{5, 1},{5, 2},{6, 1},{6, 2}},2300);
  // 6门炮列表
  aCobManager.SetList({{3, 1}, {3, 3}, {4, 2}, {4, 4}, {1, 4}, {2, 4}});
  // 脚本重新载入模式
  ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

  // C4u:6复用2：BB-JNP-A BB-PPN16

  // 热键ASDW在鼠标处放三叶草大蒜花盆地刺
  At('A') Do { ACard(ASYC_27, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(ADS_36, AMouseRow(), AMouseCol()); };
  At('D') Do { ACard(AHP_33, AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(ADC_21, AMouseRow(), AMouseCol()); };

  // 垫材逻辑
  ATimeline CC1 = {
      At(452) Card(AHY_16, 4, 8),

      At(292) Card<50>(ADC_21, 5, 9),
      At(500) Card<400>(ADS_36, 5, 8),
      At(1251) Card<400>(ADS_36, 5, 7),
  };
  OnWave(1_9,11_19) CC1;

  // 循环主体
  OnWave(1){
      //At(-599) Card({AHY_16, ANGT_30}, 4, 8),
      At(168) P(2, 8.4625),
  };
  ATimeline BBcc_b_PN1 = {
      // 1 3 5 7 9 | 11 13 15 17 19 20
      At(777) P(5, 6),
      At(2301) P(1, 7.5) & N({{3, 5}, {3, 6}, {3, 7}, {4, 6}}, true),

      At(2501 + 168) P(2, 8.4625),
      At(2501 + 235) A(1, 8),
  };
  ATimeline BAcc_b_PNJ = {
      // 2 4 6 8 9. 10| 12 14 16 18 19. 20.
      At(777) P(5, 6),
      At(2301) P(1, 7.5) & N({{3, 8}, {3, 9}, {4, 7}, {4, 9}}, false) & J(6, 3),

      At(2501 + 168) P(1, 8.4125) & P(2, 8.4625),
  };
  OnWave(1_9 % 1, 11_19 % 1) BBcc_b_PN1 | BAcc_b_PNJ;

  // w9. w19.
  At(ATime(9, 2501)){
      At(777) P(5, 6),

      At(1145) P(5, 6),

      At(2301) J(6, 3),
  };
  At(ATime(19, 2501)){
      At(777) P(5, 6),

      At(1145) P(5, 6),

      At(2301) J(6, 3),
  };
  // w10 w20
  OnWave(10,20){
      At(359) P(2, 9) & N({{3, 8}, {3, 9}, {4, 7}, {4, 9}}, false),

      At(601 + 168) P(1, 8.4125) & P(2, 8.4625),
  };
}