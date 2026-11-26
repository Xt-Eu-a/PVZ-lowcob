/*
 * 阵名: FE纯三炮
 * 节奏: C4u: I-B-Nd | I'-B-PA'A (25, 25)
 */

#include <avz.h>
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; }) // 用宏定义简化代码

ACoroutine PlantAfterStart() {
    ACard(ALILY_PAD, 4, 3);
    co_await [] { return AIsSeedUsable(ATALL_NUT); };
    ACard(ATALL_NUT, 1, 1);

    co_await [] { return AIsSeedUsable(AGARLIC); };
    ACard(AGARLIC, 2, 2);
}
APlantFixer puffFodder, garlicFixer, tallnutFixer; // 自动垫小喷菇, 自动修补大蒜和高坚果
void AScript() {
    ASetZombies({
        APJ_0, // 普僵
        ACG_3, // 撑杆
        // AGL_7,  // 橄榄
        ABC_12, // 冰车
        AHT_14, // 海豚
        AXC_15, // 小丑
        AQQ_16, // 气球
        AKG_17, // 矿工
        ATT_18, // 跳跳
        ABJ_20, // 蹦极
        AFT_21, // 扶梯
        // ATL_22, // 投篮
        ABY_23, // 白眼
        AHY_32, // 红眼
    });
    ASelectCards({
        AICE_SHROOM,   // 寒冰菇
        AM_ICE_SHROOM, // 模仿寒冰菇
        ADOOM_SHROOM,  // 毁灭菇
        ACHERRY_BOMB,  // 樱桃炸弹
        AJALAPENO,     // 火爆辣椒
        ASQUASH,       // 倭瓜
        ATALL_NUT,     // 高坚果
        ALILY_PAD,     // 荷叶
        AGARLIC,       // 大蒜
        APUFF_SHROOM,  // 小喷菇
    });

    // Replay();

    Connect(1, -599,
        aCobManager.AutoSetList();
        ACoLaunch(PlantAfterStart);
        puffFodder.Start(APUFF_SHROOM, {{2, 5}, {2, 6}, {2, 7}}, -1); // 没小喷菇了才种
    );
    Connect(2, 1001, garlicFixer.Start(AGARLIC, {{2, 2}, {2, 3}}, 30)); // 大蒜血量掉到 30 时自动铲掉补种
    Connect(9, 4500, puffFodder.Pause());                               // 暂停自动垫小喷
    Connect(10, 1000, puffFodder.GoOn());                               // 恢复自动垫小喷
    Connect(10, -1, AShovel(1, 1));
    Connect(10, 1, ACard(ATALL_NUT, 1, 1));
    Connect(10, -1, AShovel(4, 3));
    Connect(10, 1, ACard(ALILY_PAD, 4, 3));
    Connect(20, 4500, garlicFixer.Stop()); // 永久停止修补大蒜
    Connect(20, 4500, puffFodder.Stop());  // 永久停止自动垫小喷
    // I-B-Nd
    for (int wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18}) {
        if (wave == 1) {
            Connect(wave, 301, ACard({ALILY_PAD, ADOOM_SHROOM}, 3, 9));      // N
            Connect(wave, 401 + 110 - 373, aCobManager.Fire(5, 7.625));      // D
            Connect(wave, 601 + 50 - 320 - 100, ACard(AM_ICE_SHROOM, 4, 3)); // 下一波 I' (时间小于 -200 , 写在本波)
            Connect(wave, 600, ACard(ASQUASH, 1, 9));                        // a
            Connect(wave, 600, ACard(AGARLIC, 2, 9));                        // a
        } else if (wave == 5 || wave == 12) {
            Connect(wave, 99 - 100, ACard(AICE_SHROOM, {{1, 6}, {4, 3}}));           // I
            Connect(wave, 1100, puffFodder.Pause());                                 // 暂停自动垫小喷
            Connect(wave, 2501 - 200 - 100, ACard({ALILY_PAD, ADOOM_SHROOM}, 4, 7)); // N
            Connect(wave, 2501 - 200 - 373 + 226, aCobManager.Fire(5, 2.7));         // d
            Connect(wave, 2501, puffFodder.GoOn());                                  // 恢复自动垫小喷
            Connect(wave, 2501 + 50 - 320 - 100, ACard(AM_ICE_SHROOM, 4, 3));        // 下一波 I' (时间小于 -200 , 写在本波)
            Connect(wave, 650, AShovel(2, 8); ACard(ASQUASH, 2, 8));                 // a
            Connect(wave, 1000 - 373, aCobManager.Fire(4, 9));                       // B
        } else if (wave == 9) {
            Connect(wave, 99 - 100, ACard(AICE_SHROOM, {{1, 6}, {4, 3}}));                               // I
            Connect(wave, 2501 - 200 - 100, ACard({ALILY_PAD, ADOOM_SHROOM}, {{3, 8}, {3, 7}, {3, 6}})); // N
            Connect(wave, 2501 - 200 - 373 + 226, aCobManager.Fire(5, 3.0125));                          // d
            Connect(wave, 2501 + 50 - 320 - 100, ACard(AM_ICE_SHROOM, 4, 3));                            // 下一波 I' (时间小于 -200 , 写在本波)
            Connect(wave, 751, ACard(ALILY_PAD, 4, 6));
            // 第 9 波收尾
            Connect(wave, 1000 - 373, aCobManager.Fire(2, 8.7375));           // B
            Connect(wave, 2501 + 1000 - 343, aCobManager.Fire(1, 6.8));       // B
            Connect(wave, 2501 + 2501 - 200 - 343, aCobManager.Fire(5, 6.5)); // P
            Connect(wave, 2501 + 2501 - 200 - 100, ACard(AJALAPENO, 1, 5));   // A'
            Connect(wave, 2501 + 2501 - 1, ACard(ACHERRY_BOMB, 5, 3));        // A
        } else {
            Connect(wave, 1000 - 373, aCobManager.Fire(3, 8.7375));                                      // B
            Connect(wave, 99 - 100, ACard(AICE_SHROOM, {{1, 6}, {4, 3}}));                               // I
            Connect(wave, 2501 - 200 - 100, ACard({ALILY_PAD, ADOOM_SHROOM}, {{3, 8}, {3, 7}, {3, 6}})); // N
            Connect(wave, 2501 - 200 - 373 + 226, aCobManager.Fire(5, 3.0125));                          // d
            Connect(wave, 2501 + 50 - 320 - 100, ACard(AM_ICE_SHROOM, 4, 3));                            // 下一波 I' (时间小于 -200 , 写在本波)
        }
    }

    // I'-B-PA'A
    for (int wave : {2, 4, 6, 8, 11, 13, 15, 17, 19, 20}) {
        Connect(wave, 2501 - 200 - 373, aCobManager.Fire(5, 7.55));             // P
        Connect(wave, 2501 - 200 - 100, AShovel(1, 5); ACard(AJALAPENO, 1, 5)); // A'
        Connect(wave, 2501 - 1, AShovel(5, 3); ACard(ACHERRY_BOMB, 5, 3));      // A
        // 第 19/20 波收尾
        if (wave == 19) {
            Connect(wave, 751, ACard(ALILY_PAD, 4, 6));
            Connect(wave, 1000 - 373, aCobManager.Fire(2, 8.7375));                         // B
            Connect(wave, 2501 + 99 - 100, ACard(AICE_SHROOM, {{1, 6}, {4, 3}}));           // I
            Connect(wave, 2501 + 1000 - 343, aCobManager.Fire(2, 7.8));                     // B
            Connect(wave, 2501 + 2501 - 200 - 150 - 343, aCobManager.Fire(5, 6.5));         // P
            Connect(wave, 2501 + 2501 - 200 - 100, ACard({ALILY_PAD, ADOOM_SHROOM}, 3, 5)); // N
            Connect(wave, 2501 - 200, ACard(ATALL_NUT, 1, 1));
        } else if (wave == 20) {
            Connect(wave, -1, AShovel(4, 6));
            Connect(wave, 99 - 320 - 100, ACard(AM_ICE_SHROOM, 2, 1)); // I'
            Connect(wave, 751, ACard(ALILY_PAD, 4, 6));
            Connect(wave, 1000 - 373, aCobManager.Fire(2, 8.7375));                         // B
            Connect(wave, 2501 + 99 - 100, ACard(AICE_SHROOM, {{1, 6}, {4, 3}}));           // I
            Connect(wave, 2501 + 1000 - 343, aCobManager.Fire(2, 7.8));                     // B
            Connect(wave, 2501 + 2501 - 200 - 150 - 343, aCobManager.Fire(5, 6.5));         // P
            Connect(wave, 2501 + 2501 - 200 - 100, ACard({ALILY_PAD, ADOOM_SHROOM}, 4, 5)); // N
            Connect(wave, -1, AShovel(1, 1));
            Connect(wave, 60, ACard(ATALL_NUT, 1, 1));
        } else {
            Connect(wave, 1000 - 373, aCobManager.Fire(3, 8.7375)); // B
            Connect(wave, 2501 - 200, ACard(ATALL_NUT, 1, 1));
        }
    }
}
