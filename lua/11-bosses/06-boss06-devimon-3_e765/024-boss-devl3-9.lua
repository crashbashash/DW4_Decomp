if g_FBSwitch == 0 then
    be:MDLsetSeq("SQ_LEFTMVBKR")
    be:sd("MODELCTRL", "f_devl3", 0, "MOVETRANS", be:MDLgetPosStr(0.7, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
elseif g_FBSwitch == 1 then
    be:MDLsetSeq("SQ_LEFTMVFRR")
    be:sd("MODELCTRL", "f_devl3", 0, "MOVETRANS", be:MDLgetPosStr(0.7, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
elseif g_FBSwitch == 3 then
    be:MDLsetSeq("SQ_BLEFTMVR")
    be:sd("MODELCTRL", "f_devl3", 0, "MOVETRANS", be:MDLgetPosStr(0.7, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
end
