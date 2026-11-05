if be:FLGisOn(1) == 1 then
    if be:FLGisOn(571) == 0 and be:FLGisOn(33) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10347 = "TALKFONT02/font00/I<110>"
        funcOneMessage(mswk10347)
        mswk10348 = "TALKFONT02/font00/I<111>"
        funcOneMessage(mswk10348)
        be:DMsetLua("bML01007.lua")
        be:DMrun()
        be:FLGset(33, 1)
    elseif be:FLGisOn(571) == 0 and be:FLGisOn(33) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10349 = "TALKFONT02/font00/I<112>"
        funcOneMessage(mswk10349)
        mswk10350 = "TALKFONT02/font00/I<111>"
        funcOneMessage(mswk10350)
        be:DMsetLua("bML01007.lua")
        be:DMrun()
    elseif be:FLGisOn(571) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10351 = "TALKFONT02/font00/I<113>"
        funcOneMessage(mswk10351)
        mswk10352 = "TALKFONT02/font00/I<114>"
        funcOneMessage(mswk10352)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(1) == 0 then
    if be:FLGisOn(571) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10353 = "TALKFONT02/font00/I<110>"
        funcOneMessage(mswk10353)
        mswk10354 = "TALKFONT02/font00/I<115>"
        funcOneMessage(mswk10354)
        be:DMsetLua("bML01007.lua")
        be:DMrun()
    elseif be:FLGisOn(571) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10355 = "TALKFONT02/font00/I<113>"
        funcOneMessage(mswk10355)
        mswk10356 = "TALKFONT02/font00/I<114>"
        funcOneMessage(mswk10356)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
