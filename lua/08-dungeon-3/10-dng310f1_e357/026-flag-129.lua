be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(129, 1)
elseif be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 9, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
    be:FLGset(130, 1)
end
