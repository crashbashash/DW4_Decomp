mswk61007 = "TALKFONT01/font00/I<11>"
mswk61008 = "TALKFONT01/font00/I<12>"
mswk61011 = "TALKFONT02/font00/I<13>"
mswk61097 = "TALKFONT01/font00/I<14>"
local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:SYSgetDifficulty() == 1 then
    be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<100,35,-440>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<-60,35,400>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<-340,10,280>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-220,10,160>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-560,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<-540,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<-520,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<-420,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<-400,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 5, "GENERATE", "V<-320,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 6, "GENERATE", "V<-300,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 7, "GENERATE", "V<-200,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 8, "GENERATE", "V<-160,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<-440,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 1, "GENERATE", "V<-280,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 2, "GENERATE", "V<-180,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<40,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 1, "GENERATE", "V<-240,10,480>/V<0,90,0>")
    if be:FLGisOn(138) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<40,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<40,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<40,0,280>/V<0,0,0>")
    end
    if be:FLGisOn(139) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-160,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-280,0,440>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-240,0,440>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-200,0,440>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-280,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-240,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-200,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-280,0,520>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-240,0,520>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-200,0,520>/V<0,0,0>")
    end
    if be:FLGisOn(140) ~= 1 and be:FLGisOn(143) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-120,0,360>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-120,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-120,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-120,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-200,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-160,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-120,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-200,0,160>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-160,0,160>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-120,0,160>/V<0,0,0>")
    end
    if be:FLGisOn(141) ~= 1 and be:FLGisOn(131) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-600,0,360>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-640,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-600,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-560,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-640,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-600,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-560,0,280>/V<0,0,0>")
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-560,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-520,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-480,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-440,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 34, "GENERATE", "V<-400,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 35, "GENERATE", "V<-360,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 36, "GENERATE", "V<-440,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 37, "GENERATE", "V<-400,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 38, "GENERATE", "V<-360,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 39, "GENERATE", "V<-440,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 40, "GENERATE", "V<-400,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 41, "GENERATE", "V<-360,0,280>/V<0,0,0>")
    end
    if be:FLGisOn(143) ~= 1 and be:FLGisOn(129) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 42, "GENERATE", "V<-320,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 43, "GENERATE", "V<-280,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 44, "GENERATE", "V<-240,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 45, "GENERATE", "V<-200,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 46, "GENERATE", "V<-160,0,280>/V<0,0,0>")
    end
    g_enemyAmount = 302
    g_mummyStock = 30
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<85,10,-260>/V<0,-90,0>")
    if be:FLGisOn(134) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-H01")
    end
    if be:FLGisOn(136) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<430,10,-440>/V<0,0,0>")
    end
    if be:FLGisOn(137) ~= 1 then
        be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<40,10,-260>/V<0,0,0>")
    end
    if be:FLGisOn(138) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<40,10,175>/V<0,180,0>")
    end
    if be:FLGisOn(139) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-135,10,480>/V<0,90,0>")
    end
    if be:FLGisOn(140) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<-120,10,385>/V<0,0,0>")
    end
    if be:FLGisOn(141) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 3, "GENERATE", "V<-600,10,385>/V<0,0,0>/SQ_CUTLEFT")
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 4, "GENERATE", "V<-585,10,200>/V<0,-90,0>")
    end
    if be:FLGisOn(143) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 5, "GENERATE", "V<-135,10,280>/V<0,90,0>")
    end
    if be:FLGisOn(120) == 1 then
        be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
        g_door01 = 1
    end
    if be:FLGisOn(124) == 1 then
        be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 2, "SQ_OPEN")
    end
    if be:FLGisOn(126) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 1, "SQ_OPEN")
    end
    if be:FLGisOn(127) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
    end
    if be:FLGisOn(129) == 1 then
        be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(131) == 1 then
        be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dreturngate", 1, "SQ_POWERON")
