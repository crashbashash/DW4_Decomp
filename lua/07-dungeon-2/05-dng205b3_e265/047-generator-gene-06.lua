if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-07")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-12")
    if be:FLGisOn(180) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-06", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-06", 1)
end
if be:MATisAllPlayer() == 1 then
    be:sd("HITLANDMODEL", "safewall0", 0, "OFFHIT")
else
    be:sd("HITLANDMODEL", "safewall0", 0, "ONHIT")
end
