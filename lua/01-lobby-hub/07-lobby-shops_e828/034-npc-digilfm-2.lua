if be:FLGisOn(1) == 1 then
    if be:FLGisOn(27) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11075 = "TALKFONT02/font00/I<150>"
        funcOneMessage(mswk11075)
        mswk11076 = "TALKFONT02/font00/I<151>"
        funcOneMessage(mswk11076)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
        be:FLGset(27, 1)
    elseif be:FLGisOn(27) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11077 = "TALKFONT02/font00/I<152>"
        funcOneMessage(mswk11077)
        mswk11078 = "TALKFONT02/font00/I<153>"
        funcOneMessage(mswk11078)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(1) == 0 then
    if be:FLGisOn(573) == 0 and g_lFLG03 ~= 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11079 = "TALKFONT02/font00/I<154>"
        funcOneMessage(mswk11079)
        mswk11080 = "TALKFONT02/font00/I<155>"
        funcOneMessage(mswk11080)
        be:DMsetLua("bML01009.lua")
        be:DMrun()
        g_lFLG03 = 1
    elseif be:FLGisOn(573) == 0 and g_lFLG03 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11081 = "TALKFONT02/font00/I<156>"
        funcOneMessage(mswk11081)
        be:DMsetLua("bML01009.lua")
        be:DMrun()
    elseif be:FLGisOn(573) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk11082 = "TALKFONT02/font00/I<157>"
        funcOneMessage(mswk11082)
        mswk11083 = "TALKFONT02/font00/I<158>"
        funcOneMessage(mswk11083)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
