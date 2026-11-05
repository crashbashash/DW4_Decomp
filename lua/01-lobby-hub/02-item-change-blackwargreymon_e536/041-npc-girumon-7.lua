g_SItemDB = 0
funcOpenMessage("talk", "n_girumon", "M")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61582 = "TALKFONT02/font00/I<331>"
    funcOneMessage(mswk61582)
    mswk61583 = "TALKFONT02/font00/I<292>"
    funcOneMessage(mswk61583)
    mswk61584 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61584)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 75
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 0, 0, 0) == 1 then
    mswk61585 = "TALKFONT02/font00/I<332>"
    funcOneMessage(mswk61585)
    mswk61586 = "TALKFONT02/font00/I<333>"
    funcOneMessage(mswk61586)
    mswk61587 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61587)
    g_SItemDB = "weapon"
    g_SItemID = 0
    g_TItemDB = "weapon"
    g_TItemID = 202
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 25, 0, 0) == 1 then
    mswk61588 = "TALKFONT02/font00/I<334>"
    funcOneMessage(mswk61588)
    mswk61589 = "TALKFONT02/font00/I<335>"
    funcOneMessage(mswk61589)
    mswk61590 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61590)
    g_SItemDB = "weapon"
    g_SItemID = 25
    g_TItemDB = "weapon"
    g_TItemID = 102
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 1 then
    mswk61591 = "TALKFONT02/font00/I<336>"
    funcOneMessage(mswk61591)
    mswk61592 = "TALKFONT02/font00/I<337>"
    funcOneMessage(mswk61592)
    mswk61593 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61593)
    g_SItemDB = "weapon"
    g_SItemID = 200
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 135, 0, 0) == 1 then
    mswk61594 = "TALKFONT02/font00/I<338>"
    funcOneMessage(mswk61594)
    mswk61595 = "TALKFONT02/font00/I<339>"
    funcOneMessage(mswk61595)
    mswk61596 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61596)
    g_SItemDB = "weapon"
    g_SItemID = 135
    g_TItemDB = "weapon"
    g_TItemID = 203
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 60, 0, 0) == 1 then
    mswk61597 = "TALKFONT02/font00/I<340>"
    funcOneMessage(mswk61597)
    mswk61598 = "TALKFONT02/font00/I<299>"
    funcOneMessage(mswk61598)
    mswk61599 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61599)
    g_SItemDB = "weapon"
    g_SItemID = 60
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 227, 0, 0) == 1 then
    mswk61600 = "TALKFONT02/font00/I<341>"
    funcOneMessage(mswk61600)
    mswk61601 = "TALKFONT02/font00/I<342>"
    funcOneMessage(mswk61601)
    mswk61602 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61602)
    g_SItemDB = "weapon"
    g_SItemID = 227
    g_TItemDB = "armor1"
    g_TItemID = 19
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 77, 0, 0) == 1 then
    mswk61603 = "TALKFONT02/font00/I<340>"
    funcOneMessage(mswk61603)
    mswk61604 = "TALKFONT02/font00/I<343>"
    funcOneMessage(mswk61604)
    mswk61605 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61605)
    g_SItemDB = "weapon"
    g_SItemID = 77
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 53, 0, 0) == 1 then
    mswk61606 = "TALKFONT02/font00/I<344>"
    funcOneMessage(mswk61606)
    mswk61607 = "TALKFONT02/font00/I<309>"
    funcOneMessage(mswk61607)
    mswk61608 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61608)
    g_SItemDB = "weapon"
    g_SItemID = 53
    g_TItemDB = "weapon"
    g_TItemID = 174
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 103, 0, 0) == 1 then
    mswk61609 = "TALKFONT02/font00/I<345>"
    funcOneMessage(mswk61609)
    mswk61610 = "TALKFONT02/font00/I<346>"
    funcOneMessage(mswk61610)
    mswk61611 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61611)
    g_SItemDB = "weapon"
    g_SItemID = 103
    g_TItemDB = "weapon"
    g_TItemID = 29
else
    mswk61612 = "TALKFONT02/font00/I<310>"
    funcOneMessage(mswk61612)
    mswk61613 = "TALKFONT02/font00/I<311>"
    funcOneMessage(mswk61613)
    funcCloseMessage("talk", "n_girumon", "M")
end
if g_SItemDB ~= 0 then
    mswk61614 = "TALKFONT02/font01/I<71>"
    mswk61615 = "TALKFONT02/font02/I<72>"
    mswk61616 = "TALKFONT02/font00/I<312>"
    mswk61617 = "TALKFONT02/font00/I<313>"
    funcChoiceMessage(mswk61614, mswk61615)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61616)
    be:DMsetLua("itemchange78.lua")
    be:DMcase(1)
    funcOneMessage(mswk61617)
    funcCloseMessage("talk", "n_girumon", "M")
    be:DMswtEnd()
end
be:DMrun()
