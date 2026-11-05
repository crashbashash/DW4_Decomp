mswk61076 = "TALKFONT01/font00/I<13>"
mswk61077 = "TALKFONT01/font00/I<14>"
mswk61078 = "TALKFONT01/font00/I<15>"
mswk61079 = "TALKFONT02/font00/I<16>"
mswk61080 = "TALKFONT02/font00/I<17>"
mswk61081 = "TALKFONT02/font00/I<18>"
mswk61082 = "TALKFONT02/font00/I<19>"
mswk61083 = "TALKFONT02/font00/I<20>"
mswk61084 = "TALKFONT02/font00/I<21>"
mswk61090 = "TALKFONT01/font00/I<22>"
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
be:COUNTERset(2, local_2)
for local_3 = 100, 299 do
    be:FLGset(local_3, 0)
end
local_1()
be:sd("MODELCTRL", "g_d4bkwall", 0, "GENERATE", "V<875,40,100>/V<0,-90,0>")
be:sd("MODELCTRL", "g_d4door", 0, "GENERATE", "V<-1080,40,460>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 1, "GENERATE", "V<-660,40,400>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 2, "GENERATE", "V<260,40,-120>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 3, "GENERATE", "V<960,40,-20>/V<0,90,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 4, "GENERATE", "V<1020,40,-120>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 5, "GENERATE", "V<900,40,-220>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d4door", 6, "GENERATE", "V<900,65,-440>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 7, "GENERATE", "V<1420,40,-120>/V<0,0,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_d4door", 8, "GENERATE", "V<1500,40,-120>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 9, "GENERATE", "V<1580,40,-120>/V<0,0,0>/SQ_CLEAR")
be:sd("MODELCTRL", "g_d4door", 10, "GENERATE", "V<1660,40,-120>/V<0,0,0>/SQ_BOSS")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<940,40,-220>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhpheal", 0, "GENERATE", "V<-220,40,520>/V<0,0,0>")
be:sd("MODELCTRL", "g_dhphealeffect", 0, "GENERATE", "V<-220,40,520>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 0, "GENERATE", "V<220,40,-265>/V<0,0,0>")
be:sd("MODELCTRL", "g_dlasergun", 1, "GENERATE", "V<980,40,-265>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<-660,40,-660>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 1, "GENERATE", "V<-220,40,-690>/V<0,0,0>")
be:sd("MODELCTRL", "g_dscrap", 0, "GENERATE", "V<280,40,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dscrap", 1, "GENERATE", "V<880,40,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dscrap", 2, "GENERATE", "V<1480,40,220>/V<0,-90,0>")
be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<900,30,100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<940,30,100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<940,30,60>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<940,30,20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<940,30,-20>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", -1, "SQ_POWERON")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
