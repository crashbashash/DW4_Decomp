if be:MATisPlayer() == 1 and be:FLGisOn(346) == 0 then
    be:sd("MODELCTRL", "g_rockdownz01", 9, "SQ_POWERON")
    be:sd("MODELCTRL", "g_rockdownz01", 9, "SQ_ATCK1", 15)
    be:FLGset(346, 1)
end
