local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 412
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
end
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<0,40,480>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<-100,40,300>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<0,40,245>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<100,40,300>/V<0,-90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<100,40,60>/V<0,-90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<-100,40,60>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<-360,40,-80>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<-360,40,-400>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<-300,40,-460>/V<0,-90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<-360,40,-560>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<80,40,-280>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 11, "GENERATE", "V<140,40,-620>/V<0,-90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-360,40,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<300,40,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<320,40,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<340,40,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 0, "GENERATE", "V<-205,40,220>/V<0,90,0>")
be:sd("MODELCTRL", "g_dlasergun", 1, "GENERATE", "V<205,40,220>/V<0,-90,0>")
if be:FLGisOn(249) ~= 1 and be:FLGisOn(250) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<80,30,-540>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<80,30,-500>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-120,30,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-80,30,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-40,30,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<0,30,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<40,30,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<80,30,-460>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<80,30,-420>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<80,30,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<80,30,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<80,30,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<40,30,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<80,30,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<120,30,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<40,30,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<80,30,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<120,30,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<40,30,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<80,30,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<120,30,-180>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-195,40,-495>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<480,40,100>/V<0,-90,0>")
if be:FLGisOn(219) ~= 1 then
    be:FLGset(232, 0)
    be:FLGset(235, 0)
end
for flagNo = 1, 19 do
    if be:FLGisOn(flagNo + 228) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", flagNo))
    end
end
if be:FLGisOn(249) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<-145,40,-460>/V<0,-90,0>")
end
if be:FLGisOn(250) ~= 1 then
    be:sd("MODELCTRL", "g_d4bkwall", 1, "GENERATE", "V<80,40,-565>/V<0,180,0>")
end
if be:FLGisOn(251) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<0,40,520>/V<0,0,0>")
end
if be:FLGisOn(252) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<-160,40,300>/V<0,90,0>")
end
if be:FLGisOn(253) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 2, "GENERATE", "V<160,40,300>/V<0,-90,0>")
end
if be:FLGisOn(254) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 3, "GENERATE", "V<-300,40,-620>/V<0,90,0>")
end
if be:FLGisOn(255) ~= 1 then
    be:sd("MODELCTRL", "g_dscrap", 4, "GENERATE", "V<80,40,-460>/V<0,0,0>")
end
if be:FLGisOn(248) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(212) == 1 then
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(213) == 1 then
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(216) == 1 then
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(219) == 1 then
    be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(220) == 1 then
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 9, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(223) == 1 then
    be:sd("MODELCTRL", "g_d4door", 11, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 10, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map412b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map412b1", 0, "GENERATE", "SQ_OPEN")
    end
    local local_2
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
