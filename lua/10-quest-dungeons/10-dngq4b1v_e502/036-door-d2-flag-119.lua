if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(106) ~= 1 then
        if be:FLGisOn(113) == 1 then
            be:sd("MODELCTRL", "g_d2door", 10, "SQ_SWOF")
            be:sd("HITLANDMODEL", "doorwall11", 0, "ONHIT")
            be:FLGset(113, 0)
        end
        be:sd("GENERATER", nil, -1, "START", "GENE-07")
    end
    if be:FLGisOn(119) == 1 then
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SETLABEL", "SQ_WAIT/OFF")
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SETLABEL", "SQ_WAIT/OFF")
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SETLABEL", "SQ_SWON/OFF")
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SETLABEL", "SQ_SWON/OFF")
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SETLABEL", "SQ_SWOF/OFF")
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SETLABEL", "SQ_SWOF/OFF")
        be:sd("MODELCTRL", "g_dwbutton2", 0, "SQ_SWOF")
        be:sd("MODELCTRL", "g_dwbutton2", 1, "SQ_SWOF")
        be:FLGset(117, 0)
        be:FLGset(118, 0)
        be:FLGset(119, 0)
    end
end
