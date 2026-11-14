g_SItemDB = 0
funcOpenMessage("talk", "n_girumon", "M")
if be:SYSctlFlagFolder("IS", 11) == 1 then
    mswk61201 = "TALKFONT02/font00/I<296>"
    funcOneMessage(mswk61201)
    mswk61202 = "TALKFONT02/font00/I<292>"
    funcOneMessage(mswk61202)
    mswk61203 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61203)
    g_SItemDB = "impItem"
    g_SItemID = 11
    g_TItemDB = "weapon"
    g_TItemID = 176
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 15, 0, 0) == 1 then
    mswk61204 = "TALKFONT02/font00/I<314>"
    funcOneMessage(mswk61204)
    mswk61205 = "TALKFONT02/font00/I<315>"
    funcOneMessage(mswk61205)
    mswk61206 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61206)
    g_SItemDB = "armor2"
    g_SItemID = 15
    g_TItemDB = "weapon"
    g_TItemID = 205
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 12, 0, 0) == 1 then
    mswk61207 = "TALKFONT02/font00/I<316>"
    funcOneMessage(mswk61207)
    mswk61208 = "TALKFONT02/font00/I<317>"
    funcOneMessage(mswk61208)
    mswk61209 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61209)
    g_SItemDB = "armor2"
    g_SItemID = 12
    g_TItemDB = "weapon"
    g_TItemID = 77
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 9, 0, 0) == 1 then
    mswk61210 = "TALKFONT02/font00/I<318>"
    funcOneMessage(mswk61210)
    mswk61211 = "TALKFONT02/font00/I<319>"
    funcOneMessage(mswk61211)
    mswk61212 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61212)
    g_SItemDB = "armor2"
    g_SItemID = 9
    g_TItemDB = "weapon"
    g_TItemID = 177
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 6, 0, 0) == 1 then
    mswk61213 = "TALKFONT02/font00/I<320>"
    funcOneMessage(mswk61213)
    mswk61214 = "TALKFONT02/font00/I<321>"
    funcOneMessage(mswk61214)
    mswk61215 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61215)
    g_SItemDB = "armor2"
    g_SItemID = 6
    g_TItemDB = "weapon"
    g_TItemID = 105
elseif be:SYSctlDeviceFolder("IS", 0, "armor2", 36, 0, 0) == 1 then
    mswk61216 = "TALKFONT02/font00/I<322>"
    funcOneMessage(mswk61216)
    mswk61217 = "TALKFONT02/font00/I<323>"
    funcOneMessage(mswk61217)
    mswk61218 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61218)
    g_SItemDB = "armor2"
    g_SItemID = 36
    g_TItemDB = "weapon"
    g_TItemID = 187
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 26, 0, 0) == 1 then
    mswk61219 = "TALKFONT02/font00/I<324>"
    funcOneMessage(mswk61219)
    mswk61220 = "TALKFONT02/font00/I<305>"
    funcOneMessage(mswk61220)
    mswk61221 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61221)
    g_SItemDB = "weapon"
    g_SItemID = 26
    g_TItemDB = "weapon"
    g_TItemID = 125
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 51, 0, 0) == 1 then
    mswk61222 = "TALKFONT02/font00/I<325>"
    funcOneMessage(mswk61222)
    mswk61223 = "TALKFONT02/font00/I<326>"
    funcOneMessage(mswk61223)
    mswk61224 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61224)
    g_SItemDB = "weapon"
    g_SItemID = 51
    g_TItemDB = "armor2"
    g_TItemID = 3
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 201, 0, 0) == 1 then
    mswk61225 = "TALKFONT02/font00/I<300>"
    funcOneMessage(mswk61225)
    mswk61226 = "TALKFONT02/font00/I<327>"
    funcOneMessage(mswk61226)
    mswk61227 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61227)
    g_SItemDB = "weapon"
    g_SItemID = 201
    g_TItemDB = "armor2"
    g_TItemID = 0
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 152, 0, 0) == 1 then
    mswk61228 = "TALKFONT02/font00/I<328>"
    funcOneMessage(mswk61228)
    mswk61229 = "TALKFONT02/font00/I<329>"
    funcOneMessage(mswk61229)
    mswk61230 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61230)
    g_SItemDB = "weapon"
    g_SItemID = 152
    g_TItemDB = "armor2"
    g_TItemID = 39
elseif be:SYSctlDeviceFolder("IS", 0, "weapon", 212, 0, 0) == 1 then
    mswk61231 = "TALKFONT02/font00/I<328>"
    funcOneMessage(mswk61231)
    mswk61232 = "TALKFONT02/font00/I<330>"
    funcOneMessage(mswk61232)
    mswk61233 = "TALKFONT02/font00/I<293>"
    funcOneMessage(mswk61233)
    g_SItemDB = "weapon"
    g_SItemID = 212
    g_TItemDB = "armor2"
    g_TItemID = 39
else
    mswk61234 = "TALKFONT02/font00/I<310>"
    funcOneMessage(mswk61234)
    mswk61235 = "TALKFONT02/font00/I<311>"
    funcOneMessage(mswk61235)
    funcCloseMessage("talk", "n_girumon", "M")
end
if g_SItemDB ~= 0 then
    mswk61236 = "TALKFONT02/font01/I<71>"
    mswk61237 = "TALKFONT02/font02/I<72>"
    mswk61238 = "TALKFONT02/font00/I<312>"
    mswk61239 = "TALKFONT02/font00/I<313>"
    funcChoiceMessage(mswk61236, mswk61237)
    be:DMswtSD("SELECTCTRL", "i_messcr", g_messPlayerNo, "GETSELECT")
    be:DMcase(0)
    funcOneMessage(mswk61238)
    be:DMsetLua("itemchange78.lua")
    be:DMcase(1)
    funcOneMessage(mswk61239)
    funcCloseMessage("talk", "n_girumon", "M")
    be:DMswtEnd()
end
be:DMrun()
