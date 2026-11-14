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
be:FLGset(922, 0)
if be:SYSisGetShinkaDigimon(0, 0) + be:SYSisGetShinkaDigimon(0, 1) + be:SYSisGetShinkaDigimon(0, 2) + be:SYSisGetShinkaDigimon(0, 3) + be:SYSisGetShinkaDigimon(0, 4) + be:SYSisGetShinkaDigimon(0, 5) + be:SYSisGetShinkaDigimon(0, 6) + be:SYSisGetShinkaDigimon(0, 7) + be:SYSisGetShinkaDigimon(0, 8) + be:SYSisGetShinkaDigimon(0, 9) + be:SYSisGetShinkaDigimon(0, 10) + be:SYSisGetShinkaDigimon(0, 11) + be:SYSisGetShinkaDigimon(0, 12) + be:SYSisGetShinkaDigimon(0, 13) + be:SYSisGetShinkaDigimon(0, 14) + be:SYSisGetShinkaDigimon(0, 15) >= 2 then
    be:FLGset(922, 1)
end
be:FLGset(923, 0)
if be:SYSisGetShinkaDigimon(0, 0) + be:SYSisGetShinkaDigimon(0, 1) + be:SYSisGetShinkaDigimon(0, 2) + be:SYSisGetShinkaDigimon(0, 3) + be:SYSisGetShinkaDigimon(0, 4) + be:SYSisGetShinkaDigimon(0, 5) + be:SYSisGetShinkaDigimon(0, 6) + be:SYSisGetShinkaDigimon(0, 7) + be:SYSisGetShinkaDigimon(0, 8) + be:SYSisGetShinkaDigimon(0, 9) + be:SYSisGetShinkaDigimon(0, 10) + be:SYSisGetShinkaDigimon(0, 11) + be:SYSisGetShinkaDigimon(0, 12) + be:SYSisGetShinkaDigimon(0, 13) + be:SYSisGetShinkaDigimon(0, 14) + be:SYSisGetShinkaDigimon(0, 15) >= 5 then
    be:FLGset(923, 1)
end
be:FLGset(924, 0)
if be:SYSisGetShinkaDigimon(0, 0) + be:SYSisGetShinkaDigimon(0, 1) + be:SYSisGetShinkaDigimon(0, 2) + be:SYSisGetShinkaDigimon(0, 3) + be:SYSisGetShinkaDigimon(0, 4) + be:SYSisGetShinkaDigimon(0, 5) + be:SYSisGetShinkaDigimon(0, 6) + be:SYSisGetShinkaDigimon(0, 7) + be:SYSisGetShinkaDigimon(0, 8) + be:SYSisGetShinkaDigimon(0, 9) + be:SYSisGetShinkaDigimon(0, 10) + be:SYSisGetShinkaDigimon(0, 11) + be:SYSisGetShinkaDigimon(0, 12) + be:SYSisGetShinkaDigimon(0, 13) + be:SYSisGetShinkaDigimon(0, 14) + be:SYSisGetShinkaDigimon(0, 15) >= 8 then
    be:FLGset(924, 1)
end
be:FLGset(934, 0)
if g_messPlayerNo == 0 then
    be:FLGset(934, 1)
