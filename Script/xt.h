#ifndef __XT__
#define __XT__

#define interface struct

#include "dsl/shorthand_240713.h"
#include <cmath>
#include <format>
#include <vector>

using namespace ALiterals;

static bool Paused = false;
static bool PausedSlowed = false;

//智能发炮函数LeftNoDamageSmartCob不伤和RightNoDamageSmartCob不伤，注意时间为炮生效时间的前373cs
inline void LeftNoDamageSmartCob(int row, float col, ATime tm, int zombieType,     //整数行、浮点数列、ATime结构体、僵尸类型
float travelDistance, bool up , bool mid , bool down,   //373cs内的前进预测、上中下炸点判定选择
float upleft, float midleft, float downleft){   //上中下炮左距(默认巨人)

    float newcol = col;
    int abs = 800; //(默认炸10列)
    for(auto& zombie:aAliveZombieFilter) //遍历僵尸列表
    {
        // 筛选条件：存活、未消失、未死亡、僵尸类型
        if (zombie.Type() == zombieType){
            // up开关->炸上一行
            if (up && zombie.Row() == (row - 2)) abs = zombie.Abscissa() - travelDistance - upleft;
            // mid开关->炸本行
            else if (mid && zombie.Row() == (row - 1)) abs = zombie.Abscissa() - travelDistance - midleft;
            // down开关->炸下一行
            else if (down && zombie.Row() == row) abs = zombie.Abscissa() - travelDistance - downleft;
            else continue;
            // 像素转游戏列
            if (newcol > (float)(abs +7 -1) / 80) newcol = (float)(abs +7 -1) / 80;
        }
    }
    AConnect(ATime(tm.wave,tm.time),[=](){aCobManager.Fire(row,newcol);
        aPainter.SetTextColor(AArgb(255,255,0,0));
        aPainter.Draw(AText(std::format("智能落点:{}",newcol), 400, 300), 500);
    });
}
inline void RightNoDamageSmartCob(int row, float col, ATime tm, int zombieType,     //整数行、浮点数列、ATime结构体、僵尸类型
float travelDistance, bool up , bool mid , bool down,   //373cs内的前进预测、上中下炸点判定选择
float upright, float midright, float downright){   //上中下炮右距(默认巨人)

    float newcol = col;
    int abs = 0; //(默认炸0列)
    for(auto& zombie:aAliveZombieFilter) //遍历僵尸列表
    {
        // 筛选条件：存活、未消失、未死亡、僵尸类型
        if (zombie.Type() == zombieType){
            // up开关->炸上一行
            if (up && zombie.Row() == (row - 2)) abs = zombie.Abscissa() - travelDistance + upright;
            // mid开关->炸本行
            else if (mid && zombie.Row() == (row - 1)) abs = zombie.Abscissa() - travelDistance + midright;
            // down开关->炸下一行
            else if (down && zombie.Row() == row) abs = zombie.Abscissa() - travelDistance + downright;
            else continue;
            // 像素转游戏列
            if (newcol < (float)(abs +7 +1) / 80) newcol = (float)(abs +7 +1) / 80;
        }
    }
    AConnect(ATime(tm.wave,tm.time),[=](){aCobManager.Fire(row,newcol);
        aPainter.SetTextColor(AArgb(255,255,0,0));
        aPainter.Draw(AText(std::format("智能落点:{}",newcol), 400, 300), 500);
    });
}

