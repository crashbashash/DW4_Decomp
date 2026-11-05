be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_dtdoor", 0, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
    be:FLGset(180, 1)
elseif be:MDLgetRamNo() == 1 then
    be:sd("MODELCTRL", "g_dtdoor", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:FLGset(181, 1)
elseif be:MDLgetRamNo() == 2 then
    be:sd("MODELCTRL", "g_dtdoor", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(182, 1)
elseif be:MDLgetRamNo() == 3 then
    be:sd("MODELCTRL", "g_dtdoor", 3, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
    be:FLGset(183, 1)
elseif be:MDLgetRamNo() == 4 then
    be:sd("MODELCTRL", "g_dbarrierw2", 2, "SQ_POWEROF", 30)
    be:sd("MODELCTRL", "g_dbarrierw3", 2, "SQ_POWEROF", 30)
    be:sd("MODELCTRL", "g_dbarrierp", 4, "SQ_POWEROF", 30)
    be:sd("MODELCTRL", "g_dbarrierp", 5, "SQ_POWEROF", 30)
    be:sd("HITLANDMODEL", "barrierwall03", 0, "OFFHIT", 30)
    be:FLGset(184, 1)
elseif be:MDLgetRamNo() == 5 then
    be:sd("MODELCTRL", "g_dtdoor", 4, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
    be:FLGset(185, 1)
end
