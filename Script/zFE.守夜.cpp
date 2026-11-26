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
        //AQS_11, // 潜水

        AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼

        //APJ_0,  // 普僵
        //ALZ_2,  // 路障
        ATT_4,  // 铁桶

        ABJ_20, // 蹦极
    });
    ASelectCards({
        ANGT_30,   // 南瓜
        AWG_17,    // 窝瓜
        ADS_36,    // 大蒜
        ADC_21,    // 地刺

        AHY_16,    // 荷叶
        AHMG_15,   // 毁灭菇

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
    //自动补南瓜
    aPlantFixer.Start(ANGT_30,{{1,4},{2,4},{5,4}},1500);
    //3门炮列表
    aCobManager.SetList({{2,5},{3,1},{4,2}});
    // 脚本重新载入模式  
    //ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 关闭报错
    //AGetInternalLogger()->SetLevel({});

    //C4u:3复用2：I-B683-AP1832 I1-B977-JP2126 B949-N1243（2032,2326,1443）
    //循环长度5801，3炮间距2326


    //垫材逻辑
    ATimeline CCTV = {
        At(339) Card<500>(ADC_21, 2, 9),
        At(1090) Card<500>(ADC_21, 5, 8),
    };
    OnWave(1,2,4,5,7,8,11,12,14,15,17,18) CCTV;

    ATimeline CCTV1 = {
        At(280) Card(ADC_21, 2, 9),
        At(350) Shovel(ADC_21, 2, 9),
        At(1031) Card(ADC_21, 5, 8),
        At(1200) Shovel(ADC_21, 2, 9),
    };
    OnWave(3,6,13,16) CCTV1;
    
    //w1
    OnWave(1) {
        At(-599) Card({AHY_16,ADS_36}, 3, 5),
        At(751-599) Card(AHY_16, 4, 6),
        At(-599) Card({ADC_21,ANGT_30}, 6, 4),
    };

    //w1-w8,w11-w18
    ATimeline I_B683_AP1832 = { 
        At(225) I(1, 2, false),//I

        At(683) P(3,8.7375),//B3

        At(1832) A(2,8),//A2
        At(1832) P(5,8.025),//P5

        At(2032+73) I(1, 2),//I'
    };
    ATimeline I1_B977_JP2126 = {
        At(977) P(3,8.7375),//B3

        At(2126) J(1,1),//J1
        At(2126) P(5,7.7125),//P2
    };
    ATimeline B949_N1243 = {
        At(949) P(2,7),//B5

        At(1243) N({{3, 7},{4, 8}}),//N
    };
    OnWave(1_8 % 1, 11_18 % 1) I_B683_AP1832 | I1_B977_JP2126 | B949_N1243;


    //w9 NP I-P-A-P I-PJ
    OnWave(9) {
        At(443) N(4, 9),//N
        At(949) P(2,8.5),//P2

        At(868) I(1, 2, false),//I
        At(2126) P(5,7.5),//P5
        At(2475) A(2,8),//A2
        At(3275) P(5,7),//P5

        At(2869) I(1, 2),//I'
        At(4424) P(5,6.5),//P5
    };
    //w10 N
    OnWave(10) {
        At(395) N(3, 8),//N
    };
    //w19 NP I-P-A-P I-PJ
    OnWave(19) {
        At(443) N(4, 9),//N
        At(949) P(2,8.5),//P2

        At(868) I(1, 2, false),//I
        At(2126) P(5,7.5),//P5
        At(2475) A(2,8),//A2
        At(3275) P(5,7),//P5

        At(2869) I(1, 2),//I'
        At(5245+250) P(3,7.5875),//P5

    };
    //w20
    OnWave(20) {
        At(395) N(3, 8),//N

        At(357) P(2,9),//P2

        At(610) I(1, 2, false),//I
        At(1506) P(5,8.5),//P5
        At(2231) A(2,8),//A2
        At(3726) P(5,7),//P5

        At(2625) I(1, 2),//I'
    };

}