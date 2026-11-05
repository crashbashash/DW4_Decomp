be:CFLclear()
g_evocount = 0
for local_11 = 0, 3 do
    if be:SYSisJoinPlayer(local_11) == 1 then
        local_9 = be:COUNTERget(local_11 + 8)
        local_10 = be:SYSgetPlayerDigimon(local_11)
        if local_14 ~= local_15 then
            be:CFLsetName("_common/" .. local_14 .. ".igb")
            be:CFLsetName("_common/" .. local_15 .. ".igb")
            g_evocount = g_evocount + 1
        end
        if local_11 == 0 then
            g_oldNameP1 = local_14
            g_nowNameP1 = local_15
        elseif local_11 == 1 then
            g_oldNameP2 = local_14
            g_nowNameP2 = local_15
        elseif local_11 == 2 then
            g_oldNameP3 = local_14
            g_nowNameP3 = local_15
        elseif local_11 == 3 then
            g_oldNameP4 = local_14
            g_nowNameP4 = local_15
        end
    end
end
local_5("DBBase")
