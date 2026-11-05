funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
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
be:sd("MODELCTRL", "g_d1door", 0, "GENERATE", "V<-120,10,-240>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 1, "GENERATE", "V<120,10,-240>/V<0,0,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 2, "GENERATE", "V<-180,10,-300>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_d1door", 3, "GENERATE", "V<180,10,-300>/V<0,90,0>/SQ_BUTTON")
be:sd("MODELCTRL", "g_dbutton1", 0, "GENERATE", "V<-200,10,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 1, "GENERATE", "V<200,10,-260>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 2, "GENERATE", "V<-400,10,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dbutton1", 3, "GENERATE", "V<460,10,-100>/V<0,0,0>")
be:sd("MODELCTRL", "g_dwbutton1", 0, "GENERATE", "V<-120,10,-395>/V<0,180,0>")
be:sd("MODELCTRL", "g_dwbutton1", 1, "GENERATE", "V<120,10,-395>/V<0,180,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<0,10,-210>/V<0,0,0>")
if be:FLGisOn(104) ~= 1 and be:FLGisOn(102) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 0, "GENERATE", "V<-120,0,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 1, "GENERATE", "V<-120,0,-220>/V<0,0,0>")
end
if be:FLGisOn(105) ~= 1 and be:FLGisOn(103) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 2, "GENERATE", "V<120,0,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 3, "GENERATE", "V<120,0,-180>/V<0,0,0>")
end
if be:FLGisOn(106) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 4, "GENERATE", "V<-320,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 5, "GENERATE", "V<-280,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 6, "GENERATE", "V<-320,0,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 7, "GENERATE", "V<-280,0,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 8, "GENERATE", "V<-320,0,-60>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 9, "GENERATE", "V<-280,0,-60>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 10, "GENERATE", "V<-320,0,-100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 11, "GENERATE", "V<-280,0,-100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 12, "GENERATE", "V<-320,0,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 13, "GENERATE", "V<-280,0,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 14, "GENERATE", "V<-320,0,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 15, "GENERATE", "V<-280,0,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 16, "GENERATE", "V<-320,0,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 17, "GENERATE", "V<-280,0,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 18, "GENERATE", "V<-320,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 19, "GENERATE", "V<-280,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 20, "GENERATE", "V<-240,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 21, "GENERATE", "V<-200,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 22, "GENERATE", "V<-240,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 23, "GENERATE", "V<-200,0,-300>/V<0,0,0>")
end
if be:FLGisOn(107) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 24, "GENERATE", "V<280,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 25, "GENERATE", "V<320,0,20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 26, "GENERATE", "V<280,0,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 27, "GENERATE", "V<320,0,-20>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 28, "GENERATE", "V<280,0,-60>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 29, "GENERATE", "V<320,0,-60>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 30, "GENERATE", "V<280,0,-100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 31, "GENERATE", "V<320,0,-100>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 32, "GENERATE", "V<280,0,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 33, "GENERATE", "V<320,0,-140>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 34, "GENERATE", "V<280,0,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 35, "GENERATE", "V<320,0,-180>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 36, "GENERATE", "V<280,0,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 37, "GENERATE", "V<320,0,-220>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 38, "GENERATE", "V<200,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 39, "GENERATE", "V<240,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 40, "GENERATE", "V<280,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 41, "GENERATE", "V<320,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 42, "GENERATE", "V<200,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 43, "GENERATE", "V<240,0,-300>/V<0,0,0>")
end
if be:FLGisOn(100) ~= 1 and be:FLGisOn(101) ~= 1 then
    be:sd("MODELCTRL", "g_dcap", 44, "GENERATE", "V<-160,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 45, "GENERATE", "V<-120,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 46, "GENERATE", "V<-80,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 47, "GENERATE", "V<-40,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 48, "GENERATE", "V<0,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 49, "GENERATE", "V<40,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 50, "GENERATE", "V<80,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 51, "GENERATE", "V<120,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 52, "GENERATE", "V<160,0,-260>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 53, "GENERATE", "V<-160,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 54, "GENERATE", "V<-120,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 55, "GENERATE", "V<-80,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 56, "GENERATE", "V<-40,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 57, "GENERATE", "V<0,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 58, "GENERATE", "V<40,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 59, "GENERATE", "V<80,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 60, "GENERATE", "V<120,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 61, "GENERATE", "V<160,0,-300>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 62, "GENERATE", "V<-160,0,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 63, "GENERATE", "V<-120,0,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 64, "GENERATE", "V<-80,0,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 65, "GENERATE", "V<80,0,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 66, "GENERATE", "V<120,0,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 67, "GENERATE", "V<160,0,-340>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 68, "GENERATE", "V<-160,0,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 69, "GENERATE", "V<-120,0,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 70, "GENERATE", "V<-80,0,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 71, "GENERATE", "V<80,0,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 72, "GENERATE", "V<120,0,-380>/V<0,0,0>")
    be:sd("MODELCTRL", "g_dcap", 73, "GENERATE", "V<160,0,-380>/V<0,0,0>")
