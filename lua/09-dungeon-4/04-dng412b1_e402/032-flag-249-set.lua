local local_0
if be:MDLgetRamNo() == 0 then
    be:FLGset(249, 1)
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(250, 1)
end
for ramNo = 0, 20 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
