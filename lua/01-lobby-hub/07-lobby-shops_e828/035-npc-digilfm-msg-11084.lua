if be:FLGisOn(1) == 1 then
    if be:FLGisOn(28) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11084 = "TALKFONT02/font00/I<159>"
        funcOneMessage(mswk11084)
        mswk11085 = "TALKFONT02/font00/I<160>"
        funcOneMessage(mswk11085)
        mswk11086 = "TALKFONT02/font00/I<161>"
        funcOneMessage(mswk11086)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(28, 1)
    elseif be:FLGisOn(28) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11087 = "TALKFONT02/font00/I<162>"
        funcOneMessage(mswk11087)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(1) == 0 then
    if g_lFLG04 ~= 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11088 = "TALKFONT02/font00/I<159>"
        funcOneMessage(mswk11088)
        mswk11089 = "TALKFONT02/font00/I<163>"
        funcOneMessage(mswk11089)
        be:DMsetLua("bML01011.lua")
        be:DMrun()
        g_lFLG04 = 1
    elseif g_lFLG04 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11090 = "TALKFONT02/font00/I<164>"
        funcOneMessage(mswk11090)
        be:DMsetLua("bML01011.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
