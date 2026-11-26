#include <avz.h>
APlantFixer pumpkinFixer;
void AScript() //主函数
{
    //10怪极红
    ASetZombies({
        //ABC_12, // 冰车
        AKG_17, // 矿工
        AQQ_16, // 气球

        AFT_21, // 扶梯
        ATT_18, // 跳跳
        //AHT_14, // 海豚

        AGL_7,  // 橄榄
        AXC_15, // 小丑
        ATL_22, // 投篮
        ACG_3,  // 撑杆

        ABY_23, // 白眼
        AHY_32, // 红眼
        AHY_32, // 红眼
        
        //ABJ_20, // 蹦极
    });
    //选卡
    ASelectCards({
        AYMJNP_47, //玉米炮
        AYMTS_34,  //玉米投手

        ANGT_30,   //南瓜头
        AWG_17,    //窝瓜
        ASYC_27,   //三叶草

        ACHERRY_BOMB,  // 樱桃炸弹
        AHBLJ_20,  //火爆辣椒
        AHBG_14,   // 寒冰菇

        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
        AHMG_15,   // 毁灭菇

    });
    //自动修补南瓜
    pumpkinFixer.Start(ANGT_30,{{2,3},{3,3},{4,1}});
    pumpkinFixer.SetHp(4000 / 2);
    //设定波长
    ASetWavelength({
        ATime(1,2501),ATime(2,2501),ATime(3,2501),ATime(4,2501),
        ATime(5,2501),ATime(6,2501),ATime(7,2501),ATime(8,2501),
        ATime(9,5245),
        ATime(10,2501),ATime(11,2501),ATime(12,2501),ATime(13,2501),
        ATime(14,2501),ATime(15,2501),ATime(16,2501),ATime(17,2501),ATime(18,2501),
        ATime(19,5245),
    });

    //C4u:IA-B'-P | JB"I'-N

    //w1特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard(AYMTS_34,1,2);});//玉米投手
        AConnect(ATime(wave,-599),[]{ACard(ANGT_30,1,2);});//南瓜头
        AConnect(ATime(wave,751-599),[]{ACard(AYMTS_34,1,3);});//玉米投手
        AConnect(ATime(wave,751+751-599),[]{ACard(AYMTS_34,1,4);});//玉米投手
        AConnect(ATime(wave,3001-599),[]{ACard(ANGT_30,1,3);});//南瓜头
    }

    //JB"I'-N
    for(int wave:{1,3,5,7,9  ,10,12,14,16,18,  19,  20}) //白冰波
    {
        //1路辣椒，2路炮2路B''，2路核
        if(wave==1||wave==5||wave==9  ||wave==12||wave==16||wave==  19)
        {
            if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+225-100),[]{ACard(AHBLJ_20,1,8);});//1路辣椒J
                AConnect(ATime(wave,2501+357-373),[]{aCobManager.RawFire(2,1,2,8.15);});//2路炮2路B''
                AConnect(ATime(wave,2501+358-100-319),[]{ACard(AM_ICE_SHROOM,1,1);});//白冰I'

                AConnect(ATime(wave,2501+2301-100),[]{ACard(AHMG_15,{{2,7},{2,6}});});//2-67核坑

            }
            else //5 9前 12 16
            {
                AConnect(ATime(wave,225-100),[]{ACard(AHBLJ_20,1,8);});//1路辣椒J
                AConnect(ATime(wave,357-373),[]{aCobManager.RawFire(2,1,2,8.15);});//2路炮2路B''
                AConnect(ATime(wave,358-100-319),[]{ACard(AM_ICE_SHROOM,1,1);});//白冰I'

                AConnect(ATime(wave,2301-100),[]{ACard(AHMG_15,{{2,7},{2,6}});});//2-67核坑
            }
        }
        //5路辣椒，3路炮3路B''，3路核
        else
        {
            if(wave==20) //20后
            {
                AConnect(ATime(wave,2501+225-100),[]{ACard(AHBLJ_20,5,8);});//5路辣椒J
                AConnect(ATime(wave,2501+357-373),[]{aCobManager.RawFire(3,1,3,8.15);});//3路炮3路B''
                AConnect(ATime(wave,2501+358-100-319),[]{ACard(AM_ICE_SHROOM,1,1);});//白冰I'

                AConnect(ATime(wave,2501+2301-100),[]{ACard(AHMG_15,{{3,8},{3,7}});});//3-78核坑
            }
            else //3 7 10 14 18
            {
                AConnect(ATime(wave,225-100),[]{ACard(AHBLJ_20,5,8);});//5路辣椒J
                AConnect(ATime(wave,357-373),[]{aCobManager.RawFire(3,1,3,8.15);});//3路炮3路B''
                AConnect(ATime(wave,358-100-319),[]{ACard(AM_ICE_SHROOM,1,1);});//白冰I'

                AConnect(ATime(wave,2301-100),[]{ACard(AHMG_15,{{3,8},{3,7}});});//3-78核坑
            }
        }
    }

    //IA-B'-P
    for(int wave:{2,4,6,8,  9,11,13,15,17,19  ,20  }) //蓝冰波
    {
        //3路炮打1路B'，2路炮打4路P
        if(wave==2||wave==6||wave==9||wave==13||wave==17||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+100-100),[]{ACard(AICE_SHROOM,4,8);});//蓝冰I
                AConnect(ATime(wave,2501+200-100),[]{ACard(AYTZD_2,2,8);});//樱桃A

                AConnect(ATime(wave,2501+1000-373),[]{aCobManager.RawFire(3,1,2,8);});//3路炮打B'
                AConnect(ATime(wave,2501+1000-373+206),[]{AShovel(3,1);aCobManager.Plant(3,1);});//铲种3-1炮

                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(2,1,4,7.9);});//2路炮打P
            }
            else if(wave==20) //20前
            {
                AConnect(ATime(wave,100-100),[]{ACard(AICE_SHROOM,4,8);});//蓝冰I
                AConnect(ATime(wave,200-100),[]{ACard(AYTZD_2,2,9);});//樱桃A

                AConnect(ATime(wave,1000-373),[]{aCobManager.RawFire(3,1,1,9);});//3路炮打B'
                AConnect(ATime(wave,1000-373+206),[]{AShovel(3,1);aCobManager.Plant(3,1);});//铲种3-1炮

                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(2,1,4,7.9);});//2路炮打P
            }
            else //2 6 13 17
            {
                AConnect(ATime(wave,100-100),[]{ACard(AICE_SHROOM,4,8);});//蓝冰I
                AConnect(ATime(wave,200-100),[]{ACard(AYTZD_2,2,8);});//樱桃A

                AConnect(ATime(wave,1000-373),[]{aCobManager.RawFire(3,1,1,9);});//3路炮打B'
                AConnect(ATime(wave,1000-373+206),[]{AShovel(3,1);aCobManager.Plant(3,1);});//铲种3-1炮

                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(2,1,4,7.9);});//2路炮打P
            }
        }
        //2路炮打1路B'，3路炮打4路P
        else
        {
            if(wave==19) //19前
            {
                AConnect(ATime(wave,100-100),[]{ACard(AICE_SHROOM,4,8);});//蓝冰I
                AConnect(ATime(wave,200-100),[]{ACard(AYTZD_2,2,8);});//樱桃A

                AConnect(ATime(wave,1000-373),[]{aCobManager.RawFire(2,1,1,9);});//2路炮打B'
                AConnect(ATime(wave,1000-373+206),[]{AShovel(2,1);aCobManager.Plant(2,1);});//铲种2-1炮

                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,1,4,7.9);});//3路炮打P
            }
            else //4 8 11 15
            {
                AConnect(ATime(wave,100-100),[]{ACard(AICE_SHROOM,4,8);});//蓝冰I
                AConnect(ATime(wave,200-100),[]{ACard(AYTZD_2,2,8);});//樱桃A

                AConnect(ATime(wave,1000-373),[]{aCobManager.RawFire(2,1,1,9);});//2路炮打B'
                AConnect(ATime(wave,1000-373+206),[]{AShovel(2,1);aCobManager.Plant(2,1);});//铲种2-1炮

                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,1,4,7.9);});//3路炮打P
            }
        }
    }
}