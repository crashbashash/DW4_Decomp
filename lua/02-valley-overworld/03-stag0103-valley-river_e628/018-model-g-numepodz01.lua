if be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "g_numepodz01", 3, "SQ_POWERON")
    be:sd("MODELCTRL", "g_numepodz01", 4, "SQ_POWERON")
    be:sd("MODELCTRL", "g_numepodz01", 5, "SQ_POWERON")
    be:sd("MODELCTRL", "g_numepodz01", 6, "SQ_POWERON")
    be:sd("MODELCTRL", "g_numepodz01", 7, "SQ_POWERON")
else
    be:sd("MODELCTRL", "g_numepodz01", 3, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_numepodz01", 4, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_numepodz01", 5, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_numepodz01", 6, "SQ_POWEROF")
    be:sd("MODELCTRL", "g_numepodz01", 7, "SQ_POWEROF")
end
