mswk61069 = "TALKFONT01/font00/I<2>"
mswk61070 = "TALKFONT01/font00/I<3>"
mswk61071 = "TALKFONT01/font00/I<4>"
mswk61074 = "TALKFONT02/font00/I<5>"
mswk61075 = "TALKFONT02/font00/I<6>"
mswk61087 = "TALKFONT01/font00/I<7>"
mswk61088 = "TALKFONT01/font00/I<8>"
mswk61089 = "TALKFONT01/font00/I<9>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<1.1,1.1,0.9>/V<1.1,1.1,0.9>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.23,0.2>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:sd("MODELCTRL", "g_sandfalls", 0, "GENERATE", "V<-220,20,-120>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 0, "GENERATE", "V<96,10,-36>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2base", 1, "GENERATE", "V<96,10,36>/V<0,180,0>")
be:sd("MODELCTRL", "g_d2base", 2, "GENERATE", "V<-96,10,-476>/V<0,0,0>")
be:sd("MODELCTRL", "g_d2base", 3, "GENERATE", "V<-24,10,-476>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 0, "GENERATE", "V<96,10,-36>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbasewall", 1, "GENERATE", "V<96,10,36>/V<0,180,0>")
be:sd("MODELCTRL", "g_dbasewall", 2, "GENERATE", "V<-96,10,-476>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbasewall", 3, "GENERATE", "V<-24,10,-476>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d2door", 0, "GENERATE", "V<-120,35,400>/V<0,-90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 1, "GENERATE", "V<0,10,0>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 2, "GENERATE", "V<120,10,0>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 3, "GENERATE", "V<-60,10,-60>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 4, "GENERATE", "V<-60,10,-180>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 5, "GENERATE", "V<-120,10,0>/V<0,-90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 6, "GENERATE", "V<-240,10,0>/V<0,-90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 7, "GENERATE", "V<-60,10,-500>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<140,10,-1100>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 9, "GENERATE", "V<140,10,-1300>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<-145,10,-640>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 1, "GENERATE", "V<-20,10,-685>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 2, "GENERATE", "V<-15,10,-720>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 3, "GENERATE", "V<120,10,-1085>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 4, "GENERATE", "V<160,10,-1085>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 5, "GENERATE", "V<-65,10,-760>/V<0,90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 6, "GENERATE", "V<145,10,-760>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 7, "GENERATE", "V<-140,10,-845>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 8, "GENERATE", "V<-20,10,-845>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 9, "GENERATE", "V<185,10,-840>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-215,10,-35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-215,10,35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-280,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<-260,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<-180,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<-160,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<20,10,155>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 5, "GENERATE", "V<60,10,155>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<140,10,-640>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-140,10,-720>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-20,10,-800>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 3, "GENERATE", "V<-20,10,-780>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 4, "GENERATE", "V<80,10,-840>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 5, "GENERATE", "V<100,10,-840>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<-300,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 1, "GENERATE", "V<-140,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 2, "GENERATE", "V<40,10,155>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<105,10,-45>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<105,10,45>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 2, "GENERATE", "V<-105,10,-485>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 3, "GENERATE", "V<-15,10,-485>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<140,10,-1390>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<85,10,-1040>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<195,10,-1040>/V<0,90,0>")
if be:FLGisOn(139) ~= 1 and be:FLGisOn(146) ~= 1 and be:FLGisOn(147) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<20,0,-640>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<60,0,-640>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<100,0,-640>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<140,0,-640>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<20,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<140,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<20,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<140,0,-720>/V<0,0,0>")
end
if be:FLGisOn(140) ~= 1 and be:FLGisOn(149) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-100,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-140,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-100,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-60,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-20,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-140,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-100,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-140,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-140,0,-840>/V<0,0,0>")
end
if be:FLGisOn(146) ~= 1 and be:FLGisOn(148) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<60,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<60,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<100,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<60,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<100,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<140,0,-760>/V<0,0,0>")
end
if be:FLGisOn(147) ~= 1 and be:FLGisOn(149) ~= 1 and be:FLGisOn(150) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<20,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<-20,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<-60,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<-100,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<-60,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<-20,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<20,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<-20,0,-840>/V<0,0,0>")
end
if be:FLGisOn(148) ~= 1 and be:FLGisOn(150) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<60,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<100,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<60,0,-840>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 34, "GENERATE", "V<100,0,-840>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 35, "GENERATE", "V<140,0,-840>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 36, "GENERATE", "V<180,0,-840>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 37, "GENERATE", "V<100,0,-880>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 38, "GENERATE", "V<100,0,-920>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 39, "GENERATE", "V<100,0,-960>/V<0,0,0>")
end
if be:FLGisOn(151) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 40, "GENERATE", "V<140,0,-880>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 41, "GENERATE", "V<140,0,-920>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 42, "GENERATE", "V<140,0,-960>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 43, "GENERATE", "V<100,0,-1000>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 44, "GENERATE", "V<140,0,-1000>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 45, "GENERATE", "V<180,0,-1000>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 46, "GENERATE", "V<100,0,-1040>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 47, "GENERATE", "V<140,0,-1040>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 48, "GENERATE", "V<180,0,-1040>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 49, "GENERATE", "V<135,1,-995>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 50, "GENERATE", "V<175,1,-995>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-160,10,-10>/V<0,-90,0>")
for local_1 = 1, 4 do
    if be:FLGisOn(local_1 + 130) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-V%02d", local_1))
    end
end
if be:FLGisOn(137) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<160,10,180>/V<0,0,0>")
end
if be:FLGisOn(138) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<-120,35,-240>/V<0,0,0>")
end
if be:FLGisOn(139) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<-5,10,-640>/V<0,-90,0>")
    be:sd("MODELCTRL", "g_d2bkwall", 1, "SQ_CUTLEFT")
end
if be:FLGisOn(140) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-100,10,-655>/V<0,0,0>")
end
if be:FLGisOn(146) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<35,10,-680>/V<0,-90,0>")
end
if be:FLGisOn(147) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 3, "GENERATE", "V<20,10,-735>/V<0,0,0>/SQ_CUTBOTH")
end
if be:FLGisOn(148) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 4, "GENERATE", "V<100,10,-775>/V<0,0,0>/SQ_CUTLEFT")
end
if be:FLGisOn(149) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 5, "GENERATE", "V<-125,10,-800>/V<0,-90,0>")
end
if be:FLGisOn(150) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 6, "GENERATE", "V<35,10,-800>/V<0,-90,0>/SQ_CUTBOTH")
end
if be:FLGisOn(151) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 7, "GENERATE", "V<140,10,-855>/V<0,0,0>")
end
if be:FLGisOn(135) == 1 then
    be:sd("MODELCTRL", "g_dbutton2", -1, "SQ_ONLOOP")
    be:sd("MODELCTRL", "g_d2door", 6, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton2", -1, "SQ_POWERON")
end
if be:FLGisOn(136) == 1 then
    be:sd("MODELCTRL", "g_dwbutton2", -1, "SQ_ONLOOP")
end
if be:FLGisOn(121) == 1 then
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(122) == 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 0, "SQ_OPEN")
end
if be:FLGisOn(123) == 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 1, "SQ_OPEN")
end
if be:FLGisOn(124) == 1 then
    be:sd("MODELCTRL", "g_dpharocoffin", 2, "SQ_OPEN")
end
if be:FLGisOn(126) == 1 then
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT")
end
if be:FLGisOn(129) == 1 then
    be:sd("MODELCTRL", "g_d2door", 7, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_d2door", 1, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d2door", 3, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
be:sd("MODELCTRL", "g_d2door", 4, "SQ_SILENTON", 1)
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT")
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