//智能发炮函数LeftFullDamageSmartCob全伤和RightFullDamageSmartCob全伤，注意时间为炮生效时间的前373cs
inline void LeftFullDamageSmartCob(int row, float col, ATime tm, int zombieType,     //整数行、浮点数列、ATime结构体、僵尸类型
float travelDistance, bool up , bool mid , bool down,   //373cs内的前进预测、上中下炸点判定选择
float upleft, float midleft, float downleft){   //上中下炮左距(默认巨人)

    float newcol = col;
    int abs = 800; //(默认炸10列)
    for(auto& zombie:aAliveZombieFilter) //遍历僵尸列表
    {
        // 筛选条件：存活、未消失、未死亡、僵尸类型
        if (zombie.Type() == zombieType){
            // up开关->炸上一行
            if (up && zombie.Row() == (row - 2)) abs = zombie.Abscissa() - travelDistance - upleft;
            // mid开关->炸本行
            else if (mid && zombie.Row() == (row - 1)) abs = zombie.Abscissa() - travelDistance - midleft;
            // down开关->炸下一行
            else if (down && zombie.Row() == row) abs = zombie.Abscissa() - travelDistance - downleft;
            else continue;
            // 像素转游戏列
            if (newcol < (float)(abs +7 +1) / 80) newcol = (float)(abs +7 +1) / 80; //+1或许是+0
        }
    }
    AConnect(ATime(tm.wave,tm.time),[=](){aCobManager.Fire(row,newcol);
        aPainter.SetTextColor(AArgb(255,255,0,0));
        aPainter.Draw(AText(std::format("智能落点:{}",newcol), 400, 300), 500);
    });
}
inline void RightFullDamageSmartCob(int row, float col, ATime tm, int zombieType,     //整数行、浮点数列、ATime结构体、僵尸类型
float travelDistance, bool up , bool mid , bool down,   //373cs内的前进预测、上中下炸点判定选择
float upright, float midright, float downright ){   //上中下炮右距(默认巨人)

    float newcol = col;
    int abs = 0; //(默认炸0列)
    for(auto& zombie:aAliveZombieFilter) //遍历僵尸列表
    {
        // 筛选条件：存活、未消失、未死亡、僵尸类型
        if (zombie.Type() == zombieType){
            // up开关->炸上一行
            if (up && zombie.Row() == (row - 2)) abs = zombie.Abscissa() - travelDistance + upright;
            // mid开关->炸本行
            else if (mid && zombie.Row() == (row - 1)) abs = zombie.Abscissa() - travelDistance + midright;
            // down开关->炸下一行
            else if (down && zombie.Row() == row) abs = zombie.Abscissa() - travelDistance + downright;
            else continue;
            // 像素转游戏列
            if (newcol > (float)(abs +7 -1) / 80) newcol = (float)(abs +7 -1) / 80;  //-1或许是-0
        }
    }
    AConnect(ATime(tm.wave,tm.time),[=](){aCobManager.Fire(row,newcol);
        aPainter.SetTextColor(AArgb(255,255,0,0));
        aPainter.Draw(AText(std::format("智能落点:{}",newcol), 400, 300), 500);
    });
}

// 判断僵尸纵坐标在 [l, r] 区间内
inline AFodder::Constraint OrdIn(int l, int r) {
    return [=](AZombie* zombie) {
        return l <= int(zombie->Ordinate()) && int(zombie->Ordinate()) <= r;
    };
}

// 同时判断僵尸横坐标在[xl,xr]、纵坐标在[yl,yr]
inline AFodder::Constraint PosIn(int xl, int xr, int yl, int yr) {
    return [=](AZombie* zombie) {
        auto x = int(zombie->Abscissa());
        auto y = int(zombie->Ordinate());
        return xl <= x && x <= xr && yl <= y && y <= yr;
    };
}
// 矩形内是否存在某种僵尸，存在返回true，无僵尸false
inline bool HasZombieIn(const AFodder::Constraint& filter)
{
    AMainObject* mainObj = AGetMainObject();
    AZombie* zArr = mainObj->ZombieArray();
    int count = mainObj->ZombieCount();

    for (int i = 0; i < count; ++i)
    {
        AZombie* z = &zArr[i];
        if (!z->IsExist())
            continue;
        if (filter(z))
            return true;
    }
    return false;
}
inline void AXtSelectCards(const std::string& str, const std::vector<int>& lst, int selectInterval = 17) {
    static const std::unordered_set<char32_t> separators {' ', ',', ';', U'　', U'，', U'；'};
    static const std::unordered_map<char32_t, int> cardAbbr {
        {'A', ACHERRY_BOMB},
        {'B', ABLOVER},//三叶草
        //{'C', },
        {'D', ADZH_6},//大嘴花
        //{'E', },
        {'F', AFLOWER_POT},
        {'G', AGRAVE_BUSTER},//吞碑grave_buster
        {'H', AGJG_23},//高坚果
        {'I', AICE_SHROOM},
        {'J', AJALAPENO},
        {'K', ACOFFEE_BEAN},
        {'L', ALILY_PAD},
        {'M', AMHG_12},//魅惑菇
        {'N', ADOOM_SHROOM},
        //{'O', },
        {'P', APUMPKIN},
        //{'Q', },
        {'R', AXRK_1},//向日葵
        {'S', AGARLIC},//蒜
        {'T', APOTATO_MINE},//土豆
        {'U', AUMBRELLA_LEAF},//伞
        {'V', AHP_33},//花盆
        {'W', ASQUASH},//窝瓜
        //{'X', },
        {'Y', AYMTS_34},//玉米
        {'Z', AYMJNP_47},//加农炮
        {'_', ASPIKEWEED},//地刺
    };
    //小喷菇，阳光菇，花盆，胆小菇，向日葵 
    static const std::array fodders {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM, ASUNFLOWER};
//    static const std::array fodders {APUFF_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM, ASUN_SHROOM, ASUNFLOWER};
    std::vector<int> newList;
    std::unordered_set<int> existedCards;
    int fodderCount = 0;
    for (auto ch : AStrToU32str(str)) {
        if (separators.contains(ch))
            continue;
        else if (cardAbbr.contains(ch)) {
            int card = cardAbbr.at(ch);
            if (existedCards.contains(card))
                card += 49;
            newList.push_back(card);
            existedCards.insert(card);
        } else if (ch == 'C' || ch == 'c') {
            while (fodderCount < fodders.size() && existedCards.contains(fodders[fodderCount]))
                ++fodderCount;
            if (fodderCount == fodders.size()) {
                aLogger->Error("ASelectCards: 自动选择的垫材数量最大为 {}", fodders.size());
                break;
            }
            newList.push_back(fodders[fodderCount]);
            existedCards.insert(fodders[fodderCount]);
        } else
            aLogger->Error("ASelectCards: 未知的卡片缩写 {}", ch);
    }
    newList.insert(newList.end(), lst.begin(), lst.end());
    ASelectCards(newList, selectInterval);
}
inline void AXtSelectCards(const std::string& str, std::initializer_list<int> lst, int selectInterval = 17) {
    AXtSelectCards(str, std::vector<int>(lst), selectInterval);
}
inline void AXtSelectCards(const std::string& str, int selectInterval = 17) {
    AXtSelectCards(str, {}, selectInterval);
}

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

