mswk61007 = "TALKFONT01/font00/I<11>"
mswk61008 = "TALKFONT01/font00/I<12>"
mswk61011 = "TALKFONT02/font00/I<13>"
mswk61097 = "TALKFONT01/font00/I<14>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<100,35,-440>/V<0,90,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<-60,35,400>/V<0,90,0>/SQ_CLEAR")
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
be:sd("MODELCTRL", "g_dreturngate", 1, "GENERATE", "V<-240,10,480>/V<0,0,0>")
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
g_enemyAmount = 279
g_mummyStock = 30
be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<85,10,-260>/V<0,-90,0>")
if be:FLGisOn(134) ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GBOX-E01")
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
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_dreturngate", 1, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
