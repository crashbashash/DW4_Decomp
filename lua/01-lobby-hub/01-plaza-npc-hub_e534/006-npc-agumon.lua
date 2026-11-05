g_SItemDB = 0
funcOpenMessage("talk", "n_agumon", "AO")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61240 = "TALKFONT02/font00/I<109>"
    funcOneMessage(mswk61240)
    mswk61241 = "TALKFONT02/font00/I<131>"
    funcOneMessage(mswk61241)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 201
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 24, 0, 0) == 1 then
    mswk61242 = "TALKFONT02/font00/I<132>"
    funcOneMessage(mswk61242)
    mswk61243 = "TALKFONT02/font00/I<133>"
    funcOneMessage(mswk61243)
    g_SItemDB = "armor2"
    g_SItemID = 24
    g_TItemDB = "weapon"
    g_TItemID = 130
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 21, 0, 0) == 1 then
    mswk61244 = "TALKFONT02/font00/I<117>"
    funcOneMessage(mswk61244)
    mswk61245 = "TALKFONT02/font00/I<134>"
    funcOneMessage(mswk61245)
    g_SItemDB = "armor2"
    g_SItemID = 21
    g_TItemDB = "weapon"
    g_TItemID = 180
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 1, 0, 0) == 1 then
    mswk61246 = "TALKFONT02/font00/I<135>"
    funcOneMessage(mswk61246)
    mswk61247 = "TALKFONT02/font00/I<136>"
    funcOneMessage(mswk61247)
    g_SItemDB = "armor1"
    g_SItemID = 1
    g_TItemDB = "weapon"
    g_TItemID = 212
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 3, 0, 0) == 1 then
    mswk61248 = "TALKFONT02/font00/I<137>"
    funcOneMessage(mswk61248)
    mswk61249 = "TALKFONT02/font00/I<116>"
    funcOneMessage(mswk61249)
    g_SItemDB = "armor2"
    g_SItemID = 3
    g_TItemDB = "weapon"
    g_TItemID = 102
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 39, 0, 0) == 1 then
    mswk61250 = "TALKFONT02/font00/I<138>"
    funcOneMessage(mswk61250)
    mswk61251 = "TALKFONT02/font00/I<139>"
    funcOneMessage(mswk61251)
    g_SItemDB = "armor2"
    g_SItemID = 39
    g_TItemDB = "weapon"
    g_TItemID = 87
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 1, 0, 0) == 1 then
    mswk61252 = "TALKFONT02/font00/I<123>"
    funcOneMessage(mswk61252)
    mswk61253 = "TALKFONT02/font00/I<140>"
    funcOneMessage(mswk61253)
    g_SItemDB = "weapon"
    g_SItemID = 1
    g_TItemDB = "weapon"
    g_TItemID = 50
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 51, 0, 0) == 1 then
    mswk61254 = "TALKFONT02/font00/I<141>"
    funcOneMessage(mswk61254)
    mswk61255 = "TALKFONT02/font00/I<142>"
    funcOneMessage(mswk61255)
    g_SItemDB = "weapon"
    g_SItemID = 51
    g_TItemDB = "weapon"
    g_TItemID = 75
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 76, 0, 0) == 1 then
    mswk61256 = "TALKFONT02/font00/I<143>"
    funcOneMessage(mswk61256)
    mswk61257 = "TALKFONT02/font00/I<144>"
    funcOneMessage(mswk61257)
    g_SItemDB = "weapon"
    g_SItemID = 76
    g_TItemDB = "weapon"
    g_TItemID = 225
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 2, 0, 0) == 1 then
    mswk61258 = "TALKFONT02/font00/I<145>"
    funcOneMessage(mswk61258)
    mswk61259 = "TALKFONT02/font00/I<146>"
    funcOneMessage(mswk61259)
    g_SItemDB = "weapon"
    g_SItemID = 2
    g_TItemDB = "armor2"
    g_TItemID = 1
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 52, 0, 0) == 1 then
    mswk61260 = "TALKFONT02/font00/I<147>"
    funcOneMessage(mswk61260)
    mswk61261 = "TALKFONT02/font00/I<148>"
    funcOneMessage(mswk61261)
    g_SItemDB = "weapon"
    g_SItemID = 52
    g_TItemDB = "armor2"
    g_TItemID = 33
else
    mswk61262 = "TALKFONT02/font00/I<127>"
    funcOneMessage(mswk61262)
    mswk61263 = "TALKFONT02/font00/I<128>"
    funcOneMessage(mswk61263)
    funcCloseMessage("talk", "n_agumon", "AO")
end
if g_SItemDB ~= 0 then
    mswk61264 = "TALKFONT02/font01/I<71>"
    mswk61265 = "TALKFONT02/font02/I<72>"
    mswk61266 = "TALKFONT02/font00/I<129>"
    mswk61267 = "TALKFONT02/font00/I<130>"
    funcChoiceMessage(mswk61264, mswk61265)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61266)
    be:DMsetLua("itemchange97.lua")
    be:DMcase(1)
    funcOneMessage(mswk61267)
    funcCloseMessage("talk", "n_agumon", "AO")
    be:DMswtEnd()
end
be:DMrun()
