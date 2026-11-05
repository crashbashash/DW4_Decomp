if be:MATisAllPlayer() == 1 and g_IFLG02 ~= 1 and be:DMgetCount() == 0 then
    g_IFLG02 = 1
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("MODELCTRL", "g_breakinggatez05", 0, "SQ_SWOF")
    be:DMsetSD("MODELCTRL", "g_breakinggatez05", 2, "SQ_SWOF")
    be:DMsetSD("HITLANDMODEL", "hitbreakinggatez050", 0, "ONHIT")
    be:DMsetSD("HITLANDMODEL", "hitbreakinggatez052", 0, "ONHIT")
    be:DMchkSD("MODELCTRL", "g_breakinggatez05", 0, "ISSEQNAME", "SQ_SWOF", "!=0")
    be:DMsetSD("GENERATER", nil, -1, "START", "GENE-23", 15)
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 60)
    be:DMrun()
end
