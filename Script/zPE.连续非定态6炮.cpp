#include <avz.h>
#include <dsl/shorthand.h>
static bool Paused = false;
static bool PausedSlowed = false;

//配置参数
const int START_CS = 401;   // 首炮落地时间
const int INTERVAL = 601;   // 炮间隔
const int FLY_TIME = 373;   // 炮飞行时间

//全局路数（跨波延续）
int gRoad = 1;  // 1 = 2路，0 = 5路，第一波从2路开始


struct WaveFireState {
    int nextLand = START_CS; // 下一发落地时间
    int startClock = 0;      // 本波起始时钟
    int fireCount = 0; // 单波独立开炮计数
};
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

    // 加//即为自然出怪
    //ASetZombies({
    //ABC_12, // 冰车
    //AKG_17, // 矿工
    //AQQ_16, // 气球

    //AFT_21, // 扶梯
    //ATT_18, // 跳跳

    //AHT_14, // 海豚
    //AQS_11, // 潜水

    //AGL_7,  // 橄榄
    //AXC_15, // 小丑
    // ATL_22, // 投篮
    //ACG_3,  // 撑杆

    //ABY_23, // 白眼
    //AHY_32, // 红眼

    // APJ_0,  // 普僵
    // ALZ_2,  // 路障
    // ATT_4,  // 铁桶

    //ABJ_20, // 蹦极
    //});

    // 选卡 小 双冰樱辣核 豆南高荷
    ASelectCards("cBIIANKPTL");
    // 自动补高坚果
    aPlantFixer.Start(AGJG_23, {{3, 7}, {4, 7}}, 1500);
    // 6门炮列表
    aCobManager.SetList({{3, 1}, {3, 3}, {3, 5}, {4, 1}, {4, 3}, {4, 5}});
    // 脚本重新载入模式
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    //热键AS在鼠标处放小喷菇三叶草
    At('A') Do{ACard(AXPG_8,AMouseRow(),AMouseCol());};
    At('S') Do{ACard(ASYC_27,AMouseRow(),AMouseCol());};

    for (int wave = 1; wave <= 19; ++wave) {
        //if (wave  == 9|wave  == 19) continue; // 跳过w9 19
        AConnect(ATime(wave, 0), [=] { //lamda表达式,自动捕获外部变量
            auto state = std::make_shared<WaveFireState>(); //本波结构体指针：包括下一炮落地时机，本波时钟，发炮计数
            auto runner = std::make_shared<ATickRunner>();  //帧循环执行器

            runner->Start([=] { //lamda表达式,自动捕获外部变量
                if (state->startClock == 0) {
                    state->startClock = AGetMainObject()->GameClock();  //读取时钟赋值
                    return;
                }

                //下一波刷新 或 本波已经发4次炮确定激活 → 本波停止发炮 
                if (ANowWave(false) == wave + 1 || state->fireCount == 4) {
                    runner->Stop();     //停止并退出帧循环
                    return;
                }

                int now = AGetMainObject()->GameClock() - state->startClock;

                if (now >= state->nextLand - FLY_TIME) {
                    if (gRoad == 1) {
                        aCobManager.Fire(2, 7.9375);
                    } else {
                        aCobManager.Fire(5, 7.9375);
                    }
                    state->fireCount++;     //发炮计数
                    gRoad = !gRoad;     //换边
                    state->nextLand += INTERVAL;    //更新下一炮落地时机
                }
            });
        });
    }

    OnWave(20) {
        At(249) P(4, 7.4875),   //炮消珊瑚
    };
}