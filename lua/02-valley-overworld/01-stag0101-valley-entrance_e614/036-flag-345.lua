if be:MATisPlayer() == 1 and be:FLGisOn(345) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 8, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 8, "SQ_ATCK1", 15)
    be:FLGset(345, 1)
end
