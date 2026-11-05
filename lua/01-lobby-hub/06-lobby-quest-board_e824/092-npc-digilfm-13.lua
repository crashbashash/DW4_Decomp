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
be:FLGset(934, 0)
if g_messPlayerNo == 0 then
    be:FLGset(934, 1)
end
if be:FLGisOn(931) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10563 = "TALKFONT02/font00/I<357>"
        funcOneMessage(mswk10563)
        mswk10564 = "TALKFONT02/font00/I<358>"
        funcOneMessage(mswk10564)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10565 = "TALKFONT02/font00/I<359>"
        funcOneMessage(mswk10565)
        mswk10566 = "TALKFONT02/font00/I<360>"
        funcOneMessage(mswk10566)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(381) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10567 = "TALKFONT02/font00/I<361>"
        funcOneMessage(mswk10567)
        mswk10568 = "TALKFONT02/font00/I<362>"
        funcOneMessage(mswk10568)
        mswk10569 = "TALKFONT02/font00/I<363>"
        funcOneMessage(mswk10569)
        be:DMsetLua("bML01032.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(381) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10570 = "TALKFONT02/font00/I<364>"
        funcOneMessage(mswk10570)
        mswk10571 = "TALKFONT02/font00/I<365>"
        funcOneMessage(mswk10571)
        be:DMsetLua("bML01034.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 1 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10572 = "TALKFONT02/font00/I<366>"
        funcOneMessage(mswk10572)
        mswk10573 = "TALKFONT02/font00/I<367>"
        funcOneMessage(mswk10573)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10574 = "TALKFONT02/font00/I<368>"
        funcOneMessage(mswk10574)
        be:DMsetLua("treasure06.lua")
        be:DMrun()
        be:FLGset(420, 1)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10575 = "TALKFONT02/font00/I<369>"
        funcOneMessage(mswk10575)
        mswk10576 = "TALKFONT02/font00/I<370>"
        funcOneMessage(mswk10576)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10577 = "TALKFONT02/font00/I<357>"
        funcOneMessage(mswk10577)
        mswk10578 = "TALKFONT02/font00/I<358>"
        funcOneMessage(mswk10578)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10579 = "TALKFONT02/font00/I<359>"
        funcOneMessage(mswk10579)
        mswk10580 = "TALKFONT02/font00/I<360>"
        funcOneMessage(mswk10580)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(381) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10581 = "TALKFONT02/font00/I<361>"
        funcOneMessage(mswk10581)
        mswk10582 = "TALKFONT02/font00/I<362>"
        funcOneMessage(mswk10582)
        mswk10583 = "TALKFONT02/font00/I<363>"
        funcOneMessage(mswk10583)
        be:DMsetLua("bML01032.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(381) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10584 = "TALKFONT02/font00/I<364>"
        funcOneMessage(mswk10584)
        mswk10585 = "TALKFONT02/font00/I<365>"
        funcOneMessage(mswk10585)
        be:DMsetLua("bML01034.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 1 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10586 = "TALKFONT02/font00/I<366>"
        funcOneMessage(mswk10586)
        mswk10587 = "TALKFONT02/font00/I<367>"
        funcOneMessage(mswk10587)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10588 = "TALKFONT02/font00/I<368>"
        funcOneMessage(mswk10588)
        be:DMsetLua("treasure06.lua")
        be:DMrun()
        be:FLGset(420, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10589 = "TALKFONT02/font00/I<369>"
        funcOneMessage(mswk10589)
        mswk10590 = "TALKFONT02/font00/I<370>"
        funcOneMessage(mswk10590)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10591 = "TALKFONT02/font00/I<357>"
        funcOneMessage(mswk10591)
        mswk10592 = "TALKFONT02/font00/I<358>"
        funcOneMessage(mswk10592)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10593 = "TALKFONT02/font00/I<359>"
        funcOneMessage(mswk10593)
        mswk10594 = "TALKFONT02/font00/I<360>"
        funcOneMessage(mswk10594)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(381) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10595 = "TALKFONT02/font00/I<361>"
        funcOneMessage(mswk10595)
        mswk10596 = "TALKFONT02/font00/I<362>"
        funcOneMessage(mswk10596)
        mswk10597 = "TALKFONT02/font00/I<363>"
        funcOneMessage(mswk10597)
        be:DMsetLua("bML01032.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(381) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10598 = "TALKFONT02/font00/I<364>"
        funcOneMessage(mswk10598)
        mswk10599 = "TALKFONT02/font00/I<365>"
        funcOneMessage(mswk10599)
        be:DMsetLua("bML01034.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 1 and be:FLGisOn(389) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10600 = "TALKFONT02/font00/I<366>"
        funcOneMessage(mswk10600)
        mswk10601 = "TALKFONT02/font00/I<367>"
        funcOneMessage(mswk10601)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(94) == 1 and be:FLGisOn(420) == 0 and be:FLGisOn(389) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10602 = "TALKFONT02/font00/I<368>"
        funcOneMessage(mswk10602)
        be:DMsetLua("treasure06.lua")
        be:DMrun()
        be:FLGset(420, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10603 = "TALKFONT02/font00/I<369>"
        funcOneMessage(mswk10603)
        mswk10604 = "TALKFONT02/font00/I<370>"
        funcOneMessage(mswk10604)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(3) == 1 and be:FLGisOn(94) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10605 = "TALKFONT02/font00/I<371>"
        funcOneMessage(mswk10605)
        mswk10606 = "TALKFONT02/font00/I<372>"
        funcOneMessage(mswk10606)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
