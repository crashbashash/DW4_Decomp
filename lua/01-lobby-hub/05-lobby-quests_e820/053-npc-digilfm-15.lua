be:FLGset(931, 0)
be:FLGset(932, 0)
be:FLGset(933, 0)
if be:SYSgetDifficulty() == 2 then
    be:FLGset(933, 1)
elseif be:SYSgetDifficulty() == 1 then
    be:FLGset(932, 1)
else
    be:FLGset(931, 1)
end
be:FLGset(935, 0)
if be:SYSgetPlayerNinzu() == 1 then
    be:FLGset(935, 1)
end
if be:FLGisOn(931) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10238 = "TALKFONT02/font00/I<212>"
        funcOneMessage(mswk10238)
        mswk10239 = "TALKFONT02/font00/I<213>"
        funcOneMessage(mswk10239)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(417) == 0 and be:FLGisOn(386) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10240 = "TALKFONT02/font00/I<214>"
        funcOneMessage(mswk10240)
        mswk10241 = "TALKFONT02/font00/I<215>"
        funcOneMessage(mswk10241)
        be:DMsetLua("bML01019.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(378) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10242 = "TALKFONT02/font00/I<214>"
        funcOneMessage(mswk10242)
        mswk10243 = "TALKFONT02/font00/I<215>"
        funcOneMessage(mswk10243)
        be:DMsetLua("bML01020.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(378) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10244 = "TALKFONT02/font00/I<216>"
        funcOneMessage(mswk10244)
        be:DMsetLua("bML01021.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(417) == 1 and be:FLGisOn(386) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10245 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk10245)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(417) == 0 and be:FLGisOn(386) == 1 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10246 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk10246)
        be:DMsetLua("treasure03.lua")
        be:DMrun()
        be:FLGset(417, 1)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10247 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk10247)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10248 = "TALKFONT02/font00/I<212>"
        funcOneMessage(mswk10248)
        mswk10249 = "TALKFONT02/font00/I<213>"
        funcOneMessage(mswk10249)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(417) == 0 and be:FLGisOn(386) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10250 = "TALKFONT02/font00/I<214>"
        funcOneMessage(mswk10250)
        mswk10251 = "TALKFONT02/font00/I<215>"
        funcOneMessage(mswk10251)
        be:DMsetLua("bML01019.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(378) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10252 = "TALKFONT02/font00/I<214>"
        funcOneMessage(mswk10252)
        mswk10253 = "TALKFONT02/font00/I<215>"
        funcOneMessage(mswk10253)
        be:DMsetLua("bML01020.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(378) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10254 = "TALKFONT02/font00/I<216>"
        funcOneMessage(mswk10254)
        be:DMsetLua("bML01021.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(417) == 1 and be:FLGisOn(386) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10255 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk10255)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(417) == 0 and be:FLGisOn(386) == 1 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10256 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk10256)
        be:DMsetLua("treasure03.lua")
        be:DMrun()
        be:FLGset(417, 1)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10257 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk10257)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10258 = "TALKFONT02/font00/I<212>"
        funcOneMessage(mswk10258)
        mswk10259 = "TALKFONT02/font00/I<213>"
        funcOneMessage(mswk10259)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(935) == 1 and be:FLGisOn(417) == 0 and be:FLGisOn(386) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10260 = "TALKFONT02/font00/I<214>"
        funcOneMessage(mswk10260)
        mswk10261 = "TALKFONT02/font00/I<215>"
        funcOneMessage(mswk10261)
        be:DMsetLua("bML01019.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(378) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10262 = "TALKFONT02/font00/I<214>"
        funcOneMessage(mswk10262)
        mswk10263 = "TALKFONT02/font00/I<215>"
        funcOneMessage(mswk10263)
        be:DMsetLua("bML01020.lua")
        be:DMrun()
    elseif be:FLGisOn(409) == 1 and be:FLGisOn(378) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10264 = "TALKFONT02/font00/I<216>"
        funcOneMessage(mswk10264)
        be:DMsetLua("bML01021.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(417) == 1 and be:FLGisOn(386) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10265 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk10265)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(417) == 0 and be:FLGisOn(386) == 1 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10266 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk10266)
        be:DMsetLua("treasure03.lua")
        be:DMrun()
        be:FLGset(417, 1)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(91) == 1 and be:FLGisOn(68) == 1 and be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10267 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk10267)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(3) == 1 and be:FLGisOn(91) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10268 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk10268)
        mswk10269 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk10269)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
