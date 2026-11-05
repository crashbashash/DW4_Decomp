if be:MATisPlayer() == 1 then
    if g_dconvair01 ~= 1 then
        be:sd("MODELCTRL", "g_dconvair", 0, "SQ_SWON")
        g_dconvair01 = 1
    else
    end
end
be:sd("MODELCTRL", "g_dconvair", 0, "SQ_WAIT")
g_dconvair01 = 0
