local local_0
if be:MATisPlayer() == 1 then
    for ramNo = 0, 3 do
        be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWERON2")
    end
    for ramNo = 5, 9 do
        be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWERON2")
    end
end
for ramNo = 0, 3 do
    be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWEROF")
end
for ramNo = 5, 9 do
    be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWEROF")
end
