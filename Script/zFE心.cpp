#include <avz.h>

void AScript() //主函数
{
    //12怪极红
    ASetZombies({
        ABC_12, // 冰车
        AKG_17, // 矿工
        AFT_21, // 扶梯
        ATT_18, // 跳跳
        AHT_14, // 海豚
        //AQQ_16, // 气球

        AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼

        ABJ_20, // 蹦极
        ALZ_2,  // 路障
    });

    //选卡
    ASelectCards({
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
        AHMG_15,   // 毁灭菇
        AHY_16,    // 荷叶

        AXPG_8,    // 小喷菇
        ADXG_13,   // 胆小菇
        AYGG_9,    // 阳光菇

        ADS_36,    // 大蒜
        ADC_21,    // 地刺
        AHP_33,    // 花盆


    });

    //定义炮列表并管理
    aCobManager.SetList({{1,2},{1,5},{2,1},{2,6},{3,1},{3,6},{4,2},{4,5}});
    aCobManager.SetSequentialMode(ACobManager::PRIORITY); //优先级模式

    //C4u:cDBI-B-ccc/cc-cP/P | cDBI'-B-ccc/cc-cN/NS

    //特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard(ADC_21,6,1);});//地刺
        AConnect(ATime(wave,1835-751),[]{ACard(ADC_21,6,2);});//地刺
    }
    for(int wave:{11})
    {
        AConnect(ATime(wave,1835-751),[]{ACard(ADC_21,6,1);});//地刺
    }
    for(int wave:{12})
    {
        AConnect(ATime(wave,1835-751),[]{ACard(ADC_21,6,2);});//地刺
    }
    for(int wave:{20})
    {
        AConnect(ATime(wave,3000),[]{AShovel({{6,1},{6,2}});});//铲地刺
    }

    //cDBI-B-ccc/cc-cP/P
    for(int wave:{1,3,5,7,9  ,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==1||wave==9||wave==19||wave==20)
        {
            if(wave==1) //1
            {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(1,8.225);});//1路B
                AConnect(ATime(wave,304-100),[]{ACard(AICE_SHROOM,5,6);});//蓝冰I
                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(4,8.1);});//4路B

                AConnect(ATime(wave,292),[]{ACard(ADC_21,6,9);});//地刺
                AConnect(ATime(wave,339),[]{AShovel(6,9);});//铲
                AConnect(ATime(wave,520),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,521),[]{ACard(ADS_36,2,8);});//大蒜

                AConnect(ATime(wave,970),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小1
                AConnect(ATime(wave,1046),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1415),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜2
                AConnect(ATime(wave,1420),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1835),[]{ACard(ADC_21,2,9);});//地刺3
                AConnect(ATime(wave,1840),[]{AShovel({{1,9},{2,9}});});//铲3

                AConnect(ATime(wave,1986-415),[]{AShovel(6,6);});//铲6-6
                AConnect(ATime(wave,1986),[]{ACard(AHP_33,6,6);});//花盆

                AConnect(ATime(wave,2255),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜4
                AConnect(ATime(wave,2260),[]{AShovel({{1,9},{2,9}});});//铲4
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.4);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P

                AConnect(ATime(wave,2489),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小5
                AConnect(ATime(wave,2494),[]{AShovel({{1,9},{2,9}});});//铲5
                AConnect(ATime(wave,2491-373),[]{aCobManager.Fire(1,8.3);});//1路D

                AConnect(ATime(wave,2501+304-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
            else if(wave==9) //9前
            {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(1,8.225);});//1路B
                AConnect(ATime(wave,304-100),[]{ACard(AICE_SHROOM,5,6);});//蓝冰I
                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(4,8.1);});//4路B

                AConnect(ATime(wave,292),[]{ACard(ADC_21,6,9);});//地刺
                AConnect(ATime(wave,339),[]{AShovel(6,9);});//铲
                AConnect(ATime(wave,520),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,521),[]{ACard(ADS_36,2,8);});//大蒜

                AConnect(ATime(wave,970),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小1
                AConnect(ATime(wave,1046),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1415),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜2
                AConnect(ATime(wave,1420),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1835),[]{ACard(ADC_21,2,9);});//地刺3
                AConnect(ATime(wave,1840),[]{AShovel({{1,9},{2,9}});});//铲3

                AConnect(ATime(wave,1986-415),[]{AShovel(6,6);});//铲6-6
                AConnect(ATime(wave,1986),[]{ACard(AHP_33,6,6);});//花盆

                AConnect(ATime(wave,2255),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜4
                AConnect(ATime(wave,2260),[]{AShovel({{1,9},{2,9}});});//铲4
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.4);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P

                AConnect(ATime(wave,2489),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小5
                AConnect(ATime(wave,2494),[]{AShovel({{1,9},{2,9}});});//铲5
                AConnect(ATime(wave,2491-373),[]{aCobManager.Fire(1,8.3);});//1路D

                AConnect(ATime(wave,2501+304-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
            else if(wave==19) //19前
            {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(1,8.225);});//1路B
                AConnect(ATime(wave,304-100),[]{ACard(AICE_SHROOM,5,6);});//蓝冰I
                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(4,8.1);});//4路B

                AConnect(ATime(wave,292),[]{ACard(ADC_21,6,9);});//地刺
                AConnect(ATime(wave,339),[]{AShovel(6,9);});//铲
                AConnect(ATime(wave,520),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,521),[]{ACard(ADS_36,2,8);});//大蒜

                AConnect(ATime(wave,970),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小1
                AConnect(ATime(wave,1046),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1415),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜2
                AConnect(ATime(wave,1420),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1835),[]{ACard(ADC_21,2,9);});//地刺3
                AConnect(ATime(wave,1840),[]{AShovel({{1,9},{2,9}});});//铲3

                AConnect(ATime(wave,1986-415),[]{AShovel(6,6);});//铲6-6
                AConnect(ATime(wave,1986),[]{ACard(AHP_33,6,6);});//花盆

                AConnect(ATime(wave,2255),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜4
                AConnect(ATime(wave,2260),[]{AShovel({{1,9},{2,9}});});//铲4
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.4);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P

                AConnect(ATime(wave,2489),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小5
                AConnect(ATime(wave,2494),[]{AShovel({{1,9},{2,9}});});//铲5
                AConnect(ATime(wave,2491-373),[]{aCobManager.Fire(1,8.3);});//1路D

                AConnect(ATime(wave,2501+304-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
            else //20前
            {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(2,9);});//2路P
                AConnect(ATime(wave,304-100),[]{ACard(AICE_SHROOM,5,6);});//蓝冰I
                AConnect(ATime(wave,304+600-373),[]{aCobManager.Fire(2,9);});//2路S
                AConnect(ATime(wave,904+214-373),[]{aCobManager.Fire(1,9);});//1路D

                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(4,9);});//4路P

                AConnect(ATime(wave,292),[]{ACard(ADC_21,6,9);});//地刺
                AConnect(ATime(wave,339),[]{AShovel(6,9);});//铲

                AConnect(ATime(wave,2100-373),[]{aCobManager.Fire(2,8.4);});//2路P
                AConnect(ATime(wave,2100-373),[]{aCobManager.Fire(5,7.7);});//5路P
                AConnect(ATime(wave,2501+65-100-319),[]{ACard(AM_ICE_SHROOM,1,1);});//白冰I'
            }
        }
        else
        {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(1,8.225);});//1路B
                AConnect(ATime(wave,304-100),[]{ACard(AICE_SHROOM,5,6);});//蓝冰I
                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(4,8.1);});//4路B

                AConnect(ATime(wave,292),[]{ACard(ADC_21,6,9);});//地刺
                AConnect(ATime(wave,339),[]{AShovel(6,9);});//铲
                AConnect(ATime(wave,520),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,521),[]{ACard(ADS_36,2,8);});//大蒜

                AConnect(ATime(wave,970),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小1
                AConnect(ATime(wave,1046),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1415),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜2
                AConnect(ATime(wave,1420),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1835),[]{ACard(ADC_21,2,9);});//地刺3
                AConnect(ATime(wave,1840),[]{AShovel({{1,9},{2,9}});});//铲3

                AConnect(ATime(wave,1986-415),[]{AShovel(6,6);});//铲6-6
                AConnect(ATime(wave,1986),[]{ACard(AHP_33,6,6);});//花盆

                AConnect(ATime(wave,2255),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜4
                AConnect(ATime(wave,2260),[]{AShovel({{1,9},{2,9}});});//铲4
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8.4);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P

                AConnect(ATime(wave,2489),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小5
                AConnect(ATime(wave,2494),[]{AShovel({{1,9},{2,9}});});//铲5
                AConnect(ATime(wave,2491-373),[]{aCobManager.Fire(1,8.3);});//1路D

                AConnect(ATime(wave,2501+304-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
        }
    }

    //cDBI'-B-ccc/cc-cN/NS
    for(int wave:{2,4,6,8,  9,10,12,14,16,18,  19,  20}) //白冰波
    {
        if(wave==9||wave==10||wave==19||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+304-373),[]{aCobManager.Fire(1,8.225);});//1路B
                AConnect(ATime(wave,2501+775-373),[]{aCobManager.Fire(5,8.1);});//5路B

                AConnect(ATime(wave,2501+292),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,2501+339),[]{AShovel(5,8);});//铲
                AConnect(ATime(wave,2501+520),[]{ACard(ADS_36,5,7);});//大蒜
                AConnect(ATime(wave,2501+1315),[]{AShovel(5,7);});//铲

                AConnect(ATime(wave,2501+970),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小1
                AConnect(ATime(wave,2501+1046),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,2501+1415),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜2
                AConnect(ATime(wave,2501+1420),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,2501+1835),[]{ACard(ADC_21,2,9);});//地刺3
                AConnect(ATime(wave,2501+1840),[]{AShovel({{1,9},{2,9}});});//铲3

                AConnect(ATime(wave,2501+2255),[]{ACard(ADC_21,5,6);});//地刺
                AConnect(ATime(wave,2501+2260),[]{AShovel(5,6);});//铲
                AConnect(ATime(wave,2501+2489),[]{ACard(AHP_33,5,6);});//花盆
                AConnect(ATime(wave,2501+2494),[]{AShovel(5,6);});//铲5-6

                AConnect(ATime(wave,2501+2255),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜4
                AConnect(ATime(wave,2501+2260),[]{AShovel({{1,9},{2,9}});});//铲4
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路P

                AConnect(ATime(wave,2501+2489),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小5
                AConnect(ATime(wave,2501+2494),[]{AShovel({{1,9},{2,9}});});//铲5
            }
            else if(wave==10) //10
            {
                AConnect(ATime(wave,359-373),[]{aCobManager.Fire(1,9);});//1路P
                AConnect(ATime(wave,359+108-373),[]{aCobManager.Fire(1,9);});//1路D
                AConnect(ATime(wave,359-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,8},{4,9},{4,8}});});//3-89和4-89N坑
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+304-373),[]{aCobManager.Fire(1,8.225);});//1路B
                AConnect(ATime(wave,2501+775-373),[]{aCobManager.Fire(5,8.1);});//5路B

                AConnect(ATime(wave,2501+292),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,2501+339),[]{AShovel(5,8);});//铲
                AConnect(ATime(wave,2501+520),[]{ACard(ADS_36,5,7);});//大蒜
                AConnect(ATime(wave,2501+1315),[]{AShovel(5,7);});//铲

                AConnect(ATime(wave,2501+970),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小1
                AConnect(ATime(wave,2501+975),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,2501+1415),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜2
                AConnect(ATime(wave,2501+1420),[]{AShovel({{1,9},{2,9}});});//铲2

                AConnect(ATime(wave,2501+1835),[]{ACard(ADC_21,2,9);});//地刺3
                AConnect(ATime(wave,2501+1840),[]{AShovel({{5,6},{6,5}});});//铲3
                AConnect(ATime(wave,2501+2255),[]{ACard({{AYGG_9,5,6},{ADS_36,6,5}});});//阳光菇大蒜4
                AConnect(ATime(wave,2501+2260),[]{AShovel({{5,6},{6,5}});});//铲4
                AConnect(ATime(wave,2501+2489),[]{ACard({{AXPG_8,5,6},{ADXG_13,6,5}});});//小喷胆小5
                AConnect(ATime(wave,2501+2494),[]{AShovel({{5,6},{6,5}});});//铲5

                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,8},{4,9},{4,8}});});//3-89和4-89N坑

                AConnect(ATime(wave,5245-150),[]{aCobManager.Fire(4,7.5875);});//4路咆哮珊瑚
            }
            else //20后
            {

            }
        }
        else
        {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(1,8.225);});//1路B
                AConnect(ATime(wave,775-373),[]{aCobManager.Fire(4,8.1);});//4路B

                AConnect(ATime(wave,292),[]{ACard(ADC_21,6,9);});//地刺
                AConnect(ATime(wave,339),[]{AShovel(6,9);});//铲

                AConnect(ATime(wave,970),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小1
                AConnect(ATime(wave,1046),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1415),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜2
                AConnect(ATime(wave,1420),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1835),[]{ACard(ADC_21,2,9);});//地刺3
                AConnect(ATime(wave,1840),[]{AShovel({{1,9},{2,9}});});//铲3

                AConnect(ATime(wave,1986-415),[]{AShovel(6,6);});//铲6-6
                AConnect(ATime(wave,1986),[]{ACard(AHP_33,6,6);});//花盆

                AConnect(ATime(wave,2255),[]{ACard({{AYGG_9,1,9},{ADS_36,2,9}});});//阳光菇大蒜4
                AConnect(ATime(wave,2260),[]{AShovel({{1,9},{2,9}});});//铲4
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,8},{4,9},{4,8}});});//3-89和4-89N坑
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P

                AConnect(ATime(wave,2489),[]{ACard({{AXPG_8,1,9},{ADXG_13,2,9}});});//小喷胆小5
                AConnect(ATime(wave,2494),[]{AShovel({{1,9},{2,9}});});//铲5
                AConnect(ATime(wave,2491-373),[]{aCobManager.Fire(1,8.3);});//1路D
        }
    }
}