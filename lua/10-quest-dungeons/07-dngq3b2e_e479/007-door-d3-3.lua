if be:MATisPlayer() == 1 and be:FLGisOn(129) ~= 1 then
    be:sd("GENERATER", nil, -1, "START", "GENE-08", 1)
end
if be:SYSgetDifficulty() > 0 and be:MATisPlayer(be:FLGisOn(), be, 121) == 1 and be:FLGisOn(134) ~= 1 and be:FLGisOn(144) ~= 1 then
    be:sd("MODELCTRL", "g_d3door", 9, "SQ_SWOF")
    be:sd("HITLANDMODEL", "doorwall10", 0, "ONHIT")
    be:FLGset(144, 1)
else
end
