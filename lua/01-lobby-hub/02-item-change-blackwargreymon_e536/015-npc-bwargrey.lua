g_SItemDB = 0
funcOpenMessage("talk", "n_bwargrey", "BLEH[OC")
if be:SYSctlDeviceFolder("IS", 0, "weapon", 128, 0, 0) == 1 then
    mswk61701 = "TALKFONT02/font00/I<167>"
    funcOneMessage(mswk61701)
    mswk61702 = "TALKFONT02/font00/I<168>"
    funcOneMessage(mswk61702)
    g_SItemDB = "weapon"
    g_SItemID = 128
    g_TItemDB = "weapon"
    g_TItemID = 149
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 15, 0, 0) == 1 then
    mswk61703 = "TALKFONT02/font00/I<169>"
    funcOneMessage(mswk61703)
    mswk61704 = "TALKFONT02/font00/I<170>"
    funcOneMessage(mswk61704)
    g_SItemDB = "armor1"
    g_SItemID = 15
    g_TItemDB = "weapon"
    g_TItemID = 154
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 29, 0, 0) == 1 then
    mswk61705 = "TALKFONT02/font00/I<171>"
    funcOneMessage(mswk61705)
    mswk61706 = "TALKFONT02/font00/I<172>"
    funcOneMessage(mswk61706)
    g_SItemDB = "weapon"
    g_SItemID = 29
    g_TItemDB = "armor2"
    g_TItemID = 41
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 29, 0, 0) == 1 then
    mswk61707 = "TALKFONT02/font00/I<171>"
    funcOneMessage(mswk61707)
    mswk61708 = "TALKFONT02/font00/I<173>"
    funcOneMessage(mswk61708)
    g_SItemDB = "weapon"
    g_SItemID = 29
    g_TItemDB = "armor2"
    g_TItemID = 35
else
    mswk61709 = "TALKFONT02/font00/I<174>"
    funcOneMessage(mswk61709)
    mswk61710 = "TALKFONT02/font00/I<175>"
    funcOneMessage(mswk61710)
    funcCloseMessage("talk", "n_bwargrey", "BLEH[OC")
end
if g_SItemDB ~= 0 then
    mswk61711 = "TALKFONT02/font01/I<71>"
    mswk61712 = "TALKFONT02/font02/I<72>"
    mswk61713 = "TALKFONT02/font00/I<176>"
    mswk61714 = "TALKFONT02/font00/I<177>"
    funcChoiceMessage(mswk61711, mswk61712)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61713)
    be:DMsetLua("itemchange154.lua")
    be:DMcase(1)
    funcOneMessage(mswk61714)
    funcCloseMessage("talk", "n_bwargrey", "BLEH[OC")
    be:DMswtEnd()
end
be:DMrun()
