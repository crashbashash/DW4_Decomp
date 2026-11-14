g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(336) == 0 then
        be:FLGset(336, 1)
    end
    if be:DMgetCount() == 0 then
        mswk70049 = "STCHGFONT00/font00/I<47>"
        funcStageChange("stagML12", 5, mswk70049, 2)
    end
end
