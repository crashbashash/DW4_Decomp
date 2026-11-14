local local_0
if be:MATisPlayer() == 1 then
    for ramNo = 9, 12 do
        be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON")
    end
end
for ramNo = 9, 12 do
    be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/OFF")
end
