local local_0
be:sd("MODELCTRL", "g_d4door", 3, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
be:sd("MODELCTRL", "g_d4door", 4, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall05", 0, "OFFHIT", 45)
be:FLGset(141, 1)
for ramNo = 38, 41 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG", 30)
end
