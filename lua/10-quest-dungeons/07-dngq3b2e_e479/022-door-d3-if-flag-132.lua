if be:FLGisOn(121) ~= 1 then
    if be:MATisPlayer() == 1 then
        if be:FLGisOn(132) ~= 1 then
            be:sd("GENERATER", nil, -1, "START", "GENE-11", 1)
        end
    else
        be:sd("GENERATER", nil, -1, "STOP", "GENE-11", 1)
    end
elseif be:MATisPlayer() == 1 then
    if be:FLGisOn(133) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 7, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall08", 0, "ONHIT")
        be:sd("GENERATER", nil, -1, "START", "GENE-12", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-12", 1)
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-13")
end
