mswk61005 = "TALKFONT01/font00/I<12>"
mswk61006 = "TALKFONT01/font00/I<13>"
mswk61007 = "TALKFONT01/font00/I<14>"
mswk61008 = "TALKFONT01/font00/I<15>"
mswk61009 = "TALKFONT02/font00/I<16>"
mswk61010 = "TALKFONT02/font00/I<17>"
mswk61012 = "TALKFONT02/font00/I<18>"
mswk61013 = "TALKFONT02/font00/I<19>"
mswk61014 = "TALKFONT02/font00/I<20>"
mswk61015 = "TALKFONT02/font00/I<21>"
mswk61097 = "TALKFONT01/font00/I<22>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
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
if be:SYSgetDifficulty() == 0 then
    be:sd("MODELCTRL", "g_d2base", 0, "GENERATE", "V<-336,40,-396>/V<0,0,0>")
    be:sd("MODELCTRL", "g_d2base", 1, "GENERATE", "V<-264,40,-396>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<-336,40,-396>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<-264,40,-396>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<240,40,440>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<300,40,380>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<300,40,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-200,40,0>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-80,40,240>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-20,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<0,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<20,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<100,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<120,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 5, "GENERATE", "V<140,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-300,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-270,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-240,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<-345,40,-405>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<-255,40,-405>/V<0,0,0>")
    if be:FLGisOn(117) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<260,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<300,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<340,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<380,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<420,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<340,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<380,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<420,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<340,30,40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<380,30,40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<420,30,40>/V<0,0,0>")
    end
    if be:FLGisOn(118) == 1 then
        if be:FLGisOn(119) ~= 1 then
            be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-340,30,200>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-340,30,240>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-340,30,280>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-340,30,320>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-340,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-340,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-300,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-260,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-220,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-180,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-140,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-100,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-180,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-140,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-100,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-180,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-140,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-100,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-60,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-20,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-20,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-20,30,320>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-20,30,280>/V<0,0,0>")
        end
    end
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-340,30,200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-340,30,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-340,30,280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-340,30,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-340,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-340,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-300,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-260,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-220,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-180,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-140,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-100,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-180,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-140,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-100,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-180,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-140,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-100,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-60,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-20,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-20,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-20,30,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-20,30,280>/V<0,0,0>")
    g_enemyAmount = 279
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<105,40,-25>/V<0,45,0>")
    for local_2 = 1, 5 do
        if be:FLGisOn(local_2 + 111) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-E%02d", local_2))
        end
    end
    if be:FLGisOn(117) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<235,40,0>/V<0,-90,0>")
    end
    if be:FLGisOn(118) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-20,40,255>/V<0,180,0>")
    end
    if be:FLGisOn(119) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<-315,40,200>/V<0,90,0>")
    end
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    if be:FLGisOn(103) == 1 then
        be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(106) == 1 then
        be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(107) == 1 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    else
    end
end
if be:SYSgetDifficulty() == 1 then
    be:sd("MODELCTRL", "g_d2base", 0, "GENERATE", "V<-336,40,-396>/V<0,0,0>")
    be:sd("MODELCTRL", "g_d2base", 1, "GENERATE", "V<-264,40,-396>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<-336,40,-396>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<-264,40,-396>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<240,40,440>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<300,40,380>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<300,40,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-200,40,0>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-80,40,240>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-20,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<20,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<100,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<120,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<140,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<0,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-300,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-270,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-240,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<-345,40,-405>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<-255,40,-405>/V<0,0,0>")
    if be:FLGisOn(117) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<260,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<300,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<340,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<380,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<420,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<340,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<380,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<420,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<340,30,40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<380,30,40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<420,30,40>/V<0,0,0>")
    end
    if be:FLGisOn(118) == 1 then
        if be:FLGisOn(119) ~= 1 then
            be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-340,30,200>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-340,30,240>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-340,30,280>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-340,30,320>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-340,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-340,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-300,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-260,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-220,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-180,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-140,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-100,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-180,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-140,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-100,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-180,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-140,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-100,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-60,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-20,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-20,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-20,30,320>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-20,30,280>/V<0,0,0>")
        end
    end
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-340,30,200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-340,30,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-340,30,280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-340,30,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-340,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-340,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-300,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-260,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-220,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-180,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-140,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-100,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-180,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-140,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-100,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-180,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-140,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-100,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-60,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-20,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-20,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-20,30,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-20,30,280>/V<0,0,0>")
    g_enemyAmount = 302
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<105,40,-25>/V<0,45,0>")
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,-200>/V<0,45,0>")
    for local_2 = 1, 5 do
        if be:FLGisOn(local_2 + 111) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", local_2))
        end
    end
    if be:FLGisOn(117) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<235,40,0>/V<0,-90,0>")
    end
    if be:FLGisOn(118) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-20,40,255>/V<0,180,0>")
    end
    if be:FLGisOn(119) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<-315,40,200>/V<0,90,0>")
    end
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    if be:FLGisOn(103) == 1 then
        be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(106) == 1 then
        be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(107) == 1 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(111) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
    else
    end
end
if be:SYSgetDifficulty() == 2 then
    be:sd("MODELCTRL", "g_d2base", 0, "GENERATE", "V<-336,40,-396>/V<0,0,0>")
    be:sd("MODELCTRL", "g_d2base", 1, "GENERATE", "V<-264,40,-396>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<-336,40,-396>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<-264,40,-396>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<240,40,440>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<300,40,380>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<300,40,300>/V<0,0,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-200,40,0>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-80,40,240>/V<0,90,0>/SQ_CLEAR")
    be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-20,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<20,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<100,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<120,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<140,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<0,40,-45>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-300,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-270,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-240,40,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<-345,40,-405>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<-255,40,-405>/V<0,0,0>")
    if be:FLGisOn(117) ~= 1 then
        be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<260,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<300,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<340,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<380,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<420,30,-40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<340,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<380,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<420,30,0>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<340,30,40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<380,30,40>/V<0,0,0>")
        be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<420,30,40>/V<0,0,0>")
    end
    if be:FLGisOn(118) == 1 then
        if be:FLGisOn(119) ~= 1 then
            be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-340,30,200>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-340,30,240>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-340,30,280>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-340,30,320>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-340,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-340,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-300,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-260,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-220,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-180,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-140,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-100,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-180,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-140,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-100,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-180,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-140,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-100,30,440>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-60,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-20,30,400>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-20,30,360>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-20,30,320>/V<0,0,0>")
            be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-20,30,280>/V<0,0,0>")
        end
    end
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-340,30,200>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-340,30,240>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-340,30,280>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-340,30,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-340,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-340,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-300,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-260,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-220,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-180,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-140,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-100,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-180,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-140,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-100,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-180,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-140,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-100,30,440>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<-60,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-20,30,400>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<-20,30,360>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<-20,30,320>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<-20,30,280>/V<0,0,0>")
    g_enemyAmount = 302
    be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<105,40,-25>/V<0,45,0>")
    be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-220,40,-200>/V<0,45,0>")
    be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<75,40,433>/V<0,-90,0>")
    for local_2 = 1, 5 do
        if be:FLGisOn(local_2 + 111) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", local_2))
        end
    end
    if be:FLGisOn(117) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<235,40,0>/V<0,-90,0>")
    end
    if be:FLGisOn(118) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-20,40,255>/V<0,180,0>")
    end
    if be:FLGisOn(119) ~= 1 then
        be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<-315,40,200>/V<0,90,0>")
    end
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    if be:FLGisOn(103) == 1 then
        be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    end
    if be:FLGisOn(106) == 1 then
        be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
    end
    if be:FLGisOn(107) == 1 then
        be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
    end
    if be:FLGisOn(111) == 1 then
        be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
    else
    end
end
be:MsgBox("G[FïÕxªzèOÅ·B")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
