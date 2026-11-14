local local_0
be:FLGset(283, 1)
for ramNo = 0, 8 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
g_dcap = 1
