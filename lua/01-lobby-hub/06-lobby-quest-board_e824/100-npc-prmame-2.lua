be:FLGset(921, 0)
if be:SYSctlDiskFolder("ISMAX", 0, 11, 0) == 1 then
    be:FLGset(921, 1)
end
be:FLGset(935, 0)
if be:SYSgetPlayerNinzu() == 1 then
    be:FLGset(935, 1)
end
if be:FLGisOn(392) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(405) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10856 = "TALKFONT02/font00/I<505>"
        funcOneMessage(mswk10856)
        mswk10857 = "TALKFONT02/font00/I<506>"
        funcOneMessage(mswk10857)
        mswk10858 = "TALKFONT02/font00/I<507>"
        funcOneMessage(mswk10858)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
        be:FLGset(405, 1)
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(405) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10859 = "TALKFONT02/font00/I<508>"
        funcOneMessage(mswk10859)
        mswk10860 = "TALKFONT02/font00/I<509>"
        funcOneMessage(mswk10860)
        mswk10861 = "TALKFONT02/font00/I<510>"
        funcOneMessage(mswk10861)
        mswk10862 = "TALKFONT02/font00/I<511>"
        funcOneMessage(mswk10862)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(405) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10863 = "TALKFONT02/font00/I<512>"
        funcOneMessage(mswk10863)
        mswk10864 = "TALKFONT02/font00/I<513>"
        funcOneMessage(mswk10864)
        mswk10865 = "TALKFONT02/font00/I<514>"
        funcOneMessage(mswk10865)
        mswk10866 = "TALKFONT02/font00/I<515>"
        funcOneMessage(mswk10866)
        mswk10867 = "TALKFONT02/font00/I<516>"
        funcOneMessage(mswk10867)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10868 = "TALKFONT02/font00/I<517>"
        funcOneMessage(mswk10868)
        mswk10869 = "TALKFONT02/font00/I<518>"
        funcOneMessage(mswk10869)
        mswk10870 = "TALKFONT02/font00/I<519>"
        funcOneMessage(mswk10870)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10871 = "TALKFONT02/font00/I<520>"
        funcOneMessage(mswk10871)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(392) == 1 and be:FLGisOn(393) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10872 = "TALKFONT02/font00/I<508>"
        funcOneMessage(mswk10872)
        mswk10873 = "TALKFONT02/font00/I<509>"
        funcOneMessage(mswk10873)
        mswk10874 = "TALKFONT02/font00/I<510>"
        funcOneMessage(mswk10874)
        mswk10875 = "TALKFONT02/font00/I<511>"
        funcOneMessage(mswk10875)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10876 = "TALKFONT02/font00/I<512>"
        funcOneMessage(mswk10876)
        mswk10877 = "TALKFONT02/font00/I<513>"
        funcOneMessage(mswk10877)
        mswk10878 = "TALKFONT02/font00/I<514>"
        funcOneMessage(mswk10878)
        mswk10879 = "TALKFONT02/font00/I<515>"
        funcOneMessage(mswk10879)
        mswk10880 = "TALKFONT02/font00/I<521>"
        funcOneMessage(mswk10880)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10881 = "TALKFONT02/font00/I<517>"
        funcOneMessage(mswk10881)
        mswk10882 = "TALKFONT02/font00/I<518>"
        funcOneMessage(mswk10882)
        mswk10883 = "TALKFONT02/font00/I<519>"
        funcOneMessage(mswk10883)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10884 = "TALKFONT02/font00/I<520>"
        funcOneMessage(mswk10884)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(393) == 1 and be:FLGisOn(394) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10885 = "TALKFONT02/font00/I<508>"
        funcOneMessage(mswk10885)
        mswk10886 = "TALKFONT02/font00/I<509>"
        funcOneMessage(mswk10886)
        mswk10887 = "TALKFONT02/font00/I<510>"
        funcOneMessage(mswk10887)
        mswk10888 = "TALKFONT02/font00/I<511>"
        funcOneMessage(mswk10888)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10889 = "TALKFONT02/font00/I<512>"
        funcOneMessage(mswk10889)
        mswk10890 = "TALKFONT02/font00/I<513>"
        funcOneMessage(mswk10890)
        mswk10891 = "TALKFONT02/font00/I<514>"
        funcOneMessage(mswk10891)
        mswk10892 = "TALKFONT02/font00/I<515>"
        funcOneMessage(mswk10892)
        mswk10893 = "TALKFONT02/font00/I<521>"
        funcOneMessage(mswk10893)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10894 = "TALKFONT02/font00/I<517>"
        funcOneMessage(mswk10894)
        mswk10895 = "TALKFONT02/font00/I<518>"
        funcOneMessage(mswk10895)
        mswk10896 = "TALKFONT02/font00/I<519>"
        funcOneMessage(mswk10896)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10897 = "TALKFONT02/font00/I<520>"
        funcOneMessage(mswk10897)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(394) == 1 and be:FLGisOn(395) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10898 = "TALKFONT02/font00/I<508>"
        funcOneMessage(mswk10898)
        mswk10899 = "TALKFONT02/font00/I<509>"
        funcOneMessage(mswk10899)
        mswk10900 = "TALKFONT02/font00/I<510>"
        funcOneMessage(mswk10900)
        mswk10901 = "TALKFONT02/font00/I<511>"
        funcOneMessage(mswk10901)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10902 = "TALKFONT02/font00/I<512>"
        funcOneMessage(mswk10902)
        mswk10903 = "TALKFONT02/font00/I<513>"
        funcOneMessage(mswk10903)
        mswk10904 = "TALKFONT02/font00/I<514>"
        funcOneMessage(mswk10904)
        mswk10905 = "TALKFONT02/font00/I<515>"
        funcOneMessage(mswk10905)
        mswk10906 = "TALKFONT02/font00/I<521>"
        funcOneMessage(mswk10906)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10907 = "TALKFONT02/font00/I<517>"
        funcOneMessage(mswk10907)
        mswk10908 = "TALKFONT02/font00/I<518>"
        funcOneMessage(mswk10908)
        mswk10909 = "TALKFONT02/font00/I<519>"
        funcOneMessage(mswk10909)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10910 = "TALKFONT02/font00/I<520>"
        funcOneMessage(mswk10910)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if be:FLGisOn(395) == 1 and be:FLGisOn(396) == 0 and 1 == 1 then
    if be:FLGisOn(935) == 1 and be:FLGisOn(921) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10911 = "TALKFONT02/font00/I<508>"
        funcOneMessage(mswk10911)
        mswk10912 = "TALKFONT02/font00/I<509>"
        funcOneMessage(mswk10912)
        mswk10913 = "TALKFONT02/font00/I<510>"
        funcOneMessage(mswk10913)
        mswk10914 = "TALKFONT02/font00/I<511>"
        funcOneMessage(mswk10914)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(935) == 1 and be:FLGisOn(921) == 1 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10915 = "TALKFONT02/font00/I<512>"
        funcOneMessage(mswk10915)
        mswk10916 = "TALKFONT02/font00/I<513>"
        funcOneMessage(mswk10916)
        mswk10917 = "TALKFONT02/font00/I<514>"
        funcOneMessage(mswk10917)
        mswk10918 = "TALKFONT02/font00/I<515>"
        funcOneMessage(mswk10918)
        mswk10919 = "TALKFONT02/font00/I<521>"
        funcOneMessage(mswk10919)
        be:DMsetLua("bML01055.lua")
        be:DMrun()
    elseif be:FLGisOn(935) == 0 and be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10920 = "TALKFONT02/font00/I<517>"
        funcOneMessage(mswk10920)
        mswk10921 = "TALKFONT02/font00/I<518>"
        funcOneMessage(mswk10921)
        mswk10922 = "TALKFONT02/font00/I<519>"
        funcOneMessage(mswk10922)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10923 = "TALKFONT02/font00/I<520>"
        funcOneMessage(mswk10923)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
if g_lFLG16 == 1 and 1 == 1 then
    if be:FLGisOn(3) == 0 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10924 = "TALKFONT02/font00/I<508>"
        funcOneMessage(mswk10924)
        mswk10925 = "TALKFONT02/font00/I<509>"
        funcOneMessage(mswk10925)
        mswk10926 = "TALKFONT02/font00/I<510>"
        funcOneMessage(mswk10926)
        mswk10927 = "TALKFONT02/font00/I<511>"
        funcOneMessage(mswk10927)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    elseif be:FLGisOn(3) == 1 then
        funcOpenMessage("talk", "n_prmame", "vX}")
        mswk10928 = "TALKFONT02/font00/I<520>"
        funcOneMessage(mswk10928)
        funcCloseMessage("talk", "n_prmame", "vX}")
        be:DMrun()
    else
        be:MsgBox("fobOFïbÌ§äÉ²¯ª èÜ·")
    end
end
