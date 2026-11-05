funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
if be:PLAYERgetPos() == 2 then
    be:sd("PLAYER", nil, -1, "SQ_HIDE")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
end
be:sd("MODELCTRL", "g_security", 0, "GENERATE", "V<-160,40,-80>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<220,40,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<260,40,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<300,40,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-40,40,-60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<275,40,-535>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-160,40,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 0, "GENERATE", "V<-60,40,145>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 1, "GENERATE", "V<-100,40,175>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 2, "GENERATE", "V<-320,40,105>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 3, "GENERATE", "V<-400,40,175>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 4, "GENERATE", "V<100,40,-175>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 5, "GENERATE", "V<60,40,-105>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush03", 6, "GENERATE", "V<340,40,-375>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush03", 7, "GENERATE", "V<300,40,-185>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush02", 0, "GENERATE", "V<-400,40,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 1, "GENERATE", "V<-320,40,140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 2, "GENERATE", "V<60,40,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 3, "GENERATE", "V<100,40,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 4, "GENERATE", "V<300,40,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 5, "GENERATE", "V<300,40,-300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 6, "GENERATE", "V<300,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 7, "GENERATE", "V<300,40,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 8, "GENERATE", "V<340,40,-340>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 9, "GENERATE", "V<340,40,-300>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 10, "GENERATE", "V<340,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush02", 11, "GENERATE", "V<340,40,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 0, "GENERATE", "V<-100,40,145>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 1, "GENERATE", "V<-60,40,175>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush01", 2, "GENERATE", "V<-400,40,105>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 3, "GENERATE", "V<-320,40,175>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush01", 4, "GENERATE", "V<60,40,-175>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 5, "GENERATE", "V<100,40,-105>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbush01", 6, "GENERATE", "V<300,40,-375>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbush01", 7, "GENERATE", "V<340,40,-185>/V<0,180,0>")
be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<-160,40,-160>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<-60,40,-60>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<-260,40,-60>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<80,40,-200>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 4, "GENERATE", "V<240,40,-560>/V<0,0,0>")
be:sd("MODELCTRL", "g_d1door", 5, "GENERATE", "V<-260,40,500>/V<0,90,0>")
be:sd("MODELCTRL", "g_d1door", 6, "GENERATE", "V<-160,40,560>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 0, "GENERATE", "V<240,40,-660>/V<0,0,0>")
be:sd("MODELCTRL", "n_recorderdng", 1, "GENERATE", "V<120,40,-60>/V<0,-90,0>")
for local_1 = 1, 9 do
    if be:FLGisOn(local_1 + 126) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-%02d", local_1))
    end
end
be:sd("MODELCTRL", "g_d1door", 0, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 1, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 2, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 3, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 4, "SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 5, "SQ_CLEAR")
be:sd("MODELCTRL", "g_d1door", 6, "SQ_BUTTON")
if be:FLGisOn(136) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(137) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 4, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(138) ~= 1 then
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 6, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(117) == 1 then
    be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON")
    g_security = 1
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(118) == 1 then
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(126) == 1 then
    be:sd("MODELCTRL", "g_d1door", 5, "SQ_SILENTON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
if be:FLGisOn(292) == 1 then
    if be:MDLisLive("j_map102b2", 0) == 0 then
        be:DMsetSD("MODELCTRL", "j_map102b2", 0, "GENERATE", "SQ_OPEN")
    end
    for local_2 = 0, 3 do
        if be:SYSisJoinPlayer(local_2) == 1 and be:MDLisLive("j_mapcur", local_2) == 0 then
            be:DMsetSD("MODELCTRL", "j_mapcur", local_2, "GENERATE")
        end
    end
end
