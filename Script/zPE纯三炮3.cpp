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
    // AConnect('R', [] { AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 1 ? 10 : 1; });
    // 卡槽置顶
    // AConnect('V', [] { AMRef<int>(0x416DBE) = AMRef<int>(0x416DBE) == 699999 ? 100001 : 699999; });

    // 脚本重新载入模式
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

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
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼

        ALZ_2, // 路障
        // ATT_4,  // 铁桶

        // ABJ_20, // 蹦极
    });
    ASelectCards({
        AGJG_23, // 高坚果
        ADS_36,  // 大蒜
        ADC_21,  // 地刺

        AHY_16,  // 荷叶
        AHMG_15, // 毁灭菇
        AKFD_35, // 咖啡豆

        ACHERRY_BOMB, // 樱桃炸弹
        AHBLJ_20,     // 辣椒
        AHBG_14,      // 寒冰菇
        AM_HBG_14,    // 模仿寒冰菇 第一段始终是AM
    });

    /*At(ATime(1, -599))[] {
        AAverageSpawn();
        AMaidCheats::Dancing();
        aPlantFixer.Start(ANGT_30, {{4, 4}, {3, 4}}, 1332);
    };*/

    // 自动存冰 先用模仿冰,从后往前使用
    // aIceFiller.Start({{3, 8}});
    // 3门炮列表
    aCobManager.SetList({{3, 1}, {4, 1}, {3, 3}});
    // 关闭报错
    AGetInternalLogger()->SetLevel({});
    // C4u:I-/d-ANd I-B-JP I-NB-PA I-B-JP

    // 垫材逻辑
    ATimeline CCTV = {

    };
    OnWave(2_20) CCTV;

    // w1
    OnWave(1) {
        At(-599) Card(AHY_16, 4, 8) & Card(AGJG_23, 6, 1),
        At(3001 - 599) Card(AGJG_23, 5, 1),
        At(6002 - 599) Card(AGJG_23, 1, 1),
        At(134) I(2, 8), // I'
    };

    for(int wave:{1,9})
    {
        AConnect(ATime(wave,1266),[]{ACard(AHY_16,3,9);});//垫潜水
    }
    for(int wave:{5})
    {
        AConnect(ATime(wave,1266),[]{ACard(AHY_16,4,9);});//垫潜水
    }

    // w1-w9,w10-w19
    ATimeline I1_d5_A1N3d5 = {
        At(136) Shovel(3, 8, AHY_16) & Shovel(4, 8, AHY_16), // 铲垫海豚
        At(515) Card(AHY_16, {{3, 7}, {4, 7}}),              // C
        At(886 - 198 - 100) Card(AHMG_15, {{3, 7}, {4, 7}}), // N3

        At(852) P(5, 2.5), // d5

        At(2301) A(1, 4),                                     // A1
        At(2301 - 198 - 100) Card(AKFD_35, {{3, 7}, {4, 7}}), // N3
        At(2506) P(5, 3.525),                                 // d5
    };
    ATimeline I_B3_J1P5 = {
        At(135 - 100 - 199) Card({AHY_16, AICE_SHROOM}, 3, 8), // I
        At(553 - 100 - 198) Card(AKFD_35, 3, 8),               // I

        At(781) P(3, 8.375), // B3

        At(2301) J(1, 4),     // J1
        At(2301) P(5, 7.525), // P5

        At(2501 + 134) I(3, 8), // I'
    };
    ATimeline I1_N4B5_P2A5 = {
        At(1325) P(5, 7.55),                                                    // B5
        At(886 - 198 - 100) Card({AHY_16, AHMG_15, AKFD_35}, {{4, 3}, {4, 4}}), // N4

        At(2301) P(2, 7.55), // P2
        At(2301) A(5, 8),    // A5
    };
    ATimeline I_B3_J1P5_ = {
        At(135 - 100 - 199) Card({AHY_16, AICE_SHROOM, AKFD_35}, 3, 8), // I

        At(781) P(3, 8.75), // B3

        At(2301) J(1, 5),    // J1
        At(2301) P(5, 7.55), // P5

        At(2501 + 134) I(3, 8), // I'
    };
    OnWave(1_9 % 1, 11_19 % 2) I1_d5_A1N3d5 | I_B3_J1P5 | I1_N4B5_P2A5 | I_B3_J1P5_;

    // w9后
    OnWave(9) {

    };
    for (int wave : {10}) {
        AConnect(ATime(wave, 0), [] { aIceFiller.Pause(); });   // 暂停存冰
        AConnect(ATime(wave, 1500), [] { aIceFiller.GoOn(); }); // 继续
    }
    // w10
    OnWave(10) {

    };
    // w19后
    OnWave(19) {

    };
    // w20
    OnWave(20) {
        // 3

    };
}