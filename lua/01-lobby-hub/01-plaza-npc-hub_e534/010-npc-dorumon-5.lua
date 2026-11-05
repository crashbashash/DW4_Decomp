g_SItemDB = 0
funcOpenMessage("talk", "n_dorumon", "h")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61530 = "TALKFONT02/font00/I<178>"
    funcOneMessage(mswk61530)
    mswk61531 = "TALKFONT02/font00/I<219>"
    funcOneMessage(mswk61531)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 25
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 175, 0, 0) == 1 then
    mswk61532 = "TALKFONT02/font00/I<220>"
    funcOneMessage(mswk61532)
    mswk61533 = "TALKFONT02/font00/I<221>"
    funcOneMessage(mswk61533)
    g_SItemDB = "weapon"
    g_SItemID = 175
    g_TItemDB = "weapon"
    g_TItemID = 35
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 50, 0, 0) == 1 then
    mswk61534 = "TALKFONT02/font00/I<214>"
    funcOneMessage(mswk61534)
    mswk61535 = "TALKFONT02/font00/I<222>"
    funcOneMessage(mswk61535)
    g_SItemDB = "weapon"
    g_SItemID = 50
    g_TItemDB = "weapon"
    g_TItemID = 235
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 200, 0, 0) == 1 then
    mswk61536 = "TALKFONT02/font00/I<223>"
    funcOneMessage(mswk61536)
    mswk61537 = "TALKFONT02/font00/I<224>"
    funcOneMessage(mswk61537)
    g_SItemDB = "weapon"
    g_SItemID = 200
    g_TItemDB = "weapon"
    g_TItemID = 110
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 10, 0, 0) == 1 then
    mswk61538 = "TALKFONT02/font00/I<182>"
    funcOneMessage(mswk61538)
    mswk61539 = "TALKFONT02/font00/I<225>"
    funcOneMessage(mswk61539)
    g_SItemDB = "weapon"
    g_SItemID = 10
    g_TItemDB = "weapon"
    g_TItemID = 128
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 227, 0, 0) == 1 then
    mswk61540 = "TALKFONT02/font00/I<226>"
    funcOneMessage(mswk61540)
    mswk61541 = "TALKFONT02/font00/I<227>"
    funcOneMessage(mswk61541)
    g_SItemDB = "weapon"
    g_SItemID = 227
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 202, 0, 0) == 1 then
    mswk61542 = "TALKFONT02/font00/I<218>"
    funcOneMessage(mswk61542)
    mswk61543 = "TALKFONT02/font00/I<227>"
    funcOneMessage(mswk61543)
    g_SItemDB = "weapon"
    g_SItemID = 202
    g_TItemDB = "weapon"
    g_TItemID = 34
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 3, 0, 0) == 1 then
    mswk61544 = "TALKFONT02/font00/I<228>"
    funcOneMessage(mswk61544)
    mswk61545 = "TALKFONT02/font00/I<229>"
    funcOneMessage(mswk61545)
    g_SItemDB = "weapon"
    g_SItemID = 3
    g_TItemDB = "weapon"
    g_TItemID = 153
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 19, 0, 0) == 1 then
    mswk61546 = "TALKFONT02/font00/I<230>"
    funcOneMessage(mswk61546)
    mswk61547 = "TALKFONT02/font00/I<231>"
    funcOneMessage(mswk61547)
    g_SItemDB = "armor1"
    g_SItemID = 19
    g_TItemDB = "weapon"
    g_TItemID = 49
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 29, 0, 0) == 1 then
    mswk61548 = "TALKFONT02/font00/I<232>"
    funcOneMessage(mswk61548)
    mswk61549 = "TALKFONT02/font00/I<233>"
    funcOneMessage(mswk61549)
    g_SItemDB = "weapon"
    g_SItemID = 29
    g_TItemDB = "armor2"
    g_TItemID = 38
else
    mswk61550 = "TALKFONT02/font00/I<196>"
    funcOneMessage(mswk61550)
    mswk61551 = "TALKFONT02/font00/I<197>"
    funcOneMessage(mswk61551)
    funcCloseMessage("talk", "n_dorumon", "h")
end
if g_SItemDB ~= 0 then
    mswk61552 = "TALKFONT02/font01/I<71>"
    mswk61553 = "TALKFONT02/font02/I<72>"
    mswk61554 = "TALKFONT02/font00/I<198>"
    mswk61555 = "TALKFONT02/font00/I<199>"
    funcChoiceMessage(mswk61552, mswk61553)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61554)
    be:DMsetLua("itemchange40.lua")
    be:DMcase(1)
    funcOneMessage(mswk61555)
    funcCloseMessage("talk", "n_dorumon", "h")
    be:DMswtEnd()
end
be:DMrun()
