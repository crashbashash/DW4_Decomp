if be:MDLisCallName("left") == 1 then
    be:sd("MODELCTRL", "f_devl32", 0, "MOVETRANS", be:MDLgetPosStr(0, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
    be:sd("MODELCTRL", "f_devl32", 0, "SQ_BACK")
elseif be:MDLisCallName("right") == 1 then
    be:sd("MODELCTRL", "f_devl32", 0, "MOVETRANS", be:MDLgetPosStr(0, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
    be:sd("MODELCTRL", "f_devl32", 0, "SQ_BACK")
end
