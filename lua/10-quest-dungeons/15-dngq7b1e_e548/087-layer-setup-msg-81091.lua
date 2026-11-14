local local_0
mswk81091 = "TALKFONT01/font00/I<10>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 907
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for ramNo = 100, 299 do
        be:FLGset(ramNo, 0)
    end
    g_intro = 1
end
if be:SYSgetDifficulty() == 0 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<-160,40,100>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<-40,40,100>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<-360,40,20>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<80,40,-20>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-20,40,-600>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<140,40,-520>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<200,40,-460>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<300,40,-520>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-20,40,-485>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-50,40,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<10,40,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 3, "GENERATE", "V<-20,40,-555>/V<0,0,0>")
    if be:FLGisOn(163) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-20,30,-60>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-20,30,-100>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-60,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-20,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<20,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-60,30,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-20,30,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<20,30,-180>/V<0,0,0>")
    end
    if be:FLGisOn(164) + be:FLGisOn(164) < 1 then
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<180,30,-620>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<210,31,-620>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<240,30,-620>/V<0,0,0>")
    end
    for ramNo = 1, 32 do
        if be:FLGisOn(ramNo + 113) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-E%02d", ramNo))
        end
    end
    if be:FLGisOn(162) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<240,40,260>/V<0,90,0>")
    end
    if be:FLGisOn(163) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-20,40,-35>/V<0,0,0>")
    end
    if be:FLGisOn(164) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 1, "GENERATE", "V<155,40,-620>/V<0,-90,0>/SQ_CUTLEFT")
    end
    if be:FLGisOn(165) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 2, "GENERATE", "V<265,40,-620>/V<0,90,0>/SQ_CUTRIGHT")
    end
    if be:FLGisOn(104) == 1 then
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(107) == 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(108) == 1 then
        be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    end
    if be:FLGisOn(158) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(159) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(160) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(161) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
        for ramNo = 0, 3 do
            be:sd("MODELCTRL", "g_dbutton2", ramNo, "SQ_ONLOOP")
        end
    end
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_dbutton2", ramNo, "SQ_POWERON")
    end
end
if be:SYSgetDifficulty() == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<-160,40,100>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<-40,40,100>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<-360,40,20>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<80,40,-20>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-20,40,-600>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<140,40,-520>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<200,40,-460>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<300,40,-520>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-20,40,-485>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-50,40,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<10,40,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 3, "GENERATE", "V<-20,40,-555>/V<0,0,0>")
    if be:FLGisOn(163) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-20,30,-60>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-20,30,-100>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-60,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-20,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<20,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-60,30,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-20,30,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<20,30,-180>/V<0,0,0>")
    end
    if be:FLGisOn(164) + be:FLGisOn(164) < 1 then
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<180,30,-620>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<210,31,-620>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<240,30,-620>/V<0,0,0>")
    end
    for ramNo = 1, 32 do
        if be:FLGisOn(ramNo + 113) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", ramNo))
        end
    end
    if be:FLGisOn(162) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<240,40,260>/V<0,90,0>")
    end
    if be:FLGisOn(163) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-20,40,-35>/V<0,0,0>")
    end
    if be:FLGisOn(164) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 1, "GENERATE", "V<155,40,-620>/V<0,-90,0>/SQ_CUTLEFT")
    end
    if be:FLGisOn(165) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 2, "GENERATE", "V<265,40,-620>/V<0,90,0>/SQ_CUTRIGHT")
    end
    if be:FLGisOn(104) == 1 then
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(107) == 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(108) == 1 then
        be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    end
    if be:FLGisOn(158) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(159) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(160) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(161) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
        for ramNo = 0, 3 do
            be:sd("MODELCTRL", "g_dbutton2", ramNo, "SQ_ONLOOP")
        end
    end
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_dbutton2", ramNo, "SQ_POWERON")
    end
end
if be:SYSgetDifficulty() == 2 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<-160,40,100>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<-40,40,100>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<-360,40,20>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<80,40,-20>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-20,40,-600>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<140,40,-520>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<200,40,-460>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<300,40,-520>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-20,40,-485>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-50,40,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<10,40,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 3, "GENERATE", "V<-20,40,-555>/V<0,0,0>")
    if be:FLGisOn(163) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-20,30,-60>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-20,30,-100>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-60,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-20,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<20,30,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-60,30,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-20,30,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<20,30,-180>/V<0,0,0>")
    end
    if be:FLGisOn(164) + be:FLGisOn(164) < 1 then
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<180,30,-620>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<210,31,-620>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<240,30,-620>/V<0,0,0>")
    end
    for ramNo = 1, 44 do
        if be:FLGisOn(ramNo + 113) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", ramNo))
        end
    end
    if be:FLGisOn(162) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<240,40,260>/V<0,90,0>")
    end
    if be:FLGisOn(163) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-20,40,-35>/V<0,0,0>")
    end
    if be:FLGisOn(164) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 1, "GENERATE", "V<155,40,-620>/V<0,-90,0>/SQ_CUTLEFT")
    end
    if be:FLGisOn(165) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 2, "GENERATE", "V<265,40,-620>/V<0,90,0>/SQ_CUTRIGHT")
    end
    if be:FLGisOn(104) == 1 then
        be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(107) == 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(111) + be:FLGisOn(112) == 2 then
        be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    end
    if be:FLGisOn(158) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(159) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(160) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(161) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
        for ramNo = 0, 3 do
            be:sd("MODELCTRL", "g_dbutton2", ramNo, "SQ_ONLOOP")
        end
    end
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_dbutton2", ramNo, "SQ_POWERON")
    end
end
be:MsgBox("G[FïÕxªzèOÅ·B")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
