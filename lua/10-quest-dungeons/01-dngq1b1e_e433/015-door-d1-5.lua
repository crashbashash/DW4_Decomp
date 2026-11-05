if be:MATisPlayer() == 1 then
    if be:FLGisOn(103) ~= 1 then
        if g_door03 ~= 1 then
            be:sd("MODELCTRL", "g_d1door", 2, "SQ_SWOF")
            be:sd("HITLANDMODEL", "doorwall03", 0, "ONHIT")
            g_door03 = 1
        end
        be:sd("GENERATER", nil, -1, "START", "GENE-04")
    else
        be:MATsetRun(0)
    end
end
be:sd("GENERATER", nil, -1, "STOP", "GENE-04")
