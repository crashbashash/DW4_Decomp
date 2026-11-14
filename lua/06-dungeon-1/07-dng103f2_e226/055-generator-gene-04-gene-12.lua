if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    be:sd("MODELCTRL", "g_darrowshotter", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_darrowshotter", 3, "SQ_POWERON")
    be:sd("MODELCTRL", "g_darrowshotter", 2, "SQ_POWERON", 25)
else
    be:sd("MODELCTRL", "g_darrowshotter", 1, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_darrowshotter", 3, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_darrowshotter", 2, "SQ_POWEROF", 25)
end
