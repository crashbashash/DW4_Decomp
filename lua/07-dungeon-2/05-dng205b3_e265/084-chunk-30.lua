if be:MDLisStatus(local_0, local_1, "BIND") == 0 then
    be:sd("MODELCTRL", local_0, local_1, "SQ_BEND", 0)
else
    be:sd("MODELCTRL", local_0, local_1, "SQ_WAIT", 0)
end
