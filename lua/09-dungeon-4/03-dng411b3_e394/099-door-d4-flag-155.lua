local local_0
be:sd("MODELCTRL", "g_d4door", 15, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall16", 0, "OFFHIT", 45)
be:sd("MODELCTRL", "g_d4door", 16, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall17", 0, "OFFHIT", 45)
be:FLGset(155, 1)
for ramNo = 42, 49 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG", 30)
end