end
if be:FLGisOn(931) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(922) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10182 = "TALKFONT02/font00/I<196>"
        funcOneMessage(mswk10182)
        mswk10183 = "TALKFONT02/font00/I<197>"
        funcOneMessage(mswk10183)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(922) == 1 and be:FLGisOn(416) == 0 and be:FLGisOn(385) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10184 = "TALKFONT02/font00/I<198>"
        funcOneMessage(mswk10184)
        mswk10185 = "TALKFONT02/font00/I<199>"
        funcOneMessage(mswk10185)
        mswk10186 = "TALKFONT02/font00/I<200>"
        funcOneMessage(mswk10186)
        mswk10187 = "TALKFONT02/font00/I<201>"
        funcOneMessage(mswk10187)
        be:DMsetLua("bML01016.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(377) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10188 = "TALKFONT02/font00/I<198>"
        funcOneMessage(mswk10188)
        mswk10189 = "TALKFONT02/font00/I<199>"
        funcOneMessage(mswk10189)
        mswk10190 = "TALKFONT02/font00/I<200>"
        funcOneMessage(mswk10190)
        mswk10191 = "TALKFONT02/font00/I<201>"
        funcOneMessage(mswk10191)
        be:DMsetLua("bML01017.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(377) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10192 = "TALKFONT02/font00/I<202>"
        funcOneMessage(mswk10192)
        mswk10193 = "TALKFONT02/font00/I<203>"
        funcOneMessage(mswk10193)
        be:DMsetLua("bML01018.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10194 = "TALKFONT02/font00/I<204>"
        funcOneMessage(mswk10194)
        mswk10195 = "TALKFONT02/font00/I<205>"
        funcOneMessage(mswk10195)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(922) == 1 and be:FLGisOn(416) == 1 and be:FLGisOn(385) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10196 = "TALKFONT02/font00/I<206>"
        funcOneMessage(mswk10196)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(931) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(922) == 1 and be:FLGisOn(416) == 0 and be:FLGisOn(385) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10197 = "TALKFONT02/font00/I<207>"
        funcOneMessage(mswk10197)
        be:DMsetLua("treasure02.lua")
        be:DMrun()
        be:FLGset(416, 1)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10198 = "TALKFONT02/font00/I<208>"
        funcOneMessage(mswk10198)
        mswk10199 = "TALKFONT02/font00/I<209>"
        funcOneMessage(mswk10199)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(923) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10200 = "TALKFONT02/font00/I<196>"
        funcOneMessage(mswk10200)
        mswk10201 = "TALKFONT02/font00/I<197>"
        funcOneMessage(mswk10201)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(923) == 1 and be:FLGisOn(416) == 0 and be:FLGisOn(385) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10202 = "TALKFONT02/font00/I<204>"
        funcOneMessage(mswk10202)
        mswk10203 = "TALKFONT02/font00/I<205>"
        funcOneMessage(mswk10203)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10204 = "TALKFONT02/font00/I<198>"
        funcOneMessage(mswk10204)
        mswk10205 = "TALKFONT02/font00/I<199>"
        funcOneMessage(mswk10205)
        mswk10206 = "TALKFONT02/font00/I<200>"
        funcOneMessage(mswk10206)
        mswk10207 = "TALKFONT02/font00/I<201>"
        funcOneMessage(mswk10207)
        be:DMsetLua("bML01016.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(377) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10208 = "TALKFONT02/font00/I<198>"
        funcOneMessage(mswk10208)
        mswk10209 = "TALKFONT02/font00/I<199>"
        funcOneMessage(mswk10209)
        mswk10210 = "TALKFONT02/font00/I<200>"
        funcOneMessage(mswk10210)
        mswk10211 = "TALKFONT02/font00/I<201>"
        funcOneMessage(mswk10211)
        be:DMsetLua("bML01017.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(377) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10212 = "TALKFONT02/font00/I<202>"
        funcOneMessage(mswk10212)
        mswk10213 = "TALKFONT02/font00/I<203>"
        funcOneMessage(mswk10213)
        be:DMsetLua("bML01018.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(923) == 1 and be:FLGisOn(416) == 1 and be:FLGisOn(385) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10214 = "TALKFONT02/font00/I<206>"
        funcOneMessage(mswk10214)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(932) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(923) == 1 and be:FLGisOn(416) == 0 and be:FLGisOn(385) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10215 = "TALKFONT02/font00/I<207>"
        funcOneMessage(mswk10215)
        be:DMsetLua("treasure02.lua")
        be:DMrun()
        be:FLGset(416, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10216 = "TALKFONT02/font00/I<208>"
        funcOneMessage(mswk10216)
        mswk10217 = "TALKFONT02/font00/I<209>"
        funcOneMessage(mswk10217)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(924) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10218 = "TALKFONT02/font00/I<196>"
        funcOneMessage(mswk10218)
        mswk10219 = "TALKFONT02/font00/I<197>"
        funcOneMessage(mswk10219)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(924) == 1 and be:FLGisOn(416) == 0 and be:FLGisOn(385) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10220 = "TALKFONT02/font00/I<204>"
        funcOneMessage(mswk10220)
        mswk10221 = "TALKFONT02/font00/I<205>"
        funcOneMessage(mswk10221)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10222 = "TALKFONT02/font00/I<198>"
        funcOneMessage(mswk10222)
        mswk10223 = "TALKFONT02/font00/I<199>"
        funcOneMessage(mswk10223)
        mswk10224 = "TALKFONT02/font00/I<200>"
        funcOneMessage(mswk10224)
        mswk10225 = "TALKFONT02/font00/I<201>"
        funcOneMessage(mswk10225)
        be:DMsetLua("bML01016.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(377) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10226 = "TALKFONT02/font00/I<198>"
        funcOneMessage(mswk10226)
        mswk10227 = "TALKFONT02/font00/I<199>"
        funcOneMessage(mswk10227)
        mswk10228 = "TALKFONT02/font00/I<200>"
        funcOneMessage(mswk10228)
        mswk10229 = "TALKFONT02/font00/I<201>"
        funcOneMessage(mswk10229)
        be:DMsetLua("bML01017.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(377) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10230 = "TALKFONT02/font00/I<202>"
        funcOneMessage(mswk10230)
        mswk10231 = "TALKFONT02/font00/I<203>"
        funcOneMessage(mswk10231)
        be:DMsetLua("bML01018.lua")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(924) == 1 and be:FLGisOn(416) == 1 and be:FLGisOn(385) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10232 = "TALKFONT02/font00/I<206>"
        funcOneMessage(mswk10232)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(933) == 1 and be:FLGisOn(90) == 1 and be:FLGisOn(924) == 1 and be:FLGisOn(416) == 0 and be:FLGisOn(385) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10233 = "TALKFONT02/font00/I<207>"
        funcOneMessage(mswk10233)
        be:DMsetLua("treasure02.lua")
        be:DMrun()
        be:FLGset(416, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10234 = "TALKFONT02/font00/I<208>"
        funcOneMessage(mswk10234)
        mswk10235 = "TALKFONT02/font00/I<209>"
        funcOneMessage(mswk10235)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(3) == 1 and be:FLGisOn(90) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10236 = "TALKFONT02/font00/I<210>"
        funcOneMessage(mswk10236)
        mswk10237 = "TALKFONT02/font00/I<211>"
        funcOneMessage(mswk10237)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
