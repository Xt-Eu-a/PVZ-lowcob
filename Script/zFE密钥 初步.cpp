#include <avz.h>
#include <wingdi.h>

std::vector<AGrid> cobList = {{1, 3}, {3, 1}, {4, 1}}; // 炮列表
int cobIndex;  

void AScript()
{
    ASetZombies({
        //13怪极红
        ABC_12, // 冰车
        AFT_21, // 扶梯
        ATT_18, // 跳跳
        AQQ_16, // 气球
        AHT_14, // 海豚
        AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆
        ABY_23, // 白眼
        AHY_32, // 红眼
        ALZ_2,  // 智障
        ATM_6,  // 铁门
    });
    ASelectCards({
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇第一段始终是AM
        ACHERRY_BOMB,  // 樱桃炸弹
        AHBLJ_20,  //火爆辣椒
        AHMG_15,   // 毁灭菇
        AHY_16,    // 荷叶
        AYMTS_34,  //玉米投手
        AYMJNP_47, //玉米炮
        ABLOVER,   // 三叶草
        AGJG_23,    //高建国
    });

    AConnect(ATime(1, -599), [] {
        aCobManager.SetList(cobList);
    });

    aCobManager.SetSequentialMode(ACobManager::PRIORITY);
    // C4u：I'-B'D-Pcd"/J|I-b-Ncd/NA
    //w1特化
    for(int wave : {1})
    {
        AConnect(ATime(1,-599),[]{
        ACard(AYMTS_34,3,3);
        });
        AConnect(ATime(1,751-599),[]{
        ACard(AYMTS_34,3,4);
        });
        AConnect(ATime(1,-599),[]{
        ACard({AHY_16,AGJG_23},3,5);
        });
        AConnect(ATime(1,751-599),[]{
        ACard(AHY_16,4,5);
        });
        AConnect(ATime(1,751+751-599),[]{
        ACard({{AHY_16,4,3},{AYMTS_34,2,2}});
        });
    }
    // I'-b-Pcd'/JA
    for (int wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 19, 20})
    {

        if (wave == 19) //右
        {
            AConnect(ATime(wave, 2501 + 777 - 373 ), []{
            aCobManager.Fire(5, 2.30);
            }); // b

            AConnect(ATime(wave, 2501 + 2301 - 373 ), []{
            aCobManager.Fire(1, 7.55);
            }); // P

            AConnect(ATime(wave, 2501 + 2301 + 208 - 373),[]{
            aCobManager.RawFire(2,3,1, 3.588);
            }); // 3列炮的d'

            AConnect(ATime(wave, 2501 + 2301 + 208 - 373 + 206),[]{
            AShovel(2,3);
            aCobManager.Plant(2,2);
            });//铲种

            AConnect(ATime(wave,2501 + 2301 - 100), []{
            ACard(AHBLJ_20, {{6, 1},{6, 2}});
            }); // J

            AConnect(ATime(wave,2501 + 2301 + 270 - 100), []{
            ACard(AYTZD_2, {{5, 3},{6, 3}});
            }); // A
        }
        else if(wave==20) //左
        {
            AConnect(ATime(wave, 2501 + 777 - 373 ), []{
            aCobManager.Fire(5, 2.30);
            }); // b

            AConnect(ATime(wave, 2501 + 2301 - 373 ), []{
            aCobManager.Fire(1, 7.55);
            }); // P

            AConnect(ATime(wave, 2501 + 2301 + 208 - 373),[]{
            aCobManager.RawFire(2,2,1, 3.588);
            }); // 2列炮的d'

            AConnect(ATime(wave, 2501 + 2301 + 208 - 373 + 206),[]{
            AShovel(2,2);
            aCobManager.Plant(2,3);
            });//铲种

            AConnect(ATime(wave,2501 + 2301 - 100), []{
            ACard(AHBLJ_20, {{5, 1},{5, 2}});
            }); // J

            AConnect(ATime(wave,2501 + 2301 + 270 - 100), []{
            ACard(AYTZD_2, {{5, 3},{6, 3}});
            }); // A
        }
        else if(wave == 10)//左
        {
            AConnect(ATime(wave, 777 - 373 -243 ), []{
            aCobManager.Fire(5, 2.30);
            }); // b
            AConnect(ATime(wave, 2301 - 373 ), []{
            aCobManager.Fire(1, 7.55);
            }); // P

            AConnect(ATime(wave, 2301 + 208 - 373),[]{
            aCobManager.RawFire(2,2,1, 3.588);
            }); // 2列炮的d'

            AConnect(ATime(wave, 2301 + 208 - 373 + 206),[]{
            AShovel(2,2);
            aCobManager.Plant(2,3);
            });//铲种

            AConnect(ATime(wave,2301 - 100), []{
            ACard(AHBLJ_20, {{5, 1},{5, 2}});
            }); // J

            AConnect(ATime(wave,2301 + 270 - 100), []{
            ACard(AYTZD_2, {{5, 3},{6, 3}});
            }); // A
        }
        else if(wave==3||wave==7||wave==14||wave==18) //左
        {
            AConnect(ATime(wave, 777 - 373 ), []{
            aCobManager.Fire(5, 2.30);
            }); // b

            AConnect(ATime(wave, 2301 - 373 ), []{
            aCobManager.Fire(1, 7.55);
            }); // P

            AConnect(ATime(wave, 2301 + 208 - 373),[]{
            aCobManager.RawFire(2,2,1, 3.588);
            }); // 2列炮的d'

            AConnect(ATime(wave, 2301 + 208 - 373 + 206),[]{
            AShovel(2,2);
            aCobManager.Plant(2,3);
            });//铲种

            AConnect(ATime(wave,2301 - 100), []{
            ACard(AHBLJ_20, {{5, 1},{5, 2}});
            }); // J

            AConnect(ATime(wave,2301 + 270 - 100), []{
            ACard(AYTZD_2, {{5, 3},{6, 3}});
            }); // A
        }
        else //1 5 9 12 16右
        {
            AConnect(ATime(wave, 777 - 373 ), []{
            aCobManager.Fire(5, 2.30);
            }); // b

            AConnect(ATime(wave, 2301 - 373 ), []{
            aCobManager.Fire(1, 7.55);
            }); // P

            AConnect(ATime(wave, 2301 + 208 - 373),[]{
            aCobManager.RawFire(2,3,1, 3.588);
            }); // 3列炮的d'

            AConnect(ATime(wave, 2301 + 208 - 373 + 206),[]{
            AShovel(2,3);
            aCobManager.Plant(2,2);
            });//铲种

            AConnect(ATime(wave,2301 - 100), []{
            ACard(AHBLJ_20, {{6, 1},{6, 2}});
            }); // J

            AConnect(ATime(wave,2301 + 270 - 100), []{
            ACard(AYTZD_2, {{5, 3},{6, 3}});
            }); // A
        }
    }
    //I-BD"-Ncd/N
    for (int wave : {2, 4, 6, 8, 9, 11, 13, 15, 17, 19, 20})
    {

        if(wave == 9) //左
        {
            AConnect(ATime(wave, 2501 + 592),[]{
            ACard(AYMTS_34,1, 5);
            }); // c

            AConnect(ATime(wave, 2501 + 592 + 300), []{
            AShovel(1, 5);
            }); // 铲垫

            AConnect(ATime(wave, 2501 + 592 + 751),[]{
            ACard(AYMTS_34,{{2,2},{2,4}});
            }); // c

            AConnect(ATime(wave, 2501 + 1305 - 373),[]{
            aCobManager.Fire(2, 7.625);
            }); // B

            AConnect(ATime(wave, 2501 + 1518 - 373),[]{
            aCobManager.RawFire(2,2,1, 6.25);
            }); // 2列炮的D"

            AConnect(ATime(wave, 2501 + 2301 - 100), []{
            ACard({AHY_16, AHMG_15}, {{3, 9},{3, 6},{3, 7},{3, 8}});
            }); // N

            AConnect(ATime(wave, 2501 + 2301 + 208 - 373), []{
            aCobManager.Fire(1, 3.588);
            }); // d

        }
        else if(wave == 20)//左
        {
            AConnect(ATime(wave, 592-243),[]{
            ACard(AYMTS_34,1, 5);
            }); // c

            AConnect(ATime(wave, 592 + 300-243), []{
            AShovel(1, 5);
            }); // 铲垫

            AConnect(ATime(wave, 592 + 751-243),[]{
            ACard(AYMTS_34,{{2,2},{2,4}});
            }); // c

            AConnect(ATime(wave, 1305 - 373 - 243),[]{
            aCobManager.Fire(2, 7.625);
            }); // B

            AConnect(ATime(wave, 1518 - 373 - 243),[]{
            aCobManager.RawFire(2,2,1, 6.25);
            }); // 2列炮的D"

            AConnect(ATime(wave, 2301 - 100), []{
            ACard({AHY_16, AHMG_15}, {{3, 9},{3, 6},{3, 7},{3, 8}});
            }); // N

            AConnect(ATime(wave, 2301 + 208 - 373), []{
            aCobManager.Fire(1, 3.588);
            }); // d
        }
        else if (wave == 4||wave == 8||wave == 11||wave == 15||wave == 19) //右
        {
            AConnect(ATime(wave, 592),[]{
            ACard(AYMTS_34,1, 5);
            }); // c

            AConnect(ATime(wave, 592 + 300), []{
            AShovel(1, 5);
            }); // 铲垫

            AConnect(ATime(wave, 592 + 751),[]{
            ACard(AYMTS_34,{{2,2},{2,4}});
            }); // c

            AConnect(ATime(wave, 1305 - 373),[]{
            aCobManager.Fire(2, 7.625);
            }); // B

            AConnect(ATime(wave, 1518 - 373),[]{
            aCobManager.RawFire(2,3,1, 6.25);
            }); // 3列炮的D"

            AConnect(ATime(wave, 2301 - 100), []{
            ACard({AHY_16, AHMG_15}, {{3, 9},{3, 6},{3, 7},{3, 8}});
            }); // N

            AConnect(ATime(wave, 2301 + 208 - 373), []{
            aCobManager.Fire(1, 3.588);
            }); // d

        }

        else //2 6 13 17左
        {
            AConnect(ATime(wave, 592),[]{
            ACard(AYMTS_34,1, 5);
            }); // c

            AConnect(ATime(wave, 592 + 300), []{
            AShovel(1, 5);
            }); // 铲垫

            AConnect(ATime(wave, 592 + 751),[]{
            ACard(AYMTS_34,{{2,2},{2,4}});
            }); // c

            AConnect(ATime(wave, 1305 - 373),[]{
            aCobManager.Fire(2, 7.625);
            }); // B

            AConnect(ATime(wave, 1518 - 373),[]{
            aCobManager.RawFire(2,2,1, 6.25);
            }); // 2列炮的D"

            AConnect(ATime(wave, 2301 - 100), []{
            ACard({AHY_16, AHMG_15}, {{3, 9},{3, 6},{3, 7},{3, 8}});
            }); // N

            AConnect(ATime(wave, 2301 + 208 - 373), []{
            aCobManager.Fire(1, 3.588);
            }); // d

        }
    }
    //I' I
    for (int wave : {  1  , 2, 4, 6, 8,  9  , 11, 13, 15, 17, 19, 20})
    {
        if(wave == 1)
        {
            AConnect(ATime(wave, 135 - 100 - 319), []{
            ACard(AM_ICE_SHROOM, 1, 8);
            }); // I'
        }
        else if(wave == 9)
        {
            AConnect(ATime(wave, 2501 + 135 - 100), []{
            ACard(AICE_SHROOM, {{1,5},{4, 3},{4, 9}});
            }); // I

            AConnect(ATime(wave, 5245 + 135 - 100 - 319), []{
            ACard(AM_ICE_SHROOM, {{4, 3},{4, 9},{1, 5}});
            }); // I'
        }
        else
        {
            AConnect(ATime(wave, 135 - 100), []{
            ACard(AICE_SHROOM, {{1,5},{4, 3},{4, 9}});
            }); // I

            AConnect(ATime(wave, 2501 + 135 - 100 - 319), []{
            ACard(AM_ICE_SHROOM, {{4, 3},{4, 9},{1, 5}});
            }); // I'
        }
    }
    //c
    for (int wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 19, 20})
    {
        if(wave == 9)
        {
            AConnect(ATime(wave, 2301), []{
            ACard(ASYC_27, 1, 5);
            }); // c

            AConnect(ATime(wave, 2301 + 70), []{
            AShovel(1, 5);
            }); // 铲垫
        }
        else if(wave == 19||wave == 20)
        {
            AConnect(ATime(wave, 2501 + 2301), []{
            ACard(ASYC_27, 1, 5);
            }); // c

            AConnect(ATime(wave, 2501 + 2301 + 70), []{
            AShovel(1, 5);
            }); // 铲垫
        }
        else
        {
            AConnect(ATime(wave, 2301), []{
            ACard(ASYC_27, 1, 5);
            }); // c

            AConnect(ATime(wave, 2301 + 70), []{
            AShovel(1, 5);
            }); // 铲垫
        }
    }
}