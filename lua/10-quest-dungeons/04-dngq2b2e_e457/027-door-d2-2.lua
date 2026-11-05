if be:MATisPlayer() == 1 then
    if g_door01 ~= 1 then
        be:sd("MODELCTRL", "g_d2door", 0, "SQ_SWON", 1800)
        be:sd("HITLANDMODEL", "doorwall01", 0, "OFFHIT", 1815)
        g_door01 = 1
    end
    if be:FLGisOn(120) ~= 1 then
        be:sd("GENERATER", nil, -1, "START", "GENE-01")
    else
        if be:FLGisOn(122) ~= 1 then
            if be:FLGisOn(121) == 1 then
                be:sd("GENERATER", nil, -1, "START", "GENE-03")
            else
            end
        end
        be:MATsetRun(0)
    end
end
