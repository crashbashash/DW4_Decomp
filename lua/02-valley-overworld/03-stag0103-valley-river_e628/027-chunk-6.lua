if g_IFLG10 == 0 then
    be:sd("MODELCTRL", "g_factgatez06", 0, "SQ_DEAD02")
    be:sd("MODELCTRL", "g_facteyez06", 0, "SQ_DEAD02")
    be:sd("MODELCTRL", "g_facteyez06", 1, "SQ_DEAD02")
    be:sd("CAMERA", nil, -1, "SHAKE", "15/F<0.2>/F<3.0>/F<60.0>,10")
    g_IFLG10 = 1
end
