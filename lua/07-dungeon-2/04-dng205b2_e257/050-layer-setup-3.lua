funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-200,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<-200,40,45>/V<0,180,0>")
be:sd("MODELCTRL", "g_d2torch", 0, "GENERATE", "V<-350,40,295>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 1, "GENERATE", "V<-290,40,295>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 2, "GENERATE", "V<170,40,-145>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 3, "GENERATE", "V<230,40,-145>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 4, "GENERATE", "V<275,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 5, "GENERATE", "V<365,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 6, "GENERATE", "V<275,40,145>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 7, "GENERATE", "V<365,40,145>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 8, "GENERATE", "V<50,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2torch", 9, "GENERATE", "V<110,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<-245,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<-155,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 2, "GENERATE", "V<45,40,-145>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 3, "GENERATE", "V<45,40,-55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<-320,40,295>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 1, "GENERATE", "V<80,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<160,65,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<180,65,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<200,65,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<220,65,280>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<220,65,260>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<260,65,260>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<260,65,280>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<280,65,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<300,65,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<320,65,320>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-360,40,-345>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<-280,40,-345>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<200,40,-145>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<440,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<470,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 5, "GENERATE", "V<490,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 6, "GENERATE", "V<520,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<-605,40,135>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 1, "GENERATE", "V<-605,40,65>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 2, "GENERATE", "V<455,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 3, "GENERATE", "V<505,40,55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealeffect", 0, "GENERATE", "V<-320,40,-330>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealbase", 0, "GENERATE", "V<-320,40,-330>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<-140,40,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<-260,40,100>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<-500,40,100>/V<0,90,0>")
be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-320,65,0>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-320,65,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 5, "GENERATE", "V<-220,40,-300>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 6, "GENERATE", "V<-180,40,-300>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 7, "GENERATE", "V<-40,40,-400>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<-40,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 9, "GENERATE", "V<-40,40,40>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2door", 10, "GENERATE", "V<380,40,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 11, "GENERATE", "V<240,65,360>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 0, "GENERATE", "V<-240,40,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 1, "GENERATE", "V<-160,40,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2base", 2, "GENERATE", "V<40,40,-140>/V<0,270,0>")
be:sd("MODELCTRL", "g_d2base", 3, "GENERATE", "V<40,40,-60>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<-240,40,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<-160,40,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 2, "GENERATE", "V<40,40,-140>/V<0,270,0>")
be:sd("MODELCTRL", "g_dbasewall", 3, "GENERATE", "V<40,40,-60>/V<0,180,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-40,40,-495>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-740,40,300>/V<0,0,0>")
if be:FLGisOn(136) ~= 1 then
    be:FLGset(152, 0)
end
if be:FLGisOn(141) ~= 1 then
    be:FLGset(159, 0)
end
for local_1 = 1, 9 do
    if be:FLGisOn(local_1 + 150) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(166) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<-380,40,340>/V<0,0,0>")
end
if be:FLGisOn(167) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 1, "GENERATE", "V<-260,40,340>/V<0,0,0>")
end
if be:FLGisOn(168) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 2, "GENERATE", "V<-100,40,100>/V<0,0,0>")
end
if be:FLGisOn(169) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 3, "GENERATE", "V<-560,40,120>/V<0,0,0>")
end
if be:FLGisOn(170) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 4, "GENERATE", "V<-560,40,80>/V<0,0,0>")
end
if be:FLGisOn(171) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 5, "GENERATE", "V<150,40,100>/V<0,0,0>")
end
if be:FLGisOn(172) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 6, "GENERATE", "V<170,40,100>/V<0,0,0>")
end
if be:FLGisOn(173) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<-740,40,340>/V<0,0,0>")
end
if be:FLGisOn(174) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 1, "GENERATE", "V<660,40,340>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d2door", 0, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 5, "SQ_BOSS")
be:sd("MODELCTRL", "g_d2door", 6, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 8, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 9, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 10, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 11, "SQ_CLEAR")
if be:SYSgetPlayerNinzu() == 4 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-200,40,-340>/V<0,0,0>")
    if local_1 ~= 4 then
        be:FLGset(160, 0)
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    end
end
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-200,40,-340>/V<0,0,0>")
if be:FLGisOn(160) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
end
if be:SYSgetPlayerNinzu() >= 3 then
    be:sd("MODELCTRL", "g_dbutton2", 3, "GENERATE", "V<-200,40,-260>/V<0,0,0>")
    if local_1 ~= 4 then
        be:FLGset(163, 0)
        be:sd("MODELCTRL", "g_dbutton2", 3, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton2", 3, "SQ_ONLOOP")
    end
end
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<-200,40,-260>/V<0,0,0>")
if be:FLGisOn(163) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
end
if be:SYSgetPlayerNinzu() >= 2 then
    be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-200,40,-325>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<-200,40,-275>/V<0,0,0>")
    if local_1 ~= 4 then
        be:FLGset(161, 0)
        be:FLGset(162, 0)
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
        be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    end
end
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-200,40,-325>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-200,40,-275>/V<0,0,0>")
if be:FLGisOn(161) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
end
if be:FLGisOn(162) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
end
if local_1 == 4 then
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dbutton1", 4, "GENERATE", "V<-40,40,20>/V<0,0,0>")
if be:FLGisOn(164) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(165) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_d2door", 5, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
g_door06 = 1
if be:FLGisOn(133) == 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
    g_pharaoh01 = 1
end
if be:FLGisOn(135) == 1 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(136) == 1 then
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(137) == 1 then
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(138) == 1 then
    be:sd("MODELCTRL", "g_d2door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(141) == 1 then
    be:sd("MODELCTRL", "g_d2door", 10, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
end
if be:FLGisOn(143) == 1 then
    be:sd("MODELCTRL", "g_d2door", 11, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
if be:FLGisOn(144) == 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 1, "SQ_OPEN")
    g_pharaoh12 = 1
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map205b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map205b2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 and be:MDLisLive("j_mapcur", local_3) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_3, "GENERATE")
        end
    end
end