end
mswk61733 = "TALKFONT02/font00/I<495>"
mswk61734 = "TALKFONT02/font00/I<496>"
mswk61735 = "TALKFONT02/font00/I<497>"
mswk61736 = "TALKFONT02/font00/I<498>"
mswk61737 = "TALKFONT02/font00/I<499>"
mswk61738 = "TALKFONT02/font00/I<500>"
mswk61739 = "TALKFONT02/font00/I<501>"
mswk61740 = "TALKFONT02/font00/I<502>"
mswk61741 = "TALKFONT02/font00/I<503>"
mswk61742 = "TALKFONT02/font00/I<504>"
mswk61743 = "TALKFONT02/font00/I<505>"
mswk61744 = "TALKFONT02/font00/I<506>"
mswk61745 = "TALKFONT02/font00/I<507>"
mswk61746 = "TALKFONT02/font00/I<508>"
mswk61747 = "TALKFONT02/font00/I<509>"
mswk61748 = "TALKFONT02/font00/I<510>"
mswk61749 = "TALKFONT02/font00/I<511>"
mswk61750 = "TALKFONT02/font00/I<512>"
mswk61751 = "TALKFONT02/font00/I<513>"
mswk61752 = "TALKFONT02/font00/I<514>"
mswk61753 = "TALKFONT02/font00/I<515>"
mswk61754 = "TALKFONT01/font00/I<516>"
mswk61755 = "TALKFONT01/font00/I<517>"
mswk61756 = "TALKFONT02/font00/I<518>"
mswk61757 = "TALKFONT02/font00/I<519>"
be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-80,10,20>/V<0,90,0>")
be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<80,10,20>/V<0,-90,0>")
be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-240,10,140>/V<0,90,0>")
be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<240,10,140>/V<0,-90,0>")
be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-240,10,-180>/V<0,45,0>")
be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<240,10,-180>/V<0,-45,0>")
be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-240,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "n_weregaru", 0, "GENERATE", "V<240,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<0,10,60>/V<0,0,0>")
be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-20,10,-100>/V<0,0,0>")
be:sd("MODELCTRL", "n_agumon", 2, "GENERATE", "V<-320,10,-60>/V<0,90,0>")
be:sd("MODELCTRL", "n_girumon", 2, "GENERATE", "V<320,10,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-80,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<80,10,-300>/V<0,0,0>")
if be:FLGisOn(104) ~= 1 then
    be:sd("MODELCTRL", "g_d1bkwall", 0, "GENERATE", "V<-120,10,-155>/V<0,0,0>/SQ_CUTRIGHT")
end
if be:FLGisOn(105) ~= 1 then
    be:sd("MODELCTRL", "g_d1bkwall", 1, "GENERATE", "V<120,10,-155>/V<0,0,0>/SQ_CUTLEFT")
end
if be:FLGisOn(106) ~= 1 then
    be:sd("MODELCTRL", "g_d1bkwall", 2, "GENERATE", "V<-255,10,-20>/V<0,90,0>/SQ_CUTRIGHT")
end
if be:FLGisOn(107) ~= 1 then
    be:sd("MODELCTRL", "g_d1bkwall", 3, "GENERATE", "V<255,10,-20>/V<0,-90,0>/SQ_CUTLEFT")
end
if be:FLGisOn(100) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_POWERON")
end
if be:FLGisOn(101) == 1 then
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 3, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT")
else
    be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_POWERON")
end
if be:FLGisOn(102) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 0, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT")
end
if be:FLGisOn(103) == 1 then
    be:sd("MODELCTRL", "g_dwbutton1", 1, "SQ_SILENTON")
    be:sd("MODELCTRL", "g_d1door", 1, "SQ_SILENTON", 1)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT")
end
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("SOUND", nil, -1, "PLAY", "QS_WARAS")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
