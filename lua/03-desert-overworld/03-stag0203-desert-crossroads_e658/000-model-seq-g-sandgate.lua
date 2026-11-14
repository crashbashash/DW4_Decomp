be:MDLsetDMGTurn(0)
be:MDLsetSeq("SQ_SWON")
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_sandgate", 0, "SQ_SWON", 120)
    g_IFLG01 = 1
else
    be:sd("MODELCTRL", "g_sandgate", 1, "SQ_SWON", 120)
    g_IFLG01 = 1
end
