#include <avz.h>

void AScript() //主函数
{
    //10怪极红
    ASetZombies({
        ABC_12, // 冰车
        AFT_21, // 扶梯
        ATT_18, // 跳跳
        AHT_14, // 海豚

        AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼

        //ABJ_20, // 蹦极
    });

    //选卡
    ASelectCards({
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
        ACHERRY_BOMB,  // 樱桃炸弹
        AHBLJ_20,  //火爆辣椒
        AHMG_15,   // 毁灭菇
        AHY_16,    // 荷叶

        AYMTS_34,  //玉米投手
        AYMJNP_47, //玉米炮

        ADC_21,   //地刺
        ADS_36,   //大蒜
    });

    //定义铲种之外的炮列表并管理
    aCobManager.SetList({{3,1},{3,5},{4,2},{4,4}});
    aCobManager.SetSequentialMode(ACobManager::SPACE);

    //C4u:I'c-ccc/B-NSS'd/NA | I-Bcc/B-Jc/P"S

    //w1特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard(AHY_16,3,7);});//荷叶
        AConnect(ATime(wave,-599),[]{ACard({{ADS_36,2,1},{ADC_21,1,3}});});//大蒜地刺
        AConnect(ATime(wave,751-599),[]{ACard({{AHY_16,3,8}});});//荷叶
        AConnect(ATime(wave,1612+751),[]{ACard(ADS_36,2,6);});//大蒜
        AConnect(ATime(wave,1612+751+751),[]{ACard(ADS_36,2,5);});//大蒜
        AConnect(ATime(wave,1612+751+751+751),[]{ACard(ADS_36,2,2);});//大蒜
    }

    //I'c-ccc/B-NSS'd/NA
    for(int wave:{1,3,5,7,9  ,10,12,14,16,18,  19,  20}) //白冰波
    {
        //S'铲2-3炮
        if(wave==1||wave==5||wave==9||wave==12||wave==16||wave==19)
        {
            if(wave==1)
            {
                AConnect(ATime(wave,78-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,155+51+155+500),[]{ACard(ADS_36,2,9);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,9);});//铲大蒜
                AConnect(ATime(wave,1612),[]{ACard(ADS_36,2,8);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,8);});//铲大蒜

                AConnect(ATime(wave,2301-100-752),[]{AShovel(3,7);});//铲荷叶
                AConnect(ATime(wave,2301-100-751),[]{ACard(AHY_16,3,7);});//种荷叶
                AConnect(ATime(wave,1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(2,3,2,7.55);});//2-3炮打2路S'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(2,3);aCobManager.Plant(2,3);});//铲种2-3炮
                AConnect(ATime(wave,2301-373+250),[]{aCobManager.Fire(1,3.2);});//1路d
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789核坑
                AConnect(ATime(wave,2301-100),[]{ACard(AYTZD_2,6,8);});//6-8樱桃
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,471),[]{ACard(AYMTS_34,2,8);});//玉米
                AConnect(ATime(wave,1197),[]{AShovel(2,8);});//铲玉米

                AConnect(ATime(wave,2501+1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B

                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(2,3,2,7.55);});//2-3炮打2路S'
                AConnect(ATime(wave,2501+2301-373+206),[]{AShovel(2,3);aCobManager.Plant(2,3);});//铲种2-3炮
                AConnect(ATime(wave,2501+2301-373+250),[]{aCobManager.Fire(1,3.2);});//1路d
                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789核坑
                AConnect(ATime(wave,2501+2301-100),[]{ACard(AYTZD_2,6,8);});//6-8樱桃
            }
            else //5 9前 12 16
            {
                AConnect(ATime(wave,471),[]{ACard(AYMTS_34,2,8);});//玉米
                AConnect(ATime(wave,1197),[]{AShovel(2,8);});//铲玉米

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,155+51+155+500),[]{ACard(ADS_36,2,9);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,9);});//铲大蒜
                AConnect(ATime(wave,1612),[]{ACard(ADS_36,2,8);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,8);});//铲大蒜

                AConnect(ATime(wave,2301-100-751-751),[]{ACard(AHY_16,3,7);});//种荷叶
                AConnect(ATime(wave,2301-100-752),[]{AShovel(3,7);});//铲荷叶
                AConnect(ATime(wave,2301-100-751),[]{ACard(AHY_16,3,7);});//种荷叶
                AConnect(ATime(wave,1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(2,3,2,7.55);});//2-3炮打2路S'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(2,3);aCobManager.Plant(2,3);});//铲种2-3炮
                AConnect(ATime(wave,2301-373+250),[]{aCobManager.Fire(1,3.2);});//1路d
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789核坑
                AConnect(ATime(wave,2301-100),[]{ACard(AYTZD_2,6,8);});//6-8樱桃
            }
        }
        //S'铲5-3炮
        else
        {
            if(wave==20) //20后
            {
                AConnect(ATime(wave,2501+471),[]{ACard(AYMTS_34,2,8);});//玉米
                AConnect(ATime(wave,2501+1197),[]{AShovel(2,8);});//铲玉米

                AConnect(ATime(wave,2501+1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B

                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(5,3,2,7.55);});//5-3炮打2路S'
                AConnect(ATime(wave,2501+2301-373+206),[]{AShovel(5,3);aCobManager.Plant(5,3);});//铲种5-3炮
                AConnect(ATime(wave,2501+2301-373+250),[]{aCobManager.Fire(1,3.2);});//1路d
                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789核坑
                AConnect(ATime(wave,2501+2301-100),[]{ACard(AYTZD_2,6,8);});//6-8樱桃
            }
            else if(wave==10)
            {
                AConnect(ATime(wave,78-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'

                AConnect(ATime(wave,471),[]{ACard(AYMTS_34,2,8);});//玉米
                AConnect(ATime(wave,1197),[]{AShovel(2,8);});//铲玉米

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,155+51+155+500),[]{ACard(ADS_36,2,9);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,9);});//铲大蒜
                AConnect(ATime(wave,1612),[]{ACard(ADS_36,2,8);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,8);});//铲大蒜

                AConnect(ATime(wave,2301-100-751-751),[]{ACard(AHY_16,3,7);});//种荷叶
                AConnect(ATime(wave,2301-100-752),[]{AShovel(3,7);});//铲荷叶
                AConnect(ATime(wave,2301-100-751),[]{ACard(AHY_16,3,7);});//种荷叶
                AConnect(ATime(wave,1185-373),[]{aCobManager.Fire(5,8.2);});//5路B

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(5,3,2,7.55);});//5-3炮打2路S'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(5,3);aCobManager.Plant(5,3);});//铲种5-3炮
                AConnect(ATime(wave,2301-373+250),[]{aCobManager.Fire(1,3.2);});//1路d
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789核坑
                AConnect(ATime(wave,2301-100),[]{ACard(AYTZD_2,6,8);});//6-8樱桃
            }
            else //3 7 14 18
            {
                AConnect(ATime(wave,471),[]{ACard(AYMTS_34,2,8);});//玉米
                AConnect(ATime(wave,1197),[]{AShovel(2,8);});//铲玉米

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,155+51+155+500),[]{ACard(ADS_36,2,9);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,9);});//铲大蒜
                AConnect(ATime(wave,1612),[]{ACard(ADS_36,2,8);});//大蒜
                AConnect(ATime(wave,2094),[]{AShovel(2,8);});//铲大蒜

                AConnect(ATime(wave,2301-100-751-751),[]{ACard(AHY_16,3,7);});//种荷叶
                AConnect(ATime(wave,2301-100-752),[]{AShovel(3,7);});//铲荷叶
                AConnect(ATime(wave,2301-100-751),[]{ACard(AHY_16,3,7);});//种荷叶
                AConnect(ATime(wave,1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(5,3,2,7.55);});//5-3炮打2路S'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(5,3);aCobManager.Plant(5,3);});//铲种5-3炮
                AConnect(ATime(wave,2301-373+250),[]{aCobManager.Fire(1,3.2);});//1路d
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789核坑
                AConnect(ATime(wave,2301-100),[]{ACard(AYTZD_2,6,8);});//6-8樱桃
            }
        }
    }

    //I-Bcc/B-Jc/P"S
    for(int wave:{2,4,6,8,  9,11,13,15,17,19  ,20  }) //蓝冰波
    {
        //B用5-3,P"用2-3
        if(wave==2||wave==6||wave==9||wave==13||wave==17||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+78-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,2501+384+751),[]{ACard(AYMTS_34,2,7);});//玉米
                AConnect(ATime(wave,2501+2501+469),[]{AShovel(2,7);});//铲玉米
                AConnect(ATime(wave,2501+1326-373),[]{aCobManager.RawFire(5,3,3,7.75);});//5-3炮打3路B
                AConnect(ATime(wave,2501+1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B

                AConnect(ATime(wave,2501+2301-100),[]{ACard(AHBLJ_20,1,4);});//1-4辣椒
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(2,3,5,7.55);});//2-3炮打5路P"
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
            }
            else if(wave==20) //20前
            {
                AConnect(ATime(wave,78-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺

                AConnect(ATime(wave,1326-373),[]{aCobManager.RawFire(5,3,3,7.75);});//5-3炮打3路B
                AConnect(ATime(wave,1185-373),[]{aCobManager.Fire(5,8.2);});//5路B
                AConnect(ATime(wave,2134),[]{ACard(AYMTS_34,2,9);});//玉米
                AConnect(ATime(wave,2501+291),[]{AShovel(2,9);});//铲玉米

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,4);});//1-4辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(2,3,5,7.55);});//2-3炮打5路P"
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2501+78-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
            else //2 6 13 17
            {
                AConnect(ATime(wave,78-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺

                AConnect(ATime(wave,1326-373),[]{aCobManager.RawFire(5,3,3,7.75);});//5-3炮打3路B
                AConnect(ATime(wave,1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B
                AConnect(ATime(wave,2134),[]{ACard(AYMTS_34,2,9);});//玉米
                AConnect(ATime(wave,2501+291),[]{AShovel(2,9);});//铲玉米

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,4);});//1-4辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(2,3,5,7.55);});//2-3炮打5路P"
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2501+78-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
        }
        //B用2-3,P"用5-3
        else
        {
            if(wave==19) //19前
            {
                AConnect(ATime(wave,78-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺

                AConnect(ATime(wave,1326-373),[]{aCobManager.RawFire(2,3,3,7.75);});//2-3炮打3路B
                AConnect(ATime(wave,1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B
                AConnect(ATime(wave,2134),[]{ACard(AYMTS_34,2,9);});//玉米
                AConnect(ATime(wave,2501+291),[]{AShovel(2,9);});//铲玉米

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,4);});//1-4辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(5,3,5,7.55);});//5-3炮打5路P"
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2501+78-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
            else //4 8 11 15
            {
                AConnect(ATime(wave,78-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,293),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(2,9);});//铲地刺
                AConnect(ATime(wave,293+751),[]{ACard(ADC_21,6,8);});//地刺
                AConnect(ATime(wave,1556),[]{AShovel(6,8);});//铲地刺
                AConnect(ATime(wave,293+751+751),[]{ACard(ADC_21,2,9);});//地刺
                AConnect(ATime(wave,1795+50),[]{AShovel(2,9);});//铲地刺

                AConnect(ATime(wave,1326-373),[]{aCobManager.RawFire(2,3,3,7.75);});//2-3炮打3路B
                AConnect(ATime(wave,1326-373),[]{aCobManager.Fire(5,7.6625);});//5路B
                AConnect(ATime(wave,2134),[]{ACard(AYMTS_34,2,9);});//玉米
                AConnect(ATime(wave,2501+291),[]{AShovel(2,9);});//铲玉米

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,4);});//1-4辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(5,3,5,7.55);});//5-3炮打5路P"
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2501+78-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
        }
    }
}