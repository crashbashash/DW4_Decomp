be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(164) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    be:FLGset(164, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(165) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("MODELCTRL", "g_d2door", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:FLGset(165, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(166) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    if be:FLGisOn(167) == 1 then
        be:sd("MODELCTRL", "g_d2door", 10, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
    end
    be:FLGset(166, 1)
elseif be:MDLgetRamNo() == 3 and be:FLGisOn(167) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    if be:FLGisOn(166) == 1 then
        be:sd("MODELCTRL", "g_d2door", 10, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
    end
    be:FLGset(167, 1)
elseif be:MDLgetRamNo() == 4 and be:FLGisOn(168) == 0 then
    be:sd("MODELCTRL", local_1, local_0, "SQ_WAIT", 0)
    be:MDLsetSeq("SQ_SWON")
    be:sd("GENERATER", nil, -1, "START", "GENE-11")
    be:FLGset(168, 1)
end
