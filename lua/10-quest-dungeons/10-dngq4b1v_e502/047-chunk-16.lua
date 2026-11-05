if be:MATisPlayer() == 1 then
    for local_1 = 13, 16 do
        be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
    end
    for local_1 = 13, 15 do
        be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWERON2")
    end
end
for local_1 = 13, 16 do
    be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/OFF")
end
for local_1 = 13, 15 do
    be:sd("MODELCTRL", "g_darrowshotter", local_1, "SQ_POWEROF")
end
