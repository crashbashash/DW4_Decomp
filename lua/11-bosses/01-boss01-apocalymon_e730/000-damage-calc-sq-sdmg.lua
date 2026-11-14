be:MDLaddHp(-50)
if be:MDLgetHp() >= 50 then
    be:MDLsetSeq("SQ_SDMG")
else
    be:MDLsetSeq("SQ_DDMG")
end
