if be:MATisPlayer() == 1 and be:FLGisOn(337) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 0, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 0, "SQ_ATCK1", 15)
    be:FLGset(337, 1)
end
