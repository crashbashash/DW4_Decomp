g_SItemDB = 0
funcOpenMessage("talk", "n_vmon", "uC")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61173 = "TALKFONT02/font00/I<400>"
    funcOneMessage(mswk61173)
    mswk61174 = "TALKFONT02/font00/I<422>"
    funcOneMessage(mswk61174)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 76
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 21, 0, 0) == 1 then
    mswk61175 = "TALKFONT02/font00/I<423>"
    funcOneMessage(mswk61175)
    mswk61176 = "TALKFONT02/font00/I<424>"
    funcOneMessage(mswk61176)
    g_SItemDB = "armor2"
    g_SItemID = 21
    g_TItemDB = "weapon"
    g_TItemID = 227
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 15, 0, 0) == 1 then
    mswk61177 = "TALKFONT02/font00/I<425>"
    funcOneMessage(mswk61177)
    mswk61178 = "TALKFONT02/font00/I<426>"
    funcOneMessage(mswk61178)
    g_SItemDB = "armor2"
    g_SItemID = 15
    g_TItemDB = "weapon"
    g_TItemID = 202
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 12, 0, 0) == 1 then
    mswk61179 = "TALKFONT02/font00/I<427>"
    funcOneMessage(mswk61179)
    mswk61180 = "TALKFONT02/font00/I<428>"
    funcOneMessage(mswk61180)
    g_SItemDB = "armor2"
    g_SItemID = 12
    g_TItemDB = "weapon"
    g_TItemID = 25
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 1, 0, 0) == 1 then
    mswk61181 = "TALKFONT02/font00/I<429>"
    funcOneMessage(mswk61181)
    mswk61182 = "TALKFONT02/font00/I<430>"
    funcOneMessage(mswk61182)
    g_SItemDB = "armor2"
    g_SItemID = 1
    g_TItemDB = "weapon"
    g_TItemID = 12
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 1, 0, 0) == 1 then
    mswk61183 = "TALKFONT02/font00/I<431>"
    funcOneMessage(mswk61183)
    mswk61184 = "TALKFONT02/font00/I<432>"
    funcOneMessage(mswk61184)
    g_SItemDB = "weapon"
    g_SItemID = 1
    g_TItemDB = "armor2"
    g_TItemID = 6
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 176, 0, 0) == 1 then
    mswk61185 = "TALKFONT02/font00/I<433>"
    funcOneMessage(mswk61185)
    mswk61186 = "TALKFONT02/font00/I<434>"
    funcOneMessage(mswk61186)
    g_SItemDB = "weapon"
    g_SItemID = 176
    g_TItemDB = "armor1"
    g_TItemID = 1
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 201, 0, 0) == 1 then
    mswk61187 = "TALKFONT02/font00/I<435>"
    funcOneMessage(mswk61187)
    mswk61188 = "TALKFONT02/font00/I<436>"
    funcOneMessage(mswk61188)
    g_SItemDB = "weapon"
    g_SItemID = 201
    g_TItemDB = "armor1"
    g_TItemID = 19
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 50, 0, 0) == 1 then
    mswk61189 = "TALKFONT02/font00/I<437>"
    funcOneMessage(mswk61189)
    mswk61190 = "TALKFONT02/font00/I<438>"
    funcOneMessage(mswk61190)
    g_SItemDB = "weapon"
    g_SItemID = 50
    g_TItemDB = "weapon"
    g_TItemID = 81
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 127, 0, 0) == 1 then
    mswk61191 = "TALKFONT02/font00/I<439>"
    funcOneMessage(mswk61191)
    mswk61192 = "TALKFONT02/font00/I<415>"
    funcOneMessage(mswk61192)
    g_SItemDB = "weapon"
    g_SItemID = 127
    g_TItemDB = "armor2"
    g_TItemID = 30
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 77, 0, 0) == 1 then
    mswk61193 = "TALKFONT02/font00/I<440>"
    funcOneMessage(mswk61193)
    mswk61194 = "TALKFONT02/font00/I<441>"
    funcOneMessage(mswk61194)
    g_SItemDB = "weapon"
    g_SItemID = 77
    g_TItemDB = "armor2"
    g_TItemID = 27
else
    mswk61195 = "TALKFONT02/font00/I<418>"
    funcOneMessage(mswk61195)
    mswk61196 = "TALKFONT02/font00/I<419>"
    funcOneMessage(mswk61196)
    funcCloseMessage("talk", "n_vmon", "uC")
end
if g_SItemDB ~= 0 then
    mswk61197 = "TALKFONT02/font01/I<71>"
    mswk61198 = "TALKFONT02/font02/I<72>"
    mswk61199 = "TALKFONT02/font00/I<420>"
    mswk61200 = "TALKFONT02/font00/I<421>"
    funcChoiceMessage(mswk61197, mswk61198)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61199)
    be:DMsetLua("itemchange59.lua")
    be:DMcase(1)
    funcOneMessage(mswk61200)
    funcCloseMessage("talk", "n_vmon", "uC")
    be:DMswtEnd()
end
be:DMrun()
