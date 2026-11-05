funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for local_2 = 100, 299 do
        be:FLGset(local_2, 0)
    end
end
be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<-45,40,75>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<45,40,75>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 2, "GENERATE", "V<195,40,115>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 3, "GENERATE", "V<285,40,115>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 4, "GENERATE", "V<-285,40,-285>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 5, "GENERATE", "V<-195,40,-285>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-40,40,355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<-20,40,355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<20,40,355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<40,40,355>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<-120,40,-45>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 5, "GENERATE", "V<120,40,-45>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 6, "GENERATE", "V<0,40,-245>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 7, "GENERATE", "V<-40,40,-405>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 8, "GENERATE", "V<-20,40,-405>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 9, "GENERATE", "V<20,40,-405>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 10, "GENERATE", "V<40,40,-405>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<0,40,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<40,40,-360>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealeffect", 0, "GENERATE", "V<0,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealbase", 0, "GENERATE", "V<0,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<-60,40,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<60,40,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<-15,40,0>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<15,40,0>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-240,40,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 5, "GENERATE", "V<-240,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 6, "GENERATE", "V<240,40,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 7, "GENERATE", "V<340,40,0>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<60,40,-360>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2base", 0, "GENERATE", "V<-40,40,80>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 1, "GENERATE", "V<40,40,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2base", 2, "GENERATE", "V<200,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 3, "GENERATE", "V<280,40,120>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2base", 4, "GENERATE", "V<-280,40,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 5, "GENERATE", "V<-200,40,-280>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<-40,40,80>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<40,40,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 2, "GENERATE", "V<200,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 3, "GENERATE", "V<280,40,120>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 4, "GENERATE", "V<-280,40,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 5, "GENERATE", "V<-200,40,-280>/V<0,-90,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<0,40,-225>/V<0,0,0>")
if be:FLGisOn(106) ~= 1 then
    be:FLGset(121, 0)
end
for local_2 = 1, 10 do
    if be:FLGisOn(local_2 + 114) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_2))
    end
end
if be:FLGisOn(129) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<0,40,270>/V<0,0,0>")
end
if be:FLGisOn(130) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 1, "GENERATE", "V<-300,40,0>/V<0,0,0>")
end
if be:FLGisOn(131) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<-380,40,0>/V<0,0,0>")
end
if be:FLGisOn(132) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 1, "GENERATE", "V<380,40,0>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d2door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 7, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 8, "SQ_BUTTON")
if be:SYSgetPlayerNinzu() == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<275,40,-35>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<275,40,35>/V<0,0,0>")
    if be:FLGisOn(125) ~= 1 then
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    end
    if be:FLGisOn(126) ~= 1 then
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    end
end
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<275,40,-35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<275,40,35>/V<0,0,0>")
if be:FLGisOn(125) + be:FLGisOn(126) == 2 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
else
    be:FLGset(125, 0)
    be:FLGset(126, 0)
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
end
if be:FLGisOn(125) + be:FLGisOn(126) == 2 then
    be:sd("MODELCTRL", "g_d2door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(127) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(128) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(101) == 1 then
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(104) + be:FLGisOn(109) + be:FLGisOn(110) + be:FLGisOn(111) == 4 then
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(107) + be:FLGisOn(112) + be:FLGisOn(113) + be:FLGisOn(114) == 4 then
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map205b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map205b1", 0, "GENERATE", "SQ_OPEN")
    end
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 and be:MDLisLive("j_mapcur", local_3) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_3, "GENERATE")
        end
    end
end
