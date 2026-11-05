g_eneplug = g_eneplug + 1
if be:FLGisOn(49) == 0 and g_eneplug == 36 then
    be:sd("MODELCTRL", "g_enegeneratorz02", 0, "SQ_SWON")
    be:FLGset(49, 1)
end
