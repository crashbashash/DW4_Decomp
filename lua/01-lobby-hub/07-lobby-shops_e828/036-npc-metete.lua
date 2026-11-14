if be:FLGisOn(594) == 0 then
    if be:FLGisOn(575) == 0 and be:FLGisOn(35) == 0 then
        funcOpenMessage("talk", "n_metete", "^Ge")
        mswk11191 = "TALKFONT02/font00/I<210>"
        funcOneMessage(mswk11191)
        funcCloseMessage("talk", "n_metete", "^Ge")
        be:DMrun()
        be:FLGset(35, 1)
    elseif be:FLGisOn(575) == 0 and be:FLGisOn(35) == 1 then
        funcOpenMessage("talk", "n_metete", "^Ge")
        mswk11192 = "TALKFONT02/font00/I<210>"
        funcOneMessage(mswk11192)
        be:DMsetLua("metaete.lua")
        be:DMrun()
    elseif be:FLGisOn(575) == 1 then
        funcOpenMessage("talk", "n_metete", "^Ge")
        mswk11193 = "TALKFONT02/font00/I<211>"
        funcOneMessage(mswk11193)
        mswk11194 = "TALKFONT02/font00/I<212>"
        funcOneMessage(mswk11194)
        mswk11195 = "TALKFONT02/font00/I<213>"
        funcOneMessage(mswk11195)
        funcCloseMessage("talk", "n_metete", "^Ge")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(594) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_metete", "^Ge")
        mswk11196 = "TALKFONT02/font00/I<214>"
        funcOneMessage(mswk11196)
        mswk11197 = "TALKFONT02/font00/I<215>"
        funcOneMessage(mswk11197)
        mswk11198 = "TALKFONT02/font00/I<216>"
        funcOneMessage(mswk11198)
        funcCloseMessage("talk", "n_metete", "^Ge")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
