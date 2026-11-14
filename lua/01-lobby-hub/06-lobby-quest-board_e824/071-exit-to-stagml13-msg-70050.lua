g_StChangeKind = "trans"
if be:MATisAllPlayer() == 1 then
    if be:FLGisOn(336) == 1 then
        be:FLGset(336, 0)
    end
    if be:DMgetCount() == 0 then
        mswk70050 = "STCHGFONT00/font00/I<131>"
        funcStageChange("stagML13", 2, mswk70050, 5)
    end
end
