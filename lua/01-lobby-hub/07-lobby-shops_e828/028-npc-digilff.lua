if be:FLGisOn(1) == 1 then
    if be:FLGisOn(31) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11135 = "TALKFONT02/font00/I<98>"
        funcOneMessage(mswk11135)
        mswk11136 = "TALKFONT02/font00/I<99>"
        funcOneMessage(mswk11136)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
        be:FLGset(31, 1)
    elseif be:FLGisOn(31) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11137 = "TALKFONT02/font00/I<100>"
        funcOneMessage(mswk11137)
        mswk11138 = "TALKFONT02/font00/I<101>"
        funcOneMessage(mswk11138)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(1) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11139 = "TALKFONT02/font00/I<102>"
        funcOneMessage(mswk11139)
        be:DMsetLua("bML01008.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
