be:FLGset(902, 0)
if be:SYSctlFlagFolder("IS", 6) == 1 and be:SYSctlFlagFolder("IS", 7) == 1 and be:SYSctlFlagFolder("IS", 8) == 1 then
    be:FLGset(902, 1)
end
if be:FLGisOn(333) == 0 then
    if be:FLGisOn(902) == 0 and g_lFLG00 ~= 1 then
        funcOpenMessage("talk", "n_gekoa", "ÎñØ¢QR")
        mswk11412 = "TALKFONT02/font00/I<22>"
        funcOneMessage(mswk11412)
        mswk11413 = "TALKFONT02/font00/I<23>"
        funcOneMessage(mswk11413)
        mswk11414 = "TALKFONT02/font00/I<24>"
        funcOneMessage(mswk11414)
        funcCloseMessage("talk", "n_gekoa", "ÎñØ¢QR")
        be:DMrun()
        g_lFLG00 = 1
    elseif be:FLGisOn(902) == 0 and g_lFLG00 == 1 then
        funcOpenMessage("talk", "n_gekoa", "ÎñØ¢QR")
        mswk11415 = "TALKFONT02/font00/I<25>"
        funcOneMessage(mswk11415)
        mswk11416 = "TALKFONT02/font00/I<24>"
        funcOneMessage(mswk11416)
        funcCloseMessage("talk", "n_gekoa", "ÎñØ¢QR")
        be:DMrun()
    elseif be:FLGisOn(902) == 1 and be:FLGisOn(333) == 0 then
        funcOpenMessage("talk", "n_gekoa", "ÎñØ¢QR")
        mswk11417 = "TALKFONT02/font00/I<22>"
        funcOneMessage(mswk11417)
        mswk11418 = "TALKFONT02/font00/I<26>"
        funcOneMessage(mswk11418)
        mswk11419 = "TALKFONT02/font00/I<27>"
        funcOneMessage(mswk11419)
        be:DMsetLua("demo00.lua")
        be:DMrun()
        be:FLGset(333, 1)
        be:FLGset(0, 0)
    elseif be:FLGisOn(902) == 1 and be:FLGisOn(333) == 1 then
        funcOpenMessage("talk", "n_gekoa", "ÎñØ¢QR")
        mswk11420 = "TALKFONT02/font00/I<28>"
        funcOneMessage(mswk11420)
        funcCloseMessage("talk", "n_gekoa", "ÎñØ¢QR")
        be:DMrun()
        be:FLGset(0, 0)
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(333) == 1 then
    if 1 == 1 then
        funcOpenMessage("talk", "n_gekoa", "ÎñØ¢QR")
        mswk11421 = "TALKFONT02/font00/I<28>"
        funcOneMessage(mswk11421)
        funcCloseMessage("talk", "n_gekoa", "ÎñØ¢QR")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
