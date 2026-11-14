if be:MATisAllPlayer() == 1 and g_IFLG10 ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-43")
    be:sd("MODELCTRL", "g_mvbox2z04", 3, "SQ_SWOF2")
    be:sd("HITLANDMODEL", "hitmvbox2z043", 0, "ONHIT")
    g_IFLG10 = 1
end
