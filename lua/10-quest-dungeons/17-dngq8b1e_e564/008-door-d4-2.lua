if be:MDLgetRamNo() == 0 then
    g_button01 = 1
elseif be:MDLgetRamNo() == 1 then
    g_button02 = 1
elseif be:MDLgetRamNo() == 2 then
    g_button03 = 1
elseif be:MDLgetRamNo() == 3 then
    g_button04 = 1
end
if g_button01 == 1 then
    local_0 = local_0 + 1
end
if g_button02 == 1 then
    local_0 = local_0 + 1
end
if g_button03 == 1 then
    local_0 = local_0 + 1
end
if g_button04 == 1 then
    local_0 = local_0 + 1
end
if local_0 == 4 then
    for local_1 = 0, 3 do
        be:sd("MODELCTRL", "g_dbutton2", local_1, "SQ_ONLOOP")
    end
    be:sd("MODELCTRL", "g_d4door", 8, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall09", 0, "OFFHIT", 45)
    be:sd("MODELCTRL", "g_d4door", 10, "SQ_SWON", 30)
    be:sd("HITLANDMODEL", "doorwall11", 0, "OFFHIT", 45)
    be:FLGset(140, 1)
end
