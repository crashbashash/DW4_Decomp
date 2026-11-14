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
be:FLGset(908, 0)
if be:SYSgetPlayerLevel(0) >= 16 then
    be:FLGset(908, 1)
end
be:FLGset(909, 0)
if be:SYSgetPlayerLevel(0) >= 46 then
    be:FLGset(909, 1)
end
be:FLGset(910, 0)
if be:SYSgetPlayerLevel(0) >= 76 then
    be:FLGset(910, 1)
end
be:FLGset(934, 0)
if g_messPlayerNo == 0 then
    be:FLGset(934, 1)
end
if be:FLGisOn(931) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(908) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10126 = "TALKFONT02/font00/I<179>"
        funcOneMessage(mswk10126)
        mswk10127 = "TALKFONT02/font00/I<180>"
        funcOneMessage(mswk10127)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(415) == 0 and be:FLGisOn(384) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10128 = "TALKFONT02/font00/I<181>"
        funcOneMessage(mswk10128)
        mswk10129 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10129)
        mswk10130 = "TALKFONT02/font00/I<183>"
        funcOneMessage(mswk10130)
        mswk10131 = "TALKFONT02/font00/I<184>"
        funcOneMessage(mswk10131)
        be:DMsetLua("bML01013.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(376) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10132 = "TALKFONT02/font00/I<181>"
        funcOneMessage(mswk10132)
        mswk10133 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10133)
        mswk10134 = "TALKFONT02/font00/I<183>"
        funcOneMessage(mswk10134)
        mswk10135 = "TALKFONT02/font00/I<184>"
        funcOneMessage(mswk10135)
        be:DMsetLua("bML01014.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(376) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10136 = "TALKFONT02/font00/I<185>"
        funcOneMessage(mswk10136)
        mswk10137 = "TALKFONT02/font00/I<186>"
        funcOneMessage(mswk10137)
        be:DMsetLua("bML01015.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10138 = "TALKFONT02/font00/I<187>"
        funcOneMessage(mswk10138)
        mswk10139 = "TALKFONT02/font00/I<188>"
        funcOneMessage(mswk10139)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(415) == 1 and be:FLGisOn(384) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10140 = "TALKFONT02/font00/I<189>"
        funcOneMessage(mswk10140)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(908) == 1 and be:FLGisOn(415) == 0 and be:FLGisOn(384) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10141 = "TALKFONT02/font00/I<190>"
        funcOneMessage(mswk10141)
        be:DMsetLua("treasure01.lua")
        be:DMrun()
        be:FLGset(415, 1)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10142 = "TALKFONT02/font00/I<191>"
        funcOneMessage(mswk10142)
        mswk10143 = "TALKFONT02/font00/I<192>"
        funcOneMessage(mswk10143)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(909) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10144 = "TALKFONT02/font00/I<179>"
        funcOneMessage(mswk10144)
        mswk10145 = "TALKFONT02/font00/I<180>"
        funcOneMessage(mswk10145)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(415) == 0 and be:FLGisOn(384) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10146 = "TALKFONT02/font00/I<187>"
        funcOneMessage(mswk10146)
        mswk10147 = "TALKFONT02/font00/I<188>"
        funcOneMessage(mswk10147)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10148 = "TALKFONT02/font00/I<181>"
        funcOneMessage(mswk10148)
        mswk10149 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10149)
        mswk10150 = "TALKFONT02/font00/I<183>"
        funcOneMessage(mswk10150)
        mswk10151 = "TALKFONT02/font00/I<184>"
        funcOneMessage(mswk10151)
        be:DMsetLua("bML01013.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(376) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10152 = "TALKFONT02/font00/I<181>"
        funcOneMessage(mswk10152)
        mswk10153 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10153)
        mswk10154 = "TALKFONT02/font00/I<183>"
        funcOneMessage(mswk10154)
        mswk10155 = "TALKFONT02/font00/I<184>"
        funcOneMessage(mswk10155)
        be:DMsetLua("bML01014.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(376) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10156 = "TALKFONT02/font00/I<185>"
        funcOneMessage(mswk10156)
        mswk10157 = "TALKFONT02/font00/I<186>"
        funcOneMessage(mswk10157)
        be:DMsetLua("bML01015.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(415) == 1 and be:FLGisOn(384) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10158 = "TALKFONT02/font00/I<189>"
        funcOneMessage(mswk10158)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(909) == 1 and be:FLGisOn(415) == 0 and be:FLGisOn(384) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10159 = "TALKFONT02/font00/I<190>"
        funcOneMessage(mswk10159)
        be:DMsetLua("treasure01.lua")
        be:DMrun()
        be:FLGset(415, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10160 = "TALKFONT02/font00/I<191>"
        funcOneMessage(mswk10160)
        mswk10161 = "TALKFONT02/font00/I<193>"
        funcOneMessage(mswk10161)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(910) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10162 = "TALKFONT02/font00/I<179>"
        funcOneMessage(mswk10162)
        mswk10163 = "TALKFONT02/font00/I<180>"
        funcOneMessage(mswk10163)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(415) == 0 and be:FLGisOn(384) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10164 = "TALKFONT02/font00/I<187>"
        funcOneMessage(mswk10164)
        mswk10165 = "TALKFONT02/font00/I<188>"
        funcOneMessage(mswk10165)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10166 = "TALKFONT02/font00/I<181>"
        funcOneMessage(mswk10166)
        mswk10167 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10167)
        mswk10168 = "TALKFONT02/font00/I<183>"
        funcOneMessage(mswk10168)
        mswk10169 = "TALKFONT02/font00/I<184>"
        funcOneMessage(mswk10169)
        be:DMsetLua("bML01013.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(376) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10170 = "TALKFONT02/font00/I<181>"
        funcOneMessage(mswk10170)
        mswk10171 = "TALKFONT02/font00/I<182>"
        funcOneMessage(mswk10171)
        mswk10172 = "TALKFONT02/font00/I<183>"
        funcOneMessage(mswk10172)
        mswk10173 = "TALKFONT02/font00/I<184>"
        funcOneMessage(mswk10173)
        be:DMsetLua("bML01014.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(376) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10174 = "TALKFONT02/font00/I<185>"
        funcOneMessage(mswk10174)
        mswk10175 = "TALKFONT02/font00/I<186>"
        funcOneMessage(mswk10175)
        be:DMsetLua("bML01015.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(415) == 1 and be:FLGisOn(384) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10176 = "TALKFONT02/font00/I<189>"
        funcOneMessage(mswk10176)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(89) == 1 and be:FLGisOn(910) == 1 and be:FLGisOn(415) == 0 and be:FLGisOn(384) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10177 = "TALKFONT02/font00/I<190>"
        funcOneMessage(mswk10177)
        be:DMsetLua("treasure01.lua")
        be:DMrun()
        be:FLGset(415, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10178 = "TALKFONT02/font00/I<191>"
        funcOneMessage(mswk10178)
        mswk10179 = "TALKFONT02/font00/I<193>"
        funcOneMessage(mswk10179)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(3) == 1 and be:FLGisOn(89) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10180 = "TALKFONT02/font00/I<194>"
        funcOneMessage(mswk10180)
        mswk10181 = "TALKFONT02/font00/I<195>"
        funcOneMessage(mswk10181)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
