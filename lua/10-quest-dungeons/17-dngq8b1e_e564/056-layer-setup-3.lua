mswk61093 = "TALKFONT01/font00/I<10>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for local_2 = 100, 299 do
        be:FLGset(local_2, 0)
    end
    g_intro = 1
end
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<-340,40,580>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<-340,40,420>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<-120,40,160>/V<0,90,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<-40,40,160>/V<0,90,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<180,65,260>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<280,65,160>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<180,65,60>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<180,40,380>/V<0,0,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<120,40,440>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<-80,40,440>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<240,40,440>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 11, "GENERATE", "V<300,40,260>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 12, "GENERATE", "V<-440,40,-80>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 13, "GENERATE", "V<100,40,-300>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 14, "GENERATE", "V<460,40,-20>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 15, "GENERATE", "V<360,40,-80>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 16, "GENERATE", "V<460,40,-140>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 17, "GENERATE", "V<220,65,-500>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<160,40,420>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<200,40,420>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 2, "GENERATE", "V<160,40,460>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 3, "GENERATE", "V<200,40,460>/V<0,0,0>")
if be:SYSgetDifficulty() == 0 then
    for local_2 = 1, 17 do
        if be:FLGisOn(local_2 + 122) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-E%02d", local_2))
        end
    end
end
if be:SYSgetDifficulty() == 1 then
    for local_2 = 1, 17 do
        if be:FLGisOn(local_2 + 122) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", local_2))
        end
    end
end
if be:SYSgetDifficulty() == 2 then
    for local_2 = 1, 17 do
        if be:FLGisOn(local_2 + 122) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", local_2))
        end
    end
end
be:MsgBox("G[FïÕxªzèOÅ·B")
if be:FLGisOn(100) == 1 then
    be:sd("MODELCTRL", "g_d4door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(101) == 1 then
    be:sd("MODELCTRL", "g_d4door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
if be:FLGisOn(105) == 1 then
    be:sd("MODELCTRL", "g_d4door", 4, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 5, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
end
if be:FLGisOn(119) == 1 then
    be:sd("MODELCTRL", "g_d4door", 13, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
end
if be:FLGisOn(120) == 1 then
    be:sd("MODELCTRL", "g_d4door", 14, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall15", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 15, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 16, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT")
end
if be:FLGisOn(122) == 1 then
    be:sd("MODELCTRL", "g_d4door", 17, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT")
end
if be:FLGisOn(140) == 1 then
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    for local_2 = 0, 3 do
        be:sd("MODELCTRL", "g_dbutton2", local_2, "SQ_ONLOOP")
    end
end
be:sd("MODELCTRL", "g_dbutton2", 3, "SQ_POWERON")
if be:SYSgetPlayerNinzu() >= 2 then
    be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton2", 2, "SQ_ONLOOP")
    g_button03 = 1
end
if be:SYSgetPlayerNinzu() >= 3 then
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton2", 1, "SQ_ONLOOP")
    g_button02 = 1
end
if be:SYSgetPlayerNinzu() >= 4 then
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_dbutton2", 0, "SQ_ONLOOP")
    g_button01 = 1
end
if be:FLGisOn(140) == 1 then
    if be:FLGisOn(106) == 1 then
        be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
    end
end
be:sd("MODELCTRL", "g_d4door", 7, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
if be:PLAYERgetPos() == 0 then
    be:sd("MODELCTRL", "g_d4door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:FLGset(143, 0)
else
    be:sd("MODELCTRL", "g_d4door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    be:FLGset(143, 1)
end
be:sd("MODELCTRL", "g_d4door", 9, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 11, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d4door", 12, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
