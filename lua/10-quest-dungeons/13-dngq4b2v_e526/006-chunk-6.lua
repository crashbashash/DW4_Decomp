if be:MATisPlayer() == 1 then
    for local_1 = 3, 4 do
        be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWERON")
    end
end
for local_1 = 3, 4 do
    be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWEROF")
end
