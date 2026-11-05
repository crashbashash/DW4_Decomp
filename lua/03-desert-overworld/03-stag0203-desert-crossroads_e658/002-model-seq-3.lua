be:MDLsetDMGTurn(0)
be:MDLsetSeq("SQ_SWON")
g_IFLG01 = 1
be:sd("MODELCTRL", "j_panels0203", 0, "SQ_STRA")
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_turnright", 0, "SQ_SWOF")
elseif be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_turnright", 1, "SQ_SWOF")
elseif be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_turnright", 2, "SQ_SWOF")
elseif be:MDLgetRamNo() == 3 then
    be:sd("MODELCTRL", "g_turnright", 3, "SQ_SWOF")
elseif be:MDLgetRamNo() == 4 then
    be:sd("MODELCTRL", "g_turnright", 4, "SQ_SWOF")
elseif be:MDLgetRamNo() == 5 then
    be:sd("MODELCTRL", "g_turnright", 5, "SQ_SWOF")
elseif be:MDLgetRamNo() == 6 then
    be:sd("MODELCTRL", "g_turnleft", 0, "SQ_SWOF")
elseif be:MDLgetRamNo() == 7 then
    be:sd("MODELCTRL", "g_turnleft", 1, "SQ_SWOF")
elseif be:MDLgetRamNo() == 8 then
    be:sd("MODELCTRL", "g_turnleft", 2, "SQ_SWOF")
end
