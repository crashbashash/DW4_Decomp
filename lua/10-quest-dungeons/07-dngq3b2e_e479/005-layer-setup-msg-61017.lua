mswk61017 = "TALKFONT01/font00/I<1>"
mswk61018 = "TALKFONT01/font00/I<2>"
mswk61019 = "TALKFONT01/font00/I<3>"
mswk61020 = "TALKFONT01/font00/I<4>"
mswk61021 = "TALKFONT01/font00/I<5>"
mswk61022 = "TALKFONT01/font01/I<6>"
mswk61023 = "TALKFONT01/font02/I<7>"
mswk61024 = "TALKFONT01/font00/I<8>"
mswk61025 = "TALKFONT01/font01/I<9>"
mswk61026 = "TALKFONT01/font02/I<10>"
mswk61027 = "TALKFONT01/font00/I<11>"
mswk61028 = "TALKFONT01/font01/I<12>"
mswk61029 = "TALKFONT01/font02/I<13>"
mswk61030 = "TALKFONT01/font00/I<14>"
mswk61031 = "TALKFONT01/font01/I<15>"
mswk61032 = "TALKFONT01/font02/I<16>"
mswk61033 = "TALKFONT01/font00/I<17>"
mswk61034 = "TALKFONT01/font01/I<18>"
mswk61035 = "TALKFONT01/font02/I<19>"
mswk61036 = "TALKFONT01/font00/I<20>"
mswk61037 = "TALKFONT01/font01/I<21>"
mswk61038 = "TALKFONT01/font02/I<22>"
mswk61039 = "TALKFONT01/font00/I<23>"
mswk61040 = "TALKFONT01/font01/I<24>"
mswk61041 = "TALKFONT01/font02/I<25>"
mswk61042 = "TALKFONT01/font00/I<26>"
mswk61043 = "TALKFONT01/font01/I<27>"
mswk61044 = "TALKFONT01/font02/I<28>"
mswk61045 = "TALKFONT01/font00/I<29>"
mswk61046 = "TALKFONT01/font01/I<30>"
mswk61047 = "TALKFONT01/font02/I<31>"
mswk61048 = "TALKFONT01/font00/I<32>"
mswk61049 = "TALKFONT01/font01/I<33>"
mswk61050 = "TALKFONT01/font02/I<34>"
mswk61051 = "TALKFONT01/font00/I<35>"
mswk61052 = "TALKFONT01/font01/I<36>"
mswk61053 = "TALKFONT01/font02/I<37>"
mswk61054 = "TALKFONT01/font00/I<38>"
mswk61055 = "TALKFONT01/font01/I<39>"
mswk61056 = "TALKFONT01/font02/I<40>"
mswk61057 = "TALKFONT01/font00/I<41>"
mswk61058 = "TALKFONT01/font01/I<42>"
mswk61059 = "TALKFONT01/font02/I<43>"
mswk61060 = "TALKFONT01/font00/I<44>"
mswk61061 = "TALKFONT01/font00/I<45>"
mswk61065 = "TALKFONT02/font00/I<46>"
mswk61066 = "TALKFONT02/font00/I<47>"
mswk61095 = "TALKFONT01/font00/I<48>"
mswk61096 = "TALKFONT01/font00/I<49>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
g_putItemSelection = 0
if be:SYSgetDifficulty() == 0 then
    g_putItemList = {}
    g_putItemList[1] = {["msgNo"] = 1, ["category"] = "flag", ["number"] = 11, ["result"] = 1}
    g_putItemList[2] = {["msgNo"] = 2, ["category"] = "weapon", ["number"] = 26, ["result"] = 0}
    g_putItemList[3] = {["msgNo"] = 3, ["category"] = "weapon", ["number"] = 76, ["result"] = 2}
    g_putItemList[4] = {["msgNo"] = 4, ["category"] = "weapon", ["number"] = 176, ["result"] = 0}
    g_putItemList[5] = {["msgNo"] = 5, ["category"] = "weapon", ["number"] = 201, ["result"] = 0}
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<20,10,400>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<100,10,280>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<-20,10,240>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-80,10,180>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-20,10,-80>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-80,10,-140>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-145,10,-200>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<0,10,-220>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<0,10,-460>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3pedstal", 0, "GENERATE", "V<0,10,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<80,10,280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<200,10,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<200,10,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<230,10,-270>/V<0,-45,0>")
    if be:FLGisOn(136) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(123) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(129) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(132) == 1 then
        be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    if be:FLGisOn(121) == 1 then
        if be:SYSctlFlagFolder("IS", 11) == 0 then
            be:DMsetSD("MODELCTRL", "g_mecha", 0, "GENERATE", "V<0,15.2,-600>/V<0,0,0>/SQ_ENTR2")
        else
            be:DMsetSD("MODELCTRL", "g_qweapon", 0, "GENERATE", "V<0,15.2,-600>/V<0,0,0>/SQ_ENTR2")
        end
    end
