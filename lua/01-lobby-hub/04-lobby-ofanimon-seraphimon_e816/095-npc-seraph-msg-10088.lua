if be:FLGisOn(4) == 1 then
    if be:FLGisOn(68) == 0 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10088 = "TALKFONT02/font00/I<454>"
        funcOneMessage(mswk10088)
        mswk10089 = "TALKFONT02/font00/I<455>"
        funcOneMessage(mswk10089)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
        be:FLGset(0, 1)
    elseif be:FLGisOn(68) == 1 and be:FLGisOn(334) == 0 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10090 = "TALKFONT02/font00/I<456>"
        funcOneMessage(mswk10090)
        mswk10091 = "TALKFONT02/font00/I<457>"
        funcOneMessage(mswk10091)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
    elseif be:FLGisOn(68) == 1 and be:FLGisOn(334) == 1 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10092 = "TALKFONT02/font00/I<458>"
        funcOneMessage(mswk10092)
        mswk10093 = "TALKFONT02/font00/I<459>"
        funcOneMessage(mswk10093)
        mswk10094 = "TALKFONT02/font00/I<460>"
        funcOneMessage(mswk10094)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
        be:FLGset(82, 1)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(5) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10095 = "TALKFONT02/font00/I<461>"
        funcOneMessage(mswk10095)
        mswk10096 = "TALKFONT02/font00/I<462>"
        funcOneMessage(mswk10096)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(6) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10097 = "TALKFONT02/font00/I<463>"
        funcOneMessage(mswk10097)
        mswk10098 = "TALKFONT02/font00/I<464>"
        funcOneMessage(mswk10098)
        mswk10099 = "TALKFONT02/font00/I<465>"
        funcOneMessage(mswk10099)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(86) == 1 then
    if be:FLGisOn(85) == 0 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10100 = "TALKFONT02/font00/I<466>"
        funcOneMessage(mswk10100)
        mswk10101 = "TALKFONT02/font00/I<467>"
        funcOneMessage(mswk10101)
        mswk10102 = "TALKFONT02/font00/I<468>"
        funcOneMessage(mswk10102)
        mswk10103 = "TALKFONT02/font00/I<469>"
        funcOneMessage(mswk10103)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
        be:FLGset(85, 1)
    elseif be:FLGisOn(85) == 1 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10104 = "TALKFONT02/font00/I<470>"
        funcOneMessage(mswk10104)
        mswk10105 = "TALKFONT02/font00/I<469>"
        funcOneMessage(mswk10105)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(3) == 1 then
    if be:FLGisOn(4) == 0 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10106 = "TALKFONT02/font00/I<471>"
        funcOneMessage(mswk10106)
        mswk10107 = "TALKFONT02/font00/I<472>"
        funcOneMessage(mswk10107)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
        be:FLGset(0, 1)
        be:FLGset(0, 1)
    elseif be:FLGisOn(4) == 1 then
        funcOpenMessage("talk", "n_seraph", "ZtB")
        mswk10108 = "TALKFONT02/font00/I<454>"
        funcOneMessage(mswk10108)
        mswk10109 = "TALKFONT02/font00/I<473>"
        funcOneMessage(mswk10109)
        funcCloseMessage("talk", "n_seraph", "ZtB")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
