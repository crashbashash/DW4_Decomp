if be:FLGisOn(1) == 1 then
    if be:FLGisOn(30) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11183 = "TALKFONT02/font00/I<145>"
        funcOneMessage(mswk11183)
        mswk11184 = "TALKFONT02/font00/I<146>"
        funcOneMessage(mswk11184)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
        be:FLGset(30, 1)
    elseif be:FLGisOn(30) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11185 = "TALKFONT02/font00/I<147>"
        funcOneMessage(mswk11185)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(1) == 0 then
    if be:FLGisOn(572) == 0 and g_lFLG06 ~= 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11186 = "TALKFONT02/font00/I<145>"
        funcOneMessage(mswk11186)
        mswk11187 = "TALKFONT02/font00/I<146>"
        funcOneMessage(mswk11187)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
        g_lFLG06 = 1
    elseif be:FLGisOn(572) == 0 and g_lFLG06 == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11188 = "TALKFONT02/font00/I<147>"
        funcOneMessage(mswk11188)
        be:DMsetLua("bML01005.lua")
        be:DMrun()
    elseif be:FLGisOn(572) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11189 = "TALKFONT02/font00/I<148>"
        funcOneMessage(mswk11189)
        mswk11190 = "TALKFONT02/font00/I<149>"
        funcOneMessage(mswk11190)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
