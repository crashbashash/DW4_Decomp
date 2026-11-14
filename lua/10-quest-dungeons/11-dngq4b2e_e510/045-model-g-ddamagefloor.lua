local local_0
if be:MATisPlayer() == 1 then
    for ramNo = 0, 1 do
        be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON")
    end
    for ramNo = 0, 2 do
        be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWERON2")
    end
end
for ramNo = 0, 1 do
    be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/OFF")
end
for ramNo = 0, 2 do
    be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWEROF")
end
