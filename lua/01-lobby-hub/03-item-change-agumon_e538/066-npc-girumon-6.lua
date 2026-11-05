g_SItemDB = 0
funcOpenMessage("talk", "n_girumon", "M")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61364 = "TALKFONT02/font00/I<291>"
    funcOneMessage(mswk61364)
    mswk61365 = "TALKFONT02/font00/I<292>"
    funcOneMessage(mswk61365)
    mswk61366 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61366)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 110
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 10, 0, 0) == 1 then
    mswk61367 = "TALKFONT02/font00/I<294>"
    funcOneMessage(mswk61367)
    mswk61368 = "TALKFONT02/font00/I<295>"
    funcOneMessage(mswk61368)
    mswk61369 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61369)
    g_SItemDB = "weapon"
    g_SItemID = 10
    g_TItemDB = "weapon"
    g_TItemID = 201
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 35, 0, 0) == 1 then
    mswk61370 = "TALKFONT02/font00/I<296>"
    funcOneMessage(mswk61370)
    mswk61371 = "TALKFONT02/font00/I<297>"
    funcOneMessage(mswk61371)
    mswk61372 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61372)
    g_SItemDB = "weapon"
    g_SItemID = 35
    g_TItemDB = "weapon"
    g_TItemID = 176
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 60, 0, 0) == 1 then
    mswk61373 = "TALKFONT02/font00/I<298>"
    funcOneMessage(mswk61373)
    mswk61374 = "TALKFONT02/font00/I<299>"
    funcOneMessage(mswk61374)
    mswk61375 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61375)
    g_SItemDB = "weapon"
    g_SItemID = 60
    g_TItemDB = "weapon"
    g_TItemID = 152
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 126, 0, 0) == 1 then
    mswk61376 = "TALKFONT02/font00/I<300>"
    funcOneMessage(mswk61376)
    mswk61377 = "TALKFONT02/font00/I<301>"
    funcOneMessage(mswk61377)
    mswk61378 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61378)
    g_SItemDB = "weapon"
    g_SItemID = 126
    g_TItemDB = "armor2"
    g_TItemID = 0
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 76, 0, 0) == 1 then
    mswk61379 = "TALKFONT02/font00/I<302>"
    funcOneMessage(mswk61379)
    mswk61380 = "TALKFONT02/font00/I<303>"
    funcOneMessage(mswk61380)
    mswk61381 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61381)
    g_SItemDB = "weapon"
    g_SItemID = 76
    g_TItemDB = "armor1"
    g_TItemID = 3
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 26, 0, 0) == 1 then
    mswk61382 = "TALKFONT02/font00/I<304>"
    funcOneMessage(mswk61382)
    mswk61383 = "TALKFONT02/font00/I<305>"
    funcOneMessage(mswk61383)
    mswk61384 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61384)
    g_SItemDB = "weapon"
    g_SItemID = 26
    g_TItemDB = "weapon"
    g_TItemID = 241
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 3, 0, 0) == 1 then
    mswk61385 = "TALKFONT02/font00/I<306>"
    funcOneMessage(mswk61385)
    mswk61386 = "TALKFONT02/font00/I<307>"
    funcOneMessage(mswk61386)
    mswk61387 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61387)
    g_SItemDB = "weapon"
    g_SItemID = 3
    g_TItemDB = "weapon"
    g_TItemID = 20
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 53, 0, 0) == 1 then
    mswk61388 = "TALKFONT02/font00/I<308>"
    funcOneMessage(mswk61388)
    mswk61389 = "TALKFONT02/font00/I<309>"
    funcOneMessage(mswk61389)
    mswk61390 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61390)
    g_SItemDB = "weapon"
    g_SItemID = 53
    g_TItemDB = "weapon"
    g_TItemID = 45
else
    mswk61391 = "TALKFONT02/font00/I<310>"
    funcOneMessage(mswk61391)
    mswk61392 = "TALKFONT02/font00/I<311>"
    funcOneMessage(mswk61392)
    funcCloseMessage("talk", "n_girumon", "M")
end
if g_SItemDB ~= 0 then
    mswk61393 = "TALKFONT02/font01/I<71>"
    mswk61394 = "TALKFONT02/font02/I<72>"
    mswk61395 = "TALKFONT02/font00/I<312>"
    mswk61396 = "TALKFONT02/font00/I<313>"
    funcChoiceMessage(mswk61393, mswk61394)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61395)
    be:DMsetLua("itemchange78.lua")
    be:DMcase(1)
    funcOneMessage(mswk61396)
    funcCloseMessage("talk", "n_girumon", "M")
    be:DMswtEnd()
end
be:DMrun()
