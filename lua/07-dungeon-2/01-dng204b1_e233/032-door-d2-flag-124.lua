be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(122) == 0 then
    if be:FLGisOn(123) == 1 then
        be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(122, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(123) == 0 then
    if be:FLGisOn(122) == 1 then
        be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    end
    be:FLGset(123, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(124) == 0 then
    be:sd("GENERATER", nil, -1, "START", "GENE-04")
    if be:FLGisOn(125) == 1 then
        be:sd("MODELCTRL", "g_d2door", 3, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    end
    be:FLGset(124, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(125) == 0 then
    be:sd("GENERATER", nil, -1, "START", "GENE-06")
    if be:FLGisOn(124) == 1 then
        be:sd("MODELCTRL", "g_d2door", 3, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    end
    be:FLGset(125, 1)
end
