g_SItemDB = 0
funcOpenMessage("talk", "n_prmame", "vX}")
if be:SYSctlDeviceFolder("IS", 0, "weapon", 60, 0, 0) == 1 then
    mswk61421 = "TALKFONT02/font00/I<347>"
    funcOneMessage(mswk61421)
    mswk61422 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61422)
    mswk61423 = "TALKFONT02/font00/I<349>"
    funcOneMessage(mswk61423)
    g_SItemDB = "weapon"
    g_SItemID = 60
    g_TItemDB = "weapon"
    g_TItemID = 160
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 110, 0, 0) == 1 then
    mswk61424 = "TALKFONT02/font00/I<350>"
    funcOneMessage(mswk61424)
    mswk61425 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61425)
    mswk61426 = "TALKFONT02/font00/I<351>"
    funcOneMessage(mswk61426)
    g_SItemDB = "weapon"
    g_SItemID = 110
    g_TItemDB = "weapon"
    g_TItemID = 101
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 135, 0, 0) == 1 then
    mswk61427 = "TALKFONT02/font00/I<352>"
    funcOneMessage(mswk61427)
    mswk61428 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61428)
    mswk61429 = "TALKFONT02/font00/I<353>"
    funcOneMessage(mswk61429)
    g_SItemDB = "weapon"
    g_SItemID = 135
    g_TItemDB = "weapon"
    g_TItemID = 2
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 201, 0, 0) == 1 then
    mswk61430 = "TALKFONT02/font00/I<354>"
    funcOneMessage(mswk61430)
    mswk61431 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61431)
    mswk61432 = "TALKFONT02/font00/I<355>"
    funcOneMessage(mswk61432)
    g_SItemDB = "weapon"
    g_SItemID = 201
    g_TItemDB = "weapon"
    g_TItemID = 185
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 235, 0, 0) == 1 then
    mswk61433 = "TALKFONT02/font00/I<356>"
    funcOneMessage(mswk61433)
    mswk61434 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61434)
    mswk61435 = "TALKFONT02/font00/I<357>"
    funcOneMessage(mswk61435)
    g_SItemDB = "weapon"
    g_SItemID = 235
    g_TItemDB = "armor2"
    g_TItemID = 12
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 26, 0, 0) == 1 then
    mswk61436 = "TALKFONT02/font00/I<358>"
    funcOneMessage(mswk61436)
    mswk61437 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61437)
    mswk61438 = "TALKFONT02/font00/I<359>"
    funcOneMessage(mswk61438)
    g_SItemDB = "weapon"
    g_SItemID = 26
    g_TItemDB = "weapon"
    g_TItemID = 53
elseif be:SYSctlDeviceFolder("IS", 0, "armor1", 3, 0, 0) == 1 then
    mswk61439 = "TALKFONT02/font00/I<360>"
    funcOneMessage(mswk61439)
    mswk61440 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61440)
    mswk61441 = "TALKFONT02/font00/I<361>"
    funcOneMessage(mswk61441)
    g_SItemDB = "armor1"
    g_SItemID = 3
    g_TItemDB = "weapon"
    g_TItemID = 70
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 20, 0, 0) == 1 then
    mswk61442 = "TALKFONT02/font00/I<362>"
    funcOneMessage(mswk61442)
    mswk61443 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61443)
    mswk61444 = "TALKFONT02/font00/I<363>"
    funcOneMessage(mswk61444)
    g_SItemDB = "weapon"
    g_SItemID = 20
    g_TItemDB = "weapon"
    g_TItemID = 120
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 70, 0, 0) == 1 then
    mswk61445 = "TALKFONT02/font00/I<364>"
    funcOneMessage(mswk61445)
    mswk61446 = "TALKFONT02/font00/I<348>"
    funcOneMessage(mswk61446)
    mswk61447 = "TALKFONT02/font00/I<365>"
    funcOneMessage(mswk61447)
    g_SItemDB = "weapon"
    g_SItemID = 70
    g_TItemDB = "weapon"
    g_TItemID = 170
else
    mswk61448 = "TALKFONT02/font00/I<366>"
    funcOneMessage(mswk61448)
    mswk61449 = "TALKFONT02/font00/I<367>"
    funcOneMessage(mswk61449)
    funcCloseMessage("talk", "n_prmame", "vX}")
end
if g_SItemDB ~= 0 then
    mswk61450 = "TALKFONT02/font01/I<71>"
    mswk61451 = "TALKFONT02/font02/I<72>"
    mswk61452 = "TALKFONT02/font00/I<368>"
    mswk61453 = "TALKFONT02/font00/I<369>"
    funcChoiceMessage(mswk61450, mswk61451)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61452)
    be:DMsetLua("itemchange116.lua")
    be:DMcase(1)
    funcOneMessage(mswk61453)
    funcCloseMessage("talk", "n_prmame", "vX}")
    be:DMswtEnd()
end
be:DMrun()
