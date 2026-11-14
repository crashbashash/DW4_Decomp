if be:MDLisCallName("stp") == 1 then
    be:sd("MODELCTRL", "g_dtrailmon", 1, "SQ_STOP")
elseif be:MDLisCallName("sta") == 1 then
    be:sd("MODELCTRL", "g_dtrailmon", 1, "SQ_B4TRIL01")
end
