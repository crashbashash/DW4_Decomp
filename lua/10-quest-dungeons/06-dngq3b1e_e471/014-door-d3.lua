if be:MDLgetRamNo() == 0 and be:FLGisOn(114) ~= 1 then
    be:FLGset(114, 1)
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(115) ~= 1 then
    be:FLGset(115, 1)
    be:sd("MODELCTRL", "g_d3door", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(116) ~= 1 then
    be:FLGset(116, 1)
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
end
if be:SYSgetDifficulty() == 2 then
    if be:MDLgetRamNo() == 3 and be:FLGisOn(117) ~= 1 and be:FLGisOn(121) == 1 then
        be:FLGset(117, 1)
        be:sd("MODELCTRL", "g_d3door", 8, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
        be:sd("MODELCTRL", "g_d3door", 9, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    elseif be:MDLgetRamNo() == 4 and be:FLGisOn(118) ~= 1 then
        be:FLGset(118, 1)
        be:sd("MODELCTRL", "g_d3door", 10, "SQ_SWOF", 30)
        be:sd("HITLANDMODEL", "doorwall11", 0, "ONHIT", 45)
    end
end
