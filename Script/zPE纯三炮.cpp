#include <avz.h>
#include <dsl/shorthand.h>

static bool Paused = false;
static bool PausedSlowed = false;

void AScript()
{
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
    //AConnect('R', [] { AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 1 ? 10 : 1; });
    // 卡槽置顶
    //AConnect('V', [] { AMRef<int>(0x416DBE) = AMRef<int>(0x416DBE) == 699999 ? 100001 : 699999; });

    // 脚本重新载入模式  
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    ASetZombies({
        ABC_12, // 冰车
        AKG_17, // 矿工
        AQQ_16, // 气球

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

        ABJ_20, // 蹦极
    });
    ASelectCards({
        AGJG_23,   // 高坚果
        ADS_36,    // 大蒜
        ADC_21,    // 地刺

        AHY_16,    // 荷叶
        AHMG_15,   // 毁灭菇
        AKFD_35,   // 咖啡豆

        ACHERRY_BOMB,  // 樱桃炸弹
        AHBLJ_20,  // 辣椒
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
    });

    /*At(ATime(1, -599))[] {
        AAverageSpawn();
        AMaidCheats::Dancing();
        aPlantFixer.Start(ANGT_30, {{4, 4}, {3, 4}}, 1332);
    };*/

    //自动存冰 先用模仿冰,从后往前使用
    aIceFiller.Start({{4, 3}});
    //3门炮列表
    aCobManager.SetList({{3,1},{4,1},{3,3}});

    //C4u:I-B-J/PA | I-B-Nd

    //垫材逻辑
    ATimeline CCTV = {
        At(254) Card(AHY_16, 4, 8),
        At(751+254) Card(AHY_16, 4, 7),
    };
    OnWave(2_20) CCTV;

    //w1
    OnWave(1) {
        At(-599) Card(AHY_16, 4, 3) & Card(AGJG_23, 2, 4),
        At(751-599) Card(AHY_16, 4, 4),
        At(751+751-599) Card(AHY_16, 4, 5),
        At(751+751+751-599) Card(AHY_16, 3, 5),
        At(3001-599) Card(AGJG_23, 1, 1) ,
    };

    //w1-w9,w11-w19
    ATimeline I_B_JPA = {
        At(551-198-100) Card(AKFD_35, 4, 3),//I

        At(779) P(3,8.3875),//B3

        At(2301) J(1,4),//J1
        At(2301) P(5,7.4),//P5
        At(2650) A(5,3),//A2
    };
    ATimeline I_B_Nd = { 
        At(134-100-198) Card(AKFD_35, 4, 3),//I

        At(1325) P(2,7.55),//B2

        At(2301) N({{3, 8},{3, 7},{3, 6},{4, 7}}),//N
        At(2650) P(5,3),//d5
    };
    OnWave(1_9 % 1, 11_19 % 2) I_B_JPA | I_B_Nd;

    //w9后
    OnWave(9) {
        At(2501+134-100-198) Card(AKFD_35, 4, 3),//I

        At(2501+1325) P(2,7),//B2

        At(2501+2301) N({{3, 8},{3, 7},{3, 6},{4, 7}}),//N
        At(2501+2650) P(5,3),//d5
    };
    for(int wave:{10})
    {
        AConnect(ATime(wave,0),[]{aIceFiller.Pause();});//暂停存冰
        AConnect(ATime(wave,1300),[]{aIceFiller.GoOn();});//继续
    }
    //w10
    OnWave(10) {
        At(309-198-100) Card(AKFD_35, 4, 3),//I

        At(779) P(3,9),//B3

        At(2301) J(1,4),//J1
        At(2301) P(5,7.525),//P5
        At(2650) A(5,3),//A2
    };
    //w19后
    OnWave(19) {
        At(2501+551-198-100) Card(AKFD_35, 4, 3),//I

        At(2501+779) P(2,7),//B3

        At(2501+2301) P(5,7.525),//P5
    };
    for(int wave:{20})
    {
        AConnect(ATime(wave,0),[]{aIceFiller.Pause();});//暂停存冰
        AConnect(ATime(wave,1300),[]{aIceFiller.GoOn();});//继续
    }
    //w20
    OnWave(20) { 
        At(134-100-198) Card(AKFD_35, 4, 3),//I

        At(1325-240) P(2,9),//B2

        At(2301) N({{3, 8},{3, 7},{3, 6},{4, 7}}),//N
        At(2650) P(5,3),//d5


        At(2501+551-198-100) Card(AKFD_35, 4, 3),//I

        At(2501+779) P(2,7),//B3

        At(2501+2301) P(5,7.525),//P5
    };

}