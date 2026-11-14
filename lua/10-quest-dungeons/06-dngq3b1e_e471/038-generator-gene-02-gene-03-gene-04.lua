local local_0
if be:FLGisOn(121) == 1 then
    if be:MATisPlayer() == 1 then
        for ramNo = 0, 4 do
            be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON2")
        end
    end
    for ramNo = 0, 4 do
        be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/OFF")
    end
end
if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
end
