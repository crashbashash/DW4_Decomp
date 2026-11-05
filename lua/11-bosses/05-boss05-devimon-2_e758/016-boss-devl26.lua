if not g_devl26 then
    be:sd("MODELCTRL", "f_devl26", 0, "SQ_SCALE0102")
    g_devl26 = 0
elseif g_devl26 == 0 then
    be:sd("MODELCTRL", "f_devl26", 0, "SQ_SCALE0203")
    g_devl26 = 1
elseif g_devl26 == 1 then
    be:sd("MODELCTRL", "f_devl26", 0, "SQ_EXIT")
end
