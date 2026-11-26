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

      AGL_7, // 橄榄
      AXC_15, // 小丑
      // ATL_22, // 投篮
      ACG_3, // 撑杆

      ABY_23, // 白眼
      AHY_32, // 红眼

      // APJ_0,  // 普僵
      // ALZ_2,  // 路障
      ATT_4, // 铁桶

      ABJ_20, // 蹦极
  });

  /*At(ATime(1, -599))[] {
      AAverageSpawn();
      AMaidCheats::Dancing();
  };*/

  // 选卡 冰双核 南叶 刺窝荷 樱辣
  ASelectCards("INN PB _WL AJ");
  // 自动补南瓜头
  aPlantFixer.Start(ANGT_30, {{1, 1}, {1, 2}, {2, 1}, {5, 1}, {6, 1}, {6, 2}, {6, 3}}, 1500);
  // 6门炮列表
  aCobManager.SetList({{3, 1}, {3, 3}, {3, 5}, {4, 1}, {4, 3}, {4, 5}});
  // 脚本重新载入模式
  ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

  // C4u:6复用2：BB-JNP-A BB-PPN16

  // 热键AS在鼠标处放三叶草地刺
  At('A') Do { ACard(ASYC_27, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(ADC_21, AMouseRow(), AMouseCol()); };

  OnWave(1){
      At(688) P(3, 7.4),
      At(622) Card<1000>(ADC_21, 5, 8),

      At(779) P(4, 7.1375),

      At(2301) J(1, 4) & N({{4, 9}, {5, 9}}, false),
      At(2301) P(5, 6.4),

      At(2401) A(2, 7),
  };

  ATimeline Bc_B_JNP_A = { //1 5 9 13 17
      At(688) P(3, 7.4),
      At(622) Card<1000>(ADC_21, 5, 8),

      At(779) P(4, 7.1375),

      At(2301) J(1, 4) & N({{4, 9}, {5, 9}}, false),
      At(2301) P(5, 6),

      At(2401) A(2, 7),
  };

  ATimeline Bc_B_NJP_A = { //3 7 11 15 19
      At(688) P(3, 7.4),
      At(622) Card<1000>(ADC_21, 5, 8),

      At(779) P(4, 7.1375),

      At(2301) J(6, 4) & N({{2, 9}, {3, 9}}, false),
      At(2301) P(1, 6),

      At(2401) A(5, 7),
  };

  ATimeline B_B_N1PP_I = { //2 4 6 8 10 12 14 16 18 20
      At(688) P(3, 7.4),
      At(622) Card<1000>(ADC_21, 5, 8),

      At(779) P(4, 7),

      At(2301) N({{3, 8}, {3, 7}, {4, 8}, {4, 7}}, true),
      At(2301) P(1, 6),
      At(2301) P(5, 6),

      At(2301) I(2, 4),
  };
  OnWave(2_9 % 2,11_19 % 3)  Bc_B_JNP_A | B_B_N1PP_I | Bc_B_NJP_A | B_B_N1PP_I;

  // w9
  At(ATime(9, 2501)) {
      At(688) P(1, 7),
      At(779) P(5, 7),
      At(2301) P(5, 6),
  };

  // w10
  OnWave(10){
    At(225) P(2,9),
    At(359) N({{3, 7}, {4, 7}, {3, 8}, {4, 8}}, true),
  };

  // w19
  At(ATime(19, 2501)) {
      At(688) P(1, 7),
      At(779) P(5, 7),
      At(2301) P(5, 6),
  };

  // w20
  OnWave(20){
    At(1) I(2, 4),
    At(1250) N({{3, 7}, {4, 7}, {3, 8}, {4, 8}}, true),
  };
}