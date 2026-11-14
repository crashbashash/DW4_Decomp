if be:MATisAllPlayer() == 1 and be:FLGisOn(383) == 0 and be:DMgetCount() == 0 and g_IFLG02 ~= 1 then
    g_IFLG02 = 1
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("MODELCTRL", "g_breakinggatez05", 0, "SQ_SWOF")
    be:DMsetSD("HITLANDMODEL", "hitbreakinggatez05", 0, "ONHIT")
    be:DMchkSD("MODELCTRL", "g_breakinggatez05", 0, "ISSEQNAME", "SQ_SWOF", "!=0")
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 20)
    be:DMrun()
end
