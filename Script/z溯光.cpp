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



    ASetZombies({ //11怪极红
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
        ADC_21,    // 地刺
        AHP_33,    // 花盆
        ASYC_27,   // 三叶草
        ADZH_6,    // 大嘴花

        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM

        AYTZD_2,   // 樱桃炸弹
        AHBLJ_20,  // 火爆辣椒
        AHMG_15,   // 毁灭菇
        AHY_16,    // 荷叶
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

    //C4u:I-B-Pd/PJA | I'-B-Nd/NSd

    //自动存冰 先用模仿冰,从后往前使用
    //aIceFiller.Start({{1, 4}});
    //自动补南瓜
    //aPlantFixer.Start(ANGT_30,{{1,3},{2,3},{4,1}},2000);

    //垫材逻辑
    ATimeline CCTV = {
        At(292) Card(ADC_21, 1, 9),//地刺轧车
        At(339) Shovel(1, 9),

        At(1638) Card(ADC_21, 1, 9),//地刺扎篮球,26cs后生效
        At(1685) Shovel(1, 9),

        At(851) Card(AHP_33, 1, 9),//花盆垫丑
        At(1117) Shovel(1, 9),
        At(1464) Card(ASYC_27, 1, 8),//三叶草垫丑，小丑1666-1464=202走出8列垫材范围
        At(1664) Shovel(1, 8),
        At(1665) Card(AHP_33, 1, 8),//花盆垫丑
        At(1800) Shovel(1, 8),//1730落槌

        At(2215) Card(ASYC_27, 5, 5),//三叶草2215垫快扶梯179(130+),2394放慢扶梯
        At(2394) Shovel(5, 5),


        At(713) Card(ASYC_27, 2, 8),//三叶草垫巨人
        At(761) Shovel(2, 8),
        At(1170) Card(ADZH_6, 2, 8),//大嘴花垫巨人
        At(1436) Shovel(2, 8),


        At(418) Shovel(2, 2),
        At(419) Card(ADZH_6, 2, 2),//大嘴花
        At(2415) Shovel(2, 3),
        At(2416) Card(AHP_33, 2, 3),//花盆
    };
    OnWave(1_7,9_14,16_20) CCTV;
    ATimeline CCTV1 = {
        At(292) Card(ADC_21, 1, 9),//地刺轧车
        At(339) Shovel(1, 9),
        At(1043) Card(ADC_21, 5, 8),//地刺轧车
        At(1090) Shovel(5, 8),
        At(1794) Card(ADC_21, 1, 9),//地刺扎篮球
        At(1842) Shovel(1, 9),

        At(851) Card(AHP_33, 1, 9),//花盆垫丑
        At(1117) Shovel(1, 9),
        At(1464) Card(ASYC_27, 1, 8),//三叶草垫丑，小丑1666-1464=202走出8列垫材范围
        At(1664) Shovel(1, 8),

        At(713) Card(ASYC_27, 2, 8),//三叶草垫巨人
        At(761) Shovel(2, 8),
        At(1602) Card(AHP_33, 2, 7),//花盆垫巨人
        At(2000) Shovel(2, 7),

        At(2215) Card(ASYC_27, 5, 5),//三叶草2215垫快扶梯179(130+),2394放慢扶梯
        At(2394) Shovel(5, 5),
        
        At(418) Shovel(2, 2),
        At(419) Card(ADZH_6, 2, 2),//大嘴花
        At(2415) Shovel(2, 3),
        At(2416) Card(AHP_33, 2, 3),//花盆
    };
    OnWave(8,15) CCTV1;
    //w1
    OnWave(1) {
        At(-599) Card(ADZH_6, 2, 3),//大嘴花
    };

    //w1-w9,w10-w19
    ATimeline I_B_PdPJA_I1 = { //1,3,5,7,9前,10,12,14,16,18,(19后),(20后)
        At(22) I(2,4, false),//2I

        At(1050) P(3,8.75),//3B

        At(2301) P(1,7.55),//1P
        At(2523) A(1,3),//1A 扶梯1286

        At(2301) P(5,7.55),//5P
        At(2301) J(5,2),//5J
        At(2301+206) P(5,3.525),//5d

        At(2501+22) I(2,4),//I'
    };
    ATimeline _B_NdNSd = { //2,4,6,8,(9后),11,13,15,17,19前,(20前)
        At(1050) P(3,8.75),//3B

        At(2301) N({{3, 8}, {3, 9}, {3, 7}, {4, 7}}),//N
        At(2523) P(1,3.0875),//1d

        At(2301) P(5,7.55),//5S
        At(2301+206) P(5,3.525),//5d
    };
    OnWave(1_9 % 1, 10_19 % 1) I_B_PdPJA_I1 | _B_NdNSd;


    //w9后
    OnWave(9) {
        At(2501+1050) P(2,8.75),//2B

        At(2501+2301) N({{3, 8}, {3, 9}, {3, 7}, {4, 9}}),//N
        At(2501+2523) P(1,3.0875),//1d

        At(2501+2301) P(5,7.55),//5S
        At(2501+2301+206) P(5,3.525),//5d
    };
    //w19后
    OnWave(19) {
        At(2501+22) I(2,4, false),//2I

        At(2501+1050) P(2,8.75),//2B

        At(2501+2301) P(1,7.55),//1P
        At(2501+2523) A(1,3),//1A

        At(2501+2301) P(5,7.55),//5P
        At(2501+2301) J(5,2),//5J
        At(2501+2301+206) P(5,3.525),//5d

        At(5245+22) I(2,4),//I'
    };
    //w20
    OnWave(20) { //3
        At(1050) P(3,8.75),//3B

        At(2301) N({{3, 8}, {3, 9}, {3, 7}, {4, 9}}),//N
        At(2523) P(1,3.0875),//1d

        At(2301) P(5,7.55),//5S
        At(2301+206) P(5,3.525),//5d


        At(2501+22) I(2,4, false),//2I

        At(2501+1050) P(2,8.75),//2B

        At(2501+2301) P(1,7.55),//1P
        At(2501+2523) A(1,3),//1A

        At(2501+2301) P(5,7.55),//5P
        At(2501+2301) J(5,2),//5J
        At(2501+2301+206) P(5,3.525),//5d
    };

}