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
be:sd("MODELCTRL", "g_dallhealbase", 0, "GENERATE", "V<0,10,-560>/V<0,0,0>")
be:sd("MODELCTRL", "g_dallhealeffect", 0, "GENERATE", "V<0,10,-560>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<0,10,115>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-35,10,-65>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<0,10,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<35,10,-65>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<0,35,540>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<-100,10,240>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<100,10,240>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<0,10,80>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<0,10,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<0,10,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 6, "GENERATE", "V<0,35,-460>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 7, "GENERATE", "V<0,10,-620>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 8, "GENERATE", "V<0,10,-820>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-200,10,-280>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<200,10,-280>/V<0,-90,0>")
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<0,35,640>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<0,10,-910>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-240,10,80>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<240,10,80>/V<0,0,0>")
for i = 1, 11 do
    if be:FLGisOn(i + 234) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", i))
    end
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 5, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 6, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 7, "SQ_BOSS")
be:sd("MODELCTRL", "g_d3door", 8, "SQ_CLEAR")
if be:FLGisOn(246) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(247) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
end
if be:FLGisOn(248) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(249) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON")
end
if be:FLGisOn(247) + be:FLGisOn(249) == 2 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(211) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(212) == 1 then
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(233) == 1 then
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(234) == 1 then
    be:sd("MODELCTRL", "g_d3door", 8, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d3door", 7, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(294) == 1 then
    if be:MDLisLive("j_map309b4", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map309b4", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
