#include <avz.h>
void AScript() //主函数
{
    //11怪极红
    ASetZombies({
        ABC_12, // 冰车
        //AKG_17, // 矿工
        //AFT_21, // 扶梯
        ATT_18, // 跳跳
        AHT_14, // 海豚
        //AQQ_16, // 气球

        //AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆

        ATM_6,  // 铁门
        ATT_18, // 铁桶

        ABY_23, // 白眼
        AHY_32, // 红眼

        ABJ_20, // 蹦极
    });

    //选卡
    ASelectCards({
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM

        ADXG_13,    //胆小菇1A
        AXRK_1,     //向日葵2A
        ASYC_27,    //三叶草1B
        AWDSS_0,     //豌豆2B

        ADPG_10,    //大喷菇5A
        AYZBHS_37,  //保护伞6A
        ADZH_6,     //大嘴花5B
        AHP_33,     //花盆6B

    });

    //自动定义炮列表并管理
    aCobManager.AutoSetList();
    //设置W为高级暂停
    AConnect('W', []{
        static bool isPaused = false;
        isPaused = !isPaused;
        ASetAdvancedPause(isPaused);
    });

    //C4u:BB-c1-I-B-BB-c2-C3-c4PPDD | BB-c1-I'-B-BB-c2-C3-c4PPDD

    //BB-c1-I-B-BB-c2-C3-c4PPDD
    for(int wave:{1,3,5,7,9  ,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==1||wave==9||wave==11||wave==13||wave==19||wave==20)
        {
            if(wave==1) //1
            {
                AConnect(ATime(wave,265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,265-373),[]{aCobManager.Fire(5,8.2625);});//5路B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100),[]{ACard(AICE_SHROOM,3,5);});//蓝冰I

                AConnect(ATime(wave,730-373),[]{aCobManager.Fire(3,7.4125);});//3路B

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.4125);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.4125);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
            }
            else if(wave==9) //9前
            {
                AConnect(ATime(wave,100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100),[]{ACard(AICE_SHROOM,3,5);});//蓝冰I

                AConnect(ATime(wave,730-373),[]{aCobManager.Fire(3,7.4125);});//3路B

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.4125);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.4125);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,9);});//5路P
            }
            else if(wave==11) //11
            {
                AConnect(ATime(wave,100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100),[]{ACard(AICE_SHROOM,3,5);});//蓝冰I

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.45);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.45);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
            }
            else if(wave==13) //13
            {
                AConnect(ATime(wave,100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100),[]{ACard(AICE_SHROOM,3,5);});//蓝冰I

                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(3,7.4125);});//3路B

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.4125);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.4125);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
            }
            else if(wave==19) //19前
            {
                AConnect(ATime(wave,100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100),[]{ACard(AICE_SHROOM,3,5);});//蓝冰I

                AConnect(ATime(wave,730-373),[]{aCobManager.Fire(3,7.4125);});//3路B

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.4125);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.4125);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,9);});//5路P
            }
            else //20前
            {
                AConnect(ATime(wave,100),[]{ACard(AYZBHS_37,3,5);});//偷伞
                AConnect(ATime(wave,395),[]{AShovel(3,5,AYZBHS_37);});//铲伞

                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(1,9);});//1路D
                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(5,9);});//5路D

                AConnect(ATime(wave,535-373),[]{aCobManager.Fire(3,9);});//3路D
                AConnect(ATime(wave,535-373),[]{aCobManager.Fire(5,9);});//5路D

                AConnect(ATime(wave,500-100),[]{ACard(AICE_SHROOM,3,5);});//蓝冰I

                AConnect(ATime(wave,2862-100-319),[]{ACard(AM_ICE_SHROOM,3,5);});//白冰I'

            }
        }
        else
        {
                AConnect(ATime(wave,100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100),[]{ACard(AICE_SHROOM,3,5);});//蓝冰I

                AConnect(ATime(wave,730-373),[]{aCobManager.Fire(3,7.4125);});//3路B

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.4125);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.4125);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
        }
    }

    //BB-c1-I'-B-BB-c2-C3-c4PPDD
    for(int wave:{2,4,6,8,  9,10,12,14,16,18,  19,  20}) //白冰波
    {
        if(wave==9||wave==10||wave==12||wave==19||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                AConnect(ATime(wave,2501+290),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9}});});//胆小菇 向日葵12A
                AConnect(ATime(wave,2501+360),[]{AShovel({{1,9},{2,9}});});//铲A

                AConnect(ATime(wave,2501+500),[]{ACard({{ADPG_10,1,9},{AYZBHS_37,2,9}});});//大喷菇 保护伞12A
                AConnect(ATime(wave,2501+600),[]{AShovel({{1,9},{2,9}});});//铲A

                AConnect(ATime(wave,2501+602-100-319),[]{ACard(AM_ICE_SHROOM,3,5);});//白冰I'

                AConnect(ATime(wave,2501+800-373),[]{aCobManager.Fire(3,9);});//3路P

                //三叶草 豌豆 1-9B轮垫
                AConnect(ATime(wave,2501+1270),[]{ACard(ASYC_27,1,9);});
                AConnect(ATime(wave,2501+1415),[]{AShovel(1,9);});//铲B

                AConnect(ATime(wave,2501+1690),[]{ACard(AWDSS_0,1,9);});
                AConnect(ATime(wave,4301),[]{AShovel(1,9);});//铲B

                AConnect(ATime(wave,4301-373),[]{aCobManager.Fire(2,9);});//1路P

                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(1,9);});//1路P
                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(5,9);});//5路P
                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(2,9);});//2路P
                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(5,9);});//5路P
            }
            else if(wave==10) //10
            {
                AConnect(ATime(wave,100),[]{ACard(AYZBHS_37,3,5);});//偷伞
                AConnect(ATime(wave,500),[]{AShovel(3,5,AYZBHS_37);});//铲伞

                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(1,9);});//1路D
                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(5,9);});//5路D

                AConnect(ATime(wave,601+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,601+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
            }
            else if(wave==12) //12
            {
                AConnect(ATime(wave,100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100-319),[]{ACard(AM_ICE_SHROOM,3,5);});//白冰I'

                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(3,1);});//3路B*******
                
                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(3,7.4125);});//3路B

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.4125);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.4125);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                AConnect(ATime(wave,2501+290),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9}});});//胆小菇 向日葵12A
                AConnect(ATime(wave,2501+360),[]{AShovel({{1,9},{2,9}});});//铲A

                AConnect(ATime(wave,2501+500),[]{ACard({{ADPG_10,1,9},{AYZBHS_37,2,9}});});//大喷菇 保护伞12A
                AConnect(ATime(wave,2501+600),[]{AShovel({{1,9},{2,9}});});//铲A

                AConnect(ATime(wave,2501+602-100-319),[]{ACard(AM_ICE_SHROOM,3,5);});//白冰I'

                AConnect(ATime(wave,2501+800-373),[]{aCobManager.Fire(3,9);});//3路P

                //三叶草 豌豆 1-9B轮垫
                AConnect(ATime(wave,2501+1270),[]{ACard(ASYC_27,1,9);});
                AConnect(ATime(wave,2501+1415),[]{AShovel(1,9);});//铲B

                AConnect(ATime(wave,2501+1690),[]{ACard(AWDSS_0,1,9);});
                AConnect(ATime(wave,4301),[]{AShovel(1,9);});//铲B

                AConnect(ATime(wave,4301-373),[]{aCobManager.Fire(2,9);});//1路P

                //咆哮珊瑚
                AConnect(ATime(wave,5245+250-373),[]{aCobManager.Fire(4, 7.5875);});//1路P

                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(1,9);});//1路P
                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(5,9);});//5路P
                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(2,9);});//2路P
                AConnect(ATime(wave,5245+359-373),[]{aCobManager.Fire(5,9);});//5路P


            }
            else //20后
            {
                AConnect(ATime(wave,4500-373),[]{aCobManager.Fire(1,9);});//1路P
            }
        }
        else
        {
                AConnect(ATime(wave,100),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,400),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,520),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                AConnect(ATime(wave,602-100-319),[]{ACard(AM_ICE_SHROOM,3,5);});//白冰I'

                AConnect(ATime(wave,730-373),[]{aCobManager.Fire(3,7.4125);});//3路B

                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(2,7.4125);});//2路B
                AConnect(ATime(wave,1142-373),[]{aCobManager.Fire(5,7.4125);});//5路B

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,1400),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1770),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲B

                //胆小菇 向日葵 大喷菇 保护伞1256A
                AConnect(ATime(wave,1775),[]{ACard({{ADXG_13,1,9},{AXRK_1,2,9},{ADPG_10,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1885),[]{AShovel({{1,9},{2,9},{5,9},{6,9}});});//铲A

                //三叶草 豌豆 大嘴花 花盆1256B
                AConnect(ATime(wave,2190),[]{ACard({{ASYC_27,1,9},{AWDSS_0,2,9},{ADZH_6,5,9},{AHP_33,6,9}});});

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.5);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8.5);});//5路P

                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(1,8.3375);});//1路D
                AConnect(ATime(wave,2501+144-373),[]{aCobManager.Fire(5,8.3375);});//5路D

                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(1,8.2625);});//1路B
                AConnect(ATime(wave,2501+265-373),[]{aCobManager.Fire(5,8.2625);});//5路B
        }
    }
}