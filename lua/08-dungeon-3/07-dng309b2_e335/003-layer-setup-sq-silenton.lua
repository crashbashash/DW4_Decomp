local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<20,65,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-220,40,380>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<260,40,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<380,65,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<120,65,60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<20,65,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<280,40,-100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<380,65,-280>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<-480,40,-380>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<380,65,-480>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-180,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<260,40,-100>/V<0,0,0>")
for i = 1, 9 do
    if be:FLGisOn(i + 144) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", i))
    end
end
if be:FLGisOn(156) ~= 1 then
    be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<260,40,-40>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 5, "SQ_CLEAR")
if be:FLGisOn(154) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(155) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(133) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(141) == 1 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(144) == 1 then
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map309b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map309b2", 0, "GENERATE", "SQ_OPEN")
    end
    local local_1
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
