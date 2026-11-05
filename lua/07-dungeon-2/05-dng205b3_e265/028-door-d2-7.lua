be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(201) == 0 then
    be:sd("MODELCTRL", "g_d2door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(201, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(202) == 0 then
    be:sd("MODELCTRL", "g_d2door", 13, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall14", 0, "OFFHIT", 45)
    be:FLGset(202, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(203) == 0 then
    be:sd("GENERATER", nil, -1, "START", "GENE-10")
    be:FLGset(203, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(204) == 0 then
    be:sd("MODELCTRL", "g_d2door", 16, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d2door", 17, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall18", 0, "OFFHIT", 45)
    be:FLGset(204, 1)
elseif be:MDLgetRamNo() == 4 and be:FLGisOn(205) == 0 then
    be:sd("MODELCTRL", "g_d2door", 18, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall19", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d2door", 19, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall20", 0, "OFFHIT", 45)
    be:FLGset(205, 1)
end
