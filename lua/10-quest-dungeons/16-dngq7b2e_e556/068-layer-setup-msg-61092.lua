local local_0
mswk61092 = "TALKFONT01/font00/I<10>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:SYSgetDifficulty() == 0 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<720,10,-300>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<440,10,-380>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<435,10,-220>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<120,10,-340>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-40,10,-220>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-140,10,-280>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-160,10,-260>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<-420,35,-480>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<-520,35,-380>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 9, "GENERATE", "V<-420,35,-160>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 10, "GENERATE", "V<-520,35,-260>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 11, "GENERATE", "V<-720,10,-100>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 12, "GENERATE", "V<-660,10,160>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 13, "GENERATE", "V<-640,10,180>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 14, "GENERATE", "V<-660,10,200>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 15, "GENERATE", "V<-680,10,180>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 16, "GENERATE", "V<-700,10,400>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 17, "GENERATE", "V<-580,10,400>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 18, "GENERATE", "V<-440,10,540>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 19, "GENERATE", "V<-240,10,540>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-660,10,145>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-625,10,180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-660,10,215>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-695,10,180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-500,10,540>/V<0,90,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-500,10,540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-150,10,540>/V<0,0,0>")
    if be:FLGisOn(177) ~= 1 and be:FLGisOn(248) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-700,0,-220>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-700,0,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-700,0,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-700,0,-100>/V<0,0,0>")
    end
    for ramNo = 1, 28 do
        if be:FLGisOn(ramNo + 187) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-E%02d", ramNo))
        end
    end
    if be:FLGisOn(247) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<760,10,-300>/V<0,90,0>")
    end
    if be:FLGisOn(248) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-700,10,-245>/V<0,180,0>")
    end
    if be:FLGisOn(166) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(167) == 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(171) == 1 and be:FLGisOn(172) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(174) == 1 then
        be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    end
    if be:FLGisOn(175) == 1 then
        be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 10, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    end
    if be:FLGisOn(177) == 1 then
        be:sd("MODELCTRL", "g_d3door", 11, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    end
    if be:FLGisOn(185) == 1 then
        be:sd("MODELCTRL", "g_d3door", 16, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
    end
    if be:FLGisOn(186) == 1 then
        be:sd("MODELCTRL", "g_d3door", 17, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
    end
    if be:FLGisOn(187) == 1 then
        be:sd("MODELCTRL", "g_d3door", 19, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall20", 0, "OFFHIT")
    end
    if be:FLGisOn(244) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(245) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(246) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(249) == 1 then
        be:sd("MODELCTRL", "g_d3door", 12, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
    end
    if be:FLGisOn(250) ~= 1 then
        if be:FLGisOn(251) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 13, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
    if be:FLGisOn(249) ~= 1 then
        if be:FLGisOn(252) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 14, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
    if be:FLGisOn(250) == 1 then
        be:sd("MODELCTRL", "g_d3door", 15, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
    end
    for ramNo = 0, 3 do
        if be:FLGisOn(249 + ramNo) == 1 then
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_SILENTON")
        else
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_POWERON")
        end
    end
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 18, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
elseif be:SYSgetDifficulty() == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<720,10,-300>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<440,10,-380>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<435,10,-220>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<120,10,-340>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-40,10,-220>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-140,10,-280>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-160,10,-260>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<-420,35,-480>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<-520,35,-380>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 9, "GENERATE", "V<-420,35,-160>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 10, "GENERATE", "V<-520,35,-260>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 11, "GENERATE", "V<-720,10,-100>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 12, "GENERATE", "V<-660,10,160>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 13, "GENERATE", "V<-640,10,180>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 14, "GENERATE", "V<-660,10,200>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 15, "GENERATE", "V<-680,10,180>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 16, "GENERATE", "V<-700,10,400>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 17, "GENERATE", "V<-580,10,400>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 18, "GENERATE", "V<-440,10,540>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 19, "GENERATE", "V<-240,10,540>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-660,10,145>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-625,10,180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-660,10,215>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-695,10,180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-500,10,540>/V<0,90,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-500,10,540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-150,10,540>/V<0,0,0>")
    if be:FLGisOn(177) ~= 1 and be:FLGisOn(248) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-700,0,-220>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-700,0,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-700,0,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-700,0,-100>/V<0,0,0>")
    end
    for ramNo = 1, 28 do
        if be:FLGisOn(ramNo + 187) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", ramNo))
        end
    end
    for ramNo = 33, 40 do
        if be:FLGisOn(ramNo + 187) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", ramNo))
        end
    end
    if be:FLGisOn(247) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<760,10,-300>/V<0,90,0>")
    end
    if be:FLGisOn(248) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-700,10,-245>/V<0,180,0>")
    end
    if be:FLGisOn(166) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(167) == 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(171) == 1 and be:FLGisOn(172) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(174) == 1 then
        be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    end
    if be:FLGisOn(175) == 1 then
        be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 10, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    end
    if be:FLGisOn(177) == 1 then
        be:sd("MODELCTRL", "g_d3door", 11, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    end
    if be:FLGisOn(185) == 1 then
        be:sd("MODELCTRL", "g_d3door", 16, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
    end
    if be:FLGisOn(186) == 1 then
        be:sd("MODELCTRL", "g_d3door", 17, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
    end
    if be:FLGisOn(187) == 1 then
        be:sd("MODELCTRL", "g_d3door", 19, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall20", 0, "OFFHIT")
    end
    if be:FLGisOn(244) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(245) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(246) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(249) == 1 then
        be:sd("MODELCTRL", "g_d3door", 12, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
    end
    if be:FLGisOn(250) ~= 1 then
        if be:FLGisOn(251) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 13, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
    if be:FLGisOn(249) ~= 1 then
        if be:FLGisOn(252) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 14, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
    if be:FLGisOn(250) == 1 then
        be:sd("MODELCTRL", "g_d3door", 15, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
    end
    for ramNo = 0, 3 do
        if be:FLGisOn(249 + ramNo) == 1 then
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_SILENTON")
        else
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_POWERON")
        end
    end
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 18, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
elseif be:SYSgetDifficulty() == 2 then
    be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<720,10,-300>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<440,10,-380>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<435,10,-220>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<120,10,-340>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-40,10,-220>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-140,10,-280>/V<0,0,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-160,10,-260>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<-420,35,-480>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<-520,35,-380>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 9, "GENERATE", "V<-420,35,-160>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 10, "GENERATE", "V<-520,35,-260>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 11, "GENERATE", "V<-720,10,-100>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 12, "GENERATE", "V<-660,10,160>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 13, "GENERATE", "V<-640,10,180>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 14, "GENERATE", "V<-660,10,200>/V<0,0,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 15, "GENERATE", "V<-680,10,180>/V<0,90,0>/SQ_BUTTON")
    be:sd("MODELCTRL", "g_d3door", 16, "GENERATE", "V<-700,10,400>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 17, "GENERATE", "V<-580,10,400>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d3door", 18, "GENERATE", "V<-440,10,540>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d3door", 19, "GENERATE", "V<-240,10,540>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-660,10,145>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-625,10,180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-660,10,215>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-695,10,180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-500,10,540>/V<0,90,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-500,10,540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-150,10,540>/V<0,0,0>")
    if be:FLGisOn(177) ~= 1 and be:FLGisOn(248) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-700,0,-220>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-700,0,-180>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-700,0,-140>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-700,0,-100>/V<0,0,0>")
    end
    for ramNo = 1, 28 do
        if be:FLGisOn(ramNo + 187) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", ramNo))
        end
    end
    for ramNo = 33, 56 do
        if be:FLGisOn(ramNo + 187) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", ramNo))
        end
    end
    if be:FLGisOn(247) ~= 1 then
        be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<760,10,-300>/V<0,90,0>")
    end
    if be:FLGisOn(248) ~= 1 then
        be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-700,10,-245>/V<0,180,0>")
    end
    if be:FLGisOn(166) == 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    end
    if be:FLGisOn(167) == 1 then
        be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(171) == 1 and be:FLGisOn(172) == 1 then
        be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(174) == 1 then
        be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    end
    if be:FLGisOn(175) == 1 then
        be:sd("MODELCTRL", "g_d3door", 9, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
        be:sd("MODELCTRL", "g_d3door", 10, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    end
    if be:FLGisOn(177) == 1 then
        be:sd("MODELCTRL", "g_d3door", 11, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    end
    if be:FLGisOn(185) == 1 then
        be:sd("MODELCTRL", "g_d3door", 16, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
    end
    if be:FLGisOn(186) == 1 then
        be:sd("MODELCTRL", "g_d3door", 17, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
    end
    if be:FLGisOn(187) == 1 then
        be:sd("MODELCTRL", "g_d3door", 19, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall20", 0, "OFFHIT")
    end
    if be:FLGisOn(244) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(245) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    end
    if be:FLGisOn(246) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
    end
    if be:FLGisOn(249) == 1 then
        be:sd("MODELCTRL", "g_d3door", 12, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
    end
    if be:FLGisOn(250) ~= 1 then
        if be:FLGisOn(251) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 13, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
    if be:FLGisOn(249) ~= 1 then
        if be:FLGisOn(252) == 1 then
        end
    end
    be:sd("MODELCTRL", "g_d3door", 14, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
    if be:FLGisOn(250) == 1 then
        be:sd("MODELCTRL", "g_d3door", 15, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
    end
    for ramNo = 0, 3 do
        if be:FLGisOn(249 + ramNo) == 1 then
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_SILENTON")
        else
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_POWERON")
        end
    end
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 18, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
else
    be:MsgBox("G[FïÕxªzèOÅ·B")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