elseif be:SYSgetDifficulty() == 1 then
    g_putItemList = {}
    g_putItemList[1] = {["msgNo"] = 1, ["category"] = "flag", ["number"] = 11, ["result"] = 1}
    g_putItemList[2] = {["msgNo"] = 6, ["category"] = "weapon", ["number"] = 62, ["result"] = 0}
    g_putItemList[3] = {["msgNo"] = 7, ["category"] = "weapon", ["number"] = 137, ["result"] = 0}
    g_putItemList[4] = {["msgNo"] = 8, ["category"] = "armor2", ["number"] = 18, ["result"] = 2}
    g_putItemList[5] = {["msgNo"] = 9, ["category"] = "weapon", ["number"] = 236, ["result"] = 0}
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<20,10,400>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<100,10,280>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<-20,10,240>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-80,10,180>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-20,10,-80>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-80,10,-140>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-145,10,-200>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<0,10,-220>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<0,10,-460>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 9, "GENERATE", "V<-140,10,-80>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3pedstal", 0, "GENERATE", "V<0,10,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<80,10,280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<200,10,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<200,10,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<-15,10,-605>/V<0,0,0>")
    be:sd("MODELCTRL", "g_darrowshotter", 1, "GENERATE", "V<15,10,-605>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-10,10,-580>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<10,10,-580>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-10,10,-560>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<10,10,-560>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<-10,10,-540>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<10,10,-540>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<-10,10,-520>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<10,10,-520>/V<0,-90,0>")
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<230,10,-270>/V<0,-45,0>")
    if be:FLGisOn(136) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(123) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(129) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(132) == 1 then
        be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    if be:FLGisOn(144) == 1 then
        if be:FLGisOn(134) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    if be:FLGisOn(121) == 1 then
        if be:SYSctlFlagFolder("IS", 11) == 0 then
            be:DMsetSD("MODELCTRL", "g_mecha", 0, "GENERATE", "V<0,15.2,-600>/V<0,0,0>/SQ_ENTR2")
        else
            be:DMsetSD("MODELCTRL", "g_qarmor", 0, "GENERATE", "V<0,15.2,-600>/V<0,0,0>/SQ_ENTR2")
        end
    end
elseif be:SYSgetDifficulty() == 2 then
    g_putItemList = {}
    g_putItemList[1] = {["msgNo"] = 1, ["category"] = "flag", ["number"] = 11, ["result"] = 1}
    g_putItemList[2] = {["msgNo"] = 10, ["category"] = "weapon", ["number"] = 74, ["result"] = 0}
    g_putItemList[3] = {["msgNo"] = 11, ["category"] = "weapon", ["number"] = 123, ["result"] = 0}
    g_putItemList[4] = {["msgNo"] = 12, ["category"] = "armor2", ["number"] = 34, ["result"] = 0}
    g_putItemList[5] = {["msgNo"] = 13, ["category"] = "abChip", ["number"] = 183, ["result"] = 2}
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<20,10,400>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<100,10,280>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<-20,10,240>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-80,10,180>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-20,10,-80>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-80,10,-140>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-145,10,-200>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<0,10,-220>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<0,10,-460>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 9, "GENERATE", "V<-140,10,-80>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 10, "GENERATE", "V<0,10,-500>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 11, "GENERATE", "V<80,10,500>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3pedstal", 0, "GENERATE", "V<0,10,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<80,10,280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<200,10,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<200,10,-240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<135,10,280>/V<0,90,0>")
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<230,10,-270>/V<0,-45,0>")
    if be:FLGisOn(136) == 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(123) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(129) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(132) == 1 then
        be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    end
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 10, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 11, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    if be:FLGisOn(144) == 1 then
        if be:FLGisOn(134) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    if be:FLGisOn(121) == 1 then
        if be:SYSctlFlagFolder("IS", 11) == 0 then
            be:DMsetSD("MODELCTRL", "g_mecha", 0, "GENERATE", "V<0,15.2,-600>/V<0,0,0>/SQ_ENTR2")
        else
            be:DMsetSD("MODELCTRL", "g_qaccess", 0, "GENERATE", "V<0,15.2,-600>/V<0,0,0>/SQ_ENTR2")
        end
    end
else
    be:MsgBox("G[FïÕxªzèOÅ·B")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
