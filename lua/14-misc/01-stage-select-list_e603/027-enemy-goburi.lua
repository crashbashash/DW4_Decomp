local ramNo = be:MDLgetRamNo()
local isCritical = be:BLTisCritical()
if ramNo == 0 then
    be:BLTcalcEXPUp()
    for i = 0, 40 do
        be:BLTcalcSkillUp(1, isCritical)
    end
end
if ramNo == 1 then
    for i = 0, 500 do
        be:BLTcalcSkillUp(1, isCritical)
    end
end
be:DMsetSD("MODELCTRL", "e_goburi", ramNo, "SQ_MDMG")
be:DMchkSD("MODELCTRL", "e_goburi", ramNo, "ISSEQNAME", "SQ_MDMG", "!=0")
be:DMsetSD("MODELCTRL", "e_goburi", ramNo, "SQ_SLEP")
be:DMrun()
