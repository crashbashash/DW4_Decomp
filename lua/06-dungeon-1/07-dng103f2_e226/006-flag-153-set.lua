local local_0
if be:FLGisOn(153) + be:FLGisOn(154) == 0 then
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
    end
end
if be:MDLgetRamNo() == 0 then
    be:FLGset(153, 1)
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(154, 1)
end
