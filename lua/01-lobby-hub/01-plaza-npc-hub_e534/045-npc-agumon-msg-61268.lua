g_SItemDB = 0
funcOpenMessage("talk", "n_agumon", "AO")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61268 = "TALKFONT02/font00/I<51>"
    funcOneMessage(mswk61268)
    mswk61269 = "TALKFONT02/font00/I<52>"
    funcOneMessage(mswk61269)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 10
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 85, 0, 0) == 1 then
    mswk61270 = "TALKFONT02/font00/I<53>"
    funcOneMessage(mswk61270)
    mswk61271 = "TALKFONT02/font00/I<54>"
    funcOneMessage(mswk61271)
    g_SItemDB = "weapon"
    g_SItemID = 85
    g_TItemDB = "weapon"
    g_TItemID = 127
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 110, 0, 0) == 1 then
    mswk61272 = "TALKFONT02/font00/I<55>"
    funcOneMessage(mswk61272)
    mswk61273 = "TALKFONT02/font00/I<56>"
    funcOneMessage(mswk61273)
    g_SItemDB = "weapon"
    g_SItemID = 110
    g_TItemDB = "weapon"
    g_TItemID = 77
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 135, 0, 0) == 1 then
    mswk61274 = "TALKFONT02/font00/I<57>"
    funcOneMessage(mswk61274)
    mswk61275 = "TALKFONT02/font00/I<58>"
    funcOneMessage(mswk61275)
    g_SItemDB = "weapon"
    g_SItemID = 135
    g_TItemDB = "weapon"
    g_TItemID = 26
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 235, 0, 0) == 1 then
    mswk61276 = "TALKFONT02/font00/I<59>"
    funcOneMessage(mswk61276)
    mswk61277 = "TALKFONT02/font00/I<60>"
    funcOneMessage(mswk61277)
    g_SItemDB = "weapon"
    g_SItemID = 235
    g_TItemDB = "armor2"
    g_TItemID = 15
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 160, 0, 0) == 1 then
    mswk61278 = "TALKFONT02/font00/I<61>"
    funcOneMessage(mswk61278)
    mswk61279 = "TALKFONT02/font00/I<62>"
    funcOneMessage(mswk61279)
    g_SItemDB = "weapon"
    g_SItemID = 160
    g_TItemDB = "armor2"
    g_TItemID = 9
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 12, 0, 0) == 1 then
    mswk61280 = "TALKFONT02/font00/I<63>"
    funcOneMessage(mswk61280)
    mswk61281 = "TALKFONT02/font00/I<64>"
    funcOneMessage(mswk61281)
    g_SItemDB = "armor1"
    g_SItemID = 12
    g_TItemDB = "weapon"
    g_TItemID = 220
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 101, 0, 0) == 1 then
    mswk61282 = "TALKFONT02/font00/I<65>"
    funcOneMessage(mswk61282)
    mswk61283 = "TALKFONT02/font00/I<66>"
    funcOneMessage(mswk61283)
    g_SItemDB = "weapon"
    g_SItemID = 101
    g_TItemDB = "weapon"
    g_TItemID = 28
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 116, 0, 0) == 1 then
    mswk61284 = "TALKFONT02/font00/I<67>"
    funcOneMessage(mswk61284)
    mswk61285 = "TALKFONT02/font00/I<68>"
    funcOneMessage(mswk61285)
    g_SItemDB = "weapon"
    g_SItemID = 116
    g_TItemDB = "weapon"
    g_TItemID = 228
else
    mswk61286 = "TALKFONT02/font00/I<69>"
    funcOneMessage(mswk61286)
    mswk61287 = "TALKFONT02/font00/I<70>"
    funcOneMessage(mswk61287)
    funcCloseMessage("talk", "n_agumon", "AO")
end
if g_SItemDB ~= 0 then
    mswk61288 = "TALKFONT02/font01/I<71>"
    mswk61289 = "TALKFONT02/font02/I<72>"
    mswk61290 = "TALKFONT02/font00/I<73>"
    mswk61291 = "TALKFONT02/font00/I<74>"
    funcChoiceMessage(mswk61288, mswk61289)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61290)
    be:DMsetLua("itemchange2.lua")
    be:DMcase(1)
    funcOneMessage(mswk61291)
    funcCloseMessage("talk", "n_agumon", "AO")
    be:DMswtEnd()
end
be:DMrun()
