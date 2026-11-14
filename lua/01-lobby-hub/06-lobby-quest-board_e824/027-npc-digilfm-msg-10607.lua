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
if be:FLGisOn(931) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10607 = "TALKFONT02/font00/I<373>"
        funcOneMessage(mswk10607)
        mswk10608 = "TALKFONT02/font00/I<374>"
        funcOneMessage(mswk10608)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 1 then
    if be:FLGisOn(469) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10609 = "TALKFONT02/font00/I<375>"
        funcOneMessage(mswk10609)
        mswk10610 = "TALKFONT02/font00/I<376>"
        funcOneMessage(mswk10610)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(469, 1)
    elseif be:FLGisOn(469) == 1 and be:FLGisOn(447) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10611 = "TALKFONT02/font00/I<377>"
        funcOneMessage(mswk10611)
        mswk10612 = "TALKFONT02/font00/I<378>"
        funcOneMessage(mswk10612)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(469) == 1 and be:FLGisOn(447) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10613 = "TALKFONT02/font00/I<379>"
        funcOneMessage(mswk10613)
        mswk10614 = "TALKFONT02/font00/I<380>"
        funcOneMessage(mswk10614)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(469) == 1 and be:FLGisOn(447) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(475) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10615 = "TALKFONT02/font00/I<381>"
        funcOneMessage(mswk10615)
        mswk10616 = "TALKFONT02/font00/I<382>"
        funcOneMessage(mswk10616)
        mswk10617 = "TALKFONT02/font00/I<383>"
        funcOneMessage(mswk10617)
        be:DMsetLua("treasure07.lua")
        be:DMrun()
    elseif be:FLGisOn(469) == 1 and be:FLGisOn(447) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(475) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10618 = "TALKFONT02/font00/I<384>"
        funcOneMessage(mswk10618)
        mswk10619 = "TALKFONT02/font00/I<385>"
        funcOneMessage(mswk10619)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10620 = "TALKFONT02/font00/I<373>"
        funcOneMessage(mswk10620)
        mswk10621 = "TALKFONT02/font00/I<374>"
        funcOneMessage(mswk10621)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 1 then
    if be:FLGisOn(471) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10622 = "TALKFONT02/font00/I<375>"
        funcOneMessage(mswk10622)
        mswk10623 = "TALKFONT02/font00/I<376>"
        funcOneMessage(mswk10623)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(471, 1)
    elseif be:FLGisOn(471) == 1 and be:FLGisOn(449) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10624 = "TALKFONT02/font00/I<377>"
        funcOneMessage(mswk10624)
        mswk10625 = "TALKFONT02/font00/I<378>"
        funcOneMessage(mswk10625)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(471) == 1 and be:FLGisOn(449) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10626 = "TALKFONT02/font00/I<379>"
        funcOneMessage(mswk10626)
        mswk10627 = "TALKFONT02/font00/I<380>"
        funcOneMessage(mswk10627)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(471) == 1 and be:FLGisOn(449) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(477) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10628 = "TALKFONT02/font00/I<381>"
        funcOneMessage(mswk10628)
        mswk10629 = "TALKFONT02/font00/I<382>"
        funcOneMessage(mswk10629)
        mswk10630 = "TALKFONT02/font00/I<383>"
        funcOneMessage(mswk10630)
        be:DMsetLua("treasure07.lua")
        be:DMrun()
    elseif be:FLGisOn(471) == 1 and be:FLGisOn(449) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(477) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10631 = "TALKFONT02/font00/I<384>"
        funcOneMessage(mswk10631)
        mswk10632 = "TALKFONT02/font00/I<385>"
        funcOneMessage(mswk10632)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10633 = "TALKFONT02/font00/I<373>"
        funcOneMessage(mswk10633)
        mswk10634 = "TALKFONT02/font00/I<374>"
        funcOneMessage(mswk10634)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(95) == 1 and be:FLGisOn(70) == 1 then
    if be:FLGisOn(473) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10635 = "TALKFONT02/font00/I<375>"
        funcOneMessage(mswk10635)
        mswk10636 = "TALKFONT02/font00/I<376>"
        funcOneMessage(mswk10636)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(473, 1)
    elseif be:FLGisOn(473) == 1 and be:FLGisOn(451) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10637 = "TALKFONT02/font00/I<377>"
        funcOneMessage(mswk10637)
        mswk10638 = "TALKFONT02/font00/I<378>"
        funcOneMessage(mswk10638)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(473) == 1 and be:FLGisOn(451) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10639 = "TALKFONT02/font00/I<379>"
        funcOneMessage(mswk10639)
        mswk10640 = "TALKFONT02/font00/I<380>"
        funcOneMessage(mswk10640)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(473) == 1 and be:FLGisOn(451) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(479) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10641 = "TALKFONT02/font00/I<381>"
        funcOneMessage(mswk10641)
        mswk10642 = "TALKFONT02/font00/I<382>"
        funcOneMessage(mswk10642)
        mswk10643 = "TALKFONT02/font00/I<383>"
        funcOneMessage(mswk10643)
        be:DMsetLua("treasure07.lua")
        be:DMrun()
    elseif be:FLGisOn(473) == 1 and be:FLGisOn(451) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(479) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10644 = "TALKFONT02/font00/I<384>"
        funcOneMessage(mswk10644)
        mswk10645 = "TALKFONT02/font00/I<385>"
        funcOneMessage(mswk10645)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
