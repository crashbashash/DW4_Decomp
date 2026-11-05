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
be:sd("MODELCTRL", "g_d2door", 8, "GENERATE", "V<-60,10,-980>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d2door", 9, "GENERATE", "V<-60,10,-1180>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_darrowshotter", 0, "GENERATE", "V<25,10,-560>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 1, "GENERATE", "V<25,10,-680>/V<0,-90,0>")
be:sd("MODELCTRL", "g_darrowshotter", 2, "GENERATE", "V<-20,10,-725>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 3, "GENERATE", "V<-80,10,-965>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 4, "GENERATE", "V<-40,10,-965>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 5, "GENERATE", "V<-100,10,-765>/V<0,0,0>")
be:sd("MODELCTRL", "g_darrowshotter", 6, "GENERATE", "V<-15,10,-800>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dbutton2", 0, "GENERATE", "V<-215,10,-35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton2", 1, "GENERATE", "V<-215,10,35>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 0, "GENERATE", "V<-280,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 1, "GENERATE", "V<-260,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 2, "GENERATE", "V<-180,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 3, "GENERATE", "V<-160,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 4, "GENERATE", "V<20,10,155>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcoffin", 5, "GENERATE", "V<60,10,155>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 0, "GENERATE", "V<-20,10,-620>/V<0,-90,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 1, "GENERATE", "V<-140,10,-800>/V<0,0,0>")
be:sd("MODELCTRL", "g_ddamagefloor", 2, "GENERATE", "V<-100,10,-800>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 0, "GENERATE", "V<-300,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 1, "GENERATE", "V<-140,10,195>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpharocoffin", 2, "GENERATE", "V<40,10,155>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 0, "GENERATE", "V<105,10,-45>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 1, "GENERATE", "V<105,10,45>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 2, "GENERATE", "V<-105,10,-485>/V<0,0,0>")
be:sd("MODELCTRL", "g_dpot", 3, "GENERATE", "V<-15,10,-485>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-60,10,-1270>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton2", 0, "GENERATE", "V<-115,10,-920>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dwbutton2", 1, "GENERATE", "V<-5,10,-920>/V<0,90,0>")
if be:FLGisOn(139) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-20,0,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<20,0,-560>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<-20,0,-600>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<-20,0,-640>/V<0,0,0>")
end
if be:FLGisOn(140) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-60,0,-639>/V<0,0,0>")
end
if be:FLGisOn(143) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-100,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-60,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-20,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<20,0,-680>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-20,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-100,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-100,0,-760>/V<0,0,0>")
end
if be:FLGisOn(144) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-140,0,-720>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-140,0,-760>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-140,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-100,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-60,0,-800>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-20,0,-800>/V<0,0,0>")
end
be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-160,10,-10>/V<0,-90,0>")
for local_1 = 1, 4 do
    if be:FLGisOn(local_1 + 130) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", format("GBOX-H%02d", local_1))
    end
end
if be:FLGisOn(137) ~= 1 then
    be:sd("MODELCTRL", "g_d2dktower", 0, "GENERATE", "V<160,10,180>/V<0,0,0>")
end
if be:FLGisOn(138) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkstone", 0, "GENERATE", "V<-120,35,-240>/V<0,0,0>")
end
if be:FLGisOn(139) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 0, "GENERATE", "V<-45,10,-560>/V<0,-90,0>")
end
if be:FLGisOn(140) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 1, "GENERATE", "V<-60,10,-615>/V<0,0,0>/SQ_CUTBOTH")
end
if be:FLGisOn(143) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 2, "GENERATE", "V<-20,10,-655>/V<0,0,0>/SQ_CUTBOTH")
end
if be:FLGisOn(144) ~= 1 then
    be:sd("MODELCTRL", "g_d2bkwall", 3, "GENERATE", "V<-115,10,-720>/V<0,90,0>")
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
