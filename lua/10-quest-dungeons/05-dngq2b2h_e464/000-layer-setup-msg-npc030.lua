mswkNPC030 = "TALKFONT03/font00/I<9>"
local local_0
local count = 0
funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("SOUND", nil, -1, "PLAY", "QS_THEME")
be:sd("NDMWPANEL", nil, -1, "NOGATEDISK", "I<1>")
g_counter_min = floor(be:COUNTERget(0) / 60)
g_counter_sec = be:COUNTERget(0) - 60 * g_counter_min
be:sd("NUMBERCTRL", "timenm0", 0, "SETVALUE", "I<" .. g_counter_min .. ">")
be:sd("NUMBERCTRL", "timenm1", 0, "SETVALUE", "I<" .. g_counter_sec .. ">")
local list = {"-260", "-110", "40", "190"}
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        be:sd("NUMBERCTRL", "questnm0", playerIndex, "SETVALUE", "I<" .. be:COUNTERget(playerIndex + 3) .. ">")
        be:sd("MODELCTRL", "i_questnm0", playerIndex, "GENERATE", "V<" .. list[playerIndex + 1] .. ",-160,0>/SQ_OPEN", 60)
        count = count + 1
    end
end
if 1 < count then
    g_counter_total = be:COUNTERget(3) + be:COUNTERget(4) + be:COUNTERget(5) + be:COUNTERget(6)
    be:sd("NUMBERCTRL", "questnm1", 0, "SETVALUE", "I<" .. g_counter_total .. ">")
    be:sd("MODELCTRL", "i_questnm1", 0, "GENERATE", "V<-290,182,0>/SQ_OPEN", 60)
end
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
be:sd("MODELCTRL", "i_timenm0", 0, "GENERATE", "V<-290,217,0>/SQ_OPENDOWN", 60)
if be:FLGisOn(144) == 1 then
    be:sd("MODELCTRL", "i_timenm0", 0, "SQ_STOP", 61)
end
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
