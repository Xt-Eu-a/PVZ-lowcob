#include <avz.h>
#include <dsl/shorthand.h>

static bool Paused = false;
static bool PausedSlowed = false;

// 获取Type类型植物对小丑爆炸的判定范围
std::pair<int, int> GetExplodeRange(APlantType Type) {
    switch (Type) {
    case ATALL_NUT:
        return {10, 90};
    case APUMPKIN:
        return {0, 100};
    case ACOB_CANNON:
        return {0, 140};
    default:
        return {10, 70}; // 普通
    }
}
// 将给定格子转化为坐标
// 支持非整型参数
std::pair<int, int> MyGridToCoordinate(double Row, double Col) {
    if (ARangeIn(AGetMainObject()->Scene(), {0, 1, 6, 7, 8, 9}))
        return {40 + (Col - 1) * 80, 80 + (Row - 1) * 100};
    else if (ARangeIn(AGetMainObject()->Scene(), {2, 3, 10, 11}))
        return {40 + (Col - 1) * 80, 80 + (Row - 1) * 85};
    return {40 + (Col - 1) * 80, 70 + (Row - 1) * 85 + (Col < 6 ? (6 - Col) * 20 : 0)}; // 天台
}
// 预测小丑是否可炸到(Row, Col)格Type类型植物
bool PredictExplode(AZombie* Zombie, int PlantRow, int PlantCol, APlantType PlantType) {
    int JackX = Zombie->Abscissa() + 60;
    int JackY = Zombie->Ordinate() + 60; // 小丑爆心偏移
    auto PlantCoordinate = MyGridToCoordinate(PlantRow, PlantCol);
    int PlantX = PlantCoordinate.first, PlantY = PlantCoordinate.second;
    int YDistance = 0;
    if (JackY < PlantY)
        YDistance = PlantY - JackY;
    else if (JackY > PlantY + 80)
        YDistance = JackY - (PlantY + 80);
    if (YDistance > 90)
        return false;
    int XDistance = sqrt(90 * 90 - YDistance * YDistance);
    auto Range = GetExplodeRange(PlantType);
    return PlantX + Range.first - XDistance <= JackX && JackX <= PlantX + Range.second + XDistance;
}
// 检查卡片是否能用或是被拿着
bool isSeedUsableOrHolding(APlantType Type) { return AIsSeedUsable(Type) || AMRef<int>(0x6A9EC0, 0x768, 0x138, 0x28) == Type; }
// 拖延至不会被小丑炸的情况下再用卡
// 需存活时间NeedTime应填写≥1的数，默认卡片需存活至99cs后
// 延迟铲除ShovelDelay默认0为不铲除
void SafeCard(APlantType PlantType, int Row, int Col, int NeedTime = 99, int ShovelDelay = 0) {
    if (AGetCardIndex(PlantType) < 0 || AGetCardIndex(PlantType) > 9 || !isSeedUsableOrHolding(PlantType))
        return; // 卡片需要带了且CD是好的
    for (auto& Zombie : aAliveZombieFilter) {
        if (Zombie.Type() == AJACK_IN_THE_BOX_ZOMBIE && Zombie.State() == 16 && PredictExplode(&Zombie, Row, Col, PlantType) && Zombie.StateCountdown() <= NeedTime) {
            AConnect(ANowDelayTime(1), [=] { SafeCard(PlantType, Row, Col, NeedTime, ShovelDelay); });
            return; // 小丑倒计时≤NeedTime，则延迟到下一帧重新判断
        }
    }
    ACard(PlantType, Row, Col); // 查完小丑后发现一切正常，则用卡
    if (ShovelDelay == 0)
        return;
    AConnect(ANowDelayTime(ShovelDelay), [=] { AShovel(Row, Col, PlantType); }); // 以种植时间为参照进行延迟铲除
}

