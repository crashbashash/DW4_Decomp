if be:FLGisOn(63) == 0 then
    if g_IFLG07 ~= 1 then
        g_IFLG07 = 1
    elseif g_IFLG07 == 1 then
        be:sd("MODELCTRL", "g_lift01z02", 2, "SQ_SWON", 60)
        be:sd("HITLANDMODEL", "hitlift012", 0, "OFFHIT", 180)
    else
    end
end
if be:FLGisOn(63) == 1 then
    be:sd("MODELCTRL", "g_lift03z02", 0, "SQ_SWON", 30)
    be:sd("MODELCTRL", "g_lift03az02", 0, "SQ_SWON")
    be:sd("MODELCTRL", "g_lift03bz02", 0, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "hitlift030", 0, "OFFHIT", 150)
end
