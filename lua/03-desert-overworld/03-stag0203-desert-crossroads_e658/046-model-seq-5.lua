be:MDLsetDMGTurn(0)
be:MDLsetSeq("SQ_SWON")
g_IFLG01 = 2
be:sd("MODELCTRL", "j_panels0203", 0, "SQ_RIGHT")
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_turnstra", 0, "SQ_SWOF")
elseif be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_turnstra", 1, "SQ_SWOF")
elseif be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_turnstra", 2, "SQ_SWOF")
elseif be:MDLgetRamNo() == 3 then
    be:sd("MODELCTRL", "g_turnstra", 3, "SQ_SWOF")
elseif be:MDLgetRamNo() == 4 then
    be:sd("MODELCTRL", "g_turnstra", 4, "SQ_SWOF")
elseif be:MDLgetRamNo() == 5 then
    be:sd("MODELCTRL", "g_turnstra", 5, "SQ_SWOF")
end
