if be:FLGisOn(1) == 1 then
    if be:FLGisOn(25) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10442 = "TALKFONT02/font00/I<266>"
        funcOneMessage(mswk10442)
        mswk10443 = "TALKFONT02/font00/I<267>"
        funcOneMessage(mswk10443)
        mswk10444 = "TALKFONT02/font00/I<268>"
        funcOneMessage(mswk10444)
        mswk10445 = "TALKFONT02/font00/I<269>"
        funcOneMessage(mswk10445)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(25, 1)
    elseif be:FLGisOn(25) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10446 = "TALKFONT02/font00/I<270>"
        funcOneMessage(mswk10446)
        mswk10447 = "TALKFONT02/font00/I<269>"
        funcOneMessage(mswk10447)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(1) == 0 then
    if g_lFLG01 ~= 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10448 = "TALKFONT02/font00/I<266>"
        funcOneMessage(mswk10448)
        mswk10449 = "TALKFONT02/font00/I<267>"
        funcOneMessage(mswk10449)
        mswk10450 = "TALKFONT02/font00/I<271>"
        funcOneMessage(mswk10450)
        mswk10451 = "TALKFONT02/font00/I<272>"
        funcOneMessage(mswk10451)
        be:DMsetLua("bML01003.lua")
        be:DMrun()
        g_lFLG01 = 1
    elseif g_lFLG01 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10452 = "TALKFONT02/font00/I<273>"
        funcOneMessage(mswk10452)
        be:DMsetLua("bML01003.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
