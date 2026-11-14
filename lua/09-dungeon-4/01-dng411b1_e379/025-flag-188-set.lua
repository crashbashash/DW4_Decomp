local local_0
if be:FLGisOn(188) ~= 1 then
    be:FLGset(188, 1)
    for ramNo = 0, 4 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
