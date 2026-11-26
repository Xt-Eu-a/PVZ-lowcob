#include <avz.h>
#include <dsl/shorthand.h>
#include <nb30.h>
#include <wingdi.h>
#include "xt.h"

void AScript() {
  // 出怪
  ASetZombies({
      AKG_17, /*矿*/ AQQ_16, /*气*/ AFT_21, /*梯*/ ATT_18, /*跳*/
      AGL_7,  /*橄*/ AXC_15, /*丑*/ ATL_22, /*篮*/ ACG_3,  /*杆*/
      ABY_23, /*白*/ AHY_32, /*红*/
      ATT_4,  /*桶*/ ABJ_20, /*偷*/
  });
  // 选卡 双冰 樱辣核 高碑 叶伞 蒜
  ASelectCards("II AJN TG BU", {ADS_36}, 15);

  // 均匀出怪
  At(ATime(1, -599))[] { AAverageSpawn(); };
  // 确保w9 w19 w20的2路出至少⼀只红眼
  OnWave(9, 19, 20) EnsureExist(AGIGA_GARGANTUAR, {2});

  // 自动补高坚果/南瓜 设置血量＞6000-6000/炮数(不省，血量设置再高都等效) 或 ＞炮数*30s单门炮掉血(省)
  aPlantFixer.Start(AGJG_23, {{1, 1}, {2, 1}}, 4500);
  // 9门炮列表
  aCobManager.SetList(
      {{1, 2}, {1, 4}, {3, 1}, {3, 3}, {4, 2}, {4, 4}, {5, 1}, {5, 3}, {5, 5}});
  // 脚本重新载入模式
  ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

////////////////////////////////////////////////////////////////////////////////////////////

  // C4u:9复用3：I1-B3B4d-PNJ/PSN I-B2B4b-PA/Pd

  // 垫材逻辑
  // 垫材列表
  C.SetCards({AYZBHS_37,ASYC_27});
  // w1
  OnWave(1) {
      At(961) Card<300>(ADS_36,1,8),
      At(961+751) Card<150>(ADS_36,1,7), //最多延迟174铲
  };

  // 核波15路垫材
  ATimeline CC1 = {
      At(961) Card<300>(ADS_36,1,8),
      At(961+751) Card<150>(ADS_36,1,7), //174
      At(1275) C.TriggerBy(AHY_32 & PosIn(510, 607, 449, 451))(400,APosition{5,7}), //智能放垫，最多延迟407铲
      At(2250) Card<100>(ASYC_27,1,7),
  };
  OnWave(3,5,7,9,12,14,16,18) CC1;
  // 樱波15路垫材
  ATimeline CC2 = {
      At(2305) C.TriggerBy(AHY_32 & PosIn(638, 734, 449, 451))(350,APosition{5,8}), //智能放垫
      At(2305) C.TriggerBy(AHY_32 & PosIn(638, 711, 49, 51))(250,APosition{1,8}), //智能放垫
  };
  OnWave(2,4,6,8,11,13,15,17,19,20) CC2;

  // w10 垫4路丑5路榄丑
  OnWave(1,10) {
      At(961) Card<300>(ADS_36,1,8),
      At(961+751) Card<150>(ADS_36,1,7), //174

      At(1270) C.TriggerBy(AGL_7 & OrdIn(449,451),AXC_15 & OrdIn(449,451))(617,APosition{5,8}), //智能放垫最晚1887铲
      At(1270) C.TriggerBy(AXC_15 & OrdIn(349,351))(250,APosition{4,8}), //智能放垫
  };
  // w10 w20伞处理蹦极
  ATimeline CC3 = {
      At(33) Do{aPlantFixer.Pause();},
      At(34) Shovel(2,1,AGJG_23),
      At(35) Card<400>(AYZBHS_37,2,1),
      At(36) Do{aPlantFixer.GoOn();},
  };
  OnWave(10, 20) CC3;
  // w20 吞碑 垫4路丑5路榄丑
  OnWave(20){
      At(363) Do{ACard(AMBTSZ_11, AGetGraves());},

      At(1270) C.TriggerBy(AGL_7 & OrdIn(449,451),AXC_15 & OrdIn(449,451))(617,APosition{5,8}), //1887
      At(1270) C.TriggerBy(AXC_15 & OrdIn(349,351))(250,APosition{4,8}), //智能放垫
  };

////////////////////////////////////////////////////////////////////////////////////////////

  // 循环主体
  ATimeline I1_B3B4d_PNJ_PSN = {
      // 1 3 5 7 9 |10 12 14 16 18 19. 20.
      At(362)
          I(3, 5, true), // 小丑516~1270,巨人616~1270,炸7.4125,362冰~2362解冻
      At(1270) P(3, 7.4125),
      At(1270) P(4, 7.4125),
      At(1594) P(4, 2.325), // 324~346

      At(2301) P(2, 7.725) & P(4, 7.725) & P(4, 7.725),
      At(2301 + 139) N({{2, 7}, {2, 8}, {3, 7}, {3, 8}}),
      At(2301 + 246) J(1, 6),
  };
  ATimeline I_B2B4b_PA_Pd = {
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(362)
          I(3, 5, false), // 小丑516~1270,巨人616~1270,炸7.4125,362冰~2362解冻
      At(1270) P(2, 7.4125),
      At(1270) P(4, 7.4125),
      At(1100) P(4, 2),

      At(2301) P(2, 7.725) & P(4, 7.725), // 全伤1,3路红眼
      At(2301 + 269) A(2, 4),             // 238
      At(2301 + 268) P(4, 2.4125),        // 237
  };
  OnWave(1_9 % 1, 10_19 % 1, 20_20 % 2) I1_B3B4d_PNJ_PSN | I_B2B4b_PA_Pd;

////////////////////////////////////////////////////////////////////////////////////////////

  // w9.
  At(ATime(9, 2501)){
      At(362)
          I(3, 5, false),
      At(1270) P(2, 7.4125),
      At(1270) P(4, 7.4125),

      At(2301) P(2, 7.725),

      At(2024) Shovel(2,3) & Card(AYZBHS_37,2,3),
  };
  // w19.
  At(ATime(19, 2501)){
      At(961) Card<300>(ADS_36,1,8),
      At(961+751) Card<150>(ADS_36,1,7), //174
      At(1275) C.TriggerBy(AHY_32 & PosIn(510, 607, 449, 451))(400,APosition{5,7}), //407
      At(2250) Card<100>(ASYC_27,1,7),

      At(362)
          I(3, 5, true),
      At(1270) P(3, 7.4125),
      At(1270) P(4, 7.4125),
      At(1593) P(4, 2.4625), //323

      At(2301) P(2, 7.725) & P(4, 7.725) & P(4, 7.725),
      At(2301 + 139) N({{2, 7}, {2, 8}, {3, 7}, {3, 8}}),
      At(2301 + 246) J(1, 6),

      At(2026) Shovel(2,3) & Card(AYZBHS_37,2,3),
  };
  // w20.
  At(ATime(20, 2501)){
      At(961) Card<300>(ADS_36,1,8),
      At(961+751) Card<150>(ADS_36,1,7), //174
      At(1275) C.TriggerBy(AHY_32 & PosIn(510, 607, 449, 451))(400,APosition{5,7}), //407
      At(2250) Card<100>(ASYC_27,1,7),

      At(362)
          I(3, 5, true),
      At(1270) P(3, 7.4125),
      At(1270) P(4, 7.4125),
      At(1593) P(4, 2.4625), // 323

      At(2301) P(2, 7.725) & P(4, 7.725) & P(4, 7.725),
      At(2301 + 139) N({{2, 7}, {2, 8}, {3, 7}, {3, 8}}),
      At(2301 + 246) J(1, 6),

      At(2600) Shovel(2,3) & Card(AYZBHS_37,2,3) & Do{aPlantFixer.Stop();},
      At(2601) Shovel(1,1,AGJG_23) & Shovel(2,1,AGJG_23),
  };
}