be:sd("MODELCTRL", "g_security", 0, "SQ_POWERON", 30)
g_security = 1
be:sd("MODELCTRL", "g_d1door", 1, "SQ_SWON", 30)
be:sd("HITLANDMODEL", "doorwall02", 0, "OFFHIT", 45)
be:FLGset(113, 1)
