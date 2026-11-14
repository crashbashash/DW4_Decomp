local local_0
if be:SYSgetDifficulty() == 1 then
    if be:MATisPlayer() == 1 then
        if be:FLGisOn(143) == 1 then
            for ramNo = 0, 7 do
                be:DMsetSD("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON")
            end
            be:DMsetSD("MODELCTRL", "g_darrowshotter", 0, "SQ_POWERON")
            be:DMsetSD("MODELCTRL", "g_darrowshotter", 1, "SQ_POWERON")
        end
    else
        for ramNo = 0, 7 do
            be:DMsetSD("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/OFF")
        end
        be:DMsetSD("MODELCTRL", "g_darrowshotter", 0, "SQ_POWEROF")
        be:DMsetSD("MODELCTRL", "g_darrowshotter", 1, "SQ_POWEROF")
    end
end
