local local_0
if be:MATisPlayer() == 1 then
    for ramNo = 3, 4 do
        be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWERON")
    end
end
for ramNo = 3, 4 do
    be:sd("MODELCTRL", "g_darrowshotter", ramNo, "SQ_POWEROF")
end
