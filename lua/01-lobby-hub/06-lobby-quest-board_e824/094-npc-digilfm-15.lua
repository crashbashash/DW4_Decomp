be:FLGset(908, 0)
if be:SYSgetPlayerLevel(0) >= 16 then
    be:FLGset(908, 1)
end
be:FLGset(909, 0)
if be:SYSgetPlayerLevel(0) >= 46 then
    be:FLGset(909, 1)
end
be:FLGset(910, 0)
if be:SYSgetPlayerLevel(0) >= 76 then
    be:FLGset(910, 1)
end
if be:FLGisOn(97) == 1 and be:FLGisOn(908) == 0 and be:FLGisOn(86) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10691 = "TALKFONT02/font00/I<401>"
        funcOneMessage(mswk10691)
        mswk10692 = "TALKFONT02/font00/I<402>"
        funcOneMessage(mswk10692)
        mswk10693 = "TALKFONT02/font00/I<403>"
        funcOneMessage(mswk10693)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(97) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(909) == 0 and be:FLGisOn(86) == 0 then
    if be:FLGisOn(368) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10694 = "TALKFONT02/font00/I<404>"
        funcOneMessage(mswk10694)
        mswk10695 = "TALKFONT02/font00/I<405>"
        funcOneMessage(mswk10695)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(368) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10696 = "TALKFONT02/font00/I<406>"
        funcOneMessage(mswk10696)
        mswk10697 = "TALKFONT02/font00/I<407>"
        funcOneMessage(mswk10697)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(97) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(910) == 0 and be:FLGisOn(86) == 0 then
    if be:FLGisOn(368) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10698 = "TALKFONT02/font00/I<408>"
        funcOneMessage(mswk10698)
        mswk10699 = "TALKFONT02/font00/I<409>"
        funcOneMessage(mswk10699)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(368) == 1 and be:FLGisOn(369) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10700 = "TALKFONT02/font00/I<410>"
        funcOneMessage(mswk10700)
        mswk10701 = "TALKFONT02/font00/I<411>"
        funcOneMessage(mswk10701)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(368) == 1 and be:FLGisOn(369) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10702 = "TALKFONT02/font00/I<406>"
        funcOneMessage(mswk10702)
        mswk10703 = "TALKFONT02/font00/I<407>"
        funcOneMessage(mswk10703)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(97) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(86) == 0 and 1 == 1 then
    if be:FLGisOn(368) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10704 = "TALKFONT02/font00/I<408>"
        funcOneMessage(mswk10704)
        mswk10705 = "TALKFONT02/font00/I<409>"
        funcOneMessage(mswk10705)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(368) == 1 and be:FLGisOn(369) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10706 = "TALKFONT02/font00/I<410>"
        funcOneMessage(mswk10706)
        mswk10707 = "TALKFONT02/font00/I<411>"
        funcOneMessage(mswk10707)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(368) == 1 and be:FLGisOn(369) == 1 and be:FLGisOn(370) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10708 = "TALKFONT02/font00/I<412>"
        funcOneMessage(mswk10708)
        mswk10709 = "TALKFONT02/font00/I<413>"
        funcOneMessage(mswk10709)
        mswk10710 = "TALKFONT02/font00/I<414>"
        funcOneMessage(mswk10710)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(368) == 1 and be:FLGisOn(369) == 1 and be:FLGisOn(370) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10711 = "TALKFONT02/font00/I<406>"
        funcOneMessage(mswk10711)
        mswk10712 = "TALKFONT02/font00/I<407>"
        funcOneMessage(mswk10712)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(97) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(86) == 1 then
    if be:FLGisOn(374) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10713 = "TALKFONT02/font00/I<415>"
        funcOneMessage(mswk10713)
        mswk10714 = "TALKFONT02/font00/I<416>"
        funcOneMessage(mswk10714)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(374, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10715 = "TALKFONT02/font00/I<408>"
        funcOneMessage(mswk10715)
        mswk10716 = "TALKFONT02/font00/I<409>"
        funcOneMessage(mswk10716)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 1 and be:FLGisOn(369) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10717 = "TALKFONT02/font00/I<410>"
        funcOneMessage(mswk10717)
        mswk10718 = "TALKFONT02/font00/I<411>"
        funcOneMessage(mswk10718)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 1 and be:FLGisOn(369) == 1 and be:FLGisOn(370) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10719 = "TALKFONT02/font00/I<412>"
        funcOneMessage(mswk10719)
        mswk10720 = "TALKFONT02/font00/I<413>"
        funcOneMessage(mswk10720)
        mswk10721 = "TALKFONT02/font00/I<414>"
        funcOneMessage(mswk10721)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 1 and be:FLGisOn(369) == 1 and be:FLGisOn(370) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10722 = "TALKFONT02/font00/I<406>"
        funcOneMessage(mswk10722)
        mswk10723 = "TALKFONT02/font00/I<407>"
        funcOneMessage(mswk10723)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(97) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(909) == 0 and be:FLGisOn(86) == 1 then
    if be:FLGisOn(374) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10724 = "TALKFONT02/font00/I<415>"
        funcOneMessage(mswk10724)
        mswk10725 = "TALKFONT02/font00/I<417>"
        funcOneMessage(mswk10725)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(374, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10726 = "TALKFONT02/font00/I<408>"
        funcOneMessage(mswk10726)
        mswk10727 = "TALKFONT02/font00/I<409>"
        funcOneMessage(mswk10727)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10728 = "TALKFONT02/font00/I<406>"
        funcOneMessage(mswk10728)
        mswk10729 = "TALKFONT02/font00/I<407>"
        funcOneMessage(mswk10729)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(0, 0)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(97) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(910) == 0 and be:FLGisOn(86) == 1 then
    if be:FLGisOn(374) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10730 = "TALKFONT02/font00/I<415>"
        funcOneMessage(mswk10730)
        mswk10731 = "TALKFONT02/font00/I<416>"
        funcOneMessage(mswk10731)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(374, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10732 = "TALKFONT02/font00/I<408>"
        funcOneMessage(mswk10732)
        mswk10733 = "TALKFONT02/font00/I<409>"
        funcOneMessage(mswk10733)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 1 and be:FLGisOn(369) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10734 = "TALKFONT02/font00/I<410>"
        funcOneMessage(mswk10734)
        mswk10735 = "TALKFONT02/font00/I<411>"
        funcOneMessage(mswk10735)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(63, 1)
    elseif be:FLGisOn(374) == 1 and be:FLGisOn(368) == 1 and be:FLGisOn(369) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10736 = "TALKFONT02/font00/I<406>"
        funcOneMessage(mswk10736)
        mswk10737 = "TALKFONT02/font00/I<407>"
        funcOneMessage(mswk10737)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
