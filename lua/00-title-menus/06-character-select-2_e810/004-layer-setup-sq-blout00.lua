local local_0
funcStartLayerSet()
if be:SYSgetDifficulty() == 0 then
    for index = 0, 11 do
        be:FLGset(518 + index, be:SYSctlFlagFolder("IS", index))
    end
end
if be:SYSgetDifficulty() == 1 then
    for index = 0, 11 do
        be:FLGset(530 + index, be:SYSctlFlagFolder("IS", index))
    end
end
if be:SYSgetDifficulty() == 2 then
    for index = 0, 11 do
        be:FLGset(542 + index, be:SYSctlFlagFolder("IS", index))
    end
end
be:MsgBox("ïÕxÌæ¾É¸sµÜµ½/tOtH_Zbg")
if be:SYSgetDifficulty() == 0 then
    for index = 0, 5 do
        be:FLGset(700 + index, be:FLGisOn(1 + index))
    end
    for index = 0, 1 do
        be:FLGset(706 + index, be:FLGisOn(19 + index))
    end
    for index = 0, 3 do
        be:FLGset(708 + index, be:FLGisOn(67 + index))
    end
    be:FLGset(712, be:FLGisOn(83))
    be:FLGset(713, be:FLGisOn(86))
    for index = 0, 10 do
        be:FLGset(714 + index, be:FLGisOn(89 + index))
    end
    for index = 0, 7 do
        be:FLGset(725 + index, be:FLGisOn(320 + index))
    end
    for index = 0, 4 do
        be:FLGset(733 + index, be:FLGisOn(329 + index))
    end
    be:FLGset(738, be:FLGisOn(335))
    be:FLGset(801, be:FLGisOn(49))
    be:FLGset(804, be:FLGisOn(383))
    be:FLGset(807, be:FLGisOn(82))
    be:FLGset(810, be:FLGisOn(334))
elseif be:SYSgetDifficulty() == 1 then
    for index = 0, 5 do
        be:FLGset(7 + index, be:FLGisOn(1 + index))
    end
    for index = 0, 1 do
        be:FLGset(741 + index, be:FLGisOn(19 + index))
    end
    for index = 0, 3 do
        be:FLGset(74 + index, be:FLGisOn(67 + index))
    end
    be:FLGset(743, be:FLGisOn(83))
    be:FLGset(87, be:FLGisOn(86))
    for index = 0, 10 do
        be:FLGset(744 + index, be:FLGisOn(89 + index))
    end
    for index = 0, 7 do
        be:FLGset(755 + index, be:FLGisOn(320 + index))
    end
    for index = 0, 4 do
        be:FLGset(763 + index, be:FLGisOn(329 + index))
    end
    be:FLGset(768, be:FLGisOn(335))
    be:FLGset(802, be:FLGisOn(49))
    be:FLGset(805, be:FLGisOn(383))
    be:FLGset(808, be:FLGisOn(82))
    be:FLGset(811, be:FLGisOn(334))
elseif be:SYSgetDifficulty() == 2 then
    for index = 0, 5 do
        be:FLGset(13 + index, be:FLGisOn(1 + index))
    end
    for index = 0, 1 do
        be:FLGset(771 + index, be:FLGisOn(19 + index))
    end
    for index = 0, 3 do
        be:FLGset(78 + index, be:FLGisOn(67 + index))
    end
    be:FLGset(773, be:FLGisOn(83))
    be:FLGset(88, be:FLGisOn(86))
    for index = 0, 10 do
        be:FLGset(774 + index, be:FLGisOn(89 + index))
    end
    for index = 0, 7 do
        be:FLGset(785 + index, be:FLGisOn(320 + index))
    end
    for index = 0, 4 do
        be:FLGset(793 + index, be:FLGisOn(329 + index))
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
