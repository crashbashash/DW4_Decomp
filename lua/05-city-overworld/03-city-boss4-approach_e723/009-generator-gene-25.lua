if be:MATisAllPlayer() == 1 and g_IFLG08 ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-25")
    be:sd("MODELCTRL", "g_mvbox2z04", 1, "SQ_SWOF2")
    be:sd("HITLANDMODEL", "hitmvbox2z041", 0, "ONHIT")
    g_IFLG08 = 1
end
