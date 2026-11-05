be:sd("MODELCTRL", "g_d4door", 3, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall04", 0, "OFFHIT", 45)
be:sd("GENERATER", nil, -1, "START", "GENE-09")
be:FLGset(113, 1)
for local_1 = 0, 4 do
    be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
end
be:FLGset(104, 1)
