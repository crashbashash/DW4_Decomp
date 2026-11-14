local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 1 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_dbush01", 0, "GENERATE", "V<320,10,5>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 1, "GENERATE", "V<360,10,75>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush01", 2, "GENERATE", "V<200,10,165>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 3, "GENERATE", "V<240,10,275>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush01", 4, "GENERATE", "V<655,10,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbush01", 5, "GENERATE", "V<585,10,60>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbush01", 6, "GENERATE", "V<695,10,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbush01", 7, "GENERATE", "V<625,10,220>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbush02", 0, "GENERATE", "V<620,10,20>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbush02", 1, "GENERATE", "V<620,10,60>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbush02", 2, "GENERATE", "V<660,10,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbush02", 3, "GENERATE", "V<660,10,220>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbush02", 4, "GENERATE", "V<320,10,40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 5, "GENERATE", "V<360,10,40>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush02", 6, "GENERATE", "V<200,10,200>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 7, "GENERATE", "V<200,10,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 8, "GENERATE", "V<240,10,200>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush02", 9, "GENERATE", "V<240,10,240>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 0, "GENERATE", "V<240,10,165>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 1, "GENERATE", "V<200,10,275>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 2, "GENERATE", "V<360,10,5>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 3, "GENERATE", "V<320,10,75>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 4, "GENERATE", "V<585,10,20>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbush03", 5, "GENERATE", "V<655,10,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbush03", 6, "GENERATE", "V<625,10,180>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbush03", 7, "GENERATE", "V<695,10,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<25,35,35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-260,10,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-260,10,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<540,35,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<440,35,-160>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<340,10,258>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<522,10,360>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<-40,35,40>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 5, "GENERATE", "V<-40,35,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 6, "GENERATE", "V<-300,10,-18>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 7, "GENERATE", "V<-358,10,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 8, "GENERATE", "V<-560,10,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 9, "GENERATE", "V<-760,10,120>/V<0,90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<340,10,0>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<340,10,40>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<340,10,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-260,10,70>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<-260,10,90>/V<0,-90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<540,35,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-500,10,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-500,10,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-850,10,120>/V<0,0,0>")
if be:FLGisOn(170) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<740,0,0>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<740,0,-40>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<700,0,-80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<740,0,-80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<780,0,-80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<700,0,-120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<740,0,-120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<780,0,-120>/V<0,0,0>")
end
if be:FLGisOn(171) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<740,0,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<740,0,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<740,0,160>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-300,10,-115>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<425,10,-355>/V<0,90,0>")
for i = 1, 16 do
    if be:FLGisOn(i + 150) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", i))
    end
end
if be:FLGisOn(170) ~= 1 then
    be:sd("MODELCTRL", "g_d1bkwall", 0, "GENERATE", "V<740,10,25>/V<0,0,0>")
end
if be:FLGisOn(171) ~= 1 then
    be:sd("MODELCTRL", "g_d1bkwall", 1, "GENERATE", "V<740,10,55>/V<0.0,180,0>")
end
be:sd("MODELCTRL", "g_d1door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 6, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 7, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 8, "SQ_BOSS")
be:sd("MODELCTRL", "g_d1door", 9, "SQ_CLEAR")
if be:FLGisOn(140) == 1 then
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(141) == 1 then
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(144) == 1 then
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(147) == 1 then
    be:sd("MODELCTRL", "g_d1door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(148) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
    be:FLGset(168, 0)
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(149) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
    be:FLGset(169, 0)
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(150) == 1 then
    be:sd("MODELCTRL", "g_d1door", 9, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(167) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(168) == 1 and be:FLGisOn(169) == 1 then
    g_dmgfloor45 = 1
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d1door", 8, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(293) == 1 then
    if be:MDLisLive("j_map102b3", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map102b3", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
