local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 1 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-120,10,-335>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-40,10,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-40,10,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-360,10,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<0,10,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<120,10,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<-120,10,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<240,10,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<240,10,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<180,10,-20>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<140,10,180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<-40,10,200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<-100,10,300>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<-300,10,300>/V<0,90,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-390,10,300>/V<0,0,0>")
if be:FLGisOn(136) + be:FLGisOn(116) == 0 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<240,0,-220>/V<0,0,0>")
end
if be:FLGisOn(137) + be:FLGisOn(118) == 0 then
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<240,0,-100>/V<0,0,0>")
end
if be:FLGisOn(138) == 0 then
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<80,0,100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<120,0,100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<80,0,140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<120,0,140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<80,0,180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<120,0,180>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<240,10,60>/V<0,0,0>")
for i = 1, 9 do
    if be:FLGisOn(i + 124) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", i))
    end
end
if be:FLGisOn(136) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<240,10,-245>/V<0,180,0>")
end
if be:FLGisOn(137) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 1, "GENERATE", "V<240,10,-125>/V<0,180,0>")
end
if be:FLGisOn(138) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 2, "GENERATE", "V<55,10,140>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d3bkwall", 2, "SQ_CUTBOTH")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 5, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 6, "SQ_BOSS")
be:sd("MODELCTRL", "g_d3door", 7, "SQ_CLEAR")
if be:FLGisOn(134) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(135) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(114) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(116) == 1 then
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(118) == 1 then
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(124) == 1 then
    be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map307b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map307b2", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
