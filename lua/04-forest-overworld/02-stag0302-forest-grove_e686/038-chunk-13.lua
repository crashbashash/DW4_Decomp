if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_cannon01", 2, "SQ_POWERON")
    be:sd("MODELCTRL", "g_cannon01", 3, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_cannon01", 2, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_cannon01", 3, "SQ_POWEROF")
end
