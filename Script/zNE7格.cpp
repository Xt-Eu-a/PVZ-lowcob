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
        //ABC_12, // 冰车
        AKG_17, // 矿工
        AQQ_16, // 气球

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
        ATDDL_4,   // 土豆雷
        AYMJNP_47, // 玉米炮

        AYMTS_34,  // 玉米投手
        AXRZ_26,   // 仙人掌
        ANGT_30,   // 南瓜头

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
    //ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 关闭报错
    //AGetInternalLogger()->SetLevel({});

    //C4u:CB"_N | AJ_I'_c_P'd_I

    //自动存冰 先用模仿冰,从后往前使用
    //aIceFiller.Start({{1, 4}});
    //自动补南瓜
    aPlantFixer.Start(ANGT_30,{{1,3},{5,2},{2,3}},2000);

    //垫材逻辑
    ATimeline CCTV = {
        At(-599) Card(AYMTS_34,2,2),
        At(751-599) Card(AYMTS_34,2,4),
        At(751+751-599) Card(AYMTS_34,2,5),
    };
    OnWave(1) CCTV;

    //w1-w9,w10-w19
    ATimeline AJ_I1_c_P2d1 = { //4,8,11,15,（19前）
        At(200) A(4, 3),//A
        At(225) J(1, 6),//J
        At(528) I(1, 3),//I'

        At(1850) Card(ATDDL_4,1,3),//1-3 c

        At(2301) RP(1,4,4,7.475),//1-4 P4铲种
        At(2301-373+206) Shovel(1, 4) & Card(AYMTS_34, 1, 4),
        At(2301-373+206+751) Card(AYMTS_34, 1, 5) & Card(AYMJNP_47, 1, 4),

        At(2501+200) RP(1,1,4,3.0875),//1-1 d4
    };
    ATimeline I_CB22N = { //1,5,（9前）,12,16,（19后）
        At(158) I(2, 9, false),//I

        At(2000) RP(1,4,2,7.275),//1-4 B2
        At(2301) N({{2, 9}, {2, 8}, {2, 7}, {3, 9}}),//N
    };
    ATimeline AJ_I1_c_P1d2 = { //2,6,（9后）,13,17,（20前）
        At(200) A(4, 3),//A
        At(225) J(1, 6),//J
        At(528) I(1, 3),//I'

        At(1850) Card(ATDDL_4,1,3),//1-3 c

        At(2301) RP(1,1,4,7.475),//1-1 P4铲种
        At(2301-373+206) Shovel(1, 1) & Card(AYMTS_34, 1, 1),
        At(2301-373+206+751) Card(AYMTS_34, 1, 2) & Card(AYMJNP_47, 1, 1),

        At(2501+200) RP(1,4,4,3.0875),//1-4 d4
    };
    ATimeline I_CB11N = { //3,7,(10),14,18,（20后）
        At(158) I(2, 9, false),//I

        At(2000) RP(1,1,2,7.275),//1-1 B2
        At(2301) N({{2, 9}, {2, 8}, {2, 7}, {3, 9}}),//N
    };

    OnWave(1_9 % 1, 10_19 % 3)  AJ_I1_c_P2d1 | I_CB22N | AJ_I1_c_P1d2 | I_CB11N;




    //w9后
    OnWave(9) {
        At(2501+2200) RP(3,2,2,5.5),//3-2 B2铲种
        At(2501+2200-373+206) Shovel(3, 2) & Card(AYMTS_34, 3, 2),
        At(2501+2200-373+206+751) Card(AYMTS_34, 3, 3) & Card(AYMJNP_47, 3, 2),

        At(2501+2301) N({{3, 8}, {2, 7}, {2, 8}, {2, 6}}),//N
        At(2501+2401) J(3,7),

        At(5245+285) I(2, 1),//I'
    };
    //w10

    //w19后
    OnWave(19) {
        At(2501+1224) RP(3,2,4,7),//3-2 B4

        At(2501+2301) RP(3,4,2,7) & A(4,7),//3-4 P2/A4

        At(5245+285) I(2, 1, false),//I
    };
    //w20后
    OnWave(20) { //3
        At(2200) RP(3,2,2,7),//3-2 B2铲种
        At(2200-373+206) Shovel(3, 2) & Card(AYMTS_34, 3, 2),
        At(2200-373+206+751) Card(AYMTS_34, 3, 3) & Card(AYMJNP_47, 3, 2),

        At(2301) N({{3, 8}, {2, 7}, {2, 8}, {2, 6}}),//N
        At(2401) J(3,7),

        At(2501+285) I(2, 1),//I'


        At(2501+1224) RP(3,4,4,7),//3-4 B4

        At(2501+2301) RP(3,2,2,7) & A(4,7),//3-2 P2 A4
    };

}