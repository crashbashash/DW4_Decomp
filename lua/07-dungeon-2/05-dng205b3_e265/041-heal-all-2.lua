funcHealGate("ALL", "g_dallhealeffect", 1)
for local_1 = 0, 3 do
    if be:MATisRidePlayer(local_1) == 1 then
        be:sd("PLAYER", be:SYSgetPlayerName(local_1), local_1, "CLEARMETAL")
    end
    if be:MATisRideOffPlayer(local_1) == 1 then
        be:sd("PLAYER", be:SYSgetPlayerName(local_1), local_1, "SETMETAL")
    end
end
