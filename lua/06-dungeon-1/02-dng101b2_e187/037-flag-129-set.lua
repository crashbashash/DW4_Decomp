local local_0
for ramNo = 0, 6 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
be:FLGset(129, 1)
