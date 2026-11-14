local local_0
funcPlayerStatusSet()
be:sd("SOUND", nil, -1, "PLAY", "AM_DUNGE")
be:sd("SOUND", nil, -1, "PLAY", "DG_CAVE2")
if be:PLAYERgetPos() == 2 then
    funcStageIn("trans")
else
    be:sd("PLAYER", nil, -1, "SQ_DEMOWALK", 15)
    be:sd("PLAYER", nil, -1, "SQ_WAIT", 60)
end
for playerIndex = 0, 3 do
    if be:SYSisJoinPlayer(playerIndex) == 1 then
        be:sd("PLAYER", be:SYSgetPlayerName(playerIndex), playerIndex, "SETMETAL", 60)
    end
end
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN30", 5)
