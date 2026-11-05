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
be:FLGset(925, 0)
if be:SYSctlCardFolder("KAZU", 0) >= 25 then
    be:FLGset(925, 1)
end
be:FLGset(926, 0)
if be:SYSctlCardFolder("KAZU", 0) >= 35 then
    be:FLGset(926, 1)
end
be:FLGset(927, 0)
if be:SYSctlCardFolder("KAZU", 0) >= 45 then
    be:FLGset(927, 1)
end
be:FLGset(934, 0)
if g_messPlayerNo == 0 then
    be:FLGset(934, 1)
end
be:FLGset(936, 0)
if be:SYSgetPlayerNinzu() <= 2 then
    be:FLGset(936, 1)
end
if be:FLGisOn(931) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(925) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10270 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk10270)
        mswk10271 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk10271)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(925) == 1 and be:FLGisOn(936) == 1 and be:FLGisOn(418) == 0 and be:FLGisOn(387) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10272 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk10272)
        mswk10273 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk10273)
        mswk10274 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk10274)
        mswk10275 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk10275)
        mswk10276 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk10276)
        mswk10277 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk10277)
        be:DMsetLua("bML01022.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(379) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10278 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk10278)
        mswk10279 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk10279)
        mswk10280 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk10280)
        mswk10281 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk10281)
        mswk10282 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk10282)
        mswk10283 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk10283)
        be:DMsetLua("bML01023.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(379) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10284 = "TALKFONT02/font00/I<230>"
        funcOneMessage(mswk10284)
        be:DMsetLua("bML01024.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10285 = "TALKFONT02/font00/I<231>"
        funcOneMessage(mswk10285)
        mswk10286 = "TALKFONT02/font00/I<232>"
        funcOneMessage(mswk10286)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(925) == 1 and be:FLGisOn(418) == 1 and be:FLGisOn(387) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10287 = "TALKFONT02/font00/I<233>"
        funcOneMessage(mswk10287)
        mswk10288 = "TALKFONT02/font00/I<234>"
        funcOneMessage(mswk10288)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(925) == 1 and be:FLGisOn(418) == 0 and be:FLGisOn(387) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10289 = "TALKFONT02/font00/I<235>"
        funcOneMessage(mswk10289)
        be:DMsetLua("treasure04.lua")
        be:DMrun()
        be:FLGset(418, 1)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
        be:FLGset(0, 0)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10290 = "TALKFONT02/font00/I<236>"
        funcOneMessage(mswk10290)
        mswk10291 = "TALKFONT02/font00/I<237>"
        funcOneMessage(mswk10291)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(931) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(925) == 1 and be:FLGisOn(936) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10292 = "TALKFONT02/font00/I<238>"
        funcOneMessage(mswk10292)
        mswk10293 = "TALKFONT02/font00/I<239>"
        funcOneMessage(mswk10293)
        mswk10294 = "TALKFONT02/font00/I<240>"
        funcOneMessage(mswk10294)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(926) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10295 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk10295)
        mswk10296 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk10296)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(926) == 1 and be:FLGisOn(936) == 1 and be:FLGisOn(418) == 0 and be:FLGisOn(387) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10297 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk10297)
        mswk10298 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk10298)
        mswk10299 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk10299)
        mswk10300 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk10300)
        mswk10301 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk10301)
        mswk10302 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk10302)
        be:DMsetLua("bML01022.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(379) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10303 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk10303)
        mswk10304 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk10304)
        mswk10305 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk10305)
        mswk10306 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk10306)
        mswk10307 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk10307)
        mswk10308 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk10308)
        be:DMsetLua("bML01023.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(379) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10309 = "TALKFONT02/font00/I<230>"
        funcOneMessage(mswk10309)
        be:DMsetLua("bML01024.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10310 = "TALKFONT02/font00/I<231>"
        funcOneMessage(mswk10310)
        mswk10311 = "TALKFONT02/font00/I<232>"
        funcOneMessage(mswk10311)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(926) == 1 and be:FLGisOn(418) == 1 and be:FLGisOn(387) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10312 = "TALKFONT02/font00/I<233>"
        funcOneMessage(mswk10312)
        mswk10313 = "TALKFONT02/font00/I<234>"
        funcOneMessage(mswk10313)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(926) == 1 and be:FLGisOn(418) == 0 and be:FLGisOn(387) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10314 = "TALKFONT02/font00/I<235>"
        funcOneMessage(mswk10314)
        be:DMsetLua("treasure04.lua")
        be:DMrun()
        be:FLGset(418, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10315 = "TALKFONT02/font00/I<236>"
        funcOneMessage(mswk10315)
        mswk10316 = "TALKFONT02/font00/I<237>"
        funcOneMessage(mswk10316)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(932) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(926) == 1 and be:FLGisOn(936) == 0 and 1 == 1 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10317 = "TALKFONT02/font00/I<238>"
        funcOneMessage(mswk10317)
        mswk10318 = "TALKFONT02/font00/I<239>"
        funcOneMessage(mswk10318)
        mswk10319 = "TALKFONT02/font00/I<240>"
        funcOneMessage(mswk10319)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(927) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10320 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk10320)
        mswk10321 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk10321)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(927) == 1 and be:FLGisOn(936) == 1 and be:FLGisOn(418) == 0 and be:FLGisOn(387) == 0 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and be:FLGisOn(409) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10322 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk10322)
        mswk10323 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk10323)
        mswk10324 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk10324)
        mswk10325 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk10325)
        mswk10326 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk10326)
        mswk10327 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk10327)
        be:DMsetLua("bML01022.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(379) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10328 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk10328)
        mswk10329 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk10329)
        mswk10330 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk10330)
        mswk10331 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk10331)
        mswk10332 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk10332)
        mswk10333 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk10333)
        be:DMsetLua("bML01023.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 1 and be:FLGisOn(409) == 1 and be:FLGisOn(379) == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10334 = "TALKFONT02/font00/I<230>"
        funcOneMessage(mswk10334)
        be:DMsetLua("bML01024.lua")
        be:DMrun()
    elseif be:FLGisOn(934) == 0 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10335 = "TALKFONT02/font00/I<231>"
        funcOneMessage(mswk10335)
        mswk10336 = "TALKFONT02/font00/I<232>"
        funcOneMessage(mswk10336)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(927) == 1 and be:FLGisOn(418) == 1 and be:FLGisOn(387) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10337 = "TALKFONT02/font00/I<233>"
        funcOneMessage(mswk10337)
        mswk10338 = "TALKFONT02/font00/I<234>"
        funcOneMessage(mswk10338)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(927) == 1 and be:FLGisOn(418) == 0 and be:FLGisOn(387) == 1 and be:FLGisOn(3) == 0 then
    if be:FLGisOn(934) == 1 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10339 = "TALKFONT02/font00/I<235>"
        funcOneMessage(mswk10339)
        be:DMsetLua("treasure04.lua")
        be:DMrun()
        be:FLGset(418, 1)
    elseif be:FLGisOn(934) == 0 and 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10340 = "TALKFONT02/font00/I<241>"
        funcOneMessage(mswk10340)
        mswk10341 = "TALKFONT02/font00/I<237>"
        funcOneMessage(mswk10341)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(933) == 1 and be:FLGisOn(92) == 1 and be:FLGisOn(927) == 1 and be:FLGisOn(936) == 0 and be:FLGisOn(3) == 0 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10342 = "TALKFONT02/font00/I<238>"
        funcOneMessage(mswk10342)
        mswk10343 = "TALKFONT02/font00/I<239>"
        funcOneMessage(mswk10343)
        mswk10344 = "TALKFONT02/font00/I<240>"
        funcOneMessage(mswk10344)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(3) == 1 and be:FLGisOn(92) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_digilfm", "fWt")
        mswk10345 = "TALKFONT02/font00/I<242>"
        funcOneMessage(mswk10345)
        mswk10346 = "TALKFONT02/font00/I<243>"
        funcOneMessage(mswk10346)
        funcCloseMessage("talk", "n_digilfm", "fWt")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
