be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(167) == 0 then
    be:sd("MODELCTRL", "g_d1door", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    be:FLGset(167, 1)
elseif be:MDLgetRamNo() == 1 and be:FLGisOn(168) == 0 then
    be:sd("GENERATER", nil, -1, "START", "GENE-10", 30)
    be:sd("MODELCTRL", "g_d1door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    be:FLGset(168, 1)
elseif be:MDLgetRamNo() == 2 and be:FLGisOn(169) == 0 then
    be:sd("GENERATER", nil, -1, "START", "GENE-11", 30)
    be:FLGset(169, 1)
end
if g_dmgfloor45 ~= 1 and be:FLGisOn(168) == 1 and be:FLGisOn(169) == 1 then
    be:sd("MODELCTRL", "g_ddamagefloor", 3, "SQ_SWOF")
    be:sd("MODELCTRL", "g_ddamagefloor", 4, "SQ_SWOF")
    g_dmgfloor45 = 1
end
