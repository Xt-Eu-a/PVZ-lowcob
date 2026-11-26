#include <avz.h>
void AScript()
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
        AWW_8,  // 舞王
    });
    //选卡
    ASelectCards({
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM

        AKFD_35,   // 咖啡豆
        AHMG_15,   // 毁灭菇
        AHY_16,    // 荷叶

        AYTZD_2,   // 樱桃炸弹
        AHBLJ_20,  // 火爆辣椒
        ANGT_30,   // 南瓜

        AHBSS_5,   // 冰豆
        ADC_21,    // 地刺
    });
    //波长设置
    AAssumeWavelength({
        ATime(1, 601),
        ATime(2, 601),  //N
        ATime(3, 601),  //J

        ATime(4, 1309), //A
        ATime(5, 1309),
        ATime(6, 1309),

        ATime(7, 601),  //N
        ATime(8, 601),  //J

        //（764，2073，3215，4238）N（4139）J(4851）A（980）
        //w9打【IAPP IPP PP PP】（1050，2074，3216，4526）A（981）

        ATime(10, 601),
        ATime(11, 1309),
        ATime(12, 601), //N
        ATime(13, 601), //J

        ATime(14, 1309),//A
        ATime(15, 1309),
        ATime(16, 1309),

        ATime(17, 601), //N
        ATime(18, 601), //J

        //（764，2073，3215，4238）N（4139）J(4851）A（980）
        //w19打【IAPP IPP PP JP】（1050，2074，3216，4526）A（981）J(4852）

        //（304，1446，2756）N（-1106）A（736）
        //w20 打【Pao-PPI N PP PP】Pao（205）（305，1447，2757）N（1162）
        //（3525，4727，6036）N（2601）J（3313）A（4511）
    });

    //自动设置炮列表
    aCobManager.AutoSetList();
    //自动补南瓜
    aPlantFixer.Start(ANGT_30, {{1, 4}, {1, 5}, {2, 5}, {2, 6}, {5, 5}, {6, 5}});
    aPlantFixer.SetHp(4000 / 8);
    //自动存冰
    aIceFiller.Start({{3, 4}, {4, 4}, {4, 5}, {3, 5}});
    //女仆秘籍
    AMaidCheats::CallPartner();
    //设置W为高级暂停
    AConnect('W', []{
        static bool isPaused = false;
        isPaused = !isPaused;
        ASetAdvancedPause(isPaused);
    });

    for (auto wave : {1, 10})  //341 PP-I
    {

        if(wave==1)
        {
            AConnect(ATime(wave,341-373),[]{aCobManager.Fire({{2,9},{5,9}});});
        }
        else
        {
            AConnect(ATime(wave,341-373),[]{aCobManager.Fire({{2,9},{5,9}});});
            AConnect(ATime(wave,601+1-298),[]{
                aIceFiller.Coffee();
                ASetPlantActiveTime(AICE_SHROOM, 298);
            });
        }
    }
    for (auto wave : {2,7,12,17})  //341 N
    {
        AConnect(ATime(wave,341-298),[]{
            ACard({AHY_16,AHMG_15,AKFD_35},{{3,8},{3,9},{4,8},{4,9}});
            ASetPlantActiveTime(ADOOM_SHROOM, 298);
        });
    }
    for (auto wave : {3,8,13,18})  //341 PPJ-I
    {
        AConnect(ATime(wave,341-373),[]{aCobManager.Fire({{2,9},{5,9}});});
        AConnect(ATime(wave,341+111-100),[]{ACard(AHBLJ_20,1,8);});
        AConnect(ATime(wave,601+1-298),[]{
            aIceFiller.Coffee();
            ASetPlantActiveTime(AICE_SHROOM, 298);
        });
    }
    for (auto wave : {4,14})  //I-PPA-i3
    {
        AConnect(ATime(wave,1109-373),[]{aCobManager.Fire({{2,9},{5,9}});});
        AConnect(ATime(wave,1309-200+211-298),[]{//i3
            aIceFiller.Coffee();
            ASetPlantActiveTime(AICE_SHROOM, 298);
        });
        if(wave==4){
        AConnect(ATime(wave,1109-100),[]{ACard(AYTZD_2,5,8);});
        }
    }
    for (auto wave : {5,6,15,16})  //I3-PP-i3
    {
        AConnect(ATime(wave,1109-373),[]{aCobManager.Fire({{2,9},{5,9}});});
        if(wave==5||wave==15)
        {
            AConnect(ATime(wave,1309-200+211-298),[]{//i3
                aIceFiller.Coffee();
                ASetPlantActiveTime(AICE_SHROOM, 298);
            });
        }
    }
    for (auto wave : {11})  //I-PP
    {
        AConnect(ATime(wave,1109-373),[]{aCobManager.Fire({{2,9},{5,9}});});
    }
    //收尾
    for (auto wave : {9,19})   //IAPP IPP PP PP（1050，2074，3216，4526）A（981）//J(4852）
    {
        AConnect(ATime(wave,1050-373),[]{aCobManager.Fire({{2,9},{5,9}});});
        AConnect(ATime(wave,981-100),[]{ACard(AYTZD_2,5,8);});
        //i3
        AConnect(ATime(wave,2074-373),[]{aCobManager.Fire({{2,8.5},{5,8.5}});});
        AConnect(ATime(wave,2074+106-298),[]{
            aIceFiller.Coffee();
            ASetPlantActiveTime(AICE_SHROOM, 298);
        });

        AConnect(ATime(wave,3216-373),[]{aCobManager.Fire({{2,8.5},{5,8.5}});});
        if(wave==9)
        {
            AConnect(ATime(wave,4526-373),[]{aCobManager.Fire({{2,8.5},{5,8.5}});});
        }
        else 
        {
            AConnect(ATime(wave,4526-373),[]{aCobManager.Fire(5,8.5);});
            AConnect(ATime(wave,4852-100),[]{ACard(AHBLJ_20,1,8);});
            AConnect(ATime(wave,5245+205-373),[]{aCobManager.Fire(4,7.5875);});//Pao
        }
    }
    for (auto wave : {20})   //Pao-PPI N PP PP（205）（305，1447，2757）N（1162）
    {
        //i3
        AConnect(ATime(wave,305-373),[]{aCobManager.Fire({{2,8.5},{5,8.5}});});
        AConnect(ATime(wave,305+106-298),[]{
            aIceFiller.Coffee();
            ASetPlantActiveTime(AICE_SHROOM, 298);
        });
        AConnect(ATime(wave,305+106+751-298),[]{
            ACard({AHY_16,AHMG_15,AKFD_35},{{3,8},{3,9},{4,8},{4,9}});
            ASetPlantActiveTime(ADOOM_SHROOM, 298);
        });
        AConnect(ATime(wave,1447-373),[]{aCobManager.Fire({{2,8.5},{5,8.5}});});
        AConnect(ATime(wave,2757-373),[]{aCobManager.Fire(5,8.5);});
        AConnect(ATime(wave,3681-373),[]{aCobManager.Fire(2,8.5);});
    }

// 停止自动存冰线程
//AConnect(ATime(wave, 1800 - 373 - 200 + 1000), [=] {aIceFiller.Pause();});
}