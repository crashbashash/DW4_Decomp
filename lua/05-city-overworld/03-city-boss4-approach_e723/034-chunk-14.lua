if be:MATisAllPlayer() == 1 and g_IFLG09 ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-34")
    be:sd("MODELCTRL", "g_mvbox2z04", 2, "SQ_SWOF1")
    be:sd("HITLANDMODEL", "hitmvbox2z042", 0, "ONHIT")
    g_IFLG09 = 1
end
