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
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-420,10,-40>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<830,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<480,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<480,10,-240>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-40,10,0>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-40,10,40>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-40,10,80>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-240,10,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<-580,10,-40>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<-300,10,-40>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<-220,10,-160>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<220,10,-240>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<540,10,-240>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 5, "GENERATE", "V<740,10,-240>/V<0,90,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<240,10,-240>/V<0,90,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-165,10,-195>/V<0,90,0>")
if be:FLGisOn(129) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<120,0,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<160,0,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<160,0,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<160,0,160>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<200,0,80>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<200,0,120>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<200,0,160>/V<0,0,0>")
end
for local_1 = 1, 8 do
    if be:FLGisOn(local_1 + 119) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
if be:FLGisOn(129) ~= 1 then
    be:sd("MODELCTRL", "g_d1bkwall", 0, "GENERATE", "V<95,10,120>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d1bkwall", 0, "SQ_CUTLEFT")
end
be:sd("MODELCTRL", "g_d1door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 1, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 4, "SQ_BOSS")
be:sd("MODELCTRL", "g_d1door", 5, "SQ_CLEAR")
if be:FLGisOn(128) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(112) == 1 then
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(113) == 1 then
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
end
if be:FLGisOn(118) == 1 then
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(119) == 1 then
    be:sd("MODELCTRL", "g_d1door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON")
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map101b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map101b2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
