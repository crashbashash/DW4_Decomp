if be:FLGisOn(2) == 1 and be:FLGisOn(20) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_leomon", "I")
        mswk10405 = "TALKFONT02/font00/I<244>"
        funcOneMessage(mswk10405)
        mswk10406 = "TALKFONT02/font00/I<245>"
        funcOneMessage(mswk10406)
        funcCloseMessage("talk", "n_leomon", "I")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(3) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_leomon", "I")
        mswk10407 = "TALKFONT02/font00/I<246>"
        funcOneMessage(mswk10407)
        mswk10408 = "TALKFONT02/font00/I<247>"
        funcOneMessage(mswk10408)
        mswk10409 = "TALKFONT02/font00/I<248>"
        funcOneMessage(mswk10409)
        funcCloseMessage("talk", "n_leomon", "I")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(4) == 1 and be:FLGisOn(82) == 0 then
    if be:FLGisOn(611) == 0 then
        funcOpenMessage("talk", "n_leomon", "I")
        mswk10410 = "TALKFONT02/font00/I<249>"
        funcOneMessage(mswk10410)
        mswk10411 = "TALKFONT02/font00/I<250>"
        funcOneMessage(mswk10411)
        mswk10412 = "TALKFONT02/font00/I<251>"
        funcOneMessage(mswk10412)
        mswk10413 = "TALKFONT02/font00/I<252>"
        funcOneMessage(mswk10413)
        funcCloseMessage("talk", "n_leomon", "I")
        be:DMrun()
        be:FLGset(611, 1)
    elseif be:FLGisOn(611) == 1 then
        funcOpenMessage("talk", "n_leomon", "I")
        mswk10414 = "TALKFONT02/font00/I<253>"
        funcOneMessage(mswk10414)
        mswk10415 = "TALKFONT02/font00/I<254>"
        funcOneMessage(mswk10415)
        mswk10416 = "TALKFONT02/font00/I<255>"
        funcOneMessage(mswk10416)
        mswk10417 = "TALKFONT02/font00/I<256>"
        funcOneMessage(mswk10417)
        mswk10418 = "TALKFONT02/font00/I<257>"
        funcOneMessage(mswk10418)
        funcCloseMessage("talk", "n_leomon", "I")
        be:DMrun()
        be:FLGset(611, 0)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
