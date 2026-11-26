#include <avz.h>
int cobIndex; //炮索引
std::vector<AGrid> cobList ={{1,1},{2,1},{5,2},{6,2}};    //定义铲种炮列表并管理
void AScript() //主函数
{
    //11怪极红
    ASetZombies({
        AKG_17, // 矿工
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
        ANGT_30,   //南瓜头
    });

    aCobManager.SetList({{1,1},{2,1},{5,2},{6,2}});
    aCobManager.SetSequentialMode(ACobManager::PRIORITY);//优先级形式

    //C4u:I'-B'd/-NJ/NSd"|I-b/A-P/Pd
    //上半场:I'-B'd-NJ I-b-P
    //下半场:I'--NSd" I-A-Pd
    //四炮铲种I-B'd-Sd"|I-b-P

    //w1特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard(AHY_16,4,9);});//荷叶
        AConnect(ATime(wave,-599),[]{ACard({ANGT_30,ADC_21},6,1);});//南瓜地刺
    }

    //I'-B'd/-NJ/NSd"
    for(int wave:{1,3,5,7,9  ,10,12,14,16,18,  19,  20}) //白冰波
    {
        if(wave==1||wave==10||wave==19||wave==20)
        {
            if(wave==1)
            {
                AConnect(ATime(wave,78-100-319),[]{ACard(AM_ICE_SHROOM,4,9);});//白冰I'

                AConnect(ATime(wave,293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,1044),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,1044+50),[]{AShovel(5,8);});//铲地刺

                AConnect(ATime(wave,1795),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,2301-207),[]{AShovel(1,9);});//铲地刺
                
                AConnect(ATime(wave,2383),[]{ACard(AYMTS_34,1,9);});//玉米
                AConnect(ATime(wave,2501+42),[]{AShovel(1,9);});//铲玉米

                AConnect(ATime(wave,774-373),[]{cobIndex = aCobManager.Fire(2,8.275);});//2路B'
                AConnect(ATime(wave,774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1080-373),[]{aCobManager.Fire(1,3.05);});//1路d

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,8}});});//3-789和4-8N坑
                AConnect(ATime(wave,2301-100-100),[]{ACard(AHBLJ_20,2,4);});//2-4J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2542-373),[]{aCobManager.Fire(5,3.19);});//5路d"
            }
            else if(wave==10)
            {
                AConnect(ATime(wave,78-100-319),[]{ACard(AM_ICE_SHROOM,4,9);});//白冰I'

                AConnect(ATime(wave,293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,1044),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,1044+50),[]{AShovel(5,8);});//铲地刺

                AConnect(ATime(wave,1795),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,2301-207),[]{AShovel(1,9);});//铲地刺
                
                AConnect(ATime(wave,2383),[]{ACard(AYMTS_34,1,9);});//玉米
                AConnect(ATime(wave,2501+939),[]{AShovel(1,9);});//铲玉米

                AConnect(ATime(wave,774-373),[]{cobIndex = aCobManager.Fire(2,8.275);});//2路B'
                AConnect(ATime(wave,774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,799-373),[]{aCobManager.Fire(1,4.25);});//1路d

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,8}});});//3-789和4-8N坑
                AConnect(ATime(wave,2301-100-100),[]{ACard(AHBLJ_20,2,4);});//2-4J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2542-373),[]{aCobManager.Fire(5,3.19);});//5路d"
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,2501+293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,2501+1044),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,2501+1044+50),[]{AShovel(5,8);});//铲地刺

                AConnect(ATime(wave,2501+1795),[]{ACard(ADC_21,1,7);});//地刺
                AConnect(ATime(wave,2501+2301-207),[]{AShovel(1,7);});//铲地刺
                
                AConnect(ATime(wave,2501+2383),[]{ACard(AYMTS_34,1,5);});//玉米
                AConnect(ATime(wave,2501+2501+939),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,2501+774-373),[]{cobIndex = aCobManager.Fire(2,8.275);});//2路B'
                AConnect(ATime(wave,2501+774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,2501+1080-373),[]{aCobManager.Fire(1,3.05);});//1路d

                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,8}});});//3-789和4-8N坑
                AConnect(ATime(wave,2501+2301-100-100),[]{ACard(AHBLJ_20,2,4);});//2-4J
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2501+2542-373),[]{aCobManager.Fire(5,3.19);});//5路d"
            }
            else //20后
            {
                AConnect(ATime(wave,2501+293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,2501+293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,2501+1044),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,2501+1044+50),[]{AShovel(5,8);});//铲地刺

                AConnect(ATime(wave,2501+1795),[]{ACard(ADC_21,1,7);});//地刺
                AConnect(ATime(wave,2501+2301-207),[]{AShovel(1,7);});//铲地刺
                
                AConnect(ATime(wave,2501+2383),[]{ACard(AYMTS_34,1,5);});//玉米
                AConnect(ATime(wave,2501+2501+939),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,2501+774-373),[]{cobIndex = aCobManager.Fire(2,8.275);});//2路B'
                AConnect(ATime(wave,2501+774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,2501+1080-373),[]{aCobManager.Fire(1,3.05);});//1路d

                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,8}});});//3-789和4-8N坑
                AConnect(ATime(wave,2501+2301-100-100),[]{ACard(AHBLJ_20,2,4);});//2-4J
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2501+2542-373),[]{aCobManager.Fire(5,3.19);});//5路d"
            }
        }
        else//3,5,7,9  ,12,14,16,18
        {
            if(wave==9) //9前
            {
                AConnect(ATime(wave,293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,1044),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,1044+50),[]{AShovel(5,8);});//铲地刺

                AConnect(ATime(wave,1795),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,2301-207),[]{AShovel(1,9);});//铲地刺
                
                AConnect(ATime(wave,2383),[]{ACard(AYMTS_34,1,5);});//玉米
                AConnect(ATime(wave,2501+939),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,774-373),[]{cobIndex = aCobManager.Fire(2,8.275);});//2路B'
                AConnect(ATime(wave,774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1080-373),[]{aCobManager.Fire(1,3.05);});//1路d

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,8}});});//3-789和4-8N坑
                AConnect(ATime(wave,2301-100-100),[]{ACard(AHBLJ_20,2,4);});//2-4J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2542-373),[]{aCobManager.Fire(5,3.19);});//5路d"
            }
            else //3,5,7,12,14,16,18    //I'-B'd/-NJ/NSd"
            {
                AConnect(ATime(wave,293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,1044),[]{ACard(ADC_21,5,8);});//地刺
                AConnect(ATime(wave,1044+50),[]{AShovel(5,8);});//铲地刺

                AConnect(ATime(wave,1795),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,2301-207),[]{AShovel(1,9);});//铲地刺
                
                AConnect(ATime(wave,2383),[]{ACard(AYMTS_34,1,5);});//玉米
                AConnect(ATime(wave,2501+939),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,774-373),[]{cobIndex = aCobManager.Fire(2,8.275);});//2路B'
                AConnect(ATime(wave,774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1080-373),[]{aCobManager.Fire(1,3.05);});//1路d

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,8}});});//3-789和4-8N坑
                AConnect(ATime(wave,2301-100-100),[]{ACard(AHBLJ_20,2,4);});//2-4J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
                AConnect(ATime(wave,2542-373),[]{aCobManager.Fire(5,3.19);});//5路d"
            }
        }
    }

    //I-b/A-P/Pd
    for(int wave:{2,4,6,8,  9,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==9||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+42-100),[]{ACard(AICE_SHROOM,1,7);});//蓝冰I

                AConnect(ATime(wave,2501+293),[]{ACard(ADC_21,6,1);});//地刺

                AConnect(ATime(wave,2501+633),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,2501+633+266),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,2501+1044),[]{ACard(ADC_21,{{6,1},{1,7}});});//地刺
                AConnect(ATime(wave,2501+1118),[]{AShovel(1,7);});//铲地刺

                AConnect(ATime(wave,2501+1384),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,2501+2094),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,2501+1795),[]{ACard(ADC_21,1,8);});//地刺
                AConnect(ATime(wave,2501+1795+47),[]{AShovel(1,8);});//铲地刺

                AConnect(ATime(wave,2501+2135),[]{ACard(AYMTS_34,1,5);});//玉米（2135,2357）
                AConnect(ATime(wave,2501+2501+1080),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,2501+939-373),[]{aCobManager.Fire(1,4.25);});//1路b
                AConnect(ATime(wave,2501+600-100),[]{ACard(AYTZD_2,5,7);});//5-7A

                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.RawFire(3,2,1,7.55);});//3-2炮打1路P
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2501+2498-373),[]{aCobManager.RawFire(4,2,5,4.5);});//4-2炮打5路d

            }
            else //20前
            {
                AConnect(ATime(wave,42-100),[]{ACard(AICE_SHROOM,1,7);});//蓝冰I

                AConnect(ATime(wave,293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,633),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,633+266),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,1044),[]{ACard(ADC_21,{{6,1},{1,7}});});//地刺
                AConnect(ATime(wave,1118),[]{AShovel(1,7);});//铲地刺
                
                AConnect(ATime(wave,1384),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,2094),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,1795),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,1795+47),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,2135),[]{ACard(AYMTS_34,1,5);});//玉米（2135,2357）
                AConnect(ATime(wave,2501+1080),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,700-373),[]{aCobManager.Fire(1,4.25);});//1路b(531,799)
                AConnect(ATime(wave,600-100),[]{ACard(AYTZD_2,5,7);});//5-7A

                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,2,1,7.55);});//3-2炮打1路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2498-373),[]{aCobManager.RawFire(4,2,5,4.5);});//4-2炮打5路d

                AConnect(ATime(wave,2501+78-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},4,9);});//白冰I'
            }
        }
        else//2,4,6,8,11,13,15,17,19  ,
        {
            if(wave==19) //19前
            {
                AConnect(ATime(wave,42-100),[]{ACard(AICE_SHROOM,1,7);});//蓝冰I

                AConnect(ATime(wave,293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,633),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,633+266),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,1044),[]{ACard(ADC_21,{{6,1},{1,7}});});//地刺
                AConnect(ATime(wave,1118),[]{AShovel(1,7);});//铲地刺
                
                AConnect(ATime(wave,1384),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,2094),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,1795),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,1795+47),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,2135),[]{ACard(AYMTS_34,1,5);});//玉米（2135,2357）
                AConnect(ATime(wave,2501+1080),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,939-373),[]{aCobManager.Fire(1,4.25);});//1路b
                AConnect(ATime(wave,600-100),[]{ACard(AYTZD_2,5,7);});//5-7A

                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,2,1,7.55);});//3-2炮打1路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2498-373),[]{aCobManager.RawFire(4,2,5,4.5);});//4-2炮打5路d

                AConnect(ATime(wave,2501+78-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},4,9);});//白冰I'
            }
            else //2,4,6,8,11,13,15,17
            {
                AConnect(ATime(wave,42-100),[]{ACard(AICE_SHROOM,1,7);});//蓝冰I

                AConnect(ATime(wave,293),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,293+50),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,633),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,633+266),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,1044),[]{ACard(ADC_21,{{6,1},{1,7}});});//地刺
                AConnect(ATime(wave,1118),[]{AShovel(1,7);});//铲地刺
                
                AConnect(ATime(wave,1384),[]{ACard(AYMTS_34,1,7);});//玉米
                AConnect(ATime(wave,2094),[]{AShovel(1,7);});//铲玉米

                AConnect(ATime(wave,1795),[]{ACard(ADC_21,1,9);});//地刺
                AConnect(ATime(wave,1795+47),[]{AShovel(1,9);});//铲地刺

                AConnect(ATime(wave,2135),[]{ACard(AYMTS_34,1,5);});//玉米（2135,2357）
                AConnect(ATime(wave,2501+1080),[]{AShovel(1,5);});//铲玉米

                AConnect(ATime(wave,939-373),[]{aCobManager.Fire(1,4.25);});//1路b
                AConnect(ATime(wave,600-100),[]{ACard(AYTZD_2,5,7);});//5-7A

                AConnect(ATime(wave,2301-373),[]{aCobManager.RawFire(3,2,1,7.55);});//3-2炮打1路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2498-373),[]{aCobManager.RawFire(4,2,5,4.5);});//4-2炮打5路d

                AConnect(ATime(wave,2501+78-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},4,9);});//白冰I'
            }
        }
    }
}