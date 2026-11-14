local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(103, 1)
    if be:FLGisOn(104) ~= 1 then
        for ramNo = 0, 4 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
        be:FLGset(104, 1)
    end
end
