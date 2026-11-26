#include <avz.h>
#include <dsl/shorthand.h>

static bool Paused = false;
// 同时判断僵尸横坐标[xl,xr]、纵坐标[yl,yr]
inline AFodder::Constraint PosIn(int xl, int xr, int yl, int yr) {
    return [=](AZombie* zombie) {
        auto x = int(zombie->Abscissa());
        auto y = int(zombie->Ordinate());
        return xl <= x && x <= xr && yl <= y && y <= yr;
    };
}
// 矩形内是否存在某种僵尸，存在返回true，无僵尸false
inline bool HasZombieIn(const AFodder::Constraint& filter) {
    AMainObject* mainObj = AGetMainObject();
    AZombie* zArr = mainObj->ZombieArray();
    int count = mainObj->ZombieCount();
    for (int i = 0; i < count; ++i) {
        AZombie* z = &zArr[i];
        if (!z->IsExist()) continue;
        if (filter(z)) return true;
    }
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
  ASetZombies("矿梯跳车 豚潜 橄丑篮杆 白红 偷");
  // 选卡 双冰 樱辣核 荷 窝喷 刺蒜
  ASelectCards("II AJN L Wc_", {ADS_36},15);
  // 3门炮列表
  aCobManager.AutoSetList();
  // 脚本重新载入模式,避免录制出错时重复启动脚本
  ASetReloadMode(AReloadMode::MAIN_UI); // 主界面重新载入
  // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI); // 主界面+选卡重新载入
  /////////////////////////////////////////////////////////////////////////////////////////
  // C4u:I-B-Nd I1-B-J/PA
  // 垫材逻辑
  // ASW在鼠标处放小喷菇大蒜窝瓜,D在鼠标处铲除植物
  At('A') Do { ACard(AXPG_8, AMouseRow(), AMouseCol()); };
  At('S') Do { ACard(ADS_36, AMouseRow(), AMouseCol()); };
  At('W') Do { ACard(AWG_17, AMouseRow(), AMouseCol()); };
  At('D') Do { AShovel(AMouseRow(), AMouseCol()); };
  // 自动放小喷
  AConnect(ANowTime(), [] {
    if (ANowTime(20) >= 4000) return false;
    if (AIsSeedUsable(AXPG_8)) ACard(AXPG_8, {{2, 4}, {2, 5}, {2, 6}, {2, 7}});
    return true;
  });
  // 窝瓜垫材自动处理下半场漏炸的红眼（需配合关闭报错使用）
  AConnect(ANowTime(), [] {
    if (ANowTime(20)>=5500) return false;
    if (ANowTime(9)>=2638 || ANowTime(10)>= 0 || ANowTime(11)<=896 || ANowTime(19)>=2638 || ANowTime(20)<=3397) {
        if (HasZombieIn(AHY_32 & PosIn(-150,17,390,390))) {
            ACard(AXPG_8, 5, 1);
            aPainter.SetTextColor(AArgb(255,255,0,0));
            aPainter.Draw(AText("提前垫", 400, 300), 500);
            return true;
        }
        if (HasZombieIn(AHY_32 & PosIn(-150,17,475,475))) {
            ACard(AXPG_8, 6, 1);
            aPainter.SetTextColor(AArgb(255,255,0,0));
            aPainter.Draw(AText("提前垫", 400, 300), 500);
            return true;
        }
        aPainter.SetTextColor(AArgb(255,0,255,0));
        aPainter.Draw(AText("正常", 400, 300), 1);
        return true;
    }
    if (HasZombieIn(AHY_32 & PosIn(-150,17,390,390))) {
        ACard(AWG_17, 5, 1);
        aPainter.SetTextColor(AArgb(255,255,0,0));
        aPainter.Draw(AText("漏炸交窝瓜", 400, 300), 500);
        return true;
    }
    if (HasZombieIn(AHY_32 & PosIn(-150,17,475,475))) {
        ACard(AWG_17, 6, 1);
        aPainter.SetTextColor(AArgb(255,255,0,0));
        aPainter.Draw(AText("漏炸交窝瓜", 400, 300), 500);
        return true;
    }
    aPainter.SetTextColor(AArgb(255,0,255,0));
    aPainter.Draw(AText("正常", 400, 300), 1);
    return true;
  });
  // 蒜刺控丑
  ATimeline CC1 = {
      At(293) Card<48>(ADC_21, 5, 9), // 扎车
      At(1365) Card<47>(ADC_21, 5, 9), // 扎部分篮球防止压大蒜，地刺26cs后生效，巨人最晚755举锤9普~1825-413-47=1365
      At(1484) Card<530>(ADS_36, 5, 8), // 1484~1586放置，多延迟一些铲兼容旗帜波晚出的小丑顺便垫一下巨人
  };
  OnWave(1_20) CC1;
  // 垫材列表
  C.SetCards({AHY_16,AWG_17});
  // 判断3-6是否有蹦极,在3-5智能放荷叶窝瓜,500之后自动铲除荷叶
  OnWave(10, 20){
      At(395) C.TriggerBy(ABJ_20 & PosIn(439, 441, 220, 220))(500,APosition{3, 5}) &
              C.TriggerBy(ABJ_20 & PosIn(439, 441, 220, 220))(500,APosition{3, 5}),
  };
  /////////////////////////////////////////////////////////////////////////////////////////
  // 循环主体
  ATimeline I_B_Nd = {
      // 1 3 5 7 9 |10 12 14 16 18 19. 20.
      At(54) I(2, 3, false), // I 54冰尾炸全收扶梯
      At(1210) P(3, 8.5),
      At(2301) N({{4, 7}, {3, 7}, {3, 8}, {4, 8}}) & D<254>(5, 3.0875), // 4-7会漏炸一路慢巨人,接3-7核能够自然解决
      At(2501 + 54) I(2, 3, true), // I'
  };
  ATimeline I1_B_JPA = {
      // 2 4 6 8 9. | 11 13 15 17 19 20
      At(1210) P(3, 8.5),
      At(2301) J(1, 1) & P(5, 7.55) & (At(254) A(5, 3)), // 延迟254全收扶梯
  };
  OnWave(1_9 % 1, 11_19 % 2) I_B_Nd | I1_B_JPA;
  /////////////////////////////////////////////////////////////////////////////////////////
  // 中场收尾特化
  // w9.
  At(ATime(9, 2501)){
      At(1210) P(2, 8), // 中场B炸实上半场
      At(2301) J(1, 1) & P(5, 6) & (At(254) A(5, 3)), //中场炸点左移伤更多巨人
  };
  // w10
  OnWave(10){
      At(54) I(2, 3, false), // I
      At(1210) P(3, 9),      // 旗帜波快速出场延迟,需要调整炸点
      At(2301) N({{4, 7}, {3, 7}, {3, 8}, {4, 8}}) & D<254>(5, 3.0875),
      At(2501 + 54) I(2, 3, true),
  };
  // w19.
  At(ATime(19, 2501)){
      At(54) I(2, 3, false), At(1210) P(2, 8),
      At(2301) N({{4, 7}, {3, 7}, {3, 8}, {4, 8}}) & D<254>(5, 3.0875),
      At(2744 + 54) I(2, 3, true), // w20的I' w19波长为5245
  };
  // w20
  OnWave(20){
      At(1210) P(3, 9), // 旗帜波快速出场延迟,需要调整炸点
      At(2301) J(1, 1) & P(5, 7.55) & (At(254) A(5, 3)),
      At(2501)
          (At(54) I(2, 3, false)) & (At(1210) P(2, 8)) & // 收尾B炸实上半场
          (At(2301) N({{4, 7}, {3, 7}, {3, 8}, {4, 8}}) & D<254>(5, 3.0875)) &
          (At(2999) Shovel({{2, 4}, {2, 5}, {2, 6}, {2, 7}})), // 于5500结束时,铲2路小喷菇恢复原阵
  };
}
// 手动介入说明：
// 1、需要手动垫/窝瓜减压2路密度过大时的巨人和下半场部分漏炸的巨人
// 2、中场收尾下半场的巨人要提前垫一下