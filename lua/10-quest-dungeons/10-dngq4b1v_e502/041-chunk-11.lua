if be:MATisPlayer() == 1 then
    for local_1 = 0, 3 do
        be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWERON2")
    end
    for local_1 = 5, 9 do
        be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWERON2")
    end
end
for local_1 = 0, 3 do
    be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWEROF")
end
for local_1 = 5, 9 do
    be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWEROF")
end
