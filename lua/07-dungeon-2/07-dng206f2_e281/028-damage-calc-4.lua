if be:MDLgetHp() == 100 then
    be:MDLsetSeq("SQ_MVMI")
    be:MDLaddHp(-1)
else
    be:MDLsetSeq("SQ_MVPL")
    be:MDLaddHp(1)
end
