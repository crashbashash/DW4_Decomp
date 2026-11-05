g_SItemDB = 0
funcOpenMessage("talk", "n_agumon", "AO")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61478 = "TALKFONT02/font00/I<51>"
    funcOneMessage(mswk61478)
    mswk61479 = "TALKFONT02/font00/I<95>"
    funcOneMessage(mswk61479)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 175
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 0, 0, 0) == 1 then
    mswk61480 = "TALKFONT02/font00/I<96>"
    funcOneMessage(mswk61480)
    mswk61481 = "TALKFONT02/font00/I<97>"
    funcOneMessage(mswk61481)
    g_SItemDB = "weapon"
    g_SItemID = 0
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 50, 0, 0) == 1 then
    mswk61482 = "TALKFONT02/font00/I<98>"
    funcOneMessage(mswk61482)
    mswk61483 = "TALKFONT02/font00/I<99>"
    funcOneMessage(mswk61483)
    g_SItemDB = "weapon"
    g_SItemID = 50
    g_TItemDB = "weapon"
    g_TItemID = 135
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 75, 0, 0) == 1 then
    mswk61484 = "TALKFONT02/font00/I<89>"
    funcOneMessage(mswk61484)
    mswk61485 = "TALKFONT02/font00/I<100>"
    funcOneMessage(mswk61485)
    g_SItemDB = "weapon"
    g_SItemID = 75
    g_TItemDB = "weapon"
    g_TItemID = 160
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 60, 0, 0) == 1 then
    mswk61486 = "TALKFONT02/font00/I<101>"
    funcOneMessage(mswk61486)
    mswk61487 = "TALKFONT02/font00/I<66>"
    funcOneMessage(mswk61487)
    g_SItemDB = "weapon"
    g_SItemID = 60
    g_TItemDB = "weapon"
    g_TItemID = 28
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 110, 0, 0) == 1 then
    mswk61488 = "TALKFONT02/font00/I<55>"
    funcOneMessage(mswk61488)
    mswk61489 = "TALKFONT02/font00/I<102>"
    funcOneMessage(mswk61489)
    g_SItemDB = "weapon"
    g_SItemID = 110
    g_TItemDB = "weapon"
    g_TItemID = 53
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 102, 0, 0) == 1 then
    mswk61490 = "TALKFONT02/font00/I<93>"
    funcOneMessage(mswk61490)
    mswk61491 = "TALKFONT02/font00/I<103>"
    funcOneMessage(mswk61491)
    g_SItemDB = "weapon"
    g_SItemID = 102
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 152, 0, 0) == 1 then
    mswk61492 = "TALKFONT02/font00/I<104>"
    funcOneMessage(mswk61492)
    mswk61493 = "TALKFONT02/font00/I<103>"
    funcOneMessage(mswk61493)
    g_SItemDB = "weapon"
    g_SItemID = 152
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 52, 0, 0) == 1 then
    mswk61494 = "TALKFONT02/font00/I<105>"
    funcOneMessage(mswk61494)
    mswk61495 = "TALKFONT02/font00/I<106>"
    funcOneMessage(mswk61495)
    g_SItemDB = "weapon"
    g_SItemID = 52
    g_TItemDB = "weapon"
    g_TItemID = 29
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 49, 0, 0) == 1 then
    mswk61496 = "TALKFONT02/font00/I<107>"
    funcOneMessage(mswk61496)
    mswk61497 = "TALKFONT02/font00/I<108>"
    funcOneMessage(mswk61497)
    g_SItemDB = "weapon"
    g_SItemID = 49
    g_TItemDB = "weapon"
    g_TItemID = 154
else
    mswk61498 = "TALKFONT02/font00/I<69>"
    funcOneMessage(mswk61498)
    mswk61499 = "TALKFONT02/font00/I<70>"
    funcOneMessage(mswk61499)
    funcCloseMessage("talk", "n_agumon", "AO")
end
if g_SItemDB ~= 0 then
    mswk61500 = "TALKFONT02/font01/I<71>"
    mswk61501 = "TALKFONT02/font02/I<72>"
    mswk61502 = "TALKFONT02/font00/I<73>"
    mswk61503 = "TALKFONT02/font00/I<74>"
    funcChoiceMessage(mswk61500, mswk61501)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61502)
    be:DMsetLua("itemchange2.lua")
    be:DMcase(1)
    funcOneMessage(mswk61503)
    funcCloseMessage("talk", "n_agumon", "AO")
    be:DMswtEnd()
end
be:DMrun()
