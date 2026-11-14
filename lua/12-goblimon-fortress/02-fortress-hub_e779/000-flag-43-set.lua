if be:FLGisOn(43) == 0 then
    be:sd("MODELCTRL", "g_breakinggatez05", 0, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitbreakinggatez050", 0, "OFFHIT", 75)
    be:sd("MODELCTRL", "g_movepass02z05", 0, "SQ_SWON")
    be:sd("MODELCTRL", "g_movepass02z05", 1, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitmovepass02z05", 0, "OFFHIT", 75)
    be:FLGset(43, 1)
end
