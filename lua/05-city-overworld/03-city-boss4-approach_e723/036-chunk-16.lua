if be:MATisAllPlayer() == 1 and g_IFLG11 ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-52")
    be:sd("MODELCTRL", "g_mvbox2z04", 4, "SQ_SWOF1")
    be:sd("HITLANDMODEL", "hitmvbox2z044", 0, "ONHIT")
    g_IFLG11 = 1
end
