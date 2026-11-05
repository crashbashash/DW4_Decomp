if be:MATisAllPlayer() == 1 and be:FLGisOn(43) == 0 and g_IFLG03 ~= 1 and be:DMgetCount() == 0 then
    g_IFLG03 = 1
    be:sd("PLAYER", nil, -1, "OFCTRL")
    be:sd("ENEMY", nil, -1, "OFCTRL")
    be:DMsetSD("MODELCTRL", "g_breakinggatez05", 0, "SQ_SWOF")
    be:DMsetSD("HITLANDMODEL", "hitbreakinggatez050", 0, "ONHIT")
    be:DMchkSD("MODELCTRL", "g_breakinggatez05", 0, "ISSEQNAME", "SQ_SWOF", "!=0")
    be:DMsetSD("GENERATER", nil, -1, "START", "GENE-07")
    be:DMsetSD("MODELCTRL", nil, -1, "ONCTRL", 60)
    be:DMrun()
end
