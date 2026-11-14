local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 411
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
end
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<-80,40,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<200,40,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<240,40,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<200,40,80>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<200,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<140,40,300>/V<0,90,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<200,40,60>/V<0,0,0>")
if be:FLGisOn(188) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<40,30,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<80,30,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<120,30,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<80,30,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<120,30,-300>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<205,40,-335>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<275,40,65>/V<0,0,0>")
for flagNo = 1, 9 do
    if be:FLGisOn(flagNo + 106) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", flagNo))
    end
end
be:sd("MODELCTRL", "g_d4door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 5, "SQ_CLEAR")
if be:FLGisOn(116) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(100) == 1 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(105) == 1 then
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(106) == 1 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map411b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map411b1", 0, "GENERATE", "SQ_OPEN")
    end
    local local_2
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
