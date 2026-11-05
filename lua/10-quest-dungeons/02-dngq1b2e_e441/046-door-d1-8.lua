if be:SYSgetDifficulty() == 0 then
    if be:MDLgetRamNo() == 0 and be:FLGisOn(124) ~= 1 then
        be:FLGset(124, 1)
        be:FLGset(125, 1)
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON", 30)
        if be:FLGisOn(133) ~= 1 and be:FLGisOn(134) == 1 then
            be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON", 30)
            be:FLGset(130, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 1 and be:FLGisOn(125) ~= 1 then
        be:FLGset(125, 1)
        be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
        be:FLGset(135, 1)
    else
    end
end
if be:SYSgetDifficulty() == 1 then
    if be:MDLgetRamNo() == 0 and be:FLGisOn(124) ~= 1 then
        be:FLGset(124, 1)
        if be:FLGisOn(125) + be:FLGisOn(127) == 2 then
            be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
            be:FLGset(135, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 1 and be:FLGisOn(125) ~= 1 then
        be:FLGset(125, 1)
        if be:FLGisOn(124) + be:FLGisOn(127) == 2 then
            be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
            be:FLGset(135, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 2 and be:FLGisOn(126) ~= 1 then
        be:FLGset(124, 1)
        be:FLGset(125, 1)
        be:FLGset(126, 1)
        be:FLGset(127, 1)
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON", 30)
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON", 30)
        be:sd("MODELCTRL", "g_dbutton1", 3, "SQ_SILENTON", 30)
        if be:FLGisOn(133) ~= 1 and be:FLGisOn(134) == 1 then
            be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON", 30)
            be:FLGset(130, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 3 and be:FLGisOn(127) ~= 1 and be:FLGisOn(124) + be:FLGisOn(125) == 2 then
        be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
        be:FLGset(135, 1)
    else
    end
end
if be:SYSgetDifficulty() == 2 then
    if be:MDLgetRamNo() == 0 and be:FLGisOn(124) ~= 1 then
        be:FLGset(124, 1)
        if be:FLGisOn(125) + be:FLGisOn(126) + be:FLGisOn(128) + be:FLGisOn(129) == 4 then
            be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
            be:FLGset(135, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 1 and be:FLGisOn(125) ~= 1 then
        be:FLGset(125, 1)
        if be:FLGisOn(124) + be:FLGisOn(126) + be:FLGisOn(128) + be:FLGisOn(129) == 4 then
            be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
            be:FLGset(135, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 2 and be:FLGisOn(126) ~= 1 then
        be:FLGset(126, 1)
        if be:FLGisOn(124) + be:FLGisOn(125) + be:FLGisOn(128) + be:FLGisOn(129) == 4 then
            be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
            be:FLGset(135, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 3 and be:FLGisOn(127) ~= 1 then
        be:FLGset(124, 1)
        be:FLGset(125, 1)
        be:FLGset(126, 1)
        be:FLGset(127, 1)
        be:FLGset(128, 1)
        be:FLGset(129, 1)
        be:sd("MODELCTRL", "g_dbutton1", 0, "SQ_SILENTON", 30)
        be:sd("MODELCTRL", "g_dbutton1", 1, "SQ_SILENTON", 30)
        be:sd("MODELCTRL", "g_dbutton1", 2, "SQ_SILENTON", 30)
        be:sd("MODELCTRL", "g_dbutton1", 4, "SQ_SILENTON", 30)
        be:sd("MODELCTRL", "g_dbutton1", 5, "SQ_SILENTON", 30)
        if be:FLGisOn(133) ~= 1 and be:FLGisOn(134) == 1 then
            be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SILENTON", 30)
            be:FLGset(130, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 4 and be:FLGisOn(128) ~= 1 then
        be:FLGset(128, 1)
        if be:FLGisOn(124) + be:FLGisOn(125) + be:FLGisOn(126) + be:FLGisOn(129) == 4 then
            be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
            be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
            be:FLGset(135, 1)
        else
        end
    end
    if be:MDLgetRamNo() == 5 and be:FLGisOn(129) ~= 1 and be:FLGisOn(124) + be:FLGisOn(125) + be:FLGisOn(126) + be:FLGisOn(128) == 4 then
        be:sd("MODELCTRL", "g_d1door", 5, "SQ_SWON", 30)
        be:sd("HITLANDMODEL", "doorwall06", 0, "OFFHIT", 45)
        be:FLGset(135, 1)
    else
    end
end
be:MsgBox("G[FïÕxªzèOÅ·B")
