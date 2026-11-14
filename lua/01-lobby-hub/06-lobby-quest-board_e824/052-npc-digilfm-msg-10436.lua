if be:FLGisOn(1) == 1 then
    if be:FLGisOn(24) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10436 = "TALKFONT02/font00/I<263>"
        funcOneMessage(mswk10436)
        mswk10437 = "TALKFONT02/font00/I<264>"
        funcOneMessage(mswk10437)
        be:DMsetLua("bML01002.lua")
        be:DMrun()
        be:FLGset(24, 1)
    elseif be:FLGisOn(24) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10438 = "TALKFONT02/font00/I<265>"
        funcOneMessage(mswk10438)
        be:DMsetLua("bML01002.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(1) == 0 then
    if g_lFLG00 ~= 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10439 = "TALKFONT02/font00/I<263>"
        funcOneMessage(mswk10439)
        mswk10440 = "TALKFONT02/font00/I<264>"
        funcOneMessage(mswk10440)
        be:DMsetLua("bML01002.lua")
        be:DMrun()
        g_lFLG00 = 1
    elseif g_lFLG00 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10441 = "TALKFONT02/font00/I<265>"
        funcOneMessage(mswk10441)
        be:DMsetLua("bML01002.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
