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

        ABJ_20, // 蹦极
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
        ASYC_27,   //三叶草
    });

    //定义铲种之外的炮列表并管理
    aCobManager.SetList({{3,1},{4,2}});
    aCobManager.SetSequentialMode(ACobManager::SPACE);

    // 双环C4u
    //I'-cc/B-JP'/P | I-B/-AN/P"N
    //I'-B/-JP'/P | I-B/-AN/P"N

    //w1特化(无)

    //I'-cc/B-JP'/P
    //I'-B/-JP'/P
    for(int wave:{1,3,5,7,9  ,10,12,14,16,18,  19,  20}) //白冰波
    {
        //I'-cc/B-JP'/P
        if(wave==1||wave==5||wave==9||wave==12||wave==16||wave==19)
        {
            if(wave==19)
            {
                AConnect(ATime(wave,2501+1-100-319),[]{ACard(AM_ICE_SHROOM,3,3);});//白冰I'

                AConnect(ATime(wave,2501+1050-373),[]{aCobManager.Fire(5,8.4);});//5路B

                AConnect(ATime(wave,2501+2301-100),[]{ACard(AHBLJ_20,1,5);});//1路辣椒
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(3,5,2,7.55);});//3-5炮打2路P'
                AConnect(ATime(wave,2501+2301-373+206),[]{AShovel(3,5);aCobManager.Plant(3,5);});//铲种3-5炮
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
            else if(wave==1)
            {
                AConnect(ATime(wave,1-100-319),[]{ACard(AM_ICE_SHROOM,3,3);});//白冰I'

                AConnect(ATime(wave,722),[]{ACard(ADC_21,2,8);});//2路地刺c
                AConnect(ATime(wave,722+27),[]{AShovel(2,8);});//铲2路地刺c
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,2,8);});//2路三叶草c
                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(4,8.4);});//4路B

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1路辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,5,2,7.55);});//3-5炮打2路P'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(3,5);aCobManager.Plant(3,5);});//铲种3-5炮,补种3-6荷叶
                AConnect(ATime(wave,2301+100),[]{ACard(AHY_16,3,6);});//铲种3-5炮,补种3-6荷叶
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
            else
            {
                AConnect(ATime(wave,722),[]{ACard(ADC_21,2,8);});//2路地刺c
                AConnect(ATime(wave,722+27),[]{AShovel(2,8);});//铲2路地刺c
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,2,8);});//2路三叶草c
                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(4,8.4);});//4路B

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1路辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,5,2,7.55);});//3-5炮打2路P'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(3,5);aCobManager.Plant(3,5);});//铲种3-5炮,补种3-6荷叶
                AConnect(ATime(wave,2301+100),[]{ACard(AHY_16,3,6);});//铲种3-5炮,补种3-6荷叶
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
        }
        //I'-B/-JP'/P
        else
        {
            if(wave==20)
            {
                AConnect(ATime(wave,2501+1-100-319),[]{ACard(AM_ICE_SHROOM,3,3);});//白冰I'

                AConnect(ATime(wave,2501+1050-373),[]{aCobManager.Fire(2,8.5);});//2路B
                AConnect(ATime(wave,501+1050-373),[]{ACard(ADC_21,5,7);});//5路地刺c

                AConnect(ATime(wave,2501+2301-100),[]{ACard(AHBLJ_20,1,5);});//1路辣椒
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(4,4,2,7.55);});//4-4炮打2路P'
                AConnect(ATime(wave,2501+2301-373+206),[]{AShovel(4,4);aCobManager.Plant(4,4);});//铲种4-4炮
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
            else if(wave==10)
            {
                AConnect(ATime(wave,1-100-319),[]{ACard(AM_ICE_SHROOM,3,3);});//白冰I'

                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,9);});//3路B
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,5,8);});//2路三叶草c

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1路辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(4,4,2,7.55);});//4-4炮打2路P'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(4,4);aCobManager.Plant(4,4);});//铲种4-4炮
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
            else
            {
                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.5);});//3路B
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,5,8);});//2路三叶草c

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1路辣椒
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(4,4,2,7.55);});//4-4炮打2路P'
                AConnect(ATime(wave,2301-373+206),[]{AShovel(4,4);aCobManager.Plant(4,4);});//铲种4-4炮
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
        }
    }

    //I-B/-AN/P"N
    //I-B/-AN/P"N
    for(int wave:{2,4,6,8,  9,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==2||wave==6||wave==9||wave==13||wave==17||wave==20)
        {
            if(wave==9)
            {
                AConnect(ATime(wave,2501+1-100),[]{ACard(AICE_SHROOM,3,3);});//蓝冰I

                AConnect(ATime(wave,2501+1050-373),[]{aCobManager.RawFire(4,4,2,8.5);});//4-4炮打2路B
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,5,8);});//2路三叶草c

                AConnect(ATime(wave,2501+2301+1),[]{ACard(AYTZD_2,2,8);});//2-8樱桃
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(3,5,5,7.55);});//3-5炮打5路P"
                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,9}});});//3-789和4-9核坑
            }
            else if(wave==20)
            {
                AConnect(ATime(wave,1-100),[]{ACard(AICE_SHROOM,3,3);});//蓝冰I

                AConnect(ATime(wave,1050-373),[]{aCobManager.RawFire(4,4,3,9);});//4-4炮打3路B
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,2,8);});//2路三叶草c

                AConnect(ATime(wave,2301+1),[]{ACard(AYTZD_2,2,8);});//2-8樱桃
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,5,5,7.55);});//3-5炮打5路P"
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,9}});});//3-789和4-9核坑
            }
            else
            {
                AConnect(ATime(wave,1-100),[]{ACard(AICE_SHROOM,3,3);});//蓝冰I

                AConnect(ATime(wave,1050-373),[]{aCobManager.RawFire(4,4,3,8.5);});//4-4炮打3路B
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,5,8);});//2路三叶草c

                AConnect(ATime(wave,2301+1),[]{ACard(AYTZD_2,2,8);});//2-8樱桃
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,5,5,7.55);});//3-5炮打5路P"
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,9}});});//3-789和4-9核坑
                AConnect(ATime(wave,2501+1-100-319),[]{ACard(AM_ICE_SHROOM,3,3);});//白冰I'
            }
        }
        else
        {
            if(wave==19)
            {
                AConnect(ATime(wave,1-100),[]{ACard(AICE_SHROOM,3,3);});//蓝冰I

                AConnect(ATime(wave,1050-373),[]{aCobManager.RawFire(3,5,3,8.5);});//3-5炮打3路B
                AConnect(ATime(wave,501+1050-373),[]{ACard(ADC_21,5,7);});//5路地刺c

                AConnect(ATime(wave,2301+1),[]{ACard(AYTZD_2,2,8);});//2-8樱桃
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(4,4,5,7.55);});//4-4炮打5路P"
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,7},{3,8}});});//3-789和4-9核坑
            }
            else
            {
                AConnect(ATime(wave,1-100),[]{ACard(AICE_SHROOM,3,3);});//蓝冰I

                AConnect(ATime(wave,1050-373),[]{aCobManager.RawFire(3,5,3,8.5);});//3-5炮打3路B
                AConnect(ATime(wave,1620),[]{ACard(ASYC_27,5,8);});//2路三叶草c

                AConnect(ATime(wave,2301+1),[]{ACard(AYTZD_2,2,8);});//2-8樱桃
                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(4,4,5,7.55);});//4-4炮打5路P"
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,7},{3,8}});});//3-789和4-9核坑
                AConnect(ATime(wave,2501+1-100-319),[]{ACard(AM_ICE_SHROOM,3,3);});//白冰I'
            }
        }
    }
}
