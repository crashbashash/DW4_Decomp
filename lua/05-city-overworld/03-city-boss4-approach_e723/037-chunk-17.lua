if be:MATisAllPlayer() == 1 and g_IFLG12 ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-61")
    be:sd("MODELCTRL", "g_mvbox2z04", 5, "SQ_SWOF2")
    be:sd("HITLANDMODEL", "hitmvbox2z045", 0, "ONHIT")
    g_IFLG12 = 1
end
