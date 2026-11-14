local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(135, 1)
    if g_dcap ~= 1 then
        for ramNo = 0, 11 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
        g_dcap = 1
    end
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(136, 1)
    be:sd("MODELCTRL", "g_dcap", 12, "SQ_DDMG")
end
