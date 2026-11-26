#include <avz.h>
void AScript() //主函数
{
    //11怪极红
    ASetZombies({
        ABC_12, // 冰车
        AKG_17, // 矿工
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
    });

    //选卡
    ASelectCards({
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM
        AHMG_15,   // 毁灭菇
        AHY_16,    // 荷叶
        AYTZD_2,   // 樱桃炸弹

        AYZBHS_37, // 叶子保护伞C
        ADPG_10,   // 大喷菇C

        ALJSS_28,  // 裂荚射手c
        ASYC_27,    // 三叶草c

        ANGT_30,   // 南瓜

    });

    //定义炮列表并管理
    aCobManager.SetList({{1,1},{2,1},{3,1},{1,5},{2,5}});
    //自动补南瓜
    aPlantFixer.Start(ANGT_30,{{1,3},{2,3}},2000);
    //设置W为高级暂停
    AConnect('W', []{
        static bool isPaused = false;
        isPaused = !isPaused;
        ASetAdvancedPause(isPaused);
    });

    //C4u:C5-BI-C1-c2-C3-c4P/PA | C5-BI'-C1-c2-C3-c4Nd

    //特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard(ANGT_30,1,3);});//南瓜头
        AConnect(ATime(wave,3001-599),[]{ACard(ANGT_30,2,3);});//南瓜头

        AConnect(ATime(wave,-599),[]{ACard({AHY_16,ADPG_10},3,3);});//荷叶大喷菇
        AConnect(ATime(wave,751-599),[]{ACard({AHY_16,ADPG_10},3,4);});//荷叶大喷菇

        AConnect(ATime(wave,751+751-599),[]{ACard(AHY_16,4,5);});//荷叶
        AConnect(ATime(wave,751+751+751-599),[]{ACard(AHY_16,3,6);});//荷叶
        AConnect(ATime(wave,751+751+751+751-599),[]{ACard(AHY_16,4,1);});//荷叶

        AConnect(ATime(wave,-599),[]{ACard(ALJSS_28,1,3);});//裂荚
        AConnect(ATime(wave,751-599),[]{ACard(ALJSS_28,2,3);});//裂荚
    }
    for(int wave:{2})
    {
        AConnect(ATime(wave,565),[]{ACard(ALJSS_28,1,4);});//裂荚
    }
    for(int wave:{3})
    {
        AConnect(ATime(wave,565),[]{ACard(ALJSS_28,2,4);});//裂荚
    }
    for(int wave:{4})
    {
        AConnect(ATime(wave,565),[]{ACard(ALJSS_28,{{1,4},{2,4},{3,6}});});//裂荚
    }

    //C5-BI-C1-c2-C3-c4P/PA
    for(int wave:{1,3,5,7,9  ,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==1||wave==9||wave==19||wave==20)
        {
            if(wave==1) //1
            {
                AConnect(ATime(wave,287-373),[]{aCobManager.Fire(2,8.2625);});//w1特化2路B
                AConnect(ATime(wave,287-100),[]{ACard(AICE_SHROOM,5,1);});//蓝冰I

                AConnect(ATime(wave,1063),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇1
                AConnect(ATime(wave,1065),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1480),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶2
                AConnect(ATime(wave,1482),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1897),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇3
                AConnect(ATime(wave,1899),[]{AShovel({{1,9},{2,9}});});//铲3
                AConnect(ATime(wave,2314),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶4
                AConnect(ATime(wave,2316),[]{AShovel({{1,9},{2,9}});});//铲4

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2500),[]{ACard(AYTZD_2,5,3);});//5-3A

                AConnect(ATime(wave,2501+287-100-319),[]{ACard(AM_ICE_SHROOM,5,1);});//白冰I'
            }
            else if(wave==9) //9前
            {
                AConnect(ATime(wave,148),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇5
                AConnect(ATime(wave,150),[]{AShovel({{1,9},{2,9}});});//铲5

                AConnect(ATime(wave,287-373),[]{aCobManager.Fire(1,8.25);});//1路B
                AConnect(ATime(wave,287-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I

                AConnect(ATime(wave,1063),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇1
                AConnect(ATime(wave,1310),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1480),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶2
                AConnect(ATime(wave,1482),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1897),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇3
                AConnect(ATime(wave,1899),[]{AShovel({{1,9},{2,9}});});//铲3
                AConnect(ATime(wave,2314),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶4
                AConnect(ATime(wave,2316),[]{AShovel({{1,9},{2,9}});});//铲4

                AConnect(ATime(wave,451),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,452),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶
                AConnect(ATime(wave,1202),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,1203),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶
                AConnect(ATime(wave,1953),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,1954),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2500),[]{ACard(AYTZD_2,5,3);});//5-3A

                AConnect(ATime(wave,2501+287-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
            }
            else if(wave==19) //19前
            {
                AConnect(ATime(wave,148),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇5
                AConnect(ATime(wave,150),[]{AShovel({{1,9},{2,9}});});//铲5

                AConnect(ATime(wave,287-373),[]{aCobManager.Fire(1,8.25);});//1路B
                AConnect(ATime(wave,287-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I

                AConnect(ATime(wave,1063),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇1
                AConnect(ATime(wave,1310),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1480),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶2
                AConnect(ATime(wave,1482),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1897),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇3
                AConnect(ATime(wave,1899),[]{AShovel({{1,9},{2,9}});});//铲3
                AConnect(ATime(wave,2314),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶4
                AConnect(ATime(wave,2316),[]{AShovel({{1,9},{2,9}});});//铲4

                AConnect(ATime(wave,451),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,452),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶
                AConnect(ATime(wave,1202),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,1203),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶
                AConnect(ATime(wave,1953),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,1954),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2500),[]{ACard(AYTZD_2,5,3);});//5-3A

                AConnect(ATime(wave,2501+287-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
            }
            else //20前
            {
                AConnect(ATime(wave,288-373),[]{aCobManager.Fire(2,9);});//1路B
                AConnect(ATime(wave,288-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I
            }
        }
        else
        {
                AConnect(ATime(wave,148),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇5
                AConnect(ATime(wave,150),[]{AShovel({{1,9},{2,9}});});//铲5

                AConnect(ATime(wave,287-373),[]{aCobManager.Fire(1,8.25);});//1路B
                AConnect(ATime(wave,287-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I

                AConnect(ATime(wave,1063),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇1
                AConnect(ATime(wave,1310),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1480),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶2
                AConnect(ATime(wave,1482),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1897),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇3
                AConnect(ATime(wave,1899),[]{AShovel({{1,9},{2,9}});});//铲3
                AConnect(ATime(wave,2314),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶4
                AConnect(ATime(wave,2316),[]{AShovel({{1,9},{2,9}});});//铲4

                AConnect(ATime(wave,451),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,452),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶
                AConnect(ATime(wave,1202),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,1203),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶
                AConnect(ATime(wave,1953),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,1954),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,8);});//2路P
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,7.55);});//5路P
                AConnect(ATime(wave,2500),[]{ACard(AYTZD_2,5,3);});//5-3A

                AConnect(ATime(wave,2501+287-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
        }
    }

    //C5-BI'-C1-c2-C3-c4Nd
    for(int wave:{2,4,6,8,  9,10,12,14,16,18,  19,  20}) //白冰波
    {
        if(wave==9||wave==10||wave==19||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+148),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇5
                AConnect(ATime(wave,2501+150),[]{AShovel({{1,9},{2,9}});});//铲5

                AConnect(ATime(wave,2501+287-373),[]{aCobManager.Fire(1,8.25);});//1路B

            }
            else if(wave==10) //10
            {
                AConnect(ATime(wave,332-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,9}});});//3-789和4-9N坑
                AConnect(ATime(wave,701-68-373),[]{aCobManager.Fire(5,3);});//5-3路d
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+148),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇5
                AConnect(ATime(wave,2501+150),[]{AShovel({{1,9},{2,9}});});//铲5

                AConnect(ATime(wave,2501+287-373),[]{aCobManager.Fire(1,8.25);});//1路B

                AConnect(ATime(wave,2501+2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,9}});});//3-789和4-9N坑
                AConnect(ATime(wave,2501+2601-373),[]{aCobManager.Fire(5,3);});//5-3路d
            }
            else //20后
            {


            }
        }
        else
        {
                AConnect(ATime(wave,148),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇5
                AConnect(ATime(wave,150),[]{AShovel({{1,9},{2,9}});});//铲5

                AConnect(ATime(wave,287-373),[]{aCobManager.Fire(1,8.25);});//1路B

                AConnect(ATime(wave,1063),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇1
                AConnect(ATime(wave,1310),[]{AShovel({{1,9},{2,9}});});//铲1
                AConnect(ATime(wave,1480),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶2
                AConnect(ATime(wave,1482),[]{AShovel({{1,9},{2,9}});});//铲2
                AConnect(ATime(wave,1897),[]{ACard({{AYZBHS_37,1,9},{ADPG_10,2,9}});});//叶子大喷菇3
                AConnect(ATime(wave,1899),[]{AShovel({{1,9},{2,9}});});//铲3
                AConnect(ATime(wave,2314),[]{ACard({{ALJSS_28,1,9},{ASYC_27,2,9}});});//裂荚三叶4
                AConnect(ATime(wave,2316),[]{AShovel({{1,9},{2,9}});});//铲4

                AConnect(ATime(wave,697),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,699),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶

                AConnect(ATime(wave,1448),[]{AShovel(3,5);});//铲
                AConnect(ATime(wave,1450),[]{ACard(AHY_16,{{4,5},{3,5}});});//荷叶

                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,9},{3,7},{3,8},{4,9}});});//3-789和4-9N坑
                AConnect(ATime(wave,2601-373),[]{aCobManager.Fire(5,3);});//5-3路d
        }
    }
}