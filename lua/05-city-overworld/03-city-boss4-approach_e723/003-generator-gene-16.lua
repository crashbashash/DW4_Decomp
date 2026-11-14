if be:MATisAllPlayer() == 1 and g_IFLG07 ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-16")
    be:sd("MODELCTRL", "g_mvbox2z04", 0, "SQ_SWOF1")
    be:sd("HITLANDMODEL", "hitmvbox2z040", 0, "ONHIT")
    g_IFLG07 = 1
end
