local local_0
be:FLGset(133, 1)
for ramNo = 0, 1 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
