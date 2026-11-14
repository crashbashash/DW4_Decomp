for ramNo = 0, 3 do
    be:sd("MODELCTRL", "g_d4door", ramNo, "SQ_SWON", 30)
end
be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 45)
be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
be:sd("HITLANDMODEL", "doorwall03", 0, "OFFHIT", 45)
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
be:FLGset(212, 1)
