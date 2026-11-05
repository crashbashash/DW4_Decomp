if be:MDLgetRamNo() == 0 then
    be:FLGset(247, 1)
    be:sd("MODELCTRL", "g_dcap", 0, "SQ_DDMG")
end
