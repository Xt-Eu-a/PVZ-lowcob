#include <avz.h>
int cobIndex; //炮索引
std::vector<AGrid> cobList ={{6,2},{5,3},{1,1},{2,2}};    //定义铲种炮列表并管理
ACobManager a; // 铲种炮列表
ACobManager b; // 其他炮列表
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

        ASYC_27,   //三叶草
        AYZBHS_37,   //伞
    });

    a.SetList({{{6,2},{5,3},{1,1},{2,2}}});//铲种跑列表
    b.SetList({{{3,1},{3,3},{4,2},{4,4}}});//其他炮列表
    aCobManager.SetSequentialMode(ACobManager::PRIORITY);//优先级形式

    //C4u:I'-Bd/-PA/aPd | I-B/B'd-NSd"/NDJ
    //四炮铲种:I'-B/-P/ | I-/B'd-Sd"/

    //w1特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard(AYZBHS_37,2,1);});//偷伞
        AConnect(ATime(wave,-599+751),[]{ACard(AYZBHS_37,5,2);});//偷伞
    }

    //I'-Bd/-PA/aPd
    for(int wave:{1,3,5,7,9  ,10,12,14,16,18,  19,  20}) //白冰波
    {
        if(wave==1||wave==10||wave==19||wave==20)
        {
            if(wave==1)
            {
                AConnect(ATime(wave,76-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
                
                AConnect(ATime(wave,1000-373),[]{a.Fire(3,9);});//3路B*
                AConnect(ATime(wave,1358-373),[]{b.Fire(1,2.4125);});//1路d

                AConnect(ATime(wave,2301-373),[]{a.Fire(2,7.55);});//2路P*
                AConnect(ATime(wave,2502-100),[]{ACard(AYTZD_2,1,4);});//1-4A

                AConnect(ATime(wave,2200),[]{ACard(AYZBHS_37,5,5);});//5-5伞
                AConnect(ATime(wave,2228),[]{AShovel(5,5);});//铲伞
                AConnect(ATime(wave,2229),[]{ACard(ASYC_27,5,5);});//5-5三叶草
                AConnect(ATime(wave,2350),[]{AShovel(5,5);});//铲三叶草

                AConnect(ATime(wave,2301-373),[]{b.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2577-373),[]{b.Fire(5,3.2125);});//5路d
            }
            else if(wave==10)
            {
                AConnect(ATime(wave,76-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
                
                AConnect(ATime(wave,1000-373),[]{a.Fire(3,9);});//3路B*
                AConnect(ATime(wave,1358-373),[]{b.Fire(1,2.4125);});//1路d

                AConnect(ATime(wave,2301-373),[]{a.Fire(2,7.55);});//2路P*
                AConnect(ATime(wave,2502-100),[]{ACard(AYTZD_2,1,4);});//1-4A

                AConnect(ATime(wave,2200),[]{ACard(AYZBHS_37,5,5);});//5-5伞
                AConnect(ATime(wave,2228),[]{AShovel(5,5);});//铲伞
                AConnect(ATime(wave,2229),[]{ACard(ASYC_27,5,5);});//5-5三叶草
                AConnect(ATime(wave,2350),[]{AShovel(5,5);});//铲三叶草

                AConnect(ATime(wave,2301-373),[]{b.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2577-373),[]{b.Fire(5,3.2125);});//5路d
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+1000-373),[]{a.Fire(3,9);});//3路B*
                AConnect(ATime(wave,2501+1358-373),[]{b.Fire(1,2.4125);});//1路d

                AConnect(ATime(wave,2501+2301-373),[]{a.Fire(2,7.55);});//2路P*
                AConnect(ATime(wave,2501+2502-100),[]{ACard(AYTZD_2,1,4);});//1-4A
                AConnect(ATime(wave,2501+2301-373),[]{b.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2501+2577-373),[]{b.Fire(5,3.2125);});//5路d
            }
            else //20后
            {
                AConnect(ATime(wave,2501+1000-373),[]{a.Fire(3,9);});//3路B*
                AConnect(ATime(wave,2501+1358-373),[]{b.Fire(1,2.4125);});//1路d

                AConnect(ATime(wave,2501+2301-373),[]{a.Fire(2,7.55);});//2路P*
                AConnect(ATime(wave,2501+2301-373),[]{b.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2501+2577-373),[]{b.Fire(5,3.2125);});//5路d
            }
        }
        else//3,5,7,9  ,12,14,16,18
        {
            if(wave==9) //9前
            {
                AConnect(ATime(wave,1000-373),[]{a.Fire(3,9);});//3路B*
                AConnect(ATime(wave,1358-373),[]{b.Fire(1,2.4125);});//1路d

                AConnect(ATime(wave,2301-373),[]{a.Fire(2,7.55);});//2路P*
                AConnect(ATime(wave,2502-100),[]{ACard(AYTZD_2,1,4);});//1-4A

                AConnect(ATime(wave,2200),[]{ACard(AYZBHS_37,5,5);});//5-5伞
                AConnect(ATime(wave,2228),[]{AShovel(5,5);});//铲伞
                AConnect(ATime(wave,2229),[]{ACard(ASYC_27,5,5);});//5-5三叶草
                AConnect(ATime(wave,2350),[]{AShovel(5,5);});//铲三叶草

                AConnect(ATime(wave,2301-373),[]{b.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2577-373),[]{b.Fire(5,3.2125);});//5路d
            }
            else //3,5,7,12,14,16,18    //I'-B'd/-NJ/NSd"
            {
                AConnect(ATime(wave,1000-373),[]{a.Fire(3,9);});//3路B*
                AConnect(ATime(wave,1358-373),[]{b.Fire(1,2.4125);});//1路d

                AConnect(ATime(wave,2301-373),[]{a.Fire(2,7.55);});//2路P*
                AConnect(ATime(wave,2502-100),[]{ACard(AYTZD_2,1,4);});//1-4A

                AConnect(ATime(wave,2200),[]{ACard(AYZBHS_37,5,5);});//5-5伞
                AConnect(ATime(wave,2228),[]{AShovel(5,5);});//铲伞
                AConnect(ATime(wave,2229),[]{ACard(ASYC_27,5,5);});//5-5三叶草
                AConnect(ATime(wave,2350),[]{AShovel(5,5);});//铲三叶草

                AConnect(ATime(wave,2301-373),[]{b.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2577-373),[]{b.Fire(5,3.2125);});//5路d
            }
        }
    }

    //I-B/B'd-NSd"/NDJ
    for(int wave:{2,4,6,8,  9,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==9||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+76-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,2501+900-373),[]{b.Fire(2,3);});//2路B
                AConnect(ATime(wave,2501+968-373),[]{cobIndex = a.Fire(4,9);});//4路B'
                AConnect(ATime(wave,2501+968-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                a.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,2501+1326-373),[]{a.Fire(5,2.4125);});//5路d

                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789N坑
                AConnect(ATime(wave,2501+2301-373),[]{a.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2501+2551-373),[]{a.Fire(1,3);});//1路d"
                AConnect(ATime(wave,2501+2408-373),[]{b.Fire(5,7.5375);});//5路D
                AConnect(ATime(wave,2501+2520-100),[]{ACard(AHBLJ_20,6,1);});//6-1J

            }
            else //20前
            {
                AConnect(ATime(wave,76-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,900-373),[]{b.Fire(2,3);});//2路B
                AConnect(ATime(wave,968-373),[]{cobIndex = a.Fire(4,9);});//4路B'
                AConnect(ATime(wave,968-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                a.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1326-373),[]{a.Fire(5,2.4125);});//5路d

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789N坑
                AConnect(ATime(wave,2301-373),[]{a.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2551-373),[]{a.Fire(1,3);});//1路d"
                AConnect(ATime(wave,2408-373),[]{b.Fire(5,7.5375);});//5路D
                AConnect(ATime(wave,2520-100),[]{ACard(AHBLJ_20,6,1);});//6-1J

                AConnect(ATime(wave,2501+76-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},5,1);});//白冰I'
            }
        }
        else//2,4,6,8,11,13,15,17,19  ,
        {
            if(wave==19) //19前
            {
                AConnect(ATime(wave,76-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,900-373),[]{b.Fire(2,3);});//2路B
                AConnect(ATime(wave,968-373),[]{cobIndex = a.Fire(4,9);});//4路B'
                AConnect(ATime(wave,968-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                a.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1326-373),[]{a.Fire(5,2.4125);});//5路d

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789N坑
                AConnect(ATime(wave,2301-373),[]{a.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2551-373),[]{a.Fire(1,3);});//1路d"
                AConnect(ATime(wave,2408-373),[]{b.Fire(5,7.5375);});//5路D
                AConnect(ATime(wave,2520-100),[]{ACard(AHBLJ_20,6,1);});//6-1J

                AConnect(ATime(wave,2501+76-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},5,1);});//白冰I'
            }
            else //2,4,6,8,11,13,15,17
            {
                AConnect(ATime(wave,76-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,900-373),[]{b.Fire(2,3);});//2路B
                AConnect(ATime(wave,968-373),[]{cobIndex = a.Fire(4,9);});//4路B'
                AConnect(ATime(wave,968-373+206),[]{
                AShovel(cobList[cobIndex].row, cobList[cobIndex].col); 
                a.Plant(cobList[cobIndex].row, cobList[cobIndex].col);});//铲种
                AConnect(ATime(wave,1326-373),[]{a.Fire(5,2.4125);});//5路d

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{4,7},{4,8},{4,9}});});//3-9和4-789N坑
                AConnect(ATime(wave,2301-373),[]{a.Fire(2,7.55);});//2路S
                AConnect(ATime(wave,2551-373),[]{a.Fire(1,3);});//1路d"
                AConnect(ATime(wave,2408-373),[]{b.Fire(5,7.5375);});//5路D
                AConnect(ATime(wave,2520-100),[]{ACard(AHBLJ_20,6,1);});//6-1J

                AConnect(ATime(wave,2501+76-100-319),[]{ACard({AHY_16,AM_ICE_SHROOM},5,1);});//白冰I'
            }
        }
    }
}