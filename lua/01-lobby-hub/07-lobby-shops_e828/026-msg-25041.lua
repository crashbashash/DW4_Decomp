be:sd("MODELCTRL", "n_metete", 0, "SQ_TALK")
be:sd("LAYERCTL", nil, -1, "SWITCH", "WN01/CLR")
be:sd("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
be:sd("PLAYER", nil, -1, "OFCTRL")
be:sd("ENEMY", nil, -1, "OFCTRL")
if be:COUNTERget(1) < 1000 then
    mswk25041 = "TALKFONT02/font00/I<62>"
    funcOneMessage(mswk25041)
    mswk25042 = "TALKFONT02/font00/I<63>"
    funcOneMessage(mswk25042)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 6000 then
    mswk25043 = "TALKFONT02/font00/I<64>"
    funcOneMessage(mswk25043)
    mswk25044 = "TALKFONT02/font00/I<65>"
    funcOneMessage(mswk25044)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 26000 then
    mswk25045 = "TALKFONT02/font00/I<66>"
    funcOneMessage(mswk25045)
    mswk25046 = "TALKFONT02/font00/I<67>"
    funcOneMessage(mswk25046)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 86000 then
    mswk25047 = "TALKFONT02/font00/I<68>"
    funcOneMessage(mswk25047)
    mswk25048 = "TALKFONT02/font00/I<69>"
    funcOneMessage(mswk25048)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 206000 then
    mswk25049 = "TALKFONT02/font00/I<70>"
    funcOneMessage(mswk25049)
    mswk25050 = "TALKFONT02/font00/I<71>"
    funcOneMessage(mswk25050)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 456000 then
    mswk25051 = "TALKFONT02/font00/I<72>"
    funcOneMessage(mswk25051)
    mswk25052 = "TALKFONT02/font00/I<73>"
    funcOneMessage(mswk25052)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 956000 then
    mswk25053 = "TALKFONT02/font00/I<74>"
    funcOneMessage(mswk25053)
    mswk25054 = "TALKFONT02/font00/I<75>"
    funcOneMessage(mswk25054)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 1956000 then
    mswk25055 = "TALKFONT02/font00/I<76>"
    funcOneMessage(mswk25055)
    mswk25056 = "TALKFONT02/font00/I<77>"
    funcOneMessage(mswk25056)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
elseif be:COUNTERget(1) < 3956000 then
    mswk25057 = "TALKFONT02/font00/I<78>"
    funcOneMessage(mswk25057)
    mswk25058 = "TALKFONT02/font00/I<79>"
    funcOneMessage(mswk25058)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
else
    mswk25059 = "TALKFONT02/font00/I<80>"
    funcOneMessage(mswk25059)
    mswk25060 = "TALKFONT02/font00/I<81>"
    funcOneMessage(mswk25060)
    be:DMsetLua("bML01012.lua")
    be:DMrun()
end
