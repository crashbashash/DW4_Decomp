if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    if be:FLGisOn(168) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-03", 1)
    end
end
if be:MATisAllPlayer() == 1 and be:FLGisOn(244) ~= 1 then
    be:sd("MODELCTRL", "g_d3door", 2, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall03", 0, "ONHIT")
    be:FLGset(244, 1)
end
