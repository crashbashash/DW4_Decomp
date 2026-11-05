if be:FLGisOn(148) == 1 then
    if be:MATisPlayer() == 1 then
        be:sd("MODELCTRL", "g_darrowshotter", 0, "SQ_POWERON")
    else
        be:sd("MODELCTRL", "g_darrowshotter", 0, "SQ_POWEROF")
    end
end
