funcStartLayerSet()
if be:SYSgetDifficulty() == 0 then
    for local_1 = 0, 11 do
        be:FLGset(518 + local_1, be:SYSctlFlagFolder("IS", local_1))
    end
end
if be:SYSgetDifficulty() == 1 then
    for local_1 = 0, 11 do
        be:FLGset(530 + local_1, be:SYSctlFlagFolder("IS", local_1))
    end
end
if be:SYSgetDifficulty() == 2 then
    for local_1 = 0, 11 do
        be:FLGset(542 + local_1, be:SYSctlFlagFolder("IS", local_1))
    end
end
be:MsgBox("ïÕxÌæ¾É¸sµÜµ½/tOtH_Zbg")
if be:SYSgetDifficulty() == 0 then
    for local_1 = 0, 5 do
        be:FLGset(700 + local_1, be:FLGisOn(1 + local_1))
    end
    for local_1 = 0, 1 do
        be:FLGset(706 + local_1, be:FLGisOn(19 + local_1))
    end
    for local_1 = 0, 3 do
        be:FLGset(708 + local_1, be:FLGisOn(67 + local_1))
    end
    be:FLGset(712, be:FLGisOn(83))
    be:FLGset(713, be:FLGisOn(86))
    for local_1 = 0, 10 do
        be:FLGset(714 + local_1, be:FLGisOn(89 + local_1))
    end
    for local_1 = 0, 7 do
        be:FLGset(725 + local_1, be:FLGisOn(320 + local_1))
    end
    for local_1 = 0, 4 do
        be:FLGset(733 + local_1, be:FLGisOn(329 + local_1))
    end
    be:FLGset(738, be:FLGisOn(335))
    be:FLGset(801, be:FLGisOn(49))
    be:FLGset(804, be:FLGisOn(383))
    be:FLGset(807, be:FLGisOn(82))
    be:FLGset(810, be:FLGisOn(334))
elseif be:SYSgetDifficulty() == 1 then
    for local_1 = 0, 5 do
        be:FLGset(7 + local_1, be:FLGisOn(1 + local_1))
    end
    for local_1 = 0, 1 do
        be:FLGset(741 + local_1, be:FLGisOn(19 + local_1))
    end
    for local_1 = 0, 3 do
        be:FLGset(74 + local_1, be:FLGisOn(67 + local_1))
    end
    be:FLGset(743, be:FLGisOn(83))
    be:FLGset(87, be:FLGisOn(86))
    for local_1 = 0, 10 do
        be:FLGset(744 + local_1, be:FLGisOn(89 + local_1))
    end
    for local_1 = 0, 7 do
        be:FLGset(755 + local_1, be:FLGisOn(320 + local_1))
    end
    for local_1 = 0, 4 do
        be:FLGset(763 + local_1, be:FLGisOn(329 + local_1))
    end
    be:FLGset(768, be:FLGisOn(335))
    be:FLGset(802, be:FLGisOn(49))
    be:FLGset(805, be:FLGisOn(383))
    be:FLGset(808, be:FLGisOn(82))
    be:FLGset(811, be:FLGisOn(334))
elseif be:SYSgetDifficulty() == 2 then
    for local_1 = 0, 5 do
        be:FLGset(13 + local_1, be:FLGisOn(1 + local_1))
    end
    for local_1 = 0, 1 do
        be:FLGset(771 + local_1, be:FLGisOn(19 + local_1))
    end
    for local_1 = 0, 3 do
        be:FLGset(78 + local_1, be:FLGisOn(67 + local_1))
    end
    be:FLGset(773, be:FLGisOn(83))
    be:FLGset(88, be:FLGisOn(86))
    for local_1 = 0, 10 do
        be:FLGset(774 + local_1, be:FLGisOn(89 + local_1))
    end
    for local_1 = 0, 7 do
        be:FLGset(785 + local_1, be:FLGisOn(320 + local_1))
    end
    for local_1 = 0, 4 do
        be:FLGset(793 + local_1, be:FLGisOn(329 + local_1))
    end
    be:FLGset(798, be:FLGisOn(335))
    be:FLGset(803, be:FLGisOn(49))
    be:FLGset(806, be:FLGisOn(383))
    be:FLGset(809, be:FLGisOn(82))
    be:FLGset(812, be:FLGisOn(334))
else
    be:MsgBox("ïÕxÌæ¾É¸sµÜµ½/tOtH_Zbg")
end
be:sd("SOUND", nil, -1, "PLAY", "RM_NSHOP")
be:sd("MODELCTRL", "i_fadewn01", 0, "GENERATE", "SQ_BLOUT00")
