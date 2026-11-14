if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_darrowshotter", 1, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_darrowshotter", 1, "SQ_POWEROF")
end
