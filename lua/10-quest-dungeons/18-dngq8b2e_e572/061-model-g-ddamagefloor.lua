local local_0
if be:MATisPlayer() == 1 then
    g_matt03 = 1
else
    g_matt03 = 0
end
if g_matt02 ~= 1 then
    if g_matt03 == 1 then
    end
end
for ramNo = 11, 21 do
    be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON")
end
