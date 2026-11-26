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
        //ABC_12, // 冰车
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
        
        //ABJ_20, // 蹦极
    });
    ASelectCards({
        ANGT_30,   // 南瓜头

        AYMTS_34,  // 玉米投手
        ASYC_27,   // 三叶草
        ADC_21,    // 地刺

        AYTZD_2,   // 樱桃炸弹
        AHBLJ_20,  // 火爆辣椒
        AYMJNP_47, // 玉米炮
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
    //AGetInternalLogger()->SetLevel({});

    //C4u:I-B'NJ | I'B-AP"

    //自动存冰 先用模仿冰,从后往前使用
    //aIceFiller.Start({{1, 4}});
    //自动补南瓜
    aPlantFixer.Start(ANGT_30,{{1,3},{2,3},{4,1}},2000);

    //垫材逻辑
    ATimeline CCTV = {

    };
    OnWave(1_20) CCTV;

    //w1
    OnWave(1) {
        At(-599) Card(ANGT_30, 4, 1) & Card(ADC_21, 4, 1) & Card(AYMTS_34, 2, 2),
        At(751-599) Card(ADC_21, 4, 1),
        At(751+751-599) Card(ADC_21, 3, 2),
        At(3001-599) Card(ANGT_30, 5, 2) 
    };

    //w1-w9,w10-w19
    ATimeline JI_B11_N = { //1,5,(9前),12,16,(19后)
        At(225) J(1,9),
        At(226) I(2,9, false),//I

        At(1325) RP(1,1,3,7.6),//1-1 B"3

        At(2301) N({{2, 7}, {2, 8}}),//N2
    };
    ATimeline AI1_P1 = { //2,6,(9后),13,17,(20前)
        At(225) A(1,9),
        At(226) I(3,1),//I'

        At(976) Card(AYMTS_34, 2, 1),
        At(976+751) Card(AYMTS_34, 2, 2),
        At(2134) Shovel(1, 1) & Card(AYMJNP_47, 2, 1),
        At(2301) RP(1,1,4,7.5),//1-1 P4
    };
    ATimeline JI_B22_N = { //3,7,(10),14,18,(20后)
        At(225) J(2,9),
        At(226) I(1,9, false),//I

        At(1325) RP(2,1,3,7.4625),//2-1 B"3

        At(2301) N({{3, 7}, {3, 8}}),//N3
    };
    ATimeline AI1_P2 = { //4,8,11,15,(19前)
        At(225) A(1,9),
        At(226) I(3,1),//I'

        At(976) Card(AYMTS_34, 1, 1),
        At(976+751) Card(AYMTS_34, 1, 2),
        At(2134) Shovel(2, 1) & Card(AYMJNP_47, 1, 1),
        At(2301) RP(2,1,4,7.5),//2-1 P4
    };
    OnWave(1_9 % 1, 10_19 % 3) JI_B11_N | AI1_P1 | JI_B22_N | AI1_P2;


    //w9后
    OnWave(9) {
        At(2501+225) A(1,9),
        At(2501+226) I(3,1),//I'

        At(2501+976) Card(AYMTS_34, 2, 1),
        At(2501+976+751) Card(AYMTS_34, 2, 2),
        At(2501+2134) Shovel(1, 1) & Card(AYMJNP_47, 2, 1),
        At(2501+2301) RP(1,1,4,7),//1-1 P4
    };
    //w19后
    OnWave(19) {
        At(2501+225) J(1,9),
        At(2501+226) I(2,9, false),//I

        At(2501+1325) RP(1,1,3,7.6),//1-1 B"3

        At(2501+2301) N({{2, 7}, {2, 8}}),//N2
    };
    //w20
    OnWave(20) { //3
        At(225) A(2,9),
        At(226) I(3,1),//I'

        At(976) Card(AYMTS_34, 2, 1),
        At(976+751) Card(AYMTS_34, 2, 2),
        At(2134) Shovel(1, 1) & Card(AYMJNP_47, 2, 1),
        At(2301) RP(1,1,4,7.5),//1-1 P4


        At(2501+225) J(2,9),
        At(2501+226) I(1,9, false),//I

        At(2501+1325) RP(2,1,3,7.4625),//2-1 B"3

        At(2501+2301) N({{3, 7}, {3, 8}}),//N3
    };

}