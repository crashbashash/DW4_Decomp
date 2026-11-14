if be:MATisPlayer() == 1 and be:FLGisOn(348) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 11, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 11, "SQ_ATCK1", 15)
    be:FLGset(348, 1)
end
