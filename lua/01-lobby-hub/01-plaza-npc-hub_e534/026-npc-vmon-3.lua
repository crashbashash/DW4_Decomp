g_SItemDB = 0
funcOpenMessage("talk", "n_vmon", "uC")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61340 = "TALKFONT02/font00/I<400>"
    funcOneMessage(mswk61340)
    mswk61341 = "TALKFONT02/font00/I<401>"
    funcOneMessage(mswk61341)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 85
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 24, 0, 0) == 1 then
    mswk61342 = "TALKFONT02/font00/I<402>"
    funcOneMessage(mswk61342)
    mswk61343 = "TALKFONT02/font00/I<403>"
    funcOneMessage(mswk61343)
    g_SItemDB = "armor2"
    g_SItemID = 24
    g_TItemDB = "armor1"
    g_TItemID = 12
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 60, 0, 0) == 1 then
    mswk61344 = "TALKFONT02/font00/I<404>"
    funcOneMessage(mswk61344)
    mswk61345 = "TALKFONT02/font00/I<405>"
    funcOneMessage(mswk61345)
    g_SItemDB = "weapon"
    g_SItemID = 60
    g_TItemDB = "weapon"
    g_TItemID = 151
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 110, 0, 0) == 1 then
    mswk61346 = "TALKFONT02/font00/I<406>"
    funcOneMessage(mswk61346)
    mswk61347 = "TALKFONT02/font00/I<407>"
    funcOneMessage(mswk61347)
    g_SItemDB = "weapon"
    g_SItemID = 110
    g_TItemDB = "weapon"
    g_TItemID = 51
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 135, 0, 0) == 1 then
    mswk61348 = "TALKFONT02/font00/I<408>"
    funcOneMessage(mswk61348)
    mswk61349 = "TALKFONT02/font00/I<409>"
    funcOneMessage(mswk61349)
    g_SItemDB = "weapon"
    g_SItemID = 135
    g_TItemDB = "weapon"
    g_TItemID = 27
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 226, 0, 0) == 1 then
    mswk61350 = "TALKFONT02/font00/I<410>"
    funcOneMessage(mswk61350)
    mswk61351 = "TALKFONT02/font00/I<411>"
    funcOneMessage(mswk61351)
    g_SItemDB = "weapon"
    g_SItemID = 226
    g_TItemDB = "weapon"
    g_TItemID = 210
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 126, 0, 0) == 1 then
    mswk61352 = "TALKFONT02/font00/I<412>"
    funcOneMessage(mswk61352)
    mswk61353 = "TALKFONT02/font00/I<413>"
    funcOneMessage(mswk61353)
    g_SItemDB = "weapon"
    g_SItemID = 126
    g_TItemDB = "armor2"
    g_TItemID = 3
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 101, 0, 0) == 1 then
    mswk61354 = "TALKFONT02/font00/I<414>"
    funcOneMessage(mswk61354)
    mswk61355 = "TALKFONT02/font00/I<415>"
    funcOneMessage(mswk61355)
    g_SItemDB = "weapon"
    g_SItemID = 101
    g_TItemDB = "armor2"
    g_TItemID = 30
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 166, 0, 0) == 1 then
    mswk61356 = "TALKFONT02/font00/I<416>"
    funcOneMessage(mswk61356)
    mswk61357 = "TALKFONT02/font00/I<417>"
    funcOneMessage(mswk61357)
    g_SItemDB = "weapon"
    g_SItemID = 166
    g_TItemDB = "weapon"
    g_TItemID = 153
else
    mswk61358 = "TALKFONT02/font00/I<418>"
    funcOneMessage(mswk61358)
    mswk61359 = "TALKFONT02/font00/I<419>"
    funcOneMessage(mswk61359)
    funcCloseMessage("talk", "n_vmon", "uC")
end
if g_SItemDB ~= 0 then
    mswk61360 = "TALKFONT02/font01/I<71>"
    mswk61361 = "TALKFONT02/font02/I<72>"
    mswk61362 = "TALKFONT02/font00/I<420>"
    mswk61363 = "TALKFONT02/font00/I<421>"
    funcChoiceMessage(mswk61360, mswk61361)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61362)
    be:DMsetLua("itemchange59.lua")
    be:DMcase(1)
    funcOneMessage(mswk61363)
    funcCloseMessage("talk", "n_vmon", "uC")
    be:DMswtEnd()
end
be:DMrun()
