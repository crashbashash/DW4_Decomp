if be:MDLgetRamNo() == 0 then
    be:FLGset(248, 1)
    if be:FLGisOn(177) ~= 1 then
        for ramNo = 0, 3 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
    end
end
