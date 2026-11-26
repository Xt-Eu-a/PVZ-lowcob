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
        //AHT_14, // 海豚

        AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼
        
        ABJ_20, // 蹦极
    });
    ASelectCards({
        ADPG_10,   // 大喷A
        AYZBHS_37, // 叶子保护伞A
        ASYC_27,   // 三叶草B
        AHBSS_5,   // 冰豆B


        ANGT_30,   // 南瓜头

        AHMG_15,   // 毁灭菇
        AKFD_35,   // 咖啡豆

        ACHERRY_BOMB,  // 樱桃炸弹
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
    });

    /*At(ATime(1, -599))[] {
        AAverageSpawn();
        AMaidCheats::Dancing();
        aPlantFixer.Start(ANGT_30, {{4, 4}, {3, 4}}, 1332);
    };*/

    //C4u:BI-PP BIn-AP
    //w1 N w2 PA_I  _601

    // 脚本重新载入模式  
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    //关闭报错
    AGetInternalLogger()->SetLevel({});

    //自动存冰 先用模仿冰,从后往前使用
    aIceFiller.Start({{1, 4}});
    //自动补南瓜
    aPlantFixer.Start(ANGT_30,{{1,3},{1,4},{2,3},{2,4},{3,3},{3,4},{4,2},{4,1}},2500);

    //垫材逻辑
    ATimeline CCTV = {
        At(148) Card(ADPG_10,1,9) & Card(AYZBHS_37,2,9), //C1大喷菇A1保护伞A2
        At(200) Shovel(1,9) & Shovel(2,9),

        At(1063) Card(ADPG_10,1,9) & Card(AYZBHS_37,2,9),//C2大喷菇A1保护伞A2
        At(1214) Shovel(1,9) & Shovel(2,9),

        At(1480) Card(ASYC_27,1,9) & Card(AHBSS_5,2,9),  //C3三叶草B1寒冰豆B2
        At(1488) Shovel(1,9) & Shovel(2,9),

        At(1897) Card(ADPG_10,1,9) & Card(AYZBHS_37,2,9),//C4大喷菇A1保护伞A2
        At(1901) Shovel(1,9) & Shovel(2,9),

        At(2314) Card(ASYC_27,1,9) & Card(AHBSS_5,2,9),  //C5三叶草B1寒冰豆B2
        At(2316) Shovel(1,9) & Shovel(2,9),
    };
    OnWave(1_9 % 1, 11_19 % 1,20) CCTV;


    //w1-w8,w11-w18
    ATimeline BI_PP = {
        At(321) P(2,8.2),//B2
        At(321) I(),//I

        At(2301) P(2,8) & P(4,7.4) & Trig(),//P2P4
    };
    ATimeline BIn_AP = {
        At(321) P(2,8.2),//B2
        At(321) I(),//I

        At(321+751) N({{5, 2}, {5, 3}, {5, 4}, {4, 4}}),//n

        At(2301) A(2,8) & P(4,7.4) & Trig(),//A2P4
    };
    OnWave(1_8 % 1, 11_18 % 1) BI_PP | BIn_AP;

    //w9w19
    OnWave(9,19) {
        At(321) P(2,9),//B2
        At(321) I(),//I

        At(2301) P(2,8) & P(4,7.4),//P2P4

        At(2501+321) P(2,8.2),//B2
        At(2501+321) I(),//I

        At(2501+321+751) N(3,7),//n
        At(2501+2301) P(4,7.4),//P2P4
    };
    //w10
    OnWave(10) {
        At(445) Card(ASYC_27,1,9) & Card(AHBSS_5,2,9),  //C5三叶草B1寒冰豆B2
        At(540) Shovel(1,9) & Shovel(2,9),

        At(359) A(2,9) & P(4,9),//A2P4
    };

    //w20
    OnWave(20) { //3
        At(359) A(2,9) & P(4,9),//A2P4
        At(360) I(),//I
        At(2501) I(),//I
        At(2501+321+751) N(3,8),//n
    };

}