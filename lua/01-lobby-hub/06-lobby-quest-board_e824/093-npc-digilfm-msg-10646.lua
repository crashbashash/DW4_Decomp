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
if be:FLGisOn(440) == 1 and be:FLGisOn(441) == 1 and be:FLGisOn(442) == 1 and be:FLGisOn(443) == 1 and be:FLGisOn(444) == 1 and be:FLGisOn(445) == 1 and be:FLGisOn(446) == 1 then
    be:FLGset(930, 1)
else
    be:FLGset(930, 0)
end
if be:FLGisOn(433) == 1 and be:FLGisOn(434) == 1 and be:FLGisOn(435) == 1 and be:FLGisOn(436) == 1 and be:FLGisOn(437) == 1 and be:FLGisOn(438) == 1 and be:FLGisOn(439) == 1 then
    be:FLGset(929, 1)
else
    be:FLGset(929, 0)
end
if be:FLGisOn(426) == 1 and be:FLGisOn(427) == 1 and be:FLGisOn(428) == 1 and be:FLGisOn(429) == 1 and be:FLGisOn(430) == 1 and be:FLGisOn(431) == 1 and be:FLGisOn(432) == 1 then
    be:FLGset(928, 1)
else
    be:FLGset(928, 0)
end
be:FLGset(934, 0)
if g_messPlayerNo == 0 then
    be:FLGset(934, 1)
end
if be:FLGisOn(931) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(928) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10646 = "TALKFONT02/font00/I<386>"
        funcOneMessage(mswk10646)
        mswk10647 = "TALKFONT02/font00/I<387>"
        funcOneMessage(mswk10647)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(928) == 1 then
    if be:FLGisOn(470) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10648 = "TALKFONT02/font00/I<388>"
        funcOneMessage(mswk10648)
        mswk10649 = "TALKFONT02/font00/I<389>"
        funcOneMessage(mswk10649)
        mswk10650 = "TALKFONT02/font00/I<390>"
        funcOneMessage(mswk10650)
        mswk10651 = "TALKFONT02/font00/I<391>"
        funcOneMessage(mswk10651)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(470, 1)
    elseif be:FLGisOn(470) == 1 and be:FLGisOn(448) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10652 = "TALKFONT02/font00/I<392>"
        funcOneMessage(mswk10652)
        mswk10653 = "TALKFONT02/font00/I<393>"
        funcOneMessage(mswk10653)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(470) == 1 and be:FLGisOn(448) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10654 = "TALKFONT02/font00/I<394>"
        funcOneMessage(mswk10654)
        mswk10655 = "TALKFONT02/font00/I<395>"
        funcOneMessage(mswk10655)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(470) == 1 and be:FLGisOn(448) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(476) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10656 = "TALKFONT02/font00/I<396>"
        funcOneMessage(mswk10656)
        mswk10657 = "TALKFONT02/font00/I<397>"
        funcOneMessage(mswk10657)
        mswk10658 = "TALKFONT02/font00/I<398>"
        funcOneMessage(mswk10658)
        be:DMsetLua("treasure08.lua")
        be:DMrun()
    elseif be:FLGisOn(470) == 1 and be:FLGisOn(448) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(476) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10659 = "TALKFONT02/font00/I<399>"
        funcOneMessage(mswk10659)
        mswk10660 = "TALKFONT02/font00/I<400>"
        funcOneMessage(mswk10660)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(929) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10661 = "TALKFONT02/font00/I<386>"
        funcOneMessage(mswk10661)
        mswk10662 = "TALKFONT02/font00/I<387>"
        funcOneMessage(mswk10662)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(929) == 1 then
    if be:FLGisOn(472) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10663 = "TALKFONT02/font00/I<388>"
        funcOneMessage(mswk10663)
        mswk10664 = "TALKFONT02/font00/I<389>"
        funcOneMessage(mswk10664)
        mswk10665 = "TALKFONT02/font00/I<390>"
        funcOneMessage(mswk10665)
        mswk10666 = "TALKFONT02/font00/I<391>"
        funcOneMessage(mswk10666)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(472, 1)
    elseif be:FLGisOn(472) == 1 and be:FLGisOn(450) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10667 = "TALKFONT02/font00/I<392>"
        funcOneMessage(mswk10667)
        mswk10668 = "TALKFONT02/font00/I<393>"
        funcOneMessage(mswk10668)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(472) == 1 and be:FLGisOn(450) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10669 = "TALKFONT02/font00/I<394>"
        funcOneMessage(mswk10669)
        mswk10670 = "TALKFONT02/font00/I<395>"
        funcOneMessage(mswk10670)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(472) == 1 and be:FLGisOn(450) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(478) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10671 = "TALKFONT02/font00/I<396>"
        funcOneMessage(mswk10671)
        mswk10672 = "TALKFONT02/font00/I<397>"
        funcOneMessage(mswk10672)
        mswk10673 = "TALKFONT02/font00/I<398>"
        funcOneMessage(mswk10673)
        be:DMsetLua("treasure08.lua")
        be:DMrun()
    elseif be:FLGisOn(472) == 1 and be:FLGisOn(450) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(478) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10674 = "TALKFONT02/font00/I<399>"
        funcOneMessage(mswk10674)
        mswk10675 = "TALKFONT02/font00/I<400>"
        funcOneMessage(mswk10675)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(930) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10676 = "TALKFONT02/font00/I<386>"
        funcOneMessage(mswk10676)
        mswk10677 = "TALKFONT02/font00/I<387>"
        funcOneMessage(mswk10677)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(96) == 1 and be:FLGisOn(930) == 1 then
    if be:FLGisOn(474) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10678 = "TALKFONT02/font00/I<388>"
        funcOneMessage(mswk10678)
        mswk10679 = "TALKFONT02/font00/I<389>"
        funcOneMessage(mswk10679)
        mswk10680 = "TALKFONT02/font00/I<390>"
        funcOneMessage(mswk10680)
        mswk10681 = "TALKFONT02/font00/I<391>"
        funcOneMessage(mswk10681)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(474, 1)
    elseif be:FLGisOn(474) == 1 and be:FLGisOn(452) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10682 = "TALKFONT02/font00/I<392>"
        funcOneMessage(mswk10682)
        mswk10683 = "TALKFONT02/font00/I<393>"
        funcOneMessage(mswk10683)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(474) == 1 and be:FLGisOn(452) == 1 and be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10684 = "TALKFONT02/font00/I<394>"
        funcOneMessage(mswk10684)
        mswk10685 = "TALKFONT02/font00/I<395>"
        funcOneMessage(mswk10685)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(474) == 1 and be:FLGisOn(452) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(480) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10686 = "TALKFONT02/font00/I<396>"
        funcOneMessage(mswk10686)
        mswk10687 = "TALKFONT02/font00/I<397>"
        funcOneMessage(mswk10687)
        mswk10688 = "TALKFONT02/font00/I<398>"
        funcOneMessage(mswk10688)
        be:DMsetLua("treasure08.lua")
        be:DMrun()
    elseif be:FLGisOn(474) == 1 and be:FLGisOn(452) == 1 and be:FLGisOn(934) == 1 and be:FLGisOn(480) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10689 = "TALKFONT02/font00/I<399>"
        funcOneMessage(mswk10689)
        mswk10690 = "TALKFONT02/font00/I<400>"
        funcOneMessage(mswk10690)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
