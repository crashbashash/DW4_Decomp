if be:MATisPlayer() == 1 then
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-01")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-03")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-04")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-09")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-10")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-11")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-15")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-21")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-22")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-23")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-24")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-25")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-26")
    if be:FLGisOn(164) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
    end
else
    be:sd("GENERATER", nil, -1, "STOP", "GENE-08", 1)
end
