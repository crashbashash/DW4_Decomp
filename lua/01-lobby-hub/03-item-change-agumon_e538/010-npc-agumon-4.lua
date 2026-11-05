g_SItemDB = 0
funcOpenMessage("talk", "n_agumon", "AO")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61397 = "TALKFONT02/font00/I<109>"
    funcOneMessage(mswk61397)
    mswk61398 = "TALKFONT02/font00/I<110>"
    funcOneMessage(mswk61398)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 135
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 10, 0, 0) == 1 then
    mswk61399 = "TALKFONT02/font00/I<111>"
    funcOneMessage(mswk61399)
    mswk61400 = "TALKFONT02/font00/I<112>"
    funcOneMessage(mswk61400)
    g_SItemDB = "weapon"
    g_SItemID = 10
    g_TItemDB = "weapon"
    g_TItemID = 226
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 35, 0, 0) == 1 then
    mswk61401 = "TALKFONT02/font00/I<113>"
    funcOneMessage(mswk61401)
    mswk61402 = "TALKFONT02/font00/I<114>"
    funcOneMessage(mswk61402)
    g_SItemDB = "weapon"
    g_SItemID = 35
    g_TItemDB = "weapon"
    g_TItemID = 177
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 85, 0, 0) == 1 then
    mswk61403 = "TALKFONT02/font00/I<115>"
    funcOneMessage(mswk61403)
    mswk61404 = "TALKFONT02/font00/I<116>"
    funcOneMessage(mswk61404)
    g_SItemDB = "weapon"
    g_SItemID = 85
    g_TItemDB = "weapon"
    g_TItemID = 102
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 21, 0, 0) == 1 then
    mswk61405 = "TALKFONT02/font00/I<117>"
    funcOneMessage(mswk61405)
    mswk61406 = "TALKFONT02/font00/I<118>"
    funcOneMessage(mswk61406)
    g_SItemDB = "armor2"
    g_SItemID = 21
    g_TItemDB = "weapon"
    g_TItemID = 70
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 176, 0, 0) == 1 then
    mswk61407 = "TALKFONT02/font00/I<119>"
    funcOneMessage(mswk61407)
    mswk61408 = "TALKFONT02/font00/I<120>"
    funcOneMessage(mswk61408)
    g_SItemDB = "weapon"
    g_SItemID = 176
    g_TItemDB = "armor2"
    g_TItemID = 18
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 151, 0, 0) == 1 then
    mswk61409 = "TALKFONT02/font00/I<121>"
    funcOneMessage(mswk61409)
    mswk61410 = "TALKFONT02/font00/I<122>"
    funcOneMessage(mswk61410)
    g_SItemDB = "weapon"
    g_SItemID = 151
    g_TItemDB = "weapon"
    g_TItemID = 166
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 1, 0, 0) == 1 then
    mswk61411 = "TALKFONT02/font00/I<123>"
    funcOneMessage(mswk61411)
    mswk61412 = "TALKFONT02/font00/I<124>"
    funcOneMessage(mswk61412)
    g_SItemDB = "weapon"
    g_SItemID = 1
    g_TItemDB = "weapon"
    g_TItemID = 78
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 45, 0, 0) == 1 then
    mswk61413 = "TALKFONT02/font00/I<125>"
    funcOneMessage(mswk61413)
    mswk61414 = "TALKFONT02/font00/I<126>"
    funcOneMessage(mswk61414)
    g_SItemDB = "weapon"
    g_SItemID = 45
    g_TItemDB = "weapon"
    g_TItemID = 145
else
    mswk61415 = "TALKFONT02/font00/I<127>"
    funcOneMessage(mswk61415)
    mswk61416 = "TALKFONT02/font00/I<128>"
    funcOneMessage(mswk61416)
    funcCloseMessage("talk", "n_agumon", "AO")
end
if g_SItemDB ~= 0 then
    mswk61417 = "TALKFONT02/font01/I<71>"
    mswk61418 = "TALKFONT02/font02/I<72>"
    mswk61419 = "TALKFONT02/font00/I<129>"
    mswk61420 = "TALKFONT02/font00/I<130>"
    funcChoiceMessage(mswk61417, mswk61418)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61419)
    be:DMsetLua("itemchange97.lua")
    be:DMcase(1)
    funcOneMessage(mswk61420)
    funcCloseMessage("talk", "n_agumon", "AO")
    be:DMswtEnd()
end
be:DMrun()
