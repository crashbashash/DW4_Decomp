g_SItemDB = 0
funcOpenMessage("talk", "n_weregaru", "[K")
if be:SYSctlDeviceFolder("IS", 0, "weapon", 35, 0, 0) == 1 then
    mswk61454 = "TALKFONT02/font00/I<457>"
    funcOneMessage(mswk61454)
    mswk61455 = "TALKFONT02/font00/I<458>"
    funcOneMessage(mswk61455)
    g_SItemDB = "weapon"
    g_SItemID = 35
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 85, 0, 0) == 1 then
    mswk61456 = "TALKFONT02/font00/I<459>"
    funcOneMessage(mswk61456)
    mswk61457 = "TALKFONT02/font00/I<460>"
    funcOneMessage(mswk61457)
    g_SItemDB = "weapon"
    g_SItemID = 85
    g_TItemDB = "weapon"
    g_TItemID = 76
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 110, 0, 0) == 1 then
    mswk61458 = "TALKFONT02/font00/I<461>"
    funcOneMessage(mswk61458)
    mswk61459 = "TALKFONT02/font00/I<462>"
    funcOneMessage(mswk61459)
    g_SItemDB = "weapon"
    g_SItemID = 110
    g_TItemDB = "weapon"
    g_TItemID = 52
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 3, 0, 0) == 1 then
    mswk61460 = "TALKFONT02/font00/I<463>"
    funcOneMessage(mswk61460)
    mswk61461 = "TALKFONT02/font00/I<464>"
    funcOneMessage(mswk61461)
    g_SItemDB = "armor2"
    g_SItemID = 3
    g_TItemDB = "weapon"
    g_TItemID = 45
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 21, 0, 0) == 1 then
    mswk61462 = "TALKFONT02/font00/I<465>"
    funcOneMessage(mswk61462)
    mswk61463 = "TALKFONT02/font00/I<466>"
    funcOneMessage(mswk61463)
    g_SItemDB = "armor1"
    g_SItemID = 21
    g_TItemDB = "weapon"
    g_TItemID = 195
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 226, 0, 0) == 1 then
    mswk61464 = "TALKFONT02/font00/I<467>"
    funcOneMessage(mswk61464)
    mswk61465 = "TALKFONT02/font00/I<468>"
    funcOneMessage(mswk61465)
    g_SItemDB = "weapon"
    g_SItemID = 226
    g_TItemDB = "armor2"
    g_TItemID = 24
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 160, 0, 0) == 1 then
    mswk61466 = "TALKFONT02/font00/I<469>"
    funcOneMessage(mswk61466)
    mswk61467 = "TALKFONT02/font00/I<470>"
    funcOneMessage(mswk61467)
    g_SItemDB = "weapon"
    g_SItemID = 160
    g_TItemDB = "armor2"
    g_TItemID = 6
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 1, 0, 0) == 1 then
    mswk61468 = "TALKFONT02/font00/I<471>"
    funcOneMessage(mswk61468)
    mswk61469 = "TALKFONT02/font00/I<472>"
    funcOneMessage(mswk61469)
    g_SItemDB = "weapon"
    g_SItemID = 1
    g_TItemDB = "armor2"
    g_TItemID = 27
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 70, 0, 0) == 1 then
    mswk61470 = "TALKFONT02/font00/I<473>"
    funcOneMessage(mswk61470)
    mswk61471 = "TALKFONT02/font00/I<474>"
    funcOneMessage(mswk61471)
    g_SItemDB = "weapon"
    g_SItemID = 70
    g_TItemDB = "weapon"
    g_TItemID = 245
else
    mswk61472 = "TALKFONT02/font00/I<475>"
    funcOneMessage(mswk61472)
    mswk61473 = "TALKFONT02/font00/I<476>"
    funcOneMessage(mswk61473)
    funcCloseMessage("talk", "n_weregaru", "[K")
end
if g_SItemDB ~= 0 then
    mswk61474 = "TALKFONT02/font01/I<71>"
    mswk61475 = "TALKFONT02/font02/I<72>"
    mswk61476 = "TALKFONT02/font00/I<477>"
    mswk61477 = "TALKFONT02/font00/I<478>"
    funcChoiceMessage(mswk61474, mswk61475)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61476)
    be:DMsetLua("itemchange135.lua")
    be:DMcase(1)
    funcOneMessage(mswk61477)
    funcCloseMessage("talk", "n_weregaru", "[K")
    be:DMswtEnd()
end
be:DMrun()
