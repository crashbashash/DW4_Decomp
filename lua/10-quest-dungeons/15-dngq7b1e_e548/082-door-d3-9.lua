if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(160) ~= 1 then
        be:sd("MODELCTRL", "g_d3door", 2, "SQ_SWOF")
        be:sd("HITLANDMODEL", "doorwall03", 0, "ONHIT")
        be:FLGset(160, 1)
    end
    be:MATsetRun(0)
end
