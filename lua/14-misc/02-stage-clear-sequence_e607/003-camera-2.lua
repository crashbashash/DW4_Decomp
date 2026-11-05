be:DMsetSD("PLAYER", nil, -1, "OFCTRL", 180)
be:DMsetSD("CAMERA", nil, -1, "SETDEMOCAMERA", "stageend", 220)
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "==0")
be:DMsetSD("ENEMY", nil, -1, "OFCTRL")
be:DMsetSD("LAYERCTL", nil, -1, "SWITCH", "WN00/CLR")
for local_3 = 0, 3 do
    if be:SYSisJoinPlayer(local_3) == 1 then
        be:DMsetSD("PLAYER", be:SYSgetPlayerName(local_3), local_3, "MOVETRANS", be:PLAYERgetDataStr(0, local_3, 0))
        be:DMsetSD("PLAYER", nil, local_3, "SQ_WAIT")
        be:DMsetSD("GAMERAM", nil, 0, "ADDMP", "I<" .. local_3 .. ">/I<" .. local_6 .. ">")
    end
end
be:DMsetSD("PLAYER", nil, -1, "SQ_ENJOY", 10)
be:DMsetSD("SOUND", nil, -1, "PLAY", "QS_DOIT")
be:DMchkSD("CAMERA", nil, -1, "ISDEMOCAMERA", "!=0")
be:DMsetSD("SOUND", nil, -1, "PLAY", "ST_COMMA", 80)
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT30", 50)
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLOUT30", "!=0")
be:DMsetSD("CAMERA", nil, -1, "SETBOXCAMERA")
be:DMsetSD("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 30)
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "==0")
be:DMchkSD("MODELCTRL", "i_fadewn01", 0, "ISSEQNAME", "SQ_BLIN30", "!=0")
local_0()
mswk67101 = "TALKFONT05/font00/I<25>"
be:DMsetSD("MODELCTRL", "i_messwnsp", 0, "GENERATE", "SQ_OPEN")
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67101)
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISRUN", "==0")
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "==0")
be:DMchkSD("MODELCTRL", "i_messwnsp", 0, "ISSEQNAME", "SQ_OPEN", "!=0")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
mswk67102 = "TALKFONT05/font00/I<26>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67102)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/CLR")
mswk67103 = "TALKFONT05/font00/I<27>"
mswk67136 = "TALKFONT05/font00/I<28>"
if be:SYSgetTarget() == 3 then
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67136)
else
    be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67103)
end
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67104 = "TALKFONT05/font00/I<29>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67104)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67105 = "TALKFONT05/font00/I<30>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67105)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67106 = "TALKFONT05/font00/I<31>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67106)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67107 = "TALKFONT05/font00/I<32>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67107)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67108 = "TALKFONT05/font00/I<33>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67108)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
mswk67109 = "TALKFONT05/font00/I<24>"
be:DMsetSD("TEXTCTL", nil, -1, "TEXTSET", mswk67109)
be:DMsetSD("TEXTCTL", nil, -1, "SWITCH", "TALKFONT05/font00/SET")
be:DMsetSD("SELECTCTRL", "i_messky", 0, "GENERATE")
be:DMchkSD("MODELCTRL", "i_messky", 0, "ISRUN", "==0")
be:DMchkSD("SELECTCTRL", "i_messky", 0, "ISEND", "==0")
if be:FLGisOn(382) == 0 then
    be:DMsetSD("GENERATER", nil, -1, "START", "GENE-a02", 10)
elseif be:FLGisOn(382) == 1 then
    be:DMsetSD("GENERATER", nil, -1, "START", "GENE-b02", 10)
end
local_1()
be:DMrun()
