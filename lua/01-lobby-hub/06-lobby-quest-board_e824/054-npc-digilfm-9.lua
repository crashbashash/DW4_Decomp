if be:FLGisOn(1) == 1 then
    if be:FLGisOn(26) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10453 = "TALKFONT02/font00/I<274>"
        funcOneMessage(mswk10453)
        mswk10454 = "TALKFONT02/font00/I<275>"
        funcOneMessage(mswk10454)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(26, 1)
    elseif be:FLGisOn(26) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10455 = "TALKFONT02/font00/I<276>"
        funcOneMessage(mswk10455)
        mswk10456 = "TALKFONT02/font00/I<275>"
        funcOneMessage(mswk10456)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(1) == 0 then
    if g_lFLG02 ~= 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10457 = "TALKFONT02/font00/I<274>"
        funcOneMessage(mswk10457)
        mswk10458 = "TALKFONT02/font00/I<277>"
        funcOneMessage(mswk10458)
        be:DMsetLua("bML01006.lua")
        be:DMrun()
        g_lFLG02 = 1
    elseif g_lFLG02 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10459 = "TALKFONT02/font00/I<278>"
        funcOneMessage(mswk10459)
        be:DMsetLua("bML01006.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
