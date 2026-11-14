local local_0
if be:MATisPlayer() == 1 then
    if g_dcap ~= 1 then
        for ramNo = 0, 8 do
            be:sd("MODELCTRL", "g_dcap", ramNo, "SQ_DDMG")
        end
        g_dcap = 1
    end
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-02")
    be:sd("GENERATER", nil, -1, "STOPREVERS", "GENE-05")
    for ramNo = 8, 13 do
        be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON")
    end
end
for ramNo = 8, 13 do
    be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/OFF")
end
