be:CFLclear()
if be:SYSisJoinPlayer(0) == 1 then
    for local_9 = 0, 3 do
        if be:SYSisJoinPlayer(local_9) == 1 then
            local_8 = local_8 + 1
        end
    end
    if local_8 <= 2 then
        for local_9 = 0, 3 do
            if be:SYSisJoinPlayer(local_9) == 1 then
                be:CFLsetName("_common/" .. be:SYSgetPlayerName(local_9) .. ".igb")
            end
        end
    end
    for local_9 = 0, 3 do
        if be:SYSisJoinPlayer(local_9) == 1 then
            be:CFLsetName("_common/" .. local_13 .. ".igb")
        end
    end
else
    be:CFLsetName("_common/p_agumon.igb")
end
if be:SYSisJoinPlayer(0) == 1 then
    for local_9 = 0, 3 do
        if be:SYSisJoinPlayer(local_9) == 1 then
            for local_12 = 0, 2 do
                if local_15 then
                    be:CFLsetName("_common/" .. local_15 .. ".igb")
                end
            end
        end
    end
else
    be:CFLsetName("_common/w_common05.igb")
end
local_5("FontTree", "DBBase", "bcnumic", "bitnum", "expnum", "getitempnl01", "getitempnl02", "getitempnl03", "pcnumic", "rareicon01", "stdownic00", "stdownic01", "stdownic02", "stdownic03", "stdownic04", "stdownic05", "stdownic06", "stdownic07", "stdownic08", "stdownic09", "stdownic10", "stpnl05", "zzstchgwb", "zzstchgwn", "stpnl01", "stpnl03", "stpnl04", "healnum", "stbase")
local_6("BGG00n", "BGG00s")
