be:FLGset(937, 0)
if be:SYSgetPlayerLevel(g_messPlayerNo) >= 16 then
    be:FLGset(937, 1)
end
if be:FLGisOn(1) == 1 then
    if be:FLGisOn(34) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10746 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10746)
        mswk10747 = "TALKFONT02/font00/I<183>"
        funcOneMessage(mswk10747)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
        be:FLGset(34, 1)
    elseif be:FLGisOn(34) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10748 = "TALKFONT02/font00/I<184>"
        funcOneMessage(mswk10748)
        mswk10749 = "TALKFONT02/font00/I<185>"
        funcOneMessage(mswk10749)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(1) == 0 and be:FLGisOn(937) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10750 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10750)
        mswk10751 = "TALKFONT02/font00/I<186>"
        funcOneMessage(mswk10751)
        be:DMsetLua("bML01004.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10752 = "TALKFONT02/font00/I<187>"
        funcOneMessage(mswk10752)
        mswk10753 = "TALKFONT02/font00/I<188>"
        funcOneMessage(mswk10753)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(1) == 0 and be:FLGisOn(937) == 1 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10754 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10754)
        mswk10755 = "TALKFONT02/font00/I<186>"
        funcOneMessage(mswk10755)
        be:DMsetLua("sin_digi.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk10756 = "TALKFONT02/font00/I<187>"
        funcOneMessage(mswk10756)
        mswk10757 = "TALKFONT02/font00/I<188>"
        funcOneMessage(mswk10757)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
