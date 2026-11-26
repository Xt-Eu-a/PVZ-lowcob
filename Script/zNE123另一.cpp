#include <avz.h>
#include <dsl/shorthand.h>

static bool Paused = false;
static bool PausedSlowed = false;


void AScript()
{
    // 回档0.1s
    AConnect(VK_BACK, [] {
        Paused = true;
        PausedSlowed = false;
        ASetAdvancedPause(Paused, false, 0);
        aReplay.ShowOneTick(aReplay.GetEndIdx() - 1 >= 0 ? aReplay.GetRecordIdx() - 1 : aReplay.GetStartIdx());
    });
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
        
        ABJ_20, // 蹦极

    });
    ASelectCards({

        AYMJNP_47, //玉米炮
        AYMTS_34,  //玉米投手

        ADC_21,    //地刺
        ADZH_6,    //大嘴
        AWG_17,    //窝瓜

        ACHERRY_BOMB,  // 樱桃炸弹
        AHBLJ_20,  //火爆辣椒
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
        AHMG_15,   // 毁灭菇
    });

    /*At(ATime(1, -599))[] {
        AAverageSpawn();
        AMaidCheats::Dancing();
        aPlantFixer.Start(ANGT_30, {{4, 3}, {2, 1}, {2, 4}, {4, 4}, {3, 4}}, 1332);
    };*/

    //C4u:IP'-PA I1B_JNd"

    //w1-w8,w10-w18
    ATimeline I_JPAI1 = {
        At(89) I(1, 2, false),
        At(2301) J(3, 1) & P(4, 7.725) & Trig(),
        At(2301+289+200) A(4, 3),

        At(2501+89) I(1, 2),
    };
    ATimeline B_Nd11 = {
        At(1324) P(2, 7.875),
        At(2301) N({{2, 7}, {2, 8}, {3, 9}, {3, 8}})  & Trig(), 
        At(2301+289+200) P(4, 3.0875),
    };
    OnWave(1_8 % 1, 10_18 % 1) I_JPAI1 | B_Nd11;

    ATimeline P1_1 = {
        At(1324) P(1, 8.5125),
        At(1324-373+206) Shovel(1, 4) & Card(AYMTS_34, 1, 4),
        At(1324-373+206+751) Card(AYMTS_34, 1, 5) & Card(AYMJNP_47, 1, 4),
    };
    ATimeline P1_2 = {
        At(1324) P(1, 8.5125),
        At(1324-373+206) Shovel(2, 4) & Card(AYMTS_34, 2, 4),
        At(1324-373+206+751) Card(AYMTS_34, 2, 5) & Card(AYMJNP_47, 2, 4),
    };
    ATimeline P1_3 = {
        At(1324) P(1, 8.5125),
        At(1324-373+206) Shovel(3, 4) & Card(AYMTS_34, 3, 4),
        At(1324-373+206+751) Card(AYMTS_34, 3, 5) & Card(AYMJNP_47, 3, 4),
    };
    OnWave(1,7,12,18) P1_1;
    OnWave(3,14) P1_2;
    OnWave(5,10,16) P1_3;


    //w9
    OnWave(9) { //2
        At(89) I(1, 2, false),
        At(1324) P(1, 8.5125),
        At(1324-373+206) Shovel(2, 4) & Card(AYMTS_34, 2, 4),
        At(1324-373+206+751) Card(AYMTS_34, 2, 5) & Card(AYMJNP_47, 2, 4),

        At(2301) J(3, 1) & P(4, 7.725),
        At(2301+289+200) A(4, 3),

        At(2501+89) I(1, 2),

        At(2501+1324) P(2, 7.875),
        At(2501+2301) N({{2, 7}, {2, 8}, {3, 9}, {3, 8}}), 
        At(2501+2301+289+200) P(4, 3.0875),
    };

    //w19 注意一下樱桃漏小鬼
    OnWave(19) { //2
        At(1324) P(2, 7.875),
        At(2301) N({{2, 7}, {2, 8}, {3, 9}, {3, 8}}), 
        At(2301+289+200) P(4, 3.0875),

        At(2501+89) I(1, 2, false),
        At(2501+1324) P(1, 8.5125),
        At(2501+1324-373+206) Shovel(2, 4) & Card(AYMTS_34, 2, 4),
        At(2501+1324-373+206+751) Card(AYMTS_34, 2, 5) & Card(AYMJNP_47, 2, 4),

        At(2501+2301) J(3, 1) & P(4, 7.725),
        At(2501+2301+289+200) A(4, 3),

        At(5245+89) I(1, 2),
    };

    //w20
    OnWave(20) { //3
        At(1022) P(2, 8.5),
        At(2301) N({{2, 7}, {2, 8}, {3, 9}, {3, 8}}), 
        At(2301+289) P(4, 7.725),

        At(2501) I(1, 2, false),

    };

}