if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(138) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 0, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall01", 0, "ONHIT")
        be:FLGset(138, 1)
    end
    if be:FLGisOn(100) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01")
    end
end
be:MATsetRun(0)
