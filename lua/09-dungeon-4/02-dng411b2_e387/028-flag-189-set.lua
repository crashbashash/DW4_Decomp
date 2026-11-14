local local_0
if be:MATisPlayer() == 1 and be:FLGisOn(189) ~= 1 then
    for ramNo = 2, 5 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
    be:FLGset(189, 1)
end
