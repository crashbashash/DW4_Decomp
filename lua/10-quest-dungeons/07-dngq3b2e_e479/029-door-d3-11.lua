be:sd("MODELCTRL", "g_d3door", 4, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
be:FLGset(129, 1)
if be:SYSgetDifficulty() > 0 and be:FLGisOn(121) == 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-13")
end
