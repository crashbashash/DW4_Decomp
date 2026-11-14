local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 308
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
end
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<20,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<-140,40,-60>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<260,40,60>/V<0,90,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-240,40,-100>/V<0,0,0>")
for flagNo = 1, 7 do
    if be:FLGisOn(flagNo + 107) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", flagNo))
    end
end
if be:FLGisOn(115) ~= 1 then
    be:sd("MODELCTRL", "g_dcellwall", 0, "GENERATE", "V<-240,40,-140>/V<0,0,0>")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
if be:FLGisOn(103) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(107) == 1 then
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map308b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map308b1", 0, "GENERATE", "SQ_OPEN")
    end
    local local_2
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
