local ramNo = be:MDLgetRamNo()
if be:MDLisCallName("stp") == 1 then
    be:sd("MODELCTRL", "g_dtrailmon", ramNo, "SQ_STOP")
elseif be:MDLisCallName("sta") == 1 then
    be:sd("MODELCTRL", "g_dtrailmon", ramNo, "SQ_B3TRIL01")
end
