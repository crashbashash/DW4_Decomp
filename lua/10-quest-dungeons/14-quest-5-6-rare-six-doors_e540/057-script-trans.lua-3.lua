g_StChangeKind = "stay"
if be:MATisAllPlayer() == 1 and be:DMgetCount() == 0 then
    g_destMapBlock = g_mapLink[g_curMapBlock][local_0]
    g_pNo = local_1
    if be:SYSctlPlayer("HP", "GETHP", local_1, 0) <= 0 then
        return 3, be:MATgetPlayerNo()
    end
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BHLFOUT30")
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("MODELCTRL", "i_zzstchgwb", local_1, "GENERATE", "SQ_OPEN", 10)
    be:DMsetSD("SELECTCTRL", "i_zzstchgwn", local_1, "GENERATE", 10)
    be:DMchkSD("SELECTCTRL", "i_zzstchgwn", local_1, "ISEND", "!=0")
    be:DMchkSD("SELECTCTRL", "i_zzstchgwn", local_1, "ISEND", "==0")
    be:DMsetSD("MODELCTRL", "i_zzstchgwb", local_1, "SQ_CLOSE")
    be:DMswtSD("SELECTCTRL", "i_zzstchgwn", local_1, "GETSELECT")
    be:DMcase(0)
    be:DMsetLua("trans.lua")
    be:DMcase(1)
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
    be:DMcase(-1)
    be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BHLFIN30", 10)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 30)
    be:DMswtEnd()
    be:DMrun()
end
