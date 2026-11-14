local local_0
if be:MATisPlayer() == 1 then
    for ramNo = 10, 12 do
        be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWERON2")
    end
end
for ramNo = 10, 12 do
    be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWEROF")
end
