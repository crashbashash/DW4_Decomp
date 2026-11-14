be:sd("CAMERA", nil, -1, "SETDEMOCAMERA", "entry")
funcFirstLayerSet()
if be:SYSgetArea() == 0 then
    be:sd("MOVIE", nil, -1, "PLAY", "AJP_opening.sfd")
elseif be:SYSgetArea() == 1 then
    be:sd("MOVIE", nil, -1, "PLAY", "AUS_opening.sfd")
elseif be:SYSgetArea() == 2 then
    be:sd("MOVIE", nil, -1, "PLAY", "AEU_opening.sfd")
end
be:sd("STAGECTL", nil, -1, "PADINPUT", "ENABLE", 120)
