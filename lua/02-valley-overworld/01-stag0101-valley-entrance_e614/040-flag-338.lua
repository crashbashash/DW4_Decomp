if be:MATisPlayer() == 1 and be:FLGisOn(338) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 1, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 1, "SQ_ATCK1", 15)
    be:FLGset(338, 1)
end
