local local_0
be:FLGset(113, 1)
for ramNo = 0, 6 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
