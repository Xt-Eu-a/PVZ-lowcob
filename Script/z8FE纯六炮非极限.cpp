#include <avz.h>
#include <dsl/shorthand.h>

static bool Paused = false;

// 获取Type类型植物对小丑爆炸的判定范围
inline std::pair<int, int> GetExplodeRange(APlantType Type) {
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
inline std::pair<int, int> MyGridToCoordinate(double Row, double Col) {
    if (ARangeIn(AGetMainObject()->Scene(), {0, 1, 6, 7, 8, 9}))
        return {40 + (Col - 1) * 80, 80 + (Row - 1) * 100};
    else if (ARangeIn(AGetMainObject()->Scene(), {2, 3, 10, 11}))
        return {40 + (Col - 1) * 80, 80 + (Row - 1) * 85};
    return {40 + (Col - 1) * 80, 70 + (Row - 1) * 85 + (Col < 6 ? (6 - Col) * 20 : 0)}; // 天台
}
// 预测小丑是否可炸到(Row, Col)格Type类型植物
inline bool PredictExplode(AZombie* Zombie, int PlantRow, int PlantCol, APlantType PlantType) {
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
    double XDistance = std::sqrt(90.0 * 90.0 - YDistance * YDistance);
    auto Range = GetExplodeRange(PlantType);
    return PlantX + Range.first - XDistance <= JackX && JackX <= PlantX + Range.second + XDistance;
}
// 检查卡片是否能用或是被拿着
inline bool isSeedUsableOrHolding(APlantType Type) { return AIsSeedUsable(Type) || AMRef<int>(0x6A9EC0, 0x768, 0x138, 0x28) == Type; }
// 检查位置是否会被小丑炸
inline bool IsSafePosForPlant(APlantType PlantType, int Row, int Col, int NeedTime = 99) {
    for (auto& Zombie : aAliveZombieFilter) {
        if (Zombie.Type() == AJACK_IN_THE_BOX_ZOMBIE && Zombie.State() == 16 && PredictExplode(&Zombie, Row, Col, PlantType) && Zombie.StateCountdown() <= NeedTime)
            return false;
    }
    return true;
}

//创建一个控制台对象logger,用于输出调试信息
ALogger<AConsole>logger;

// 根据候选位置列表，选第一个不会被小丑炸到的安全位置种植；都炸就不种
/*At(2201) Do{
    std::vector<APlantType> plants = {AHY_16, AHMG_15};
    std::vector<AGrid> lst = {{4, 7}, {4, 8}, {3, 7}, {3, 8}, {3, 9}, {4, 9}};
    SafePosCard(plants, lst);
},*/
// 重载1：单个固定格子
inline bool SafePosCard(const std::vector<APlantType>& plantTypeVec, int row, float col, int NeedTime = 99) {
    if (plantTypeVec.empty()) return false;
    int iRow = row;
    int iCol = static_cast<int>(std::round(col));
    APlantType firstPlant = plantTypeVec[0];

    if (IsSafePosForPlant(firstPlant, iRow, iCol, NeedTime)) {
        auto plantPtrVec = ACard(plantTypeVec, iRow, iCol);
        // 判断：所有指针都不为空，才算全部种植成功
        bool allOk = true;
        for (auto ptr : plantPtrVec) {
            if (ptr == nullptr) {
                allOk = false;
                break;
            }
        }
        if (allOk) {
            logger.Info("成功！在{}行{}列垫卡", iRow, iCol);
            return true;
        } else {
            logger.Info("{}行{}列：小丑安全，但底层Card垫卡不完全成功", iRow, iCol);
        }
    }
    return false;
}
// 重载2：APosition列表
inline bool SafePosCard(const std::vector<APlantType>& plantTypeVec, const std::vector<APosition>& lst, int NeedTime = 99) {
    if (plantTypeVec.empty()) return false;
    APlantType firstPlant = plantTypeVec[0];
    for (const auto& pos : lst) {
        logger.Info("尝试格子：{}行{}列", pos.row, pos.col);
        if (IsSafePosForPlant(firstPlant, pos.row, pos.col, NeedTime)) {
            auto plantPtrVec = ACard(plantTypeVec, pos.row, pos.col);
            bool allOk = true;
            for (auto ptr : plantPtrVec) {
                if (ptr == nullptr) {
                    allOk = false;
                    break;
                }
            }
            if (allOk) {
                logger.Info("成功！在{}行{}列垫卡", pos.row, pos.col);
                return true;
            } else {
                logger.Info("{}行{}列：小丑安全，但底层Card垫卡不完全成功", pos.row, pos.col);
            }
        } else {
            logger.Info("失败：{}行{}列存在危险小丑", pos.row, pos.col);
        }
    }
    logger.Info("全部候选位置均不可用，垫卡失败");
    return false;
}
// 重载3：AGrid vector
inline bool SafePosCard(const std::vector<APlantType>& plantTypeVec, const std::vector<AGrid>& lst, int NeedTime = 99) {
    if (plantTypeVec.empty()) return false;
    APlantType firstPlant = plantTypeVec[0];
    for (const auto& grid : lst) {
        int r = grid.row;
        int c = grid.col;
        logger.Info("尝试格子：{}行{}列", r, c);
        if (IsSafePosForPlant(firstPlant, r, c, NeedTime)) {
            auto plantPtrVec = ACard(plantTypeVec, r, c);
            bool allOk = true;
            for (auto ptr : plantPtrVec) {
                if (ptr == nullptr) {
                    allOk = false;
                    break;
                }
            }
            if (allOk) {
                logger.Info("成功！在{}行{}列垫卡", r, c);
                return true;
            } else {
                logger.Info("{}行{}列：小丑安全，但底层Card垫卡不完全成功", r, c);
            }
        } else {
            logger.Info("失败：{}行{}列存在危险小丑", r, c);
        }
    }
    logger.Info("全部候选位置均不可用，垫卡失败");
    return false;
}
// 重载4：initializer_list<AGrid>
inline bool SafePosCard(const std::vector<APlantType>& plantTypeVec, std::initializer_list<AGrid> lst, int NeedTime = 99) {
    if (plantTypeVec.empty()) return false;
    APlantType firstPlant = plantTypeVec[0];
    for (const auto& grid : lst) {
        int r = grid.row;
        int c = grid.col;
        logger.Info("尝试格子：{}行{}列", r, c);
        if (IsSafePosForPlant(firstPlant, r, c, NeedTime)) {
            auto plantPtrVec = ACard(plantTypeVec, r, c);
            bool allOk = true;
            for (auto ptr : plantPtrVec) {
                if (ptr == nullptr) {
                    allOk = false;
                    break;
                }
            }
            if (allOk) {
                logger.Info("成功！在{}行{}列垫卡", r, c);
                return true;
            } else {
                logger.Info("{}行{}列：小丑安全，但底层Card垫卡不完全成功", r, c);
            }
        } else {
            logger.Info("失败：{}行{}列存在危险小丑", r, c);
        }
    }
    logger.Info("全部候选位置均不可用，垫卡失败");
    return false;
}

void AScript() {
  // 鼠标右键:高级暂停,原速→暂停,暂停→原速
  AConnect(VK_RBUTTON, [] {Paused = !Paused; ASetAdvancedPause(Paused, false, 0);});
  // X:0.1倍速,任意倍速→0.1倍速,0.1倍速→原速
  AConnect('X', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 100 ? 10 : 100;});
  // C:10倍速,任意倍速→10倍速,10倍速→原速
  AConnect('C', [] {AGetPvzBase()->TickMs() = AGetPvzBase()->TickMs() == 1 ? 10 : 1;});
  // 出怪12怪极红
  ASetZombies("气矿梯跳车 豚 橄丑篮杆 白红 障偷");
  // 选卡 喷阳 南 双花 双冰辣核荷
  ASelectCards({AXPG_8,AYGG_9,ANGT_30,AXRK_1,ASZXRK_41,
                  AM_HBG_14,AHBG_14,AHMG_15,AHBLJ_20,AHY_16},15);
  // 6门炮列表
  aCobManager.AutoSetList();
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  // 关闭报错
  //AGetInternalLogger()->SetLevel({});
  // 自动躲炸放核
  std::vector<APlantType> plants = {AHY_16,AHMG_15};
  std::vector<AGrid> lst = {{4, 7}, {4, 8}, {3, 7}, {3, 8}, {3, 9}, {4, 9}};
  /////////////////////////////////////////////////////////////////////////////////////////
  // C4u:I1-Bd-Ndd I-Bd-J/Pd
  // 垫材逻辑
  // ASQWE在鼠标处放小喷阳光菇荷叶小向南瓜,D在鼠标处铲除植物
  At('A') Do { ACard(AXPG_8, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(AYGG_9, AMouseRow(), AMouseCol()); };
  At('D') Do { AShovel(AMouseRow(), AMouseCol()); };
  At('Q') Do { ACard(AHY_16, AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(AXRK_1, AMouseRow(), AMouseCol()); };
  At('E') Do { ACard(ANGT_30, AMouseRow(), AMouseCol()); };

  /////////////////////////////////////////////////////////////////////////////////////////
  // 循环主体
  // w1
  OnWave(1){ //核波
      At(-599) Card({{ANGT_30,2,5},{AXPG_8,5,2},{AYGG_9,5,3}}) & Card({AHY_16,AXRK_1,ASZXRK_41},3,5),
      At(751-599) Card({{AXPG_8,6,2},{AYGG_9,6,3}}) & Card({AHY_16,AXRK_1},3,6),
      At(751+751-599) Card({{AXPG_8,1,1},{AYGG_9,1,4}}) & Card({AHY_16,AXRK_1},4,5),
      At(751+751+751-599) Card({{AXPG_8,2,6},{AYGG_9,1,4}}) & Card(AXRK_1,2,5),
      At(751+751+751+751-599) Card(AXRK_1,1,2),
      At(3001-599) Card(ANGT_30,1,2),
      At(5001-599) Card(ASZXRK_41,3,6),
      At(5001+5001-599) Card(ASZXRK_41,4,5),
      At(5001+5001+5001-599) Card(ASZXRK_41,2,5),
      At(134-421) Shovel(1, 3),
      At(135) I(1, 3, true), // I'
  };
  ATimeline I1_Bd_Ndd = { //核波
      // 1 3 5 7 9 |10 12 14 16 18 19. 20.
      At(977) P(3, 8.6875) & D<355>(1,2.5), // Bd
      At(2201) Do{SafePosCard(plants, lst);}, // N
      At(2301) D<197>(1, 4.5) & D<254>(5, 3.0875), // dd 延迟247就能收气球了
  };
  ATimeline I_Bd_JPd = { //樱波
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(135) I(2, 8, false), // I
      At(977) P(3, 8.6875) & D<355>(1,2.5), // Bd
      At(2301) J(1, 5) & P(5, 7.55) & D<254>(5, 3.0875), // JPd
      At(2501+134-421) Shovel(1, 3),
      At(2501+135) I(1, 3, true), // I'
  };
  OnWave(1_9 % 1, 11_19 % 2) I1_Bd_Ndd | I_Bd_JPd;
  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9.
  At(ATime(9, 2501)){ //樱波
      At(135) I(2, 8, false), // I
      At(977) P(1, 7.5) & D<212>(1,7), // BD
      At(2301) P(5, 7.55) & D<254>(5, 3.0875), // Pd
      At(2744+134-421) Shovel(1, 3),
      At(2744+135) I(1, 3, true), // I'
  };
  // w10
  OnWave(10){ //核波
      At(1000) P(3, 8.675) & D<355>(1,2.5), // Bd 延迟收矿工
      At(2201) Do{SafePosCard(plants, lst);}, // N
      At(2301) D<197>(1, 4.5) & D<254>(5, 3.0875), // dd 延迟247就能收气球了
  };
  // w19.
  At(ATime(19, 2501)){ //核波
      At(977) P(1, 7.5) & D<212>(1,7), // BD
      At(2201) Do{SafePosCard(plants, lst);}, // N
      At(2301) P(5, 7.55) & D<254>(5, 3.0875), // Sd 延迟247就能收气球了
  };
  // w20
  OnWave(20){ //樱波 核波
      At(135) I(2, 8, false), // I
      At(1000) P(3, 8.675) & D<355>(1,2.5), // Bd 延迟收矿工
      At(2301) J(1, 5) & P(5, 7.55) & D<254>(5, 3.0875), // JPd
      At(2501+134-421) Shovel(1, 3),
      At(2501+135) I(1, 3, true), // I'
      At(2501)
          (At(977) P(1, 7.5) & D<212>(1,7)) & // BD
          (At(2201) Do{SafePosCard(plants, lst);}) & // N
          (At(2301) D<254>(5, 3.0875)), // d 延迟247就能收气球了
          //手动多打一炮
  };
}