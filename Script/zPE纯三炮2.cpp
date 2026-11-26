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


    ASetZombies({
        ABC_12, // 冰车
        AKG_17, // 矿工
        //AQQ_16, // 气球

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

        APJ_0,  // 普僵
        ALZ_2,  // 路障
        ATT_4,  // 铁桶

        //ABJ_20, // 蹦极
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
    //aIceFiller.Start({{4, 7}});
    //3门炮列表
    aCobManager.SetList({{3,1},{4,1},{4,5}});
    // 脚本重新载入模式  
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    //C4u:I-N/B-P/A I-B/-J/P

    //垫材逻辑
    ATimeline CCTV = {
        At(2302) Card(AHY_16, 3, 8),
    };
    OnWave(1_20) CCTV;

    //w1
    OnWave(1) {
        At(-599) Card(AGJG_23, 1, 1),
        At(3001-599) Card(AGJG_23, 1, 2) ,
    };

    //w1-w9,w10-w19
    ATimeline I_B3_J1P5 = { 
        At(134) I(4, 7, false),//I

        At(915) P(3,8.7375),//B3

        At(2301) J(1,5),//J1
        At(2301) P(5,7.55),//P5

        At(2501+134) I(4, 7),//I'
    };
    ATimeline I_NB5_P2A5 = {
        At(136) Shovel(4, 7, AHY_16),
        At(886) N({{3, 3},{3, 4},{4, 3},{4, 4}}),//N

        At(1325) P(5,7.55),//B5
        At(1340) Card(AHY_16, 4, 7),

        At(2301) P(2,7.55),//P2
        At(2301) A(5,8),//A5
    };
    OnWave(1_9 % 1, 11_19 % 2) I_B3_J1P5 | I_NB5_P2A5;


    //w9后
    OnWave(9) {
        At(2501+136) Shovel(4, 7, AHY_16),
        At(2501+886) N({{3, 3},{3, 4},{4, 3},{4, 4}}),//N

        At(2501+1325) P(5,7.55),//B5
        At(2501+1340) Card(AHY_16, 4, 7),

        At(2501+2301) P(2,6.5),//P2
        At(2501+2301) A(5,7),//A5
    };
    //w10
    OnWave(10) {
        At(134) I(4, 7, false),//I

        At(915) P(3,8.7375),//B3

        At(2301) J(1,5),//J1
        At(2301) P(5,7.55),//P5

        At(2501+134) I(4, 7),//I'
    };
    //w19后
    OnWave(19) {
        At(2501+134) I(4, 7, false),//I

        At(2501+915) P(2,7),//B3

        At(2501+2301) J(1,5),//J1
        At(2501+2301) P(5,7),//P5

        At(5245+134) I(4, 7),//I'
    };
    //w20
    OnWave(20) {
        At(136) Shovel(4, 7, AHY_16),
        At(886) N({{3, 3},{3, 4},{4, 3},{4, 4}}),//N

        At(1325-243) P(5,9),//B5
        At(1340) Card(AHY_16, 4, 7),

        At(2301) P(2,7),//P2
        At(2301) A(5,8),//A5

        At(2501+134) I(4, 7, false),//I
    };

}