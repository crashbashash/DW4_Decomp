be:FLGset(931, 0)
be:FLGset(932, 0)
be:FLGset(933, 0)
if be:SYSgetDifficulty() == 2 then
    be:FLGset(933, 1)
elseif be:SYSgetDifficulty() == 1 then
    be:FLGset(932, 1)
else
    be:FLGset(931, 1)
end
be:FLGset(935, 0)
if be:SYSgetPlayerNinzu() == 1 then
    be:FLGset(935, 1)
end
if be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10525 = "TALKFONT02/font00/I<344>"
        funcOneMessage(mswk10525)
        mswk10526 = "TALKFONT02/font00/I<345>"
        funcOneMessage(mswk10526)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10527 = "TALKFONT02/font00/I<346>"
        funcOneMessage(mswk10527)
        mswk10528 = "TALKFONT02/font00/I<347>"
        funcOneMessage(mswk10528)
        be:DMsetLua("bML01025.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(380) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10529 = "TALKFONT02/font00/I<346>"
        funcOneMessage(mswk10529)
        mswk10530 = "TALKFONT02/font00/I<347>"
        funcOneMessage(mswk10530)
        be:DMsetLua("bML01026.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(380) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10531 = "TALKFONT02/font00/I<348>"
        funcOneMessage(mswk10531)
        be:DMsetLua("bML01027.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(419) == 1 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10532 = "TALKFONT02/font00/I<349>"
        funcOneMessage(mswk10532)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 1 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10533 = "TALKFONT02/font00/I<350>"
        funcOneMessage(mswk10533)
        be:DMsetLua("treasure05.lua")
        be:DMrun()
        be:FLGset(419, 1)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(396) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10534 = "TALKFONT02/font00/I<351>"
        funcOneMessage(mswk10534)
        mswk10535 = "TALKFONT02/font00/I<352>"
        funcOneMessage(mswk10535)
        mswk10536 = "TALKFONT02/font00/I<353>"
        funcOneMessage(mswk10536)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10537 = "TALKFONT02/font00/I<344>"
        funcOneMessage(mswk10537)
        mswk10538 = "TALKFONT02/font00/I<345>"
        funcOneMessage(mswk10538)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10539 = "TALKFONT02/font00/I<346>"
        funcOneMessage(mswk10539)
        mswk10540 = "TALKFONT02/font00/I<347>"
        funcOneMessage(mswk10540)
        be:DMsetLua("bML01025.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(380) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10541 = "TALKFONT02/font00/I<346>"
        funcOneMessage(mswk10541)
        mswk10542 = "TALKFONT02/font00/I<347>"
        funcOneMessage(mswk10542)
        be:DMsetLua("bML01026.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(380) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10543 = "TALKFONT02/font00/I<348>"
        funcOneMessage(mswk10543)
        be:DMsetLua("bML01027.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(419) == 1 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10544 = "TALKFONT02/font00/I<349>"
        funcOneMessage(mswk10544)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 1 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10545 = "TALKFONT02/font00/I<350>"
        funcOneMessage(mswk10545)
        be:DMsetLua("treasure05.lua")
        be:DMrun()
        be:FLGset(419, 1)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(399) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10546 = "TALKFONT02/font00/I<351>"
        funcOneMessage(mswk10546)
        mswk10547 = "TALKFONT02/font00/I<352>"
        funcOneMessage(mswk10547)
        mswk10548 = "TALKFONT02/font00/I<353>"
        funcOneMessage(mswk10548)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10549 = "TALKFONT02/font00/I<344>"
        funcOneMessage(mswk10549)
        mswk10550 = "TALKFONT02/font00/I<345>"
        funcOneMessage(mswk10550)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10551 = "TALKFONT02/font00/I<346>"
        funcOneMessage(mswk10551)
        mswk10552 = "TALKFONT02/font00/I<347>"
        funcOneMessage(mswk10552)
        be:DMsetLua("bML01025.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(380) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10553 = "TALKFONT02/font00/I<346>"
        funcOneMessage(mswk10553)
        mswk10554 = "TALKFONT02/font00/I<347>"
        funcOneMessage(mswk10554)
        be:DMsetLua("bML01026.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(380) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10555 = "TALKFONT02/font00/I<348>"
        funcOneMessage(mswk10555)
        be:DMsetLua("bML01027.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(419) == 1 and be:FLGisOn(388) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10556 = "TALKFONT02/font00/I<354>"
        funcOneMessage(mswk10556)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(419) == 0 and be:FLGisOn(388) == 1 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10557 = "TALKFONT02/font00/I<350>"
        funcOneMessage(mswk10557)
        be:DMsetLua("treasure05.lua")
        be:DMrun()
        be:FLGset(419, 1)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(93) == 1 and be:FLGisOn(402) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10558 = "TALKFONT02/font00/I<351>"
        funcOneMessage(mswk10558)
        mswk10559 = "TALKFONT02/font00/I<352>"
        funcOneMessage(mswk10559)
        mswk10560 = "TALKFONT02/font00/I<353>"
        funcOneMessage(mswk10560)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(3) == 1 and be:FLGisOn(93) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10561 = "TALKFONT02/font00/I<355>"
        funcOneMessage(mswk10561)
        mswk10562 = "TALKFONT02/font00/I<356>"
        funcOneMessage(mswk10562)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
