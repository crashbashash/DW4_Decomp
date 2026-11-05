for local_0 = 7, 9 do
    be:sd("MODELCTRL", "g_d4door", local_0, "SQ_SWON", 30)
end
be:sd("HITLANDMODEL", "doorwall08", 0, "OFFHIT", 45)
be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
be:sd("HITLANDMODEL", "doorwall10", 0, "OFFHIT", 45)
be:FLGset(220, 1)