// 拖延至不会被小丑炸的情况下再用卡
// 需存活时间NeedTime应填写≥1的数，默认卡片需存活至99cs后
// 延迟铲除ShovelDelay默认0为不铲除

//SafeCard(AYTZD_2, 2, 8, 17); // 智能樱桃举例
inline void SafeCard(APlantType PlantType, int Row, int Col, int NeedTime = 99, int ShovelDelay = 0) {
    if (AGetCardIndex(PlantType) < 0 || AGetCardIndex(PlantType) > 9 || !isSeedUsableOrHolding(PlantType))
        return; // 卡片需要带了且CD是好的
    if (!IsSafePosForPlant(PlantType, Row, Col, NeedTime)) {
        AConnect(ANowDelayTime(1), [=] { SafeCard(PlantType, Row, Col, NeedTime, ShovelDelay); });
        return; // 小丑倒计时≤NeedTime，则延迟到下一帧重新判断
    }
    ACard(PlantType, Row, Col); // 查完小丑后发现一切正常，则用卡
    if (ShovelDelay == 0)
        return;
    AConnect(ANowDelayTime(ShovelDelay), [=] { AShovel(Row, Col, PlantType); }); // 以种植时间为参照进行延迟铲除
}

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
        if (allOk) return true;
    }
    return false;
}
/* 重载2：
APosition列表
    APosition动态数组
    APosition(int row, float col)支持浮点数列
示例：
    std::vector<APlantType> plants = {AHY_16, AHMG_15};
    std::vector<APosition> posList = {{4,7}, {4,8.5}};
    SafePosCard(plants, posList);
*/
inline bool SafePosCard(const std::vector<APlantType>& plantTypeVec, const std::vector<APosition>& lst, int NeedTime = 99) {
    if (plantTypeVec.empty()) return false;
    APlantType firstPlant = plantTypeVec[0];
    for (const auto& pos : lst) {
        if (IsSafePosForPlant(firstPlant, pos.row, pos.col, NeedTime)) {
            auto plantPtrVec = ACard(plantTypeVec, pos.row, pos.col);
            bool allOk = true;
            for (auto ptr : plantPtrVec) {
                if (ptr == nullptr) {
                    allOk = false;
                    break;
                }
            }
            if (allOk) return true;
        }
    }
    return false;
}
/* 重载3：
AGrid vector
    AGrid的动态数组
    AGrid(int row, int col)行列都只能是整数
示例：
    std::vector<APlantType> plants = {AHY_16, AHMG_15};
    std::vector<AGrid> gridList = {{4,7}, {4,8}};
    SafePosCard(plants, gridList);
源码内部：调用时自动通过`__AVecGridToVecPosition`把 AGrid 全部转成 APosition，防止不小心传入小数
*/
inline bool SafePosCard(const std::vector<APlantType>& plantTypeVec, const std::vector<AGrid>& lst, int NeedTime = 99) {
    if (plantTypeVec.empty()) return false;
    APlantType firstPlant = plantTypeVec[0];
    for (const auto& grid : lst) {
        int r = grid.row;
        int c = grid.col;
        if (IsSafePosForPlant(firstPlant, r, c, NeedTime)) {
            auto plantPtrVec = ACard(plantTypeVec, r, c);
            bool allOk = true;
            for (auto ptr : plantPtrVec) {
                if (ptr == nullptr) {
                    allOk = false;
                    break;
                }
            }
            if (allOk) return true;
        }
    }
    return false;
}
/* 重载4：
initializer_list<AGrid>
    是 C++ 语法，不是容器，专门用来接收`{}`直接字面量传参
    底层：传入`{ {4,7}, {3,8}, {4,9} }`这种花括号列表，自动包装成 initializer_list，再转成`vector<AGrid>`，再转 APosition
示例：
    std::vector<APlantType> plants = {AHY_16, AHMG_15};
    SafePosCard(plants, {{4,7}, {4,8}, {3,7}});
直接传大括号，不用提前定义变量，只能整数行列；编译期临时对象，不能存浮点数
*/
inline bool SafePosCard(const std::vector<APlantType>& plantTypeVec, std::initializer_list<AGrid> lst, int NeedTime = 99) {
    if (plantTypeVec.empty()) return false;
    APlantType firstPlant = plantTypeVec[0];
    for (const auto& grid : lst) {
        int r = grid.row;
        int c = grid.col;
        if (IsSafePosForPlant(firstPlant, r, c, NeedTime)) {
            auto plantPtrVec = ACard(plantTypeVec, r, c);
            bool allOk = true;
            for (auto ptr : plantPtrVec) {
                if (ptr == nullptr) {
                    allOk = false;
                    break;
                }
            }
            if (allOk) return true;
        }
    }
    return false;
}

