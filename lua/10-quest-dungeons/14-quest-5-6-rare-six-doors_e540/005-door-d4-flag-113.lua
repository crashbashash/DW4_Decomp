local local_0
be:sd("MODELCTRL", "g_d4door", 3, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
be:sd("GENERATER", nil, -1, "START", "GENE-09")
be:FLGset(113, 1)
for ramNo = 0, 4 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
be:FLGset(104, 1)
