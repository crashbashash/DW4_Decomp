if be:MDLgetRamNo() == 0 then
    g_r01mode = 0
    be:sd("MODELCTRL", "g_dtrailmon", 0, "SQ_HIDE")
elseif be:MDLgetRamNo() == 1 then
    g_r02mode = 0
    be:sd("MODELCTRL", "g_dtrailmon", 1, "SQ_HIDE")
elseif be:MDLgetRamNo() == 2 then
    g_r03mode = 0
    be:sd("MODELCTRL", "g_dtrailmon", 2, "SQ_HIDE")
elseif be:MDLgetRamNo() == 3 then
    g_r04mode = 0
    be:sd("MODELCTRL", "g_dtrailmon", 3, "SQ_HIDE")
end
