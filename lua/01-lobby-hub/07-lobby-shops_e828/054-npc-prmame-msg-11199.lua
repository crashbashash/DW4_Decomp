be:FLGset(921, 0)
if be:SYSctlDiskFolder("ISMAX", 0, 11, 0) == 1 then
    be:FLGset(921, 1)
end
be:FLGset(935, 0)
if be:SYSgetPlayerNinzu() == 1 then
    be:FLGset(935, 1)
end
if be:FLGisOn(396) == 1 and be:FLGisOn(397) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11199 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk11199)
        mswk11200 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk11200)
        mswk11201 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk11201)
        mswk11202 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk11202)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11203 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk11203)
        mswk11204 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk11204)
        mswk11205 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk11205)
        mswk11206 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk11206)
        mswk11207 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk11207)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11208 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk11208)
        mswk11209 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk11209)
        mswk11210 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk11210)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11211 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11211)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(397) == 1 and be:FLGisOn(398) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11212 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk11212)
        mswk11213 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk11213)
        mswk11214 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk11214)
        mswk11215 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk11215)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11216 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk11216)
        mswk11217 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk11217)
        mswk11218 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk11218)
        mswk11219 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk11219)
        mswk11220 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk11220)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11221 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk11221)
        mswk11222 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk11222)
        mswk11223 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk11223)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11224 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11224)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(398) == 1 and be:FLGisOn(399) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11225 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk11225)
        mswk11226 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk11226)
        mswk11227 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk11227)
        mswk11228 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk11228)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11229 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk11229)
        mswk11230 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk11230)
        mswk11231 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk11231)
        mswk11232 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk11232)
        mswk11233 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk11233)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11234 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk11234)
        mswk11235 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk11235)
        mswk11236 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk11236)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11237 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11237)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(399) == 1 and be:FLGisOn(400) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11238 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk11238)
        mswk11239 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk11239)
        mswk11240 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk11240)
        mswk11241 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk11241)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11242 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk11242)
        mswk11243 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk11243)
        mswk11244 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk11244)
        mswk11245 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk11245)
        mswk11246 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk11246)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11247 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk11247)
        mswk11248 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk11248)
        mswk11249 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk11249)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11250 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11250)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(400) == 1 and be:FLGisOn(401) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11251 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk11251)
        mswk11252 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk11252)
        mswk11253 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk11253)
        mswk11254 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk11254)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11255 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk11255)
        mswk11256 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk11256)
        mswk11257 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk11257)
        mswk11258 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk11258)
        mswk11259 = "TALKFONT02/font00/I<230>"
        funcOneMessage(mswk11259)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11260 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk11260)
        mswk11261 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk11261)
        mswk11262 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk11262)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11263 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11263)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(401) == 1 and be:FLGisOn(402) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11264 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk11264)
        mswk11265 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk11265)
        mswk11266 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk11266)
        mswk11267 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk11267)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11268 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk11268)
        mswk11269 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk11269)
        mswk11270 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk11270)
        mswk11271 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk11271)
        mswk11272 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk11272)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11273 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk11273)
        mswk11274 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk11274)
        mswk11275 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk11275)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11276 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11276)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(402) == 1 and be:FLGisOn(403) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(403) == 0 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11277 = "TALKFONT02/font00/I<217>"
        funcOneMessage(mswk11277)
        mswk11278 = "TALKFONT02/font00/I<218>"
        funcOneMessage(mswk11278)
        mswk11279 = "TALKFONT02/font00/I<219>"
        funcOneMessage(mswk11279)
        mswk11280 = "TALKFONT02/font00/I<220>"
        funcOneMessage(mswk11280)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(403) == 0 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11281 = "TALKFONT02/font00/I<221>"
        funcOneMessage(mswk11281)
        mswk11282 = "TALKFONT02/font00/I<222>"
        funcOneMessage(mswk11282)
        mswk11283 = "TALKFONT02/font00/I<223>"
        funcOneMessage(mswk11283)
        mswk11284 = "TALKFONT02/font00/I<224>"
        funcOneMessage(mswk11284)
        mswk11285 = "TALKFONT02/font00/I<225>"
        funcOneMessage(mswk11285)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(403) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11286 = "TALKFONT02/font00/I<231>"
        funcOneMessage(mswk11286)
        mswk11287 = "TALKFONT02/font00/I<232>"
        funcOneMessage(mswk11287)
        mswk11288 = "TALKFONT02/font00/I<233>"
        funcOneMessage(mswk11288)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
        be:FLGset(0, 0)
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11289 = "TALKFONT02/font00/I<226>"
        funcOneMessage(mswk11289)
        mswk11290 = "TALKFONT02/font00/I<227>"
        funcOneMessage(mswk11290)
        mswk11291 = "TALKFONT02/font00/I<228>"
        funcOneMessage(mswk11291)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11292 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11292)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
elseif be:FLGisOn(403) == 1 and 1 == 1 then
    if be:FLGisOn(404) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11293 = "TALKFONT02/font00/I<231>"
        funcOneMessage(mswk11293)
        mswk11294 = "TALKFONT02/font00/I<232>"
        funcOneMessage(mswk11294)
        mswk11295 = "TALKFONT02/font00/I<233>"
        funcOneMessage(mswk11295)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
        be:FLGset(404, 1)
    elseif be:FLGisOn(404) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11296 = "TALKFONT02/font00/I<234>"
        funcOneMessage(mswk11296)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk11297 = "TALKFONT02/font00/I<229>"
        funcOneMessage(mswk11297)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
