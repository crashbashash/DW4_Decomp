if be:MATisPlayer() == 1 then
    for local_1 = 6, 8 do
        be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
    end
end
for local_1 = 6, 8 do
    be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/OFF")
end
