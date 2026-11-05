if local_0 == 0 then
    be:BLTcalcEXPUp()
    for local_2 = 0, 40 do
        be:BLTcalcSkillUp(1, local_1)
    end
end
if local_0 == 1 then
    for local_2 = 0, 500 do
        be:BLTcalcSkillUp(1, local_1)
    end
end
be:DMsetSD("MODELCTRL", "e_goburi", local_0, "SQ_MDMG")
be:DMchkSD("MODELCTRL", "e_goburi", local_0, "ISSEQNAME", "SQ_MDMG", "!=0")
be:DMsetSD("MODELCTRL", "e_goburi", local_0, "SQ_SLEP")
be:DMrun()
