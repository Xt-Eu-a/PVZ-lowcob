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



    ASetZombies({ //九怪极红
        ABC_12, // 冰车
        AKG_17, // 矿工
        //AQQ_16, // 气球

        AFT_21, // 扶梯
        ATT_18, // 跳跳
        AHT_14, // 海豚

        AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼
        
        ABJ_20, // 蹦极
    });
    ASelectCards({
        AGJG_23,    // 高坚果
        ASYC_27,   // 三叶草

        AHY_16,    // 荷叶
        ADC_21,    // 地刺
        ADS_36,    // 大蒜

        AYTZD_2,   // 樱桃炸弹
        AHBLJ_20,  // 火爆辣椒
        AHMG_15,   // 毁灭菇

        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
    });

    /*At(ATime(1, -599))[] {
        AAverageSpawn();
        AMaidCheats::Dancing();
        aPlantFixer.Start(ANGT_30, {{4, 4}, {3, 4}}, 1332);
    };*/


    // 脚本重新载入模式  
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 关闭报错
    AGetInternalLogger()->SetLevel({});

    //C4u:I'-Bd-ND/cNd I-Bd-PD/cPJA

    //自动存冰 先用模仿冰,从后往前使用
    //aIceFiller.Start({{1, 4}});
    //自动补南瓜
    aPlantFixer.Start(AGJG_23,{{4,5},{3,6}},5000);

    //垫材逻辑 230可拦，249有伤，285d生效，延迟36cs~55cs，2134垫，延迟40cs，相当于245生效
    ATimeline CCTVA = {
        At(292) Card(ADC_21, 5, 9),
        At(339) Shovel(5, 9),

        At(466) Card(ADS_36, 2, 7),
        At(800) Shovel(2, 7),

        At(570) Card(ASYC_27, 5, 9),

        At(1321) Card(ASYC_27, 2, 7),

        At(1574) Card(ADC_21, 5, 9),
        At(1840) Shovel(5, 9),

        At(2235) Card(ASYC_27, 2, 7),
        At(2235+267) Shovel(2, 7),

        At(2462) Card(ADS_36, 5, 6),
    };
    ATimeline CCTVN = {
        At(292) Card(ADC_21, 5, 9),
        At(339) Shovel(5, 9),

        At(632) Card(ASYC_27, 2, 7),
        At(800) Shovel(2, 7),

        At(713) Card(ADS_36, 5, 9),
        At(950) Shovel(5, 9),

        At(1383) Card(ASYC_27, 2, 7),

        At(1526) Card(ADC_21, 5, 9),
        At(1790) Shovel(5, 9),
        At(1464) Card(ADS_36, 5, 8),
        At(1730) Shovel(5, 8),

        At(2134) Card(ASYC_27, 5, 9),

        At(2215) Card(ADS_36, 2, 7),
        At(2215+267) Shovel(2, 7),
    };
    OnWave(1_9 % 1,10_19 % 1) CCTVA | CCTVN;

    ATimeline HY = {
        At(660) Card(AHY_16,4,8),
        At(1411) Card(AHY_16,4,7),
    };
    OnWave(2_20) HY;

    //w1
    OnWave(1) {
        At(-599) Card(AHY_16, 4, 5),
        At(152) Card(AHY_16, 3, 8),
        At(903) Card(AHY_16, 3, 7),
        At(1654) Card(AHY_16, 3, 6),
        At(2405) Card(AHY_16, 3, 6),

        At(-205) N(2,4),//N
    };

    //w1-w9,w11-w19
    ATimeline I_Bd_PDlcPJA = { //1,3,5,7,9前,(10),12,16,18,(19后),(20后)
        At(96) I(5,9,false),//I

        At(1214) P(2,7.8875),//B
        At(1521) P(1,2.5),//d

        At(2301) P(2,8),//P
        At(2301) P(5,7.55),//P
        At(2301+110) J(5,5),//J

        At(2301+197) P(1,5.2875),//D
        At(2301+110+233) A(6,3),//A

        At(2501+96) I(1,1),//I'
    };
    ATimeline Ii_Bd_NDlcNd = { //2,4,6,8,(9后),11,13,15,17,19前,(20前)
        At(1214) P(2,7.8875),//B
        At(1521) P(1,2.5),//d

        At(2301) N({{3, 7}, {3, 8}, {4, 7}, {4, 8}}),//N

        At(2301+197) P(1,5.2875),//D
        At(2301+285) P(5,3.2),//d
    };
    OnWave(1_9 % 1, 11_19 % 2) I_Bd_PDlcPJA | Ii_Bd_NDlcNd;


    //w9后
    OnWave(9) {
        At(2501+1214) P(2,7.8875),//B
        At(2501+1214+212) P(1,7),//D

        At(2501+2301) N({{3, 7}, {3, 8}, {4, 7}, {4, 8}}),//N

        At(2501+2301+197) P(5,7.55),//S
        At(2501+2301+285) P(5,3.2),//d

        At(2501+632) Card(ASYC_27, 2, 7),
        At(2501+800) Shovel(2, 7),
        At(2501+1383) Card(ASYC_27, 2, 7),
        At(2501+2215) Card(ASYC_27, 2, 7),
        At(2501+2215+267) Shovel(2, 7),
    };   
    //w10
    OnWave(10) {
        At(96) I(1,1,false),//I

        At(1214) P(2,7.8875),//B
        At(1521) P(1,2.5),//d

        At(2301) P(2,8),//P
        At(2301) P(5,7.55),//P
        At(2301+110) J(5,5),//J

        At(2301+197) P(1,5.2875),//D
        At(2301+110+233) A(6,3),//A

        At(2501+96) I(1,1),//I'
    }; 
    //w19后
    OnWave(19) {
        At(2501+96) I(1,1,false),//I

        At(2501+1214) P(2,7.8875),//B
        At(2501+1214+212) P(1,7),//D

        At(2501+2301) P(2,8),//P

        At(2501+2301) P(5,7.55),//P
        At(2501+2301+110) J(5,5),//J
        At(2501+2301+197) P(5,7),//D
        At(2501+2301+110+233) A(6,3),//A

        At(5245+96) I(1,1),//I'


        At(2501+466) Card(ADS_36, 2, 7),
        At(2501+800) Shovel(2, 7),
        At(2501+1321) Card(ASYC_27, 2, 7),
        At(2501+2235) Card(ASYC_27, 2, 7),
    };
    //w20
    OnWave(20) {
        At(1070) P(2,9),//B
        At(1430) P(1,2.5),//d

        At(2301) P(2,8),//P
        At(2301) P(5,7.55),//P
        At(2301+200) N(2,4),//N

        At(2501+96) I(1,1,false),//I

        
        At(292) Card(ADC_21, 5, 9),
        At(339) Shovel(5, 9),

        At(632) Card(ASYC_27, 2, 7),
        At(800) Shovel(2, 7),

        At(713) Card(ADS_36, 5, 9),
        At(950) Shovel(5, 9),

        At(1383) Card(ASYC_27, 2, 7),

        At(1526) Card(ADC_21, 5, 9),
        At(1790) Shovel(5, 9),
        At(1464) Card(ADS_36, 5, 8),
        At(1730) Shovel(5, 8),

        At(2215) Card(ADS_36, 2, 7),
        At(2215+267) Shovel(2, 7),
    };

}