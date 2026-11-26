#include <avz.h>
void AScript() //主函数
{
    //11怪极红
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

        //ATM_6,  // 铁门
        ATT_18, // 铁桶
        ADB_5,  // 读报
        ADB_5,  // 读报
        
        ABY_23, // 白眼 
        AHY_32, // 红眼
        AHY_32, // 红眼
        
        ABJ_20, // 蹦极
    });

    //选卡
    ASelectCards({
        AHBG_14,   // 寒冰菇
        AM_HBG_14, // 模仿寒冰菇 第一段始终是AM

        AHY_16,     //荷叶
        AHMG_15,    //毁灭菇

        ASYC_27,    //三叶草5a
        AYZBHS_37,  //保护伞6a

        ADZH_6,     //大嘴花5b
        AHP_33,     //花盆6b

        ADS_36,     //大蒜
        ADC_21,     //地刺
    });

    //自动定义炮列表并管理
    aCobManager.AutoSetList();
    //设置W为高级暂停
    AConnect('W', []{
        static bool isPaused = false;
        isPaused = !isPaused;
        ASetAdvancedPause(isPaused);
    });

    //w1特化
    for(int wave:{1})
    {
        AConnect(ATime(wave,-599),[]{ACard({{AHY_16,4,1},{AYZBHS_37,2,1}});});
    }

    //C4u:D-cC1I-BBB-B-C2c-C3-C4-B-c-BPd/C5PC6D | D-cC1I-BBB-B-C2c-C3-C4-B-c-BNd/C5NC6D

    //D-cC1I-BBB-B-C2c-C3-C4-B-c-BPd/C5PC6D
    for(int wave:{1,3,5,7,9  ,11,13,15,17,19  ,20  }) //蓝冰波
    {
        if(wave==1||wave==9||wave==19||wave==20)
        {
            if(wave==1) //1
            {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(5,8.225);});//5路D

                AConnect(ATime(wave,375),[]{ACard(ADC_21,2,9);});//刺
                AConnect(ATime(wave,425),[]{AShovel(2,9);});//铲刺

                //C1a三叶5伞6
                AConnect(ATime(wave,374),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,380),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,376-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I

                AConnect(ATime(wave,595-373),[]{aCobManager.Fire(2,6.8875);});//2路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B

                AConnect(ATime(wave,664-373),[]{aCobManager.Fire(5,8.1125);});//5路B

                //C2b大嘴花盆
                AConnect(ATime(wave,984),[]{ACard({{AHP_33,2,8},{ADZH_6,2,8}});});//花盆大嘴花
                AConnect(ATime(wave,1360),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1365),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1372),[]{ACard(ADS_36,2,8);});//蒜
                AConnect(ATime(wave,1800),[]{AShovel(2,8);});//铲蒜

                //C3a三叶5伞6
                AConnect(ATime(wave,1292),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1465),[]{AShovel({{5,9},{6,9}});});//铲
                //C4b大嘴5花盆6
                AConnect(ATime(wave,1735),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1765),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,2043),[]{ACard(ASYC_27,1,6);});//1-6垫三叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(1,6.5);});//1路B
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.6375);});//2路P
                AConnect(ATime(wave,2560-373),[]{aCobManager.Fire(1,3);});//1路d

                //C5a大蒜5伞6
                AConnect(ATime(wave,2123),[]{ACard({{ADS_36,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,2180),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8);});//5路P
                //C6b大嘴5花盆6
                AConnect(ATime(wave,2486),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,2499),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2487-373),[]{aCobManager.Fire(5,8);});//5路D

                AConnect(ATime(wave,2501+376-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
            }
            else if(wave==9) //9前
            {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(5,8.225);});//5路D

                AConnect(ATime(wave,375),[]{ACard(ADC_21,2,9);});//刺
                AConnect(ATime(wave,425),[]{AShovel(2,9);});//铲刺

                //C1a三叶5伞6
                AConnect(ATime(wave,374),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,380),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,376-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I

                AConnect(ATime(wave,595-373),[]{aCobManager.Fire(2,6.8875);});//2路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B

                AConnect(ATime(wave,664-373),[]{aCobManager.Fire(5,8.1125);});//5路B

                //C2b大嘴花盆
                AConnect(ATime(wave,984),[]{ACard({{AHP_33,2,8},{ADZH_6,2,8}});});//花盆大嘴花
                AConnect(ATime(wave,1360),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1365),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1372),[]{ACard(ADS_36,2,8);});//蒜
                AConnect(ATime(wave,1800),[]{AShovel(2,8);});//铲蒜

                //C3a三叶5伞6
                AConnect(ATime(wave,1292),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1465),[]{AShovel({{5,9},{6,9}});});//铲
                //C4b大嘴5花盆6
                AConnect(ATime(wave,1735),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1765),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,2043),[]{ACard(ASYC_27,1,6);});//1-6垫三叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(1,6.5);});//1路B
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.6375);});//2路P
                AConnect(ATime(wave,2560-373),[]{aCobManager.Fire(1,3);});//1路d

                //C5a大蒜5伞6
                AConnect(ATime(wave,2123),[]{ACard({{ADS_36,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,2180),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8);});//5路P
                //C6b大嘴5花盆6
                AConnect(ATime(wave,2486),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,2499),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2487-373),[]{aCobManager.Fire(5,8);});//5路D

                AConnect(ATime(wave,2501+376-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
            }
            else if(wave==19) //19前
            {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(5,8.225);});//5路D

                AConnect(ATime(wave,375),[]{ACard(ADC_21,2,9);});//刺
                AConnect(ATime(wave,425),[]{AShovel(2,9);});//铲刺

                //C1a三叶5伞6
                AConnect(ATime(wave,374),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,380),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,376-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I

                AConnect(ATime(wave,595-373),[]{aCobManager.Fire(2,6.8875);});//2路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B

                AConnect(ATime(wave,664-373),[]{aCobManager.Fire(5,8.1125);});//5路B

                //C2b大嘴花盆
                AConnect(ATime(wave,984),[]{ACard({{AHP_33,2,8},{ADZH_6,2,8}});});//花盆大嘴花
                AConnect(ATime(wave,1360),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1365),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1372),[]{ACard(ADS_36,2,8);});//蒜
                AConnect(ATime(wave,1800),[]{AShovel(2,8);});//铲蒜

                //C3a三叶5伞6
                AConnect(ATime(wave,1292),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1465),[]{AShovel({{5,9},{6,9}});});//铲
                //C4b大嘴5花盆6
                AConnect(ATime(wave,1735),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1765),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,2043),[]{ACard(ASYC_27,1,6);});//1-6垫三叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(1,6.5);});//1路B
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.6375);});//2路P
                AConnect(ATime(wave,2560-373),[]{aCobManager.Fire(1,3);});//1路d

                //C5a大蒜5伞6
                AConnect(ATime(wave,2123),[]{ACard({{ADS_36,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,2180),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8);});//5路P
                //C6b大嘴5花盆6
                AConnect(ATime(wave,2486),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,2499),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2487-373),[]{aCobManager.Fire(5,8);});//5路D

                AConnect(ATime(wave,2501+376-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
            }
            else //20前
            {
                AConnect(ATime(wave,100),[]{ACard(AYZBHS_37,4,1);});//偷伞
                AConnect(ATime(wave,398),[]{AShovel(4,1,AYZBHS_37);});//铲伞

                AConnect(ATime(wave,250-100),[]{ACard({AHY_16,AHMG_15},4,9);});//4-9N坑
                AConnect(ATime(wave,359-373),[]{aCobManager.Fire(1,9);});//1路S
                AConnect(ATime(wave,359-373),[]{aCobManager.Fire(5,9);});//5路S
                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(1,9);});//1路D
                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(5,9);});//5路D

                //Cb大嘴5花盆6
                AConnect(ATime(wave,365),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,599),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,359+110-100),[]{ACard(AICE_SHROOM,1,5);});//蓝冰I

                AConnect(ATime(wave,2501+376-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
            }
        }
        else
        {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(5,8.225);});//5路D

                AConnect(ATime(wave,375),[]{ACard(ADC_21,2,9);});//刺
                AConnect(ATime(wave,425),[]{AShovel(2,9);});//铲刺

                //C1a三叶5伞6
                AConnect(ATime(wave,374),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,380),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,376-100),[]{ACard(AICE_SHROOM,4,1);});//蓝冰I

                AConnect(ATime(wave,595-373),[]{aCobManager.Fire(2,6.8875);});//2路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B

                AConnect(ATime(wave,664-373),[]{aCobManager.Fire(5,8.1125);});//5路B

                //C2b大嘴花盆
                AConnect(ATime(wave,984),[]{ACard({{AHP_33,2,8},{ADZH_6,2,8}});});//花盆大嘴花
                AConnect(ATime(wave,1360),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1365),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1372),[]{ACard(ADS_36,2,8);});//蒜
                AConnect(ATime(wave,1800),[]{AShovel(2,8);});//铲蒜

                //C3a三叶5伞6
                AConnect(ATime(wave,1292),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1465),[]{AShovel({{5,9},{6,9}});});//铲
                //C4b大嘴5花盆6
                AConnect(ATime(wave,1735),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1765),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,2043),[]{ACard(ASYC_27,1,6);});//1-6垫三叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(1,6.5);});//1路B
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(2,7.6375);});//2路P
                AConnect(ATime(wave,2560-373),[]{aCobManager.Fire(1,3);});//1路d

                //C5a大蒜5伞6
                AConnect(ATime(wave,2123),[]{ACard({{ADS_36,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,2180),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(5,8);});//5路P
                //C6b大嘴5花盆6
                AConnect(ATime(wave,2486),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,2499),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2487-373),[]{aCobManager.Fire(5,8);});//5路D

                AConnect(ATime(wave,2501+376-100-319),[]{ACard(AM_ICE_SHROOM,4,1);});//白冰I'
        }
    }

    //D-cC1I-BBB-B-C2c-C3-C4-B-c-BNd/C5NC6D
    for(int wave:{2,4,6,8,  9,10,12,14,16,18,  19,  20}) //白冰波
    {
        if(wave==9||wave==10||wave==19||wave==20)
        {
            if(wave==9) //9后
            {
                AConnect(ATime(wave,2501+304-373),[]{aCobManager.Fire(5,8.225);});//5路D

                //C1a三叶5伞6
                AConnect(ATime(wave,2501+374),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,2501+380),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,2501+590-373),[]{aCobManager.Fire(2,6.8875);});//2路B
                AConnect(ATime(wave,2501+600-373),[]{aCobManager.Fire(1,6.8);});//1路B
                AConnect(ATime(wave,2501+600-373),[]{aCobManager.Fire(1,6.8);});//1路B

                AConnect(ATime(wave,2501+662-373),[]{aCobManager.Fire(4,8.1125);});//4路B
            }
            else if(wave==10) //10
            {
                AConnect(ATime(wave,100),[]{ACard(AYZBHS_37,4,1);});//偷伞
                AConnect(ATime(wave,500),[]{AShovel(4,1,AYZBHS_37);});//铲伞

                AConnect(ATime(wave,359-100),[]{ACard({AHY_16,AHMG_15},4,9);});//4-9N坑
                AConnect(ATime(wave,259-373),[]{aCobManager.Fire(1,9);});//1路S
                AConnect(ATime(wave,259-373),[]{aCobManager.Fire(5,9);});//5路S
                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(1,9);});//1路D
                AConnect(ATime(wave,359+110-373),[]{aCobManager.Fire(5,9);});//5路D

                //Cb大嘴5花盆6
                AConnect(ATime(wave,365),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,599),[]{AShovel({{5,9},{6,9}});});//铲
            }
            else if(wave==19) //19后
            {
                AConnect(ATime(wave,2501+304-373),[]{aCobManager.Fire(5,8.225);});//5路D

                //C1a三叶5伞6
                AConnect(ATime(wave,2501+374),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,2501+380),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,2501+590-373),[]{aCobManager.Fire(2,6.8875);});//2路B
                AConnect(ATime(wave,2501+600-373),[]{aCobManager.Fire(1,6.8);});//1路B
                AConnect(ATime(wave,2501+600-373),[]{aCobManager.Fire(1,6.8);});//1路B

                AConnect(ATime(wave,2501+662-373),[]{aCobManager.Fire(4,8.1125);});//4路B
            }
            else //20后
            {

            }
        }
        else
        {
                AConnect(ATime(wave,304-373),[]{aCobManager.Fire(5,8.225);});//5路D

                AConnect(ATime(wave,375),[]{ACard(ADC_21,2,9);});//刺
                AConnect(ATime(wave,425),[]{AShovel(2,9);});//铲刺

                //C1a三叶5伞6
                AConnect(ATime(wave,374),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,380),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,595-373),[]{aCobManager.Fire(2,6.8875);});//2路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B
                AConnect(ATime(wave,600-373),[]{aCobManager.Fire(1,6.8);});//1路B

                AConnect(ATime(wave,664-373),[]{aCobManager.Fire(5,8.1125);});//5路B

                //C2b大嘴花盆
                AConnect(ATime(wave,984),[]{ACard({{AHP_33,2,8},{ADZH_6,2,8}});});//花盆大嘴花
                AConnect(ATime(wave,1360),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1365),[]{AShovel(2,8);});//铲
                AConnect(ATime(wave,1372),[]{ACard(ADS_36,2,8);});//蒜
                AConnect(ATime(wave,1800),[]{AShovel(2,8);});//铲蒜

                //C3a三叶5伞6
                AConnect(ATime(wave,1292),[]{ACard({{ASYC_27,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,1465),[]{AShovel({{5,9},{6,9}});});//铲
                //C4b大嘴5花盆6
                AConnect(ATime(wave,1735),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,1765),[]{AShovel({{5,9},{6,9}});});//铲

                AConnect(ATime(wave,2043),[]{ACard(ASYC_27,1,6);});//1-6垫三叶

                AConnect(ATime(wave,2301-373),[]{aCobManager.Fire(1,6.5);});//1路B
                AConnect(ATime(wave,2301-100),[]{ACard({AHY_16,AHMG_15},{{3,7},{3,8},{3,9},{4,8}});});//3-789和4-8N坑
                AConnect(ATime(wave,2560-373),[]{aCobManager.Fire(1,3);});//1路d

                //C5a大蒜5伞6
                AConnect(ATime(wave,2123),[]{ACard({{ADS_36,5,9},{AYZBHS_37,6,9}});});
                AConnect(ATime(wave,2180),[]{AShovel({{5,9},{6,9}});});//铲
                //C6b大嘴5花盆6
                AConnect(ATime(wave,2486),[]{ACard({{ADZH_6,5,9},{AHP_33,6,9}});});
                AConnect(ATime(wave,2499),[]{AShovel({{5,9},{6,9}});});//铲
                AConnect(ATime(wave,2487-373),[]{aCobManager.Fire(5,8);});//5路D
        }
    }
}