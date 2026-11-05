if be:MATisPlayer() == 1 then
    g_matt06 = 1
else
    g_matt06 = 0
end
if g_matt06 ~= 1 then
    if g_matt07 == 1 then
        for local_1 = 44, 54 do
            be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
        end
    end
end
for local_1 = 44, 54 do
    be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
end
