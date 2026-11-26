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

        AGL_7,  // 橄榄
        AXC_15, // 小丑
        //ATL_22, // 投篮
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼
        
        //ABJ_20, // 蹦极
    });
    ASelectCards({
        AGJG_23,   // 高坚果
        AYMJNP_47, // 玉米炮
        AYMTS_34,  // 玉米投手
        ADC_21,    // 地刺

        AHY_16,    // 荷叶
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

    //1738连续冰波:
    //w1 N w2 PA_I  _601

    //w3～5 n_PP'_I   PP"_I   PA_I   _1738
    //w6～8   PP'_I n_PP"_I   PA_I   _1738

    //w9   nPP' PP" PA_I   _1738 _31
    //-----------------------------
    //w10  N  _1150
    //w11  PP'_I  _601

    //w12～14 PP"_I PA_I n_PP'_I   _1738
    //w15～17 PP"_I PA_I   PP'_I   _1738
    //w18   n_PP"_I                _1738

    //w19 nPA PP'n PP"_I     _1738
    //w20 NPA PP' PP"       _1738


    //自动存冰 先用模仿冰,从后往前使用
    aIceFiller.Start({{3, 3}, {3, 4}, {2, 5}, {3, 8}, {1, 5}});
    //2门炮列表
    aCobManager.SetList({{3,1},{4,1}});

    //w1
    OnWave(1) {
        At(-599) Card(AHY_16,3,8),
        At(-599+751) Card(AHY_16,4,8),

        At(-599) Card(AHMG_15,3,5),
        At(-599) Card(AGJG_23,1,3),
        At(-599) Card(ADC_21,6,2),
        At(-599+751) Card(ADC_21,5,2),

        At(-599) Card(AYMTS_34,1,2),
        At(-599+751) Card(AYMTS_34,6,5),

    };

    //5列n
    OnWave(3,7,14) {
        At(11+751-198-100) Card(AKFD_35,{{3, 5}, {4, 5}, {2, 6}}),
    };
    OnWave(18) {
        At(11+751-198-100) Card(AKFD_35,{{3, 5}}),
    };

    //w3-w8,w12-w18
    ATimeline PP1_I = {
        At(1538) P(2,8.5),//2
        At(1538) RP(4,3,5,8.5),//5
        At(1538-373+206) Shovel(4, 3, AYMJNP_47) & Card(AYMTS_34, 4, 3),
        At(1538-373+206+751) Card(AYMTS_34, 4, 4) & Card(AYMJNP_47, 4, 3),
    };
    ATimeline PP11_I = {
        At(1538) P(2,8.5),//2
        At(1538) RP(4,3,5,8.5),//5
    };
    ATimeline PA_I = {
        At(1538) P(2,8.5),//2
        At(1538) A(5,8),//5
    };
    OnWave(3_8 % 1, 12_18 % 2) PP1_I | PP11_I | PA_I;

    //I w2w11,w9w19
    OnWave(2,11) {
        At(601+1) I(),
    };
    OnWave(9,19) {
        At(5245+200) I(),
    };
    //减速i3 w3~w8 w12~w18
    for (auto wave : {3,4,5,6,7,8 , 12,13,14,15,16,17,18})  
    {
        AConnect(ATime(wave,1538+211-298),[]{//i3
            aIceFiller.Coffee();
            ASetPlantActiveTime(AICE_SHROOM, 298);
        });
    }

    //w1,w2,w10,w11
    OnWave(1) { //2
        At(341-198-100) Card(AKFD_35,{{3, 9}, {4, 9}}),
    };
    OnWave(2) { //2
        At(341) P(2,8.5),//2
        At(341) A(5,9),//5
    };
    OnWave(10) { //2
        At(1150-198-100) Card(AKFD_35,{{3, 9}, {4, 9}}),
    };
    OnWave(11) { //2
        At(359) P(2,8.5),//2
        At(359) RP(4,3,5,8.5),//5
        At(359-373+206) Shovel(4, 3, AYMJNP_47) & Card(AYMTS_34, 4, 3),
        At(359-373+206+751) Card(AYMTS_34, 4, 4) & Card(AYMJNP_47, 4, 3),
    };

    //w9
    OnWave(9) { //2
        At(1538-198-100) Card(AKFD_35,{{3, 7}, {4, 7}}),

        At(1538) P(2,8.5),//2
        At(1538) RP(4,3,5,8.5),//5
        At(1538-373+206) Shovel(4, 3, AYMJNP_47) & Card(AYMTS_34, 4, 3),
        At(1538-373+206+751) Card(AYMTS_34, 4, 4) & Card(AYMJNP_47, 4, 3),

        At(1738+1538) P(2,7),//2
        At(1738+1538) RP(4,3,5,7),//5

        At(1738+1738+1538) P(5,6),//2
        At(4801) A(1,6),//5
    };

    //w19
    OnWave(19) { //2

        At(1538) P(2,8.5),//2
        At(1538) A(5,8),//5

        At(1538-198-100) Card(AKFD_35,{{3, 7}, {4, 7}}),

        At(1738+1538) P(2,8),//2
        At(1738+1538) RP(4,3,5,8),//5
        At(1738+1538-373+206) Shovel(4, 3, AYMJNP_47) & Card(AYMTS_34, 4, 3),
        At(1738+1538-373+206+751) Card(AYMTS_34, 4, 4) & Card(AYMJNP_47, 4, 3),

        At(1738+1738+1538) P(2,7),//2
        At(1738+1738+1538) RP(4,3,5,7),//5
    };

    //w20
    OnWave(20) { //3
        At(1538) P(2,8.5),//2
        At(1538) A(5,8),//5

        At(1538-198) Card(AKFD_35,{{3, 9}, {4, 9}}),

        At(1738+1538) P(2,8),//2
        At(1738+1538) RP(4,3,5,8),//5
        At(1738+1538-373+206) Shovel(4, 3, AYMJNP_47) & Card(AYMTS_34, 4, 3),
        At(1738+1538-373+206+751) Card(AYMTS_34, 4, 4) & Card(AYMJNP_47, 4, 3),

    };

}