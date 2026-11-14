local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.0,1.1,1.05>/V<1.0,1.1,1.05>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.2,0.25,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 309
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
end
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<250,65,-400>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<210,40,-400>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-10,40,-40>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 0, "GENERATE", "V<-160,40,300>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 1, "GENERATE", "V<160,65,100>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 2, "GENERATE", "V<40,40,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 3, "GENERATE", "V<-220,40,-360>/V<0,90,0>")
be:sd("MODELCTRL", "g_d3door", 4, "GENERATE", "V<320,65,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_d3door", 5, "GENERATE", "V<280,65,-420>/V<0,0,0>")
if be:FLGisOn(126) + be:FLGisOn(111) == 0 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<240,30,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<280,30,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<320,30,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<240,30,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<280,30,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<320,30,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<280,30,-520>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<280,30,-480>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<280,30,-440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<160,30,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<200,30,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<240,30,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<280,30,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<320,30,-400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<320,30,-360>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<320,65,-360>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<40,40,0>/V<0,0,0>")
for flagNo = 1, 11 do
    if be:FLGisOn(flagNo + 112) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", flagNo))
    end
end
if be:FLGisOn(126) ~= 1 then
    be:sd("MODELCTRL", "g_d3bkwall", 0, "GENERATE", "V<135,40,-400>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d3bkwall", 0, "SQ_CUTBOTH")
end
be:sd("MODELCTRL", "g_d3door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d3door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 4, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d3door", 5, "SQ_BUTTON")
if be:FLGisOn(124) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(125) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_d3door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(101) == 1 then
    be:sd("MODELCTRL", "g_d3door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(106) == 1 then
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(109) == 1 then
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(111) == 1 then
    be:sd("MODELCTRL", "g_d3door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map309b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map309b1", 0, "GENERATE", "SQ_OPEN")
    end
    local local_2
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
