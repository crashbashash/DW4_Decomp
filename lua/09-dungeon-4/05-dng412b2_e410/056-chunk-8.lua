if be:MATisPlayer() == 1 then
    if g_dcap ~= 1 then
        for local_1 = 0, 8 do
            be:sd("MODELCTRL", "g_dcap", local_1, "SQ_DDMG")
        end
        g_dcap = 1
    end
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    for local_1 = 8, 13 do
        be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/ON")
    end
end
for local_1 = 8, 13 do
    be:sd("MODELCTRL", "g_ddamagefloor", local_1, "SETLABEL", "SQ_WAIT/OFF")
end
