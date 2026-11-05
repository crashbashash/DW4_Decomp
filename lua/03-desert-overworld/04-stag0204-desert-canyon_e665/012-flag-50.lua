if be:FLGisOn(49) == 1 and be:FLGisOn(50) == 0 then
    be:sd("MODELCTRL", "g_scorpiongatez02", 0, "SQ_SWON")
    be:sd("MODELCTRL", "g_scorpiongatez02", 1, "SQ_SWON")
    be:sd("HITLANDMODEL", "hitscorpiongatez020", 0, "OFFHIT")
    be:sd("HITLANDMODEL", "hitscorpiongatez021", 0, "OFFHIT")
    be:FLGset(50, 1)
end
