funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for local_2 = 100, 299 do
        be:FLGset(local_2, 0)
    end
end
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<220,40,-200>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<220,40,-240>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-20,40,-250>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-20,40,-290>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<-180,40,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<120,40,-320>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<220,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-180,40,-120>/V<0,0,0>")
for local_2 = 1, 5 do
    if be:FLGisOn(local_2 + 106) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_2))
    end
end
be:sd("MODELCTRL", "g_d1door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 2, "SQ_CLEAR")
if be:FLGisOn(102) == 1 then
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(106) == 1 then
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map101b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map101b1", 0, "GENERATE", "SQ_OPEN")
    end
    for local_3 = 0, 3 do
        if be:SYSisJoinPlayer(local_3) == 1 and be:MDLisLive("j_mapcur", local_3) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_3, "GENERATE")
        end
    end
end
