local local_0
funcStartLayerSet()
if be:SYSgetLightMode() ~= 0 then
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape1/V<0.0,0.0,0.0>/V<0.8,0.8,1.0>/V<0.8,0.8,1.0>")
    be:sd("LIGHTCTRL", nil, -1, "SETCOLOR", "Z0101Light0Shape2/V<0.18,0.26,0.08>/V<0.0,0.0,0.0>/V<0.0,0.0,0.0>")
end
funcPlayerSet()
be:sd("PLAYER", nil, -1, "SQ_DEMOWAIT")
local local_1 = 905
if be:COUNTERget(2) ~= local_1 then
    be:COUNTERset(2, local_1)
    for flagNo = 100, 299 do
        be:FLGset(flagNo, 0)
    end
    g_intro = 1
end
be:sd("MODELCTRL", "g_dreturngate", 0, "GENERATE", "V<0,10,-210>/V<0,0,0>")
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
be:sd("MODELCTRL", "n_agumon", 0, "GENERATE", "V<-80,10,20>/V<0,90,0>")
be:sd("MODELCTRL", "n_girumon", 0, "GENERATE", "V<80,10,20>/V<0,-90,0>")
be:sd("MODELCTRL", "n_dorumon", 0, "GENERATE", "V<-240,10,140>/V<0,90,0>")
be:sd("MODELCTRL", "n_vmon", 0, "GENERATE", "V<240,10,140>/V<0,-90,0>")
be:sd("MODELCTRL", "n_girumon", 1, "GENERATE", "V<-240,10,-180>/V<0,45,0>")
be:sd("MODELCTRL", "n_agumon", 1, "GENERATE", "V<240,10,-180>/V<0,-45,0>")
be:sd("MODELCTRL", "n_digilff", 0, "GENERATE", "V<0,10,60>/V<0,0,0>")
be:sd("MODELCTRL", "n_digilff", 1, "GENERATE", "V<-20,10,-100>/V<0,0,0>")
be:sd("MODELCTRL", "n_prmame", 0, "GENERATE", "V<-240,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "n_weregaru", 0, "GENERATE", "V<240,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "n_bwargrey", 0, "GENERATE", "V<-320,10,100>/V<0,-90,0>")
be:sd("MODELCTRL", "n_prmame", 1, "GENERATE", "V<560,10,-100>/V<0,90,0>")
be:sd("MODELCTRL", "n_agumon", 2, "GENERATE", "V<-320,10,-60>/V<0,90,0>")
be:sd("MODELCTRL", "n_girumon", 2, "GENERATE", "V<320,10,-60>/V<0,-90,0>")
be:sd("MODELCTRL", "n_dorumon", 1, "GENERATE", "V<-80,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "n_vmon", 1, "GENERATE", "V<80,10,-300>/V<0,0,0>")
be:sd("MODELCTRL", "n_dorumon", 2, "GENERATE", "V<320,10,100>/V<0,90,0>")
be:sd("MODELCTRL", "n_vmon", 2, "GENERATE", "V<-400,10,-380>/V<0,0,0>")
be:sd("MODELCTRL", "g_dreturngate", 0, "SQ_POWERON")
be:sd("SOUND", nil, -1, "PLAY", "QS_WARAS")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
funcPlayerStatusGenerate()
