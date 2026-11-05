if be:MATisPlayer() == 1 and be:FLGisOn(342) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 5, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 5, "SQ_ATCK1", 15)
    be:FLGset(342, 1)
end
