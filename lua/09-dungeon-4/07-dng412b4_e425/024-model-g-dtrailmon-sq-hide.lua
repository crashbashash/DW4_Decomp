if be:MDLgetRamNo() == 0 then
    g_r01mode = 0
    be:sd("MODELCTRL", "g_dtrailmon", 0, "SQ_HIDE")
elseif be:MDLgetRamNo() == 1 then
    g_r02mode = 0
    be:sd("MODELCTRL", "g_dtrailmon", 1, "SQ_HIDE")
end
