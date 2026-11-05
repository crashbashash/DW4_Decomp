if be:MDLgetRamNo() == 0 then
    be:FLGset(249, 1)
elseif be:MDLgetRamNo() == 1 then
    be:FLGset(250, 1)
end
for local_1 = 0, 20 do
    be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
end
