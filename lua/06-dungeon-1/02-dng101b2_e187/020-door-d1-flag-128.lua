be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 and be:FLGisOn(128) == 0 then
    be:sd("MODELCTRL", "g_d1door", 2, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
    be:FLGset(128, 1)
end
