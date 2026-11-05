if be:MATisAllPlayer() == 1 and be:FLGisOn(49) == 0 and g_IFLG05 ~= 1 then
    be:sd("MODELCTRL", "g_lightningz02", 0, "GENERATE", "V<320,110,-140>/V<0,0,0>", 5)
    be:sd("MODELCTRL", "g_lightningz02", 0, "SQ_SWON", 35)
    g_IFLG05 = 1
else
end
