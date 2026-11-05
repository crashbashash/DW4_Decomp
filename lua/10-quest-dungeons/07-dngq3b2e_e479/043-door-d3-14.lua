if be:MATisAllPlayer() == 1 and be:FLGisOn(130) ~= 1 then
    be:sd("MODELCTRL", "g_d3door", 6, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall07", 0, "ONHIT")
    be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
end
