if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-06")
    if be:FLGisOn(128) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-09", 1)
    else
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-09", 1)
if be:MATisAllPlayer() == 1 then
    be:sd("HITLANDMODEL", "safewall0", 0, "OFFHIT")
else
    be:sd("HITLANDMODEL", "safewall0", 0, "ONHIT")
end
