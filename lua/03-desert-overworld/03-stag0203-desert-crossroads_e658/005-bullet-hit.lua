if be:MDLgetBulletName() == "PCBA" then
    be:MDLsetSeq("SQ_PUSHED")
elseif be:BLTisHitCheck() == 0 then
    be:MDLsetSeq("SQ_GUARD")
else
    be:MDLaddHp(-35)
    if be:MDLgetHp() >= 30 then
        be:MDLsetSeq("SQ_SDMG")
    else
        be:MDLsetSD("SETLABEL", "SQ_DDMG/" .. be:BLTgetAttributeStr())
        be:MDLsetSeq("SQ_DDMG")
        be:BLTcalcEXPUp()
    end
end
