g_SItemDB = 0
funcOpenMessage("talk", "n_weregaru", "[K")
if be:SYSctlDeviceFolder("IS", 0, "weapon", 25, 0, 0) == 1 then
    mswk61677 = "TALKFONT02/font00/I<479>"
    funcOneMessage(mswk61677)
    mswk61678 = "TALKFONT02/font00/I<480>"
    funcOneMessage(mswk61678)
    g_SItemDB = "weapon"
    g_SItemID = 25
    g_TItemDB = "weapon"
    g_TItemID = 127
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 50, 0, 0) == 1 then
    mswk61679 = "TALKFONT02/font00/I<481>"
    funcOneMessage(mswk61679)
    mswk61680 = "TALKFONT02/font00/I<458>"
    funcOneMessage(mswk61680)
    g_SItemDB = "weapon"
    g_SItemID = 50
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 1 then
    mswk61681 = "TALKFONT02/font00/I<482>"
    funcOneMessage(mswk61681)
    mswk61682 = "TALKFONT02/font00/I<483>"
    funcOneMessage(mswk61682)
    g_SItemDB = "weapon"
    g_SItemID = 200
    g_TItemDB = "weapon"
    g_TItemID = 3
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 135, 0, 0) == 1 then
    mswk61683 = "TALKFONT02/font00/I<484>"
    funcOneMessage(mswk61683)
    mswk61684 = "TALKFONT02/font00/I<485>"
    funcOneMessage(mswk61684)
    g_SItemDB = "weapon"
    g_SItemID = 135
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 202, 0, 0) == 1 then
    mswk61685 = "TALKFONT02/font00/I<486>"
    funcOneMessage(mswk61685)
    mswk61686 = "TALKFONT02/font00/I<487>"
    funcOneMessage(mswk61686)
    g_SItemDB = "weapon"
    g_SItemID = 202
    g_TItemDB = "armor1"
    g_TItemID = 15
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 27, 0, 0) == 1 then
    mswk61687 = "TALKFONT02/font00/I<488>"
    funcOneMessage(mswk61687)
    mswk61688 = "TALKFONT02/font00/I<485>"
    funcOneMessage(mswk61688)
    g_SItemDB = "weapon"
    g_SItemID = 27
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 152, 0, 0) == 1 then
    mswk61689 = "TALKFONT02/font00/I<489>"
    funcOneMessage(mswk61689)
    mswk61690 = "TALKFONT02/font00/I<490>"
    funcOneMessage(mswk61690)
    g_SItemDB = "weapon"
    g_SItemID = 152
    g_TItemDB = "armor1"
    g_TItemID = 24
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 203, 0, 0) == 1 then
    mswk61691 = "TALKFONT02/font00/I<491>"
    funcOneMessage(mswk61691)
    mswk61692 = "TALKFONT02/font00/I<492>"
    funcOneMessage(mswk61692)
    g_SItemDB = "weapon"
    g_SItemID = 203
    g_TItemDB = "weapon"
    g_TItemID = 29
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 29, 0, 0) == 1 then
    mswk61693 = "TALKFONT02/font00/I<493>"
    funcOneMessage(mswk61693)
    mswk61694 = "TALKFONT02/font00/I<494>"
    funcOneMessage(mswk61694)
    g_SItemDB = "weapon"
    g_SItemID = 29
    g_TItemDB = "armor2"
    g_TItemID = 29
else
    mswk61695 = "TALKFONT02/font00/I<475>"
    funcOneMessage(mswk61695)
    mswk61696 = "TALKFONT02/font00/I<476>"
    funcOneMessage(mswk61696)
    funcCloseMessage("talk", "n_weregaru", "[K")
end
if g_SItemDB ~= 0 then
    mswk61697 = "TALKFONT02/font01/I<71>"
    mswk61698 = "TALKFONT02/font02/I<72>"
    mswk61699 = "TALKFONT02/font00/I<477>"
    mswk61700 = "TALKFONT02/font00/I<478>"
    funcChoiceMessage(mswk61697, mswk61698)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61699)
    be:DMsetLua("itemchange135.lua")
    be:DMcase(1)
    funcOneMessage(mswk61700)
    funcCloseMessage("talk", "n_weregaru", "[K")
    be:DMswtEnd()
end
be:DMrun()
