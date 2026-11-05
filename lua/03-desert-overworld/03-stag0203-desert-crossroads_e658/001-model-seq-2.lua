be:MDLsetDMGTurn(0)
be:MDLsetSeq("SQ_SWON")
g_IFLG01 = 2
be:sd("MODELCTRL", "j_panels0203", 0, "SQ_LEFT")
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_turnstra", 6, "SQ_SWOF")
elseif be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_turnstra", 7, "SQ_SWOF")
elseif be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_turnstra", 8, "SQ_SWOF")
end
