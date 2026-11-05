if be:MATisAllPlayer() == 1 and g_IFLG02 ~= 1 then
    if be:FLGisOn(63) == 0 then
        be:sd("GENERATER", nil, -1, "START", "GENE-65")
        be:sd("GENERATER", nil, -1, "START", "GENE-66")
        g_IFLG02 = 1
    else
        be:sd("GENERATER", nil, -1, "START", "GENE-65")
        be:sd("GENERATER", nil, -1, "START", "GENE-66")
        g_IFLG02 = 1
    end
end
