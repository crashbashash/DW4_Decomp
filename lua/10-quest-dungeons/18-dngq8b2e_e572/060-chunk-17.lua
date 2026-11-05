if be:MATisPlayer() == 1 then
    g_matt02 = 1
else
    g_matt02 = 0
end
if g_matt02 ~= 1 then
    if g_matt03 == 1 then
        for local_1 = 11, 21 do
            be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
        end
    end
end
for local_1 = 11, 21 do
    be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
end