elseif be:SYSgetDifficulty() == 2 then
    be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<100,35,-440>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<-60,35,400>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<-340,10,280>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-220,10,160>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-180,10,480>/V<0,90,0>/SQ_BOSS")
    be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-560,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<-540,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<-520,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<-420,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<-400,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 5, "GENERATE", "V<-320,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 6, "GENERATE", "V<-300,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 7, "GENERATE", "V<-200,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 8, "GENERATE", "V<-160,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<-440,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 1, "GENERATE", "V<-280,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 2, "GENERATE", "V<-180,10,355>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<40,10,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-280,10,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-200,10,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-280,10,520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-200,10,520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-240,10,480>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-240,10,480>/V<0,0,0>")
    if be:FLGisOn(138) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<40,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<40,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<40,0,280>/V<0,0,0>")
    end
    if be:FLGisOn(139) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-160,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-280,0,440>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-240,0,440>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-200,0,440>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-280,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-240,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-200,0,480>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-280,0,520>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-240,0,520>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-200,0,520>/V<0,0,0>")
    end
    if be:FLGisOn(140) ~= 1 and be:FLGisOn(143) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-120,0,360>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-120,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-120,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-120,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-200,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-160,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-120,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-200,0,160>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-160,0,160>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-120,0,160>/V<0,0,0>")
    end
    if be:FLGisOn(141) ~= 1 and be:FLGisOn(131) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-600,0,360>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-640,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-600,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-560,0,320>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-640,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-600,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-560,0,280>/V<0,0,0>")
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-560,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-520,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-480,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-440,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 34, "GENERATE", "V<-400,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 35, "GENERATE", "V<-360,0,200>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 36, "GENERATE", "V<-440,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 37, "GENERATE", "V<-400,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 38, "GENERATE", "V<-360,0,240>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 39, "GENERATE", "V<-440,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 40, "GENERATE", "V<-400,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 41, "GENERATE", "V<-360,0,280>/V<0,0,0>")
    end
    if be:FLGisOn(143) ~= 1 and be:FLGisOn(129) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 42, "GENERATE", "V<-320,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 43, "GENERATE", "V<-280,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 44, "GENERATE", "V<-240,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 45, "GENERATE", "V<-200,0,280>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 46, "GENERATE", "V<-160,0,280>/V<0,0,0>")
    end
    g_enemyAmount = 302
    g_mummyStock = 30
    be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<85,10,-260>/V<0,-90,0>")
    if be:FLGisOn(134) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-V01")
    end
    if be:FLGisOn(135) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GBOX-V02")
    end
    if be:FLGisOn(136) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<430,10,-440>/V<0,0,0>")
    end
    if be:FLGisOn(137) ~= 1 then
        be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<40,10,-260>/V<0,0,0>")
    end
    if be:FLGisOn(138) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<40,10,175>/V<0,180,0>")
    end
    if be:FLGisOn(139) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-135,10,480>/V<0,90,0>")
    end
    if be:FLGisOn(140) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<-120,10,385>/V<0,0,0>")
    end
    if be:FLGisOn(141) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 3, "GENERATE", "V<-600,10,385>/V<0,0,0>/SQ_CUTLEFT")
    end
    if be:FLGisOn(142) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 4, "GENERATE", "V<-585,10,200>/V<0,-90,0>")
    end
    if be:FLGisOn(143) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 5, "GENERATE", "V<-135,10,280>/V<0,90,0>")
    end
    if be:FLGisOn(120) == 1 then
        be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
        g_door01 = 1
    end
    if be:FLGisOn(124) == 1 then
        be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    end
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 2, "SQ_OPEN")
    end
    if be:FLGisOn(126) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 1, "SQ_OPEN")
    end
    if be:FLGisOn(127) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
    end
    if be:FLGisOn(129) == 1 then
        be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(131) == 1 then
        be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    for ramNo = 0, 3 do
        if be:FLGisOn(145 + ramNo) == 1 then
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_SILENTON")
        else
            be:sd("MODELCTRL", "g_dbutton1", ramNo, "SQ_POWERON")
        end
    end
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
else
    be:MsgBox("G[FïÕxªzèOÅ·B")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
