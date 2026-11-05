be:sd("MODELCTRL", "f_devl3", 0, "SETLABEL", "SQ_FLYMV/LEFT")
be:sd("MODELCTRL", "f_devl3", 0, "MOVETRANS", be:MDLgetPosStr(0.5, 0, 0) .. "/" .. be:MDLgetRotStr(0, 0, 0))
be:sd("MODELCTRL", "f_devl3", 0, "SQ_WAIT1")
