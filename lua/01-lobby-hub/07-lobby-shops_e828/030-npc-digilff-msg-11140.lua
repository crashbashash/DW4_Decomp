if be:FLGisOn(1) == 1 then
    if be:FLGisOn(32) == 0 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11140 = "TALKFONT02/font00/I<103>"
        funcOneMessage(mswk11140)
        mswk11141 = "TALKFONT02/font00/I<104>"
        funcOneMessage(mswk11141)
        mswk11142 = "TALKFONT02/font00/I<105>"
        funcOneMessage(mswk11142)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
        be:FLGset(32, 1)
    elseif be:FLGisOn(32) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11143 = "TALKFONT02/font00/I<106>"
        funcOneMessage(mswk11143)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(1) == 0 then
    if be:FLGisOn(574) == 0 and g_lFLG07 ~= 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11144 = "TALKFONT02/font00/I<107>"
        funcOneMessage(mswk11144)
        mswk11145 = "TALKFONT02/font00/I<104>"
        funcOneMessage(mswk11145)
        mswk11146 = "TALKFONT02/font00/I<108>"
        funcOneMessage(mswk11146)
        be:DMsetLua("bML01010.lua")
        be:DMrun()
        g_lFLG07 = 1
    elseif be:FLGisOn(574) == 0 and g_lFLG07 == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11147 = "TALKFONT02/font00/I<109>"
        funcOneMessage(mswk11147)
        be:DMsetLua("bML01010.lua")
        be:DMrun()
    elseif be:FLGisOn(574) == 1 then
        funcOpenMessage("talk", "n_digilff", "fWt")
        mswk11148 = "TALKFONT02/font00/I<110>"
        funcOneMessage(mswk11148)
        mswk11149 = "TALKFONT02/font00/I<111>"
        funcOneMessage(mswk11149)
        funcCloseMessage("talk", "n_digilff", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
