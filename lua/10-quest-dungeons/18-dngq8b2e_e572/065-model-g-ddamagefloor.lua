local local_0
if be:MATisPlayer() == 1 then
    g_matt07 = 1
else
    g_matt07 = 0
end
if g_matt06 ~= 1 then
    if g_matt07 == 1 then
    end
end
for ramNo = 44, 54 do
    be:sd("MODELCTRL", "g_ddamagefloor", ramNo, "SETLABEL", "SQ_WAIT/ON")
end
