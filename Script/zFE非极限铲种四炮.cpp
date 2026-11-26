#include <avz.h>
int cobIndex; //炮索引
std::vector<AGrid> cobList ={{3,3},{3,5},{4,2},{4,4}};    //定义铲种炮列表并管理
APlantFixer pumpkinFixer;
void AScript() //主函数
{
    //11怪极红
    ASetZombies({
        AKG_17, // 矿工
        ABC_12, // 冰车
        AFT_21, // 扶梯
        ATT_18, // 跳跳
        AHT_14, // 海豚
        AQQ_16, // 气球

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
        AYGG_9,    // 阳光菇 
        ANGT_30,   // 南瓜头
        AYTZD_2,   // 樱桃炸弹 

        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
        AHBLJ_20,  // 火爆辣椒
        AHMG_15,   // 毁灭菇
        AHY_16,    // 荷叶

        AYMTS_34,  // 玉米投手
        AYMJNP_47, // 玉米炮
    });

    aCobManager.SetList({{3,3},{3,5},{4,2},{4,4}});
    aCobManager.SetSequentialMode(ACobManager::PRIORITY);//优先级形式

    pumpkinFixer.Start(ANGT_30);
    pumpkinFixer.SetHp(4000 / 2);

    //C4u:I'-B'B/-J/PP" | I-B-a/NS

    //w1特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard({AHY_16,AYGG_9},4,6);});//荷叶阳光菇
    }

    //I'-B'B/-J/PP"
    for(int wave:{1,3,5,7,9  ,10,12,14,16,18,  19,  20}) //白冰波
    {
        if(wave==1||wave==10||wave==19||wave==20)
        {
            if(wave==1)
            {
                AConnect(ATime(wave,1-100-319),[]{ACard(AM_ICE_SHROOM,5,5);});//白冰I'

                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.8);});//3路B

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1-5J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2356-373),[]{aCobManager.Fire(5,7.5375);});//5路P"
            }
            else if(wave==10)
            {
                AConnect(ATime(wave,1-100-319),[]{ACard(AM_ICE_SHROOM,5,5);});//白冰I'

                AConnect(ATime(wave,531-373),[]{cobIndex = aCobManager.Fire(1,5);});//1路B'
                AConnect(ATime(wave,774-243-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.8);});//3路B

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1-5J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2356-373),[]{aCobManager.Fire(5,7.5375);});//5路P"
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+1050-373),[]{aCobManager.Fire(2,7.4);});//2路B

                AConnect(ATime(wave,2501+2301-100),[]{ACard(AHBLJ_20,1,5);});//1-5J
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
            else //20后
            {
                AConnect(ATime(wave,2501+1050-373),[]{aCobManager.Fire(2,7.4);});//2路B
                AConnect(ATime(wave,2501+2301-100),[]{ACard(AHBLJ_20,1,5);});//1-5J
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
            }
        }
        else//3,5,7,9  ,10,12,14,16,18,
        {
            if(wave==9)
            {
                AConnect(ATime(wave,774-373),[]{cobIndex = aCobManager.Fire(1,7.2125);});//1路B'
                AConnect(ATime(wave,774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.8);});//3路B

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1-5J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2356-373),[]{aCobManager.Fire(5,7.5375);});//5路P"
            }
            else //3,5,7,10,12,14,16,18,
            {
                AConnect(ATime(wave,774-373),[]{cobIndex = aCobManager.Fire(1,7.2125);});//1路B'
                AConnect(ATime(wave,774-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                aCobManager.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.8);});//3路B

                AConnect(ATime(wave,2301-100),[]{ACard(AHBLJ_20,1,5);});//1-5J
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2356-373),[]{aCobManager.Fire(5,7.5375);});//5路P"
            }
        }
    }

    //I-B-a/NS
    for(int wave:{2,4,6,8,  9,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==9||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+1),[]{ACard({AHY_16,AYGG_9},4,6);});//荷叶阳光菇
                AConnect(ATime(wave,2501+1-100),[]{ACard(AICE_SHROOM,2,8);});//蓝冰I

                AConnect(ATime(wave,2501+800-373),[]{aCobManager.Fire(2,7.4);});//2路B

                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{4,9},{3,7},{3,8},{3,9}});});//3-789和4-9N坑
                AConnect(ATime(wave,2501+2301-373),[]{aCobManager.Fire(5,7.55);});//5路S
            }
            else //20前
            {
                AConnect(ATime(wave,395-373),[]{aCobManager.Fire(1,5);});//1路P
                AConnect(ATime(wave,1),[]{ACard({AHY_16,AYGG_9},4,6);});//荷叶阳光菇
                AConnect(ATime(wave,1-100),[]{ACard(AICE_SHROOM,2,8);});//蓝冰I

                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.8);});//3路B

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{4,9},{3,7},{3,8},{3,9}});});//3-789和4-9N坑
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S

                AConnect(ATime(wave,2501+1-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},1,4);});//白冰I'
            }
        }
        else//2,4,6,8,11,13,15,17,19  ,
        {
            if(wave==19) //19前
            {
                AConnect(ATime(wave,1),[]{ACard({AHY_16,AYGG_9},4,6);});//荷叶阳光菇
                AConnect(ATime(wave,1-100),[]{ACard(AICE_SHROOM,2,8);});//蓝冰I

                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.8);});//3路B

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{4,9},{3,7},{3,8},{3,9}});});//3-789和4-9N坑
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S

                AConnect(ATime(wave,2501+1-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},1,4);});//白冰I'
            }
            else //2,4,6,8,11,13,15,17,
            {
                AConnect(ATime(wave,1),[]{ACard({AHY_16,AYGG_9},4,6);});//荷叶阳光菇
                AConnect(ATime(wave,1-100),[]{ACard(AICE_SHROOM,2,8);});//蓝冰I

                AConnect(ATime(wave,1050-373),[]{aCobManager.Fire(3,8.8);});//3路B

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{4,9},{3,7},{3,8},{3,9}});});//3-789和4-9N坑
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路S

                AConnect(ATime(wave,2501+1-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},1,4);});//白冰I'
            }
        }
    }
}