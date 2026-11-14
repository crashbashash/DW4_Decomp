local local_0
be:FLGset(169, 1)
for ramNo = 0, 4 do
    be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
end
