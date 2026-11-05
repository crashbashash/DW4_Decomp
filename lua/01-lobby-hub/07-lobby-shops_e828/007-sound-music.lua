be:sd("STAGECTL", nil, -1, "PADINPUT", "DISABLE")
if be:FLGisOn(364) == 0 then
    if be:FLGisOn(3) == 0 then
        be:sd("SOUND", nil, -1, "PLAY", "AM_LOBBY")
    elseif be:FLGisOn(3) == 1 then
        be:sd("SOUND", nil, -1, "PLAY", "AM_OFNI2")
    end
    if be:FLGisOn(3) == 0 then
        be:sd("SOUND", nil, -1, "PLAY", "ST_LOBBY")
    elseif be:FLGisOn(3) == 1 then
        be:sd("SOUND", nil, -1, "PLAY", "QS_HURRY")
    end
end
be:sd("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 30)
