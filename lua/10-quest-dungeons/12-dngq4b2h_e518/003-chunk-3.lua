if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_darrowshotter", 1, "SQ_POWERON2")
    be:sd("MODELCTRL", "g_darrowshotter", 2, "SQ_POWERON2")
    be:sd("MODELCTRL", "g_darrowshotter", 5, "SQ_POWERON2")
else
    be:sd("MODELCTRL", "g_darrowshotter", 1, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_darrowshotter", 2, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_darrowshotter", 5, "SQ_POWEROF")
end
