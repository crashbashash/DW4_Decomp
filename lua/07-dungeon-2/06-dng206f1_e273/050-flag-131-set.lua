local local_0
be:FLGset(131, 1)
for ramNo = 0, 10 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
