if be:FLGisOn(383) == 0 and be:FLGisOn(20) == 0 and IFLG01 ~= 1 and be:MATisPlayer() == 1 then
    be:sd("MODELCTRL", "n_leomon", 0, "SQ_DEMOWAIT")
    be:sd("GENERATER", nil, -1, "START", "GENE-00")
    g_IFLG01 = 1
else
end
