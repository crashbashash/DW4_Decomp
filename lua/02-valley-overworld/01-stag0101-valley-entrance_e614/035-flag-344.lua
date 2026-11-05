if be:MATisPlayer() == 1 and be:FLGisOn(344) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 7, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 7, "SQ_ATCK1", 15)
    be:FLGset(344, 1)
end
