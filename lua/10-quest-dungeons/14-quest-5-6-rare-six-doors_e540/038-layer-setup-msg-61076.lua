local local_0
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
local sgBox = function()
    g_mapLink = {}
    g_mapBlockStartP = {}
    g_luckyMapBlock = 0
    g_destMapBlock = 1
    g_curMapBlock = 1
    g_linkPtnNum = be:SYSgetRandom(4 + be:SYSgetDifficulty())
    if g_linkPtnNum == 0 then
        g_mapLink[1] = {2, 3}
        g_mapLink[2] = {4, 5}
        g_mapLink[3] = {6}
        g_mapLink[4] = {7}
        g_mapLink[5] = {8}
        g_mapLink[6] = {8, 9}
        g_mapLink[7] = {10, 11, 12}
        g_mapLink[8] = {13, 14, 15}
        g_mapLink[11] = {16}
        g_mapLink[13] = {17}
        g_mapLink[16] = {18, 19}
        g_mapLink[17] = {22, 19, 20}
        g_mapLink[18] = {21}
        g_mapLink[20] = {22}
        g_mapLink[21] = {23}
        g_mapLink[22] = {24, 25}
        g_mapBlockStartP[2] = 3
        g_mapBlockStartP[3] = 4
        g_mapBlockStartP[4] = 4
        g_mapBlockStartP[5] = 4
        g_mapBlockStartP[6] = 3
        g_mapBlockStartP[7] = 7
        g_mapBlockStartP[8] = 6
        g_mapBlockStartP[9] = 2
        g_mapBlockStartP[10] = 1
        g_mapBlockStartP[11] = 5
        g_mapBlockStartP[12] = 2
        g_mapBlockStartP[13] = 4
        g_mapBlockStartP[14] = 2
        g_mapBlockStartP[15] = 1
        g_mapBlockStartP[16] = 3
        g_mapBlockStartP[17] = 6
        g_mapBlockStartP[18] = 4
        g_mapBlockStartP[19] = 2
        g_mapBlockStartP[20] = 4
        g_mapBlockStartP[21] = 4
        g_mapBlockStartP[22] = 3
        g_mapBlockStartP[23] = 2
        g_mapBlockStartP[24] = 1
        g_mapBlockStartP[25] = 2
        g_luckyMapBlock = 23
        g_dorumon01MapBlock = {2}
        g_dorumon02MapBlock = {3}
        g_agumon01MapBlock = {8, 17}
        g_agumon02MapBlock = {7}
        g_girumon01MapBlock = {8}
        g_girumon02MapBlock = {7}
    elseif g_linkPtnNum == 1 then
        g_mapLink[1] = {2, 3}
        g_mapLink[2] = {4, 5}
        g_mapLink[3] = {6}
        g_mapLink[4] = {7}
        g_mapLink[5] = {8}
        g_mapLink[6] = {9, 8}
        g_mapLink[7] = {10, 11, 12}
        g_mapLink[8] = {16, 13, 17}
        g_mapLink[9] = {15, 14, 13}
        g_mapLink[11] = {15}
        g_mapLink[12] = {17, 16}
        g_mapLink[13] = {21, 20}
        g_mapLink[15] = {21, 18}
        g_mapLink[17] = {19}
        g_mapLink[20] = {22}
        g_mapLink[21] = {23}
        g_mapLink[22] = {24}
        g_mapBlockStartP[2] = 3
        g_mapBlockStartP[3] = 4
        g_mapBlockStartP[4] = 4
        g_mapBlockStartP[5] = 4
        g_mapBlockStartP[6] = 3
        g_mapBlockStartP[7] = 6
        g_mapBlockStartP[8] = 7
        g_mapBlockStartP[9] = 6
        g_mapBlockStartP[10] = 2
        g_mapBlockStartP[11] = 4
        g_mapBlockStartP[12] = 3
        g_mapBlockStartP[13] = 8
        g_mapBlockStartP[14] = 1
        g_mapBlockStartP[15] = 3
        g_mapBlockStartP[16] = 1
        g_mapBlockStartP[17] = 4
        g_mapBlockStartP[18] = 2
        g_mapBlockStartP[19] = 2
        g_mapBlockStartP[20] = 5
        g_mapBlockStartP[21] = 4
        g_mapBlockStartP[22] = 4
        g_mapBlockStartP[23] = 2
        g_mapBlockStartP[24] = 2
        g_luckyMapBlock = 24
        g_dorumon01MapBlock = {2}
        g_dorumon02MapBlock = {3}
        g_agumon01MapBlock = {7, 9}
        g_agumon02MapBlock = {8}
        g_girumon01MapBlock = {7, 9}
        g_girumon02MapBlock = {8}
    elseif g_linkPtnNum == 2 then
        g_mapLink[1] = {2, 3}
        g_mapLink[2] = {4}
        g_mapLink[3] = {5}
        g_mapLink[4] = {6, 7}
        g_mapLink[5] = {8, 9}
        g_mapLink[6] = {10}
        g_mapLink[7] = {11}
        g_mapLink[8] = {12}
        g_mapLink[9] = {13}
        g_mapLink[10] = {14, 15}
        g_mapLink[11] = {17, 18, 20}
        g_mapLink[12] = {19}
        g_mapLink[13] = {20, 19, 21}
        g_mapLink[14] = {16}
        g_mapLink[15] = {17, 18}
        g_mapLink[17] = {23, 24}
        g_mapLink[18] = {22}
        g_mapLink[19] = {25, 24, 26}
        g_mapLink[22] = {23, 26}
        g_mapLink[24] = {27}
        g_mapBlockStartP[2] = 4
        g_mapBlockStartP[3] = 4
        g_mapBlockStartP[4] = 3
        g_mapBlockStartP[5] = 3
        g_mapBlockStartP[6] = 4
        g_mapBlockStartP[7] = 4
        g_mapBlockStartP[8] = 4
        g_mapBlockStartP[9] = 5
        g_mapBlockStartP[10] = 3
        g_mapBlockStartP[11] = 6
        g_mapBlockStartP[12] = 4
        g_mapBlockStartP[13] = 6
        g_mapBlockStartP[14] = 4
        g_mapBlockStartP[15] = 3
        g_mapBlockStartP[16] = 2
        g_mapBlockStartP[17] = 8
        g_mapBlockStartP[18] = 4
        g_mapBlockStartP[19] = 7
        g_mapBlockStartP[20] = 1
        g_mapBlockStartP[21] = 2
        g_mapBlockStartP[22] = 3
        g_mapBlockStartP[23] = 2
        g_mapBlockStartP[24] = 4
        g_mapBlockStartP[25] = 1
        g_mapBlockStartP[26] = 2
        g_mapBlockStartP[27] = 2
        g_luckyMapBlock = 27
        g_dorumon01MapBlock = {}
        g_dorumon02MapBlock = {2, 3}
        g_agumon01MapBlock = {11, 13}
        g_agumon02MapBlock = {19}
        g_girumon01MapBlock = {11, 13}
        g_girumon02MapBlock = {}
    elseif g_linkPtnNum == 3 then
        g_mapLink[1] = {2, 3}
        g_mapLink[2] = {4}
        g_mapLink[3] = {5}
        g_mapLink[4] = {6, 7}
        g_mapLink[5] = {8, 9}
        g_mapLink[6] = {10}
        g_mapLink[7] = {11}
        g_mapLink[8] = {12}
        g_mapLink[9] = {13}
        g_mapLink[10] = {14, 15}
        g_mapLink[11] = {18, 19, 20}
        g_mapLink[12] = {16}
        g_mapLink[13] = {20, 21, 21}
        g_mapLink[14] = {18}
        g_mapLink[15] = {17, 19}
        g_mapLink[16] = {19}
        g_mapLink[18] = {25, 24}
        g_mapLink[20] = {25, 24, 26}
        g_mapLink[21] = {22, 23}
        g_mapLink[23] = {26}
        g_mapLink[24] = {27, 28}
        g_mapBlockStartP[2] = 4
        g_mapBlockStartP[3] = 4
        g_mapBlockStartP[4] = 3
        g_mapBlockStartP[5] = 3
        g_mapBlockStartP[6] = 4
        g_mapBlockStartP[7] = 5
        g_mapBlockStartP[8] = 4
        g_mapBlockStartP[9] = 4
        g_mapBlockStartP[10] = 3
        g_mapBlockStartP[11] = 6
        g_mapBlockStartP[12] = 4
        g_mapBlockStartP[13] = 6
        g_mapBlockStartP[14] = 4
        g_mapBlockStartP[15] = 3
        g_mapBlockStartP[16] = 4
        g_mapBlockStartP[17] = 1
        g_mapBlockStartP[18] = 8
        g_mapBlockStartP[19] = 2
        g_mapBlockStartP[20] = 7
        g_mapBlockStartP[21] = 3
        g_mapBlockStartP[22] = 1
        g_mapBlockStartP[23] = 5
        g_mapBlockStartP[24] = 3
        g_mapBlockStartP[25] = 2
        g_mapBlockStartP[26] = 2
        g_mapBlockStartP[27] = 2
        g_mapBlockStartP[28] = 2
        g_luckyMapBlock = 27
        g_dorumon01MapBlock = {}
        g_dorumon02MapBlock = {2, 3}
        g_agumon01MapBlock = {13}
        g_agumon02MapBlock = {20}
        g_girumon01MapBlock = {11, 13}
        g_girumon02MapBlock = {}
    elseif g_linkPtnNum == 4 then
        g_mapLink[1] = {2, 3}
        g_mapLink[2] = {4}
        g_mapLink[3] = {5}
        g_mapLink[4] = {6, 7}
        g_mapLink[5] = {8, 9}
        g_mapLink[6] = {10}
        g_mapLink[7] = {11}
        g_mapLink[8] = {12}
        g_mapLink[9] = {13}
        g_mapLink[10] = {14, 15}
        g_mapLink[11] = {17, 16, 19}
        g_mapLink[12] = {18}
        g_mapLink[13] = {20, 18, 19}
        g_mapLink[15] = {16, 17}
        g_mapLink[16] = {22, 23}
        g_mapLink[17] = {21}
        g_mapLink[18] = {24, 23, 25}
        g_mapLink[20] = {25, 24, 25}
        g_mapLink[21] = {22, 24}
        g_mapLink[23] = {26}
        g_mapBlockStartP[2] = 4
        g_mapBlockStartP[3] = 4
        g_mapBlockStartP[4] = 3
        g_mapBlockStartP[5] = 3
        g_mapBlockStartP[6] = 5
        g_mapBlockStartP[7] = 5
        g_mapBlockStartP[8] = 4
        g_mapBlockStartP[9] = 4
        g_mapBlockStartP[10] = 3
        g_mapBlockStartP[11] = 6
        g_mapBlockStartP[12] = 5
        g_mapBlockStartP[13] = 6
        g_mapBlockStartP[14] = 1
        g_mapBlockStartP[15] = 3
        g_mapBlockStartP[16] = 8
        g_mapBlockStartP[17] = 4
        g_mapBlockStartP[18] = 7
        g_mapBlockStartP[19] = 1
        g_mapBlockStartP[20] = 7
        g_mapBlockStartP[21] = 3
        g_mapBlockStartP[22] = 2
        g_mapBlockStartP[23] = 4
        g_mapBlockStartP[24] = 1
        g_mapBlockStartP[25] = 2
        g_mapBlockStartP[26] = 2
        g_luckyMapBlock = 26
        g_dorumon01MapBlock = {}
        g_dorumon02MapBlock = {2, 3}
        g_agumon01MapBlock = {11, 13}
        g_agumon02MapBlock = {18, 20}
        g_girumon01MapBlock = {11, 13}
        g_girumon02MapBlock = {}
    elseif g_linkPtnNum == 5 then
        g_mapLink[1] = {2, 3}
        g_mapLink[2] = {4}
        g_mapLink[3] = {5}
        g_mapLink[4] = {6, 7}
        g_mapLink[5] = {8, 9}
        g_mapLink[6] = {10}
        g_mapLink[7] = {11}
        g_mapLink[8] = {12}
        g_mapLink[9] = {13}
        g_mapLink[10] = {14, 15}
        g_mapLink[11] = {17, 19, 20}
        g_mapLink[12] = {16}
        g_mapLink[13] = {20, 21, 21}
        g_mapLink[14] = {18}
        g_mapLink[15] = {17, 19}
        g_mapLink[16] = {19}
        g_mapLink[17] = {25, 24}
        g_mapLink[18] = {26, 25}
        g_mapLink[20] = {26, 25, 27}
        g_mapLink[21] = {22, 23}
        g_mapLink[23] = {27}
        g_mapLink[25] = {28, 29}
        g_mapBlockStartP[2] = 4
        g_mapBlockStartP[3] = 4
        g_mapBlockStartP[4] = 3
        g_mapBlockStartP[5] = 3
        g_mapBlockStartP[6] = 4
        g_mapBlockStartP[7] = 4
        g_mapBlockStartP[8] = 5
        g_mapBlockStartP[9] = 5
        g_mapBlockStartP[10] = 3
        g_mapBlockStartP[11] = 6
        g_mapBlockStartP[12] = 4
        g_mapBlockStartP[13] = 6
        g_mapBlockStartP[14] = 4
        g_mapBlockStartP[15] = 3
        g_mapBlockStartP[16] = 5
        g_mapBlockStartP[17] = 8
        g_mapBlockStartP[18] = 8
        g_mapBlockStartP[19] = 1
        g_mapBlockStartP[20] = 7
        g_mapBlockStartP[21] = 3
        g_mapBlockStartP[22] = 1
        g_mapBlockStartP[23] = 5
        g_mapBlockStartP[24] = 1
        g_mapBlockStartP[25] = 3
        g_mapBlockStartP[26] = 2
        g_mapBlockStartP[27] = 2
        g_mapBlockStartP[28] = 2
        g_mapBlockStartP[29] = 2
        g_luckyMapBlock = 29
        g_dorumon01MapBlock = {}
        g_dorumon02MapBlock = {2, 3}
        g_agumon01MapBlock = {13}
        g_agumon02MapBlock = {20}
        g_girumon01MapBlock = {11, 13}
        g_girumon02MapBlock = {}
    else
        be:MsgBox("ÌÍÍÜ½ÍïÕxªzèOÅ·B")
    end
end
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.9,1.0,0.9>/V<1.0,0.9,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.25,0.18,0.25>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_2 = 906
be:COUNTERset(2, local_2)
for flagNo = 100, 299 do
    be:FLGset(flagNo, 0)
end
sgBox()
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
