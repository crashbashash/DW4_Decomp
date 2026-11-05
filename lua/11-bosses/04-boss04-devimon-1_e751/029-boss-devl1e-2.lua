if be:MDLisCallName("at0") == 1 then
    g_act = 3
    be:sd("MODELCTRL", "f_devl1e", 0, "MOVETRANS", be:MDLgetPosStr(0, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
    be:sd("MODELCTRL", "f_devl1e", 0, "SQ_WAIT")
elseif be:MDLisCallName("at1") == 1 then
    be:sd("MODELCTRL", "f_devl1e", 0, "SQ_START")
elseif be:MDLisCallName("wai") == 1 then
    g_act = 1
    be:sd("MODELCTRL", "f_devl1e", 0, "MOVETRANS", "V<0.0,10.0,0.0>/V<0.0,0.0,0.0>")
    be:sd("MODELCTRL", "f_devl1e", 0, "SQ_WAIT")
end
