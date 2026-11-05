if be:MDLgetRamNo() == 0 and g_IFLG10 ~= 1 then
    be:sd("GENERATER", nil, -1, "STOP", "GENE-47")
    g_IFLG10 = 1
    be:FLGset(499, 1)
end
if be:MDLgetRamNo() == 1 and g_IFLG11 ~= 1 then
    be:sd("GENERATER", nil, -1, "STOP", "GENE-29")
    g_IFLG11 = 1
    be:FLGset(500, 1)
end
