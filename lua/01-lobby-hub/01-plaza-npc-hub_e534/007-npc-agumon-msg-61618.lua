g_SItemDB = 0
funcOpenMessage("talk", "n_agumon", "AO")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61618 = "TALKFONT02/font00/I<109>"
    funcOneMessage(mswk61618)
    mswk61619 = "TALKFONT02/font00/I<149>"
    funcOneMessage(mswk61619)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 200
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 175, 0, 0) == 1 then
    mswk61620 = "TALKFONT02/font00/I<150>"
    funcOneMessage(mswk61620)
    mswk61621 = "TALKFONT02/font00/I<151>"
    funcOneMessage(mswk61621)
    g_SItemDB = "weapon"
    g_SItemID = 175
    g_TItemDB = "weapon"
    g_TItemID = 2
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 0, 0, 0) == 1 then
    mswk61622 = "TALKFONT02/font00/I<152>"
    funcOneMessage(mswk61622)
    mswk61623 = "TALKFONT02/font00/I<153>"
    funcOneMessage(mswk61623)
    g_SItemDB = "weapon"
    g_SItemID = 0
    g_TItemDB = "weapon"
    g_TItemID = 27
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 75, 0, 0) == 1 then
    mswk61624 = "TALKFONT02/font00/I<154>"
    funcOneMessage(mswk61624)
    mswk61625 = "TALKFONT02/font00/I<155>"
    funcOneMessage(mswk61625)
    g_SItemDB = "weapon"
    g_SItemID = 75
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 160, 0, 0) == 1 then
    mswk61626 = "TALKFONT02/font00/I<156>"
    funcOneMessage(mswk61626)
    mswk61627 = "TALKFONT02/font00/I<157>"
    funcOneMessage(mswk61627)
    g_SItemDB = "weapon"
    g_SItemID = 160
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 177, 0, 0) == 1 then
    mswk61628 = "TALKFONT02/font00/I<158>"
    funcOneMessage(mswk61628)
    mswk61629 = "TALKFONT02/font00/I<159>"
    funcOneMessage(mswk61629)
    g_SItemDB = "weapon"
    g_SItemID = 177
    g_TItemDB = "weapon"
    g_TItemID = 52
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 24, 0, 0) == 1 then
    mswk61630 = "TALKFONT02/font00/I<160>"
    funcOneMessage(mswk61630)
    mswk61631 = "TALKFONT02/font00/I<161>"
    funcOneMessage(mswk61631)
    g_SItemDB = "armor1"
    g_SItemID = 24
    g_TItemDB = "weapon"
    g_TItemID = 99
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 102, 0, 0) == 1 then
    mswk61632 = "TALKFONT02/font00/I<162>"
    funcOneMessage(mswk61632)
    mswk61633 = "TALKFONT02/font00/I<163>"
    funcOneMessage(mswk61633)
    g_SItemDB = "weapon"
    g_SItemID = 102
    g_TItemDB = "armor1"
    g_TItemID = 1
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 127, 0, 0) == 1 then
    mswk61634 = "TALKFONT02/font00/I<164>"
    funcOneMessage(mswk61634)
    mswk61635 = "TALKFONT02/font00/I<157>"
    funcOneMessage(mswk61635)
    g_SItemDB = "weapon"
    g_SItemID = 127
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 178, 0, 0) == 1 then
    mswk61636 = "TALKFONT02/font00/I<165>"
    funcOneMessage(mswk61636)
    mswk61637 = "TALKFONT02/font00/I<166>"
    funcOneMessage(mswk61637)
    g_SItemDB = "weapon"
    g_SItemID = 178
    g_TItemDB = "weapon"
    g_TItemID = 24
else
    mswk61638 = "TALKFONT02/font00/I<127>"
    funcOneMessage(mswk61638)
    mswk61639 = "TALKFONT02/font00/I<128>"
    funcOneMessage(mswk61639)
    funcCloseMessage("talk", "n_agumon", "AO")
end
if g_SItemDB ~= 0 then
    mswk61640 = "TALKFONT02/font01/I<71>"
    mswk61641 = "TALKFONT02/font02/I<72>"
    mswk61642 = "TALKFONT02/font00/I<129>"
    mswk61643 = "TALKFONT02/font00/I<130>"
    funcChoiceMessage(mswk61640, mswk61641)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61642)
    be:DMsetLua("itemchange97.lua")
    be:DMcase(1)
    funcOneMessage(mswk61643)
    funcCloseMessage("talk", "n_agumon", "AO")
    be:DMswtEnd()
end
be:DMrun()
