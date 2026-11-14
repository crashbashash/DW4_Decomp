be:MDLsetDMGTurn(0)
if be:MDLgetRamNo() == 0 then
    be:sd("MODELCTRL", "g_d4door", 6, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall07", 0, "OFFHIT", 45)
    be:FLGset(248, 1)
end
