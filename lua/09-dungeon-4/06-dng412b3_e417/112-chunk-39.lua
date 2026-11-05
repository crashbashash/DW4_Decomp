if be:MDLisCallName("stp") == 1 then
    be:sd("MODELCTRL", "g_dtrailmon", local_0, "SQ_STOP")
elseif be:MDLisCallName("sta") == 1 then
    be:sd("MODELCTRL", "g_dtrailmon", local_0, "SQ_B3TRIL01")
end
