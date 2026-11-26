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

    //12怪极红
    ASetZombies({
        ABC_12, // 冰车
        AKG_17, // 矿工

        AFT_21, // 扶梯
        ATT_18, // 跳跳
        AQQ_16, // 气球

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

    //选卡
    ASelectCards({
        ATALL_NUT,     // 高坚果
        ANGT_30,       // 南瓜
        ASQUASH,       // 倭瓜
        ADC_21,        // 地刺
        ALILY_PAD,     // 荷叶

        AICE_SHROOM,   // 寒冰菇
        AM_ICE_SHROOM, // 模仿寒冰菇
        ADOOM_SHROOM,  // 毁灭菇
        ACHERRY_BOMB,  // 樱桃炸弹
        AJALAPENO,     // 火爆辣椒
    });

    //定义炮列表并管理
    aCobManager.SetList({{3,1},{3,3},{4,1}});
    aCobManager.SetSequentialMode(ACobManager::PRIORITY); //优先级模式
    // 脚本重新载入模式  
    //ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    //C4u:I-B-Ja/PA | I'-B-N/Nd

    //垫材逻辑
    ATimeline CCTV = {
        At(551) Card(AHY_16, 4, 8),
        At(1302) Card(AHY_16, 4, 7),
    };
    OnWave(2_9,11_19) CCTV;

    ATimeline CCTV1 = {
        At(551) Card(AHY_16, 4, 8),
        At(1302) Card(AHY_16, 4, 3),
    };
    OnWave(10,20) CCTV1;

    //w1
    OnWave(1) {
        At(-599) Card(AHY_16, 4, 3) & Card(AGJG_23, 1, 2),
        At(751-599) Card(AHY_16, 4, 8),
        At(751+751-599) Card(AHY_16, 4, 7),
        At(751+751+751-599) Card(AHY_16, 4, 5),
        At(3001-599) Card(AGJG_23, 4, 5) 
    };

    //w1-w9,w10-w19
    ATimeline I_B_JaPA = {
        At(135) I(4,3, false),//I

        At(1325) P(2,7.55),//B

        At(2301) J(1,6),//J
        At(2301) P(5,7.55),//P
        At(2601) A(5,3),//A

        At(2635) I(4,3),//I'
    };
    ATimeline I1_B_Nd = { 
        At(1325) P(2,7.55),//B

        At(2301) N({{3, 7},{4, 9},{3, 6},{3, 8}}),//N
        At(2601) P(5,3),//d
    };
    ATimeline I_B_JaPA2 = {
        At(135) I(4,3, false),//I

        At(1325) P(2,7.55),//B

        At(2301) J(2,6),//J
        At(2301) P(5,7.55),//P
        At(2601) A(5,3),//A

        At(2635) I(4,3),//I'
    };
    ATimeline I1_B_Nd2 = { 
        At(1325) P(2,7.55),//B

        At(2301) N({{3, 7},{4, 9},{3, 6},{3, 8}}),//N
        At(2601) P(5,3),//d
    };
    OnWave(1_9 % 1, 11_19 % 4) I_B_JaPA | I1_B_Nd | I_B_JaPA2 | I1_B_Nd2;


    //w9后
    OnWave(9) {
        At(2501+1325) P(2,7),//B

        At(2501+2301) N({{3, 7},{4, 9},{3, 6},{3, 8}}),//N
        At(2501+2601) P(5,3),//d
    };
    //w10
    OnWave(10) {
        At(135) I(4,3, false),//I

        At(1325) P(3,9),//B

        At(2301) J(1,6),//J
        At(2301) P(5,7.55),//P
        At(2601) A(5,3),//A

        At(2635) I(4,3),//I'
    };
    //w19后
    OnWave(19) {
        At(2501+135) I(4,3, false),//I

        At(2501+1325) P(2,7),//B

        At(5245+135) I(4,3),//I'
    };
    //w20
    OnWave(20) { //3
        At(1325) P(2,9),//B

        At(2301) N({{3, 7},{4, 9},{3, 6},{3, 8}}),//N
        At(2601) P(5,3),//d

        At(2501+135) I(4,3, false),//I

        At(2501+1325) P(2,7),//B
    };

}