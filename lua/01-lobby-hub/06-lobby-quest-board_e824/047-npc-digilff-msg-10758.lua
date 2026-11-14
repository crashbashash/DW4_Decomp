if be:FLGisOn(1) == 1 then
    if be:FLGisOn(29) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10758 = "TALKFONT02/font00/I<189>"
        funcOneMessage(mswk10758)
        mswk10759 = "TALKFONT02/font00/I<190>"
        funcOneMessage(mswk10759)
        mswk10760 = "TALKFONT02/font00/I<191>"
        funcOneMessage(mswk10760)
        mswk10761 = "TALKFONT02/font00/I<192>"
        funcOneMessage(mswk10761)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
        be:FLGset(29, 1)
    elseif be:FLGisOn(29) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10762 = "TALKFONT02/font00/I<193>"
        funcOneMessage(mswk10762)
        mswk10763 = "TALKFONT02/font00/I<192>"
        funcOneMessage(mswk10763)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(1) == 0 then
    if g_lFLG05 ~= 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10764 = "TALKFONT02/font00/I<189>"
        funcOneMessage(mswk10764)
        mswk10765 = "TALKFONT02/font00/I<190>"
        funcOneMessage(mswk10765)
        mswk10766 = "TALKFONT02/font00/I<194>"
        funcOneMessage(mswk10766)
        be:DMsetLua("bML01001.lua")
        be:DMrun()
        g_lFLG05 = 1
    elseif g_lFLG05 == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10767 = "TALKFONT02/font00/I<195>"
        funcOneMessage(mswk10767)
        be:DMsetLua("bML01001.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
