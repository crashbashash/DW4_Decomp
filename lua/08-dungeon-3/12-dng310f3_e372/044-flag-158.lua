if be:FLGisOn(159) == 1 then
    be:sd("MODELCTRL", "g_dbossgate", 0, "SQ_POWERON", 30)
    g_bossgate = 1
end
be:FLGset(158, 1)
