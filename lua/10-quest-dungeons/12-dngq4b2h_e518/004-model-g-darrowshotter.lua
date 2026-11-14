if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_darrowshotter", 6, "SQ_POWERON2")
else
    be:sd("MODELCTRL", "g_darrowshotter", 6, "SQ_POWEROF")
end
