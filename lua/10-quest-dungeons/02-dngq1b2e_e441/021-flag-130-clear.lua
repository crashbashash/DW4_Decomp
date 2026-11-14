if be:MATisPlayer() == 0 and be:FLGisOn(130) == 1 then
    if be:FLGisOn(133) ~= 0 then
        if be:FLGisOn(134) == 0 then
        end
    end
    be:sd("MODELCTRL", "g_dwbutton1", 0, "SQ_SWOF")
    be:FLGset(130, 0)
end
