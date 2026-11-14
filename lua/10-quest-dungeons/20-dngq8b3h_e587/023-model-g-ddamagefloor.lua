local local_0
if be:MATisPlayer() == 1 then
    for ramNo = 0, 2 do
        be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON")
    end
end
for ramNo = 0, 2 do
    be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/OFF")
end
