if be:FLGisOn(1) == 1 then
    if be:FLGisOn(30) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10738 = "TALKFONT02/font00/I<177>"
        funcOneMessage(mswk10738)
        mswk10739 = "TALKFONT02/font00/I<178>"
        funcOneMessage(mswk10739)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
        be:FLGset(30, 1)
    elseif be:FLGisOn(30) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10740 = "TALKFONT02/font00/I<179>"
        funcOneMessage(mswk10740)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(1) == 0 then
    if be:FLGisOn(572) == 0 and g_lFLG06 ~= 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10741 = "TALKFONT02/font00/I<177>"
        funcOneMessage(mswk10741)
        mswk10742 = "TALKFONT02/font00/I<178>"
        funcOneMessage(mswk10742)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
        g_lFLG06 = 1
    elseif be:FLGisOn(572) == 0 and g_lFLG06 == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10743 = "TALKFONT02/font00/I<179>"
        funcOneMessage(mswk10743)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
    elseif be:FLGisOn(572) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10744 = "TALKFONT02/font00/I<180>"
        funcOneMessage(mswk10744)
        mswk10745 = "TALKFONT02/font00/I<181>"
        funcOneMessage(mswk10745)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
