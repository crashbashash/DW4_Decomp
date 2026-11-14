local local_0
if be:MATisPlayer() == 1 and be:FLGisOn(187) ~= 1 then
    for ramNo = 1, 20 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
    be:FLGset(187, 1)
end
