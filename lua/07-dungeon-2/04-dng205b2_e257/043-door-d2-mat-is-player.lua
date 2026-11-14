if be:MATisPlayer() == 1 and g_door06 ~= 1 then
    be:sd("MODELCTRL", "g_d2door", 5, "SQ_SWON")
    be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 15)
    g_door06 = 1
end