void AScript() {
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
    // AConnect('R', [] { AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 1 ? 10 : 1; });
    // 卡槽置顶
    // AConnect('V', [] { AMRef<int>(0x416DBE) = AMRef<int>(0x416DBE) == 699999 ? 100001 : 699999; });

    ASetZombies({
        ABC_12, // 冰车
        AKG_17, // 矿工
        AQQ_16, // 气球

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

        ALZ_2, // 路障
        // ATT_4,  // 铁桶

        ABJ_20, // 蹦极
    });
    ASelectCards({
        AYMJNP_47, // 玉米炮
        AYMTS_34,  // 玉米投手
        ADC_21,    // 地刺
        AWG_17,    // 窝瓜

        AHY_16,  // 荷叶
        AHMG_15, // 毁灭菇
        AKFD_35, // 咖啡豆

        ACHERRY_BOMB, // 樱桃炸弹
        AHBG_14,      // 寒冰菇
        AM_HBG_14,    // 模仿寒冰菇 第一段始终是AM
    });

    /*At(ATime(1, -599))[] {
        AAverageSpawn();
        AMaidCheats::Dancing();
        aPlantFixer.Start(ANGT_30, {{4, 4}, {3, 4}}, 1332);
    };*/

    // 自动存冰 先用模仿冰,从后往前使用
    aIceFiller.Start({{3, 1}, {4, 3}, {3, 2}, {5, 4}, {6, 4}});
    // 2门炮列表
    // aCobManager.SetList({{3, 1}, {4, 1}});
    // 脚本重新载入模式
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 关闭报错
    // AGetInternalLogger()->SetLevel({});

    // C4u:I-/d-ANd I-B-JP I-NB-PA I-B-JP

    // 垫材逻辑
    ATimeline CCTV = {
        At(292) Card(ADC_21, 2, 9),   // 地刺
        At(339) Shovel(2, 9, ADC_21), // 铲
    };
    OnWave(1_8,10_18) CCTV;

    // w1
    OnWave(1) {
        At(-599) Card(AHY_16, 3, 6),
        At(751 - 599) Card(AHY_16, 4, 6),
        At(751+751 - 599) Card(AHY_16, 4, 5),

        At(959) RP(4, 1, 2, 7.55), // 2
        At(959) RP(3, 3, 5, 7.55), // 5
        At(959 - 373 + 206) Shovel(3, 3, AYMJNP_47) & Card(AYMTS_34, 3, 3),
        At(959 - 373 + 206 + 751) Card(AYMTS_34, 3, 4) & Card(AYMJNP_47, 3, 3),

        At(959 + 201) I(),
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // w2-w8,w13-w18
    ATimeline I_PP1_1367 = {
        // 1,4,7,(9) | 11,14,17,(19),(20) 1167~气球797_8.3_8.5625慢巨人558.5_8.375_8.2875
        At(552) I(),

        At(1167) RP(4, 1, 2, 8.3), // 2
        At(1167) RP(3, 3, 5, 8.3), // 5
        At(1167 - 373 + 206) Shovel(3, 3, AYMJNP_47) & Card(AYMTS_34, 3, 3),
        At(1167 - 373 + 206 + 751) Card(AYMTS_34, 3, 4) & Card(AYMJNP_47, 3, 3),

        At(1167 + 202) I(),
    };
    //////////////////////////////////////////////////////////////
    ATimeline smart_pot = Do {
        SafeCard(AYTZD_2, 2, 8, 17); // A2
    };
    OnWave(2, 5, 8, 15, 18) {
        At(1464) smart_pot, // A2
    };
    ATimeline I_AP11_1764 = {
        // 2,5,8,(9) | 12,15,18,(19),(20)
        At(1564) RP(3, 3, 5, 8.3), // 5
    };
    OnWave(2) {
        At(1564 + 211) I(),
    };
    OnWave(5,15) {//4-7核收1路气球
        At(1564 + 442) I(),
    };
    //////////////////////////////////////////////////////////////

    ATimeline I_N_2109 = {}; // 3,6,9 | 10,13,16,19,20
    OnWave(3) {
        At(1) Shovel(3, 8, AHY_16),
        At(536) Card({AHY_16,AHMG_15}, 3, 7),
        //At(752) Card(AHY_16,3,9),

        At(1909-100-198) Card(AKFD_35,3, 7), // N
    };
    OnWave(6) {
        At(1) Shovel(4, 8, AHY_16),
        At(298) Card({AHY_16,AHMG_15}, 4, 7),

        At(1909-100-198) Card(AKFD_35,4, 7), // N
    };

    OnWave(13) {
        At(1) Shovel(3, 8, AHY_16),
        At(359) Card({AHY_16,AHMG_15}, 3, 7),
        //At(360+751) Card(AHY_16,3,9),

        At(1909-100-198) Card(AKFD_35,3, 7), // N
    };
    OnWave(16) {
        At(1) Shovel(4, 8, AHY_16),
        At(121) Card({AHY_16,AHMG_15}, 4, 7),

        At(1909-100-198) Card(AKFD_35,4, 7), // N
    };
    OnWave(2_8 % 2, 13_18 % 3) I_PP1_1367 | I_AP11_1764 | I_N_2109;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // w9 2路a-5路a-垫2路-垫1路-1路a
    OnWave(9) {
        At(359) N(4, 9), // N
        At(1111) I(),

        At(811) Card(AHY_16,3,9),

        At(1513) RP(4, 1, 2, 8), // 2
        At(3277) RP(3, 3, 5, 7), // 5

        At(4800-101) Shovel(6,6),
        At(4801) A(6, 5), // 6
    };

    //w10_1100 全收6路小丑1006,气球1065,9列躲旗帜潜水734+300=1034,跳跳不进家800 核收跳跳844
    //2路a小丑-3cc垫潜水
    OnWave(10) {
        At(1) Card(AHY_16, 3, 8),
        At(115) Card(AHMG_15, 3, 8),
        At(844-198-100) Card(AKFD_35,3, 8),// N
    };
    OnWave(11) {//气球914_7.75
        At(552) I(),

        At(1462) RP(4, 1, 2, 7.75), // 2意外率3%
        At(1462) RP(3, 3, 5, 7.75), // 5
        At(1462 - 373 + 206) Shovel(3, 3, AYMJNP_47) & Card(AYMTS_34, 3, 3),
        At(1462 - 373 + 206 + 751) Card(AYMTS_34, 3, 4) & Card(AYMJNP_47, 3, 3),

        At(1462 + 202) I(),
    };
    OnWave(12) { //气球741_8.55 慢巨人626_8.2875
        At(1852) A(2, 8), // 2炮伤低于0.5%
        At(1852) RP(3, 3, 5, 8.2875), // 5

        At(1852 + 211) I(),
    };

    // w19 2路a-5路a,1路要窝瓜/地刺杀w18跳跳
    OnWave(19) {
        At(1) Card({AHY_16,AHMG_15}, 4, 9),
        At(359-100-198) Card(AKFD_35,4, 9), // N
        At(1111) I(),

        At(1513) RP(4, 1, 2, 8), // 2
        At(3277) RP(3, 3, 5, 7), // 5
        At(3277 - 373 + 206) Shovel(3, 3, AYMJNP_47) & Card(AYMTS_34, 3, 3),
        At(3277 - 373 + 206 + 751) Card(AYMTS_34, 3, 4) & Card(AYMJNP_47, 3, 3),

        At(4800-101) Shovel(6,6),
        At(4801) A(1, 5), // 1
        At(4859) RP(3, 3, 5, 5), // 5

        At(5025) Card({AHY_16,AHMG_15}, 3, 9),
    };
    // w20 2路a-垫6路
    OnWave(20) {
        At(409-198-100) Card(AKFD_35,3, 9), // N
        At(1161) I(),

        At(245) RP(4, 1, 2, 9), // 2

        At(3091) RP(3, 3, 5, 7), // 5
        At(3835) RP(4, 1, 5, 6), // 5

        At(5181) N(4, 8), //4最晚5057+299+100=5356
    };
}