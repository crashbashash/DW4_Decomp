local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 307
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
end
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<220,40,120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<-40,40,-240>/V<0,90,0>")
if be:FLGisOn(113) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-60,30,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-20,30,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<20,30,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-20,30,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<20,30,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-20,30,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<20,30,-520>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<220,40,-80>/V<0,0,0>")
if be:FLGisOn(102) ~= 1 then
    be:FLGset(109, 0)
end
for flagNo = 1, 4 do
    if be:FLGisOn(flagNo + 108) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", flagNo))
    end
end
if be:FLGisOn(113) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<-60,40,-545>/V<0,0,0>")
    be:sd("MODELCTRL", "g_d3bkwall", 0, "SQ_CUTBOTH")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
if be:FLGisOn(106) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map307b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map307b1", 0, "GENERATE", "SQ_OPEN")
    end
    local local_2
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
