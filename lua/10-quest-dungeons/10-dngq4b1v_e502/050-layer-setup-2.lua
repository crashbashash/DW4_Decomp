mswk61067 = "TALKFONT01/font00/I<1>"
mswk61068 = "TALKFONT01/font00/I<2>"
mswk61071 = "TALKFONT01/font00/I<3>"
mswk61072 = "TALKFONT02/font00/I<4>"
mswk61073 = "TALKFONT02/font00/I<5>"
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
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<-520,40,-260>/V<0,-90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<-320,40,-260>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<-380,40,-320>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-260,40,-320>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-320,40,-380>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 5, "GENERATE", "V<240,40,-220>/V<0,-90,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d2door", 6, "GENERATE", "V<300,40,-320>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 7, "GENERATE", "V<360,40,-380>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<520,40,-140>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 9, "GENERATE", "V<520,40,-20>/V<0,90,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d2door", 10, "GENERATE", "V<460,40,-80>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 11, "GENERATE", "V<460,40,40>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 12, "GENERATE", "V<460,40,200>/V<0,0,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d2door", 13, "GENERATE", "V<460,40,320>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<-575,40,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 1, "GENERATE", "V<-495,40,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 2, "GENERATE", "V<-665,40,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 3, "GENERATE", "V<-660,40,-225>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 4, "GENERATE", "V<580,40,-185>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 5, "GENERATE", "V<-740,40,-135>/V<0,180,0>")
be:sd("MODELCTRL", "g_darrowshotter", 6, "GENERATE", "V<-825,40,-100>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 7, "GENERATE", "V<-905,40,-60>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 8, "GENERATE", "V<-860,40,-105>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 9, "GENERATE", "V<-815,40,-140>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 10, "GENERATE", "V<-1065,40,-60>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 11, "GENERATE", "V<-935,40,-220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 12, "GENERATE", "V<-980,40,-265>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 13, "GENERATE", "V<-860,40,-215>/V<0,180,0>")
be:sd("MODELCTRL", "g_darrowshotter", 14, "GENERATE", "V<-780,40,-215>/V<0,180,0>")
be:sd("MODELCTRL", "g_darrowshotter", 15, "GENERATE", "V<-700,40,-215>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<160,40,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-720,40,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-180,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-150,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-120,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<-90,40,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<460,40,75>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 6, "GENERATE", "V<460,40,110>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 7, "GENERATE", "V<460,40,145>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 8, "GENERATE", "V<460,40,180>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 9, "GENERATE", "V<-700,40,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 10, "GENERATE", "V<-680,40,-180>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 11, "GENERATE", "V<-950,40,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 12, "GENERATE", "V<-930,40,-140>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 13, "GENERATE", "V<-840,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 14, "GENERATE", "V<-800,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 15, "GENERATE", "V<-760,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 16, "GENERATE", "V<-720,40,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<-60,40,-425>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<405,40,-35>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<405,40,-5>/V<0,-90,0>")
if be:FLGisOn(141) ~= 1 and be:FLGisOn(142) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-700,30,-140>/V<0,0,0>")
end
if be:FLGisOn(143) ~= 1 and be:FLGisOn(144) ~= 1 and be:FLGisOn(145) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-980,30,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-940,30,-140>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<-20,40,-220>/V<0,90,0>")
for local_2 = 1, 2 do
    if be:FLGisOn(local_2 + 107) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", local_2))
    end
end
if be:FLGisOn(115) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<30,40,-220>/V<0,180,0>")
end
if be:FLGisOn(141) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<-700,40,-115>/V<0,0,0>/SQ_CUTRIGHT")
end
if be:FLGisOn(142) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-700,40,-165>/V<0,180,0>")
end
if be:FLGisOn(143) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<-915,40,-140>/V<0,90,0>/SQ_CUTRIGHT")
end
if be:FLGisOn(144) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 3, "GENERATE", "V<-940,40,-115>/V<0,0,0>/SQ_CUTBOTH")
end
if be:FLGisOn(145) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 4, "GENERATE", "V<-1005,40,-140>/V<0,-90,0>")
end
if be:FLGisOn(100) == 1 then
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(101) == 1 then
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
end
if be:FLGisOn(102) == 1 then
    be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
end
if be:FLGisOn(103) == 1 then
    be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
end
if be:FLGisOn(104) == 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
end
if be:FLGisOn(105) == 1 then
    be:sd("MODELCTRL", "g_d2door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
if be:FLGisOn(107) == 1 then
    be:sd("MODELCTRL", "g_d2door", 13, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_d2door", 12, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall13", 0, "OFFHIT")
end
if be:FLGisOn(110) == 1 then
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(111) == 1 then
    be:sd("MODELCTRL", "g_d2door", 8, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT")
end
if be:FLGisOn(112) == 1 then
    be:sd("MODELCTRL", "g_d2door", 9, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT")
end
if be:FLGisOn(117) == 1 then
    be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_ONLOOP")
end
if be:FLGisOn(118) == 1 then
    be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_ONLOOP")
end
if be:FLGisOn(117) == 1 and be:FLGisOn(118) == 1 then
    if be:FLGisOn(119) == 1 then
        be:sd("MODELCTRL", "g_d2door", 10, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT")
    else
        be:sd("MODELCTRL", "g_d2door", 11, "SQ_SILENTON", 1)
        be:sd("HITLANDMODEL", "doorwall12", 0, "OFFHIT")
    end
end
be:sd("MODELCTRL", "g_d2door", 6, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