//能返回炮索引的P变体
template <AFirePolicy policy = INSTANT_FIRE>
inline ATimeline PGetIdx(ACobManager& cm, int row, float col, int& outFireIdx) {
    ATimeline ret;
    for (auto pos : __ParseRow(row, col)) {
        int r = pos.row;
        float c = pos.col;
        ATimeOffset offset = aFieldInfo.isRoof ? -387 : (aFieldInfo.rowType[r]==ARowType::POOL ? -378 : -373);
        ret &= At(offset)[=, &cm, &outFireIdx] {
            if constexpr (policy == INSTANT_FIRE)
                outFireIdx = aFieldInfo.isRoof ? cm.RoofFire(r, c) : cm.Fire(r, c);
            else
                outFireIdx = aFieldInfo.isRoof ? cm.RecoverRoofFire(r, c) : cm.RecoverFire(r, c);
            auto g = cm.GetList()[outFireIdx];
            aLogger->Info("发射炮位置：{}行{}列",g.row,g.col);
        };
    }
    return ret;
}

// 全局保存原来开启的日志列表
inline std::vector<ALogLevel> g_savedLogLevels;
inline const std::vector<ALogLevel> g_defaultLog = {ALogLevel::INFO, ALogLevel::DEBUG, ALogLevel::WARNING, ALogLevel::ERROR};

// 静音：关闭 WARNING，保留 INFO DEBUG ERROR
inline void MuteWarningLog()
{
    auto logger = AGetInternalLogger();
    // 这里不能直接读_level。
    // 缺陷：原生AAbstractLogger**没有GetLevel()接口获取当前开启的日志**
    // 替代思路：脚本启动时记住初始日志，假设脚本初始状态是全开 {INFO,DEBUG,WARNING,ERROR}
    // 如果你脚本启动后没有修改过日志，可以直接这样写：
    g_savedLogLevels = {ALogLevel::INFO, ALogLevel::DEBUG, ALogLevel::WARNING, ALogLevel::ERROR};
    logger->SetLevel({ALogLevel::INFO, ALogLevel::DEBUG, ALogLevel::ERROR});
}

// 【恢复函数】把日志还原成MuteWarningLog调用之前的状态
inline void RestoreLog()
{
    auto logger = AGetInternalLogger();
    logger->SetLevel(g_savedLogLevels);
}




#endif