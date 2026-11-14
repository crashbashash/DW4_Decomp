local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 102
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
end
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<120,40,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<160,40,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-180,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-160,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<-140,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<-180,40,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<-140,40,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<-180,40,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<-160,40,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<-140,40,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-200,40,180>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<-160,40,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 0, "GENERATE", "V<145,40,425>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 1, "GENERATE", "V<95,40,455>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 2, "GENERATE", "V<145,40,-55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 3, "GENERATE", "V<95,40,15>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 4, "GENERATE", "V<-255,40,-295>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 5, "GENERATE", "V<-305,40,-225>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush02", 0, "GENERATE", "V<95,40,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 1, "GENERATE", "V<145,40,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 2, "GENERATE", "V<-305,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 3, "GENERATE", "V<-255,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 0, "GENERATE", "V<95,40,425>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 1, "GENERATE", "V<145,40,455>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush01", 2, "GENERATE", "V<95,40,-55>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 3, "GENERATE", "V<145,40,15>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush01", 4, "GENERATE", "V<-305,40,-295>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 5, "GENERATE", "V<-255,40,-225>/V<0,180,0>")
be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<120,40,240>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<-100,40,180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<60,40,-180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<-220,40,-180>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<-280,40,-480>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<-280,40,-180>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<-75,40,145>/V<0,0,0>")
for flagNo = 1, 4 do
    if be:FLGisOn(flagNo + 108) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", flagNo))
    end
end
be:sd("MODELCTRL", "g_d1door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 2, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 3, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 4, "SQ_CLEAR")
if be:FLGisOn(113) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(114) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(101) ~= 1 then
    be:FLGset(100, 0)
else
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(104) == 1 then
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(108) == 1 then
    be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(291) == 1 then
    if be:MDLisLive("j_map102b1", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map102b1", 0, "GENERATE", "SQ_OPEN")
    end
    local local_2
    for playerIndex = 0, 3 do
        if be:SYSisJoinPlayer(playerIndex) == 1 and be:MDLisLive("j_mapcur", playerIndex) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", playerIndex, "GENERATE")
        end
    end
end
