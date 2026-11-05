if be:SYSgetDifficulty() == 1 and be:MATisPlayer(be:FLGisOn(), be, 143) == 1 then
    for local_1 = 0, 7 do
        be:DMsetSD("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
    end
    be:DMsetSD("MODELCTRL", "g_darrowshotter", 0, "SQ_POWERON")
    be:DMsetSD("MODELCTRL", "g_darrowshotter", 1, "SQ_POWERON")
else
end
