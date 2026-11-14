local local_0
be:FLGset(126, 1)
if be:FLGisOn(111) then
    for ramNo = 0, 14 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
