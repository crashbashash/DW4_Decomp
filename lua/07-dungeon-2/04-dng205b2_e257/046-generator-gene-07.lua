if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("MODELCTRL", "g_darrowshotter", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_darrowshotter", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_darrowshotter", 2, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_darrowshotter", 3, "SQ_POWEROF")
end
