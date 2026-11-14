be:FLGset(908, 0)
if be:SYSgetPlayerLevel(0) >= 16 then
    be:FLGset(908, 1)
end
be:FLGset(909, 0)
if be:SYSgetPlayerLevel(0) >= 46 then
    be:FLGset(909, 1)
end
be:FLGset(910, 0)
if be:SYSgetPlayerLevel(0) >= 76 then
    be:FLGset(910, 1)
end
if be:FLGisOn(98) == 1 and be:FLGisOn(908) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11091 = "TALKFONT02/font00/I<165>"
        funcOneMessage(mswk11091)
        mswk11092 = "TALKFONT02/font00/I<166>"
        funcOneMessage(mswk11092)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(98) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(909) == 0 and be:FLGisOn(86) == 0 then
    if be:FLGisOn(371) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11093 = "TALKFONT02/font00/I<167>"
        funcOneMessage(mswk11093)
        mswk11094 = "TALKFONT02/font00/I<168>"
        funcOneMessage(mswk11094)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(371) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11095 = "TALKFONT02/font00/I<169>"
        funcOneMessage(mswk11095)
        mswk11096 = "TALKFONT02/font00/I<170>"
        funcOneMessage(mswk11096)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(98) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(910) == 0 and be:FLGisOn(86) == 0 then
    if be:FLGisOn(371) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11097 = "TALKFONT02/font00/I<167>"
        funcOneMessage(mswk11097)
        mswk11098 = "TALKFONT02/font00/I<168>"
        funcOneMessage(mswk11098)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(371) == 1 and be:FLGisOn(372) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11099 = "TALKFONT02/font00/I<171>"
        funcOneMessage(mswk11099)
        mswk11100 = "TALKFONT02/font00/I<172>"
        funcOneMessage(mswk11100)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(371) == 1 and be:FLGisOn(372) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11101 = "TALKFONT02/font00/I<169>"
        funcOneMessage(mswk11101)
        mswk11102 = "TALKFONT02/font00/I<173>"
        funcOneMessage(mswk11102)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(98) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(86) == 0 then
    if be:FLGisOn(371) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11103 = "TALKFONT02/font00/I<167>"
        funcOneMessage(mswk11103)
        mswk11104 = "TALKFONT02/font00/I<168>"
        funcOneMessage(mswk11104)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(371) == 1 and be:FLGisOn(372) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11105 = "TALKFONT02/font00/I<171>"
        funcOneMessage(mswk11105)
        mswk11106 = "TALKFONT02/font00/I<172>"
        funcOneMessage(mswk11106)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(371) == 1 and be:FLGisOn(372) == 1 and be:FLGisOn(373) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11107 = "TALKFONT02/font00/I<174>"
        funcOneMessage(mswk11107)
        mswk11108 = "TALKFONT02/font00/I<175>"
        funcOneMessage(mswk11108)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(371) == 1 and be:FLGisOn(372) == 1 and be:FLGisOn(373) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11109 = "TALKFONT02/font00/I<169>"
        funcOneMessage(mswk11109)
        mswk11110 = "TALKFONT02/font00/I<173>"
        funcOneMessage(mswk11110)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(98) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(86) == 1 then
    if be:FLGisOn(375) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11111 = "TALKFONT02/font00/I<176>"
        funcOneMessage(mswk11111)
        mswk11112 = "TALKFONT02/font00/I<177>"
        funcOneMessage(mswk11112)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(375, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11113 = "TALKFONT02/font00/I<167>"
        funcOneMessage(mswk11113)
        mswk11114 = "TALKFONT02/font00/I<168>"
        funcOneMessage(mswk11114)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 1 and be:FLGisOn(372) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11115 = "TALKFONT02/font00/I<171>"
        funcOneMessage(mswk11115)
        mswk11116 = "TALKFONT02/font00/I<172>"
        funcOneMessage(mswk11116)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 1 and be:FLGisOn(372) == 1 and be:FLGisOn(373) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11117 = "TALKFONT02/font00/I<174>"
        funcOneMessage(mswk11117)
        mswk11118 = "TALKFONT02/font00/I<175>"
        funcOneMessage(mswk11118)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 1 and be:FLGisOn(372) == 1 and be:FLGisOn(373) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11119 = "TALKFONT02/font00/I<169>"
        funcOneMessage(mswk11119)
        mswk11120 = "TALKFONT02/font00/I<178>"
        funcOneMessage(mswk11120)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(98) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(909) == 0 and be:FLGisOn(86) == 1 then
    if be:FLGisOn(375) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11121 = "TALKFONT02/font00/I<176>"
        funcOneMessage(mswk11121)
        mswk11122 = "TALKFONT02/font00/I<177>"
        funcOneMessage(mswk11122)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(375, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11123 = "TALKFONT02/font00/I<167>"
        funcOneMessage(mswk11123)
        mswk11124 = "TALKFONT02/font00/I<168>"
        funcOneMessage(mswk11124)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11125 = "TALKFONT02/font00/I<169>"
        funcOneMessage(mswk11125)
        mswk11126 = "TALKFONT02/font00/I<173>"
        funcOneMessage(mswk11126)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(98) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(910) == 0 and be:FLGisOn(86) == 1 then
    if be:FLGisOn(375) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11127 = "TALKFONT02/font00/I<176>"
        funcOneMessage(mswk11127)
        mswk11128 = "TALKFONT02/font00/I<177>"
        funcOneMessage(mswk11128)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(375, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11129 = "TALKFONT02/font00/I<167>"
        funcOneMessage(mswk11129)
        mswk11130 = "TALKFONT02/font00/I<168>"
        funcOneMessage(mswk11130)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 1 and be:FLGisOn(372) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11131 = "TALKFONT02/font00/I<171>"
        funcOneMessage(mswk11131)
        mswk11132 = "TALKFONT02/font00/I<172>"
        funcOneMessage(mswk11132)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(64, 1)
    elseif be:FLGisOn(375) == 1 and be:FLGisOn(371) == 1 and be:FLGisOn(372) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11133 = "TALKFONT02/font00/I<169>"
        funcOneMessage(mswk11133)
        mswk11134 = "TALKFONT02/font00/I<173>"
        funcOneMessage(mswk11134)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
