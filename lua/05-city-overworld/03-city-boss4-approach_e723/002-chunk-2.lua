be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_mvbox2z04", 0, "SQ_SWON1")
    be:sd("HITLANDMODEL", "hitmvbox2z040", 0, "OFFHIT", 30)
    be:sd("MODELCTRL", "g_sbutton", 0, "SQ_ONLOOP")
end
if be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_mvbox2z04", 1, "SQ_SWON2")
    be:sd("HITLANDMODEL", "hitmvbox2z041", 0, "OFFHIT", 30)
    be:sd("MODELCTRL", "g_sbutton", 1, "SQ_ONLOOP")
end
if be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_mvbox2z04", 2, "SQ_SWON1")
    be:sd("HITLANDMODEL", "hitmvbox2z042", 0, "OFFHIT", 30)
    be:sd("MODELCTRL", "g_sbutton", 2, "SQ_ONLOOP")
end
if be:MDLgetRamNo() == 3 then
    be:sd("MODELCTRL", "g_mvbox2z04", 3, "SQ_SWON2")
    be:sd("HITLANDMODEL", "hitmvbox2z043", 0, "OFFHIT", 30)
    be:sd("MODELCTRL", "g_sbutton", 3, "SQ_ONLOOP")
end
if be:MDLgetRamNo() == 4 then
    be:sd("MODELCTRL", "g_mvbox2z04", 4, "SQ_SWON1")
    be:sd("HITLANDMODEL", "hitmvbox2z044", 0, "OFFHIT", 30)
    be:sd("MODELCTRL", "g_sbutton", 4, "SQ_ONLOOP")
end
if be:MDLgetRamNo() == 5 then
    be:sd("MODELCTRL", "g_mvbox2z04", 5, "SQ_SWON2")
    be:sd("HITLANDMODEL", "hitmvbox2z045", 0, "OFFHIT", 30)
    be:sd("MODELCTRL", "g_sbutton", 5, "SQ_ONLOOP")
end
