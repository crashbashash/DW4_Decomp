be:MDLsetDMGTurn(0)
if be:FLGisOn(136) ~= 1 then
    be:sd("MODELCTRL", "g_d3door", 1, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
    be:FLGset(136, 1)
end
