local showText = function(text, arg_1, arg_2, arg_3)
    be:sd("TEXTCTL", nil, -1, "TEXTSET", text)
    be:sd("TEXTCTL", nil, -1, "ALIGN", arg_1 .. "/" .. arg_2 .. "/" .. arg_3)
    be:sd("TEXTCTL", nil, -1, "SWITCH", arg_1 .. "/" .. arg_2 .. "/DISPON")
end
if be:TXTgetCallNo() == 1000 then
    mswkPRG1000 = "STWINFONT13/font000/I<404>"
    showText(mswkPRG1000, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1001 then
    mswkPRG1001 = "STWINFONT13/font000/I<405>"
    showText(mswkPRG1001, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1100 then
    mswkPRG1100 = "STWINFONT12/font000/I<406>"
    showText(mswkPRG1100, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1101 then
    mswkPRG1101 = "STWINFONT13/font000/I<407>"
    showText(mswkPRG1101, "STWINFONT13", "font000", "LEFT")
    mswkPRG1102 = "STWINFONT35/font001/I<408>"
    showText(mswkPRG1102, "STWINFONT35", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1103 then
    mswkPRG1103 = "STWINFONT14/font000/I<409>"
    showText(mswkPRG1103, "STWINFONT14", "font000", "LEFT")
    mswkPRG1104 = "STWINFONT14/font001/I<410>"
    showText(mswkPRG1104, "STWINFONT14", "font001", "LEFT")
    mswkPRG1105 = "STWINFONT14/font002/I<411>"
    showText(mswkPRG1105, "STWINFONT14", "font002", "LEFT")
    mswkPRG1106 = "STWINFONT14/font003/I<412>"
    showText(mswkPRG1106, "STWINFONT14", "font003", "LEFT")
    mswkPRG1107 = "STWINFONT14/font004/I<413>"
    showText(mswkPRG1107, "STWINFONT14", "font004", "LEFT")
    mswkPRG1108 = "STWINFONT14/font005/I<414>"
    showText(mswkPRG1108, "STWINFONT14", "font005", "LEFT")
    mswkPRG1109 = "STWINFONT14/font006/I<415>"
    showText(mswkPRG1109, "STWINFONT14", "font006", "LEFT")
elseif be:TXTgetCallNo() == 1110 then
    mswkPRG1110 = "STWINFONT13/font000/I<416>"
    showText(mswkPRG1110, "STWINFONT13", "font000", "LEFT")
    mswkPRG1111 = "STWINFONT35/font000/I<408>"
    showText(mswkPRG1111, "STWINFONT35", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1150 then
    mswkPRG1150 = "STWINFONT29/font000/I<417>"
    showText(mswkPRG1150, "STWINFONT29", "font000", "LEFT")
    mswkPRG1151 = "STWINFONT29/font001/I<418>"
    showText(mswkPRG1151, "STWINFONT29", "font001", "LEFT")
    mswkPRG1152 = "STWINFONT29/font002/I<419>"
    showText(mswkPRG1152, "STWINFONT29", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1153 then
    mswkPRG1153 = "STWINFONT29/font100/I<420>"
    showText(mswkPRG1153, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1154 then
    mswkPRG1154 = "STWINFONT29/font000/I<421>"
    showText(mswkPRG1154, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1155 then
    mswkPRG1155 = "STWINFONT29/font000/I<422>"
    showText(mswkPRG1155, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1156 then
    mswkPRG1156 = "STWINFONT29/font000/I<423>"
    showText(mswkPRG1156, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1157 then
    mswkPRG1157 = "STWINFONT29/font000/I<424>"
    showText(mswkPRG1157, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1158 then
    mswkPRG1158 = "STWINFONT29/font000/I<425>"
    showText(mswkPRG1158, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1159 then
    mswkPRG1159 = "STWINFONT29/font000/I<426>"
    showText(mswkPRG1159, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1160 then
    mswkPRG1160 = "STWINFONT29/font000/I<427>"
    showText(mswkPRG1160, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1161 then
    mswkPRG1161 = "STWINFONT29/font000/I<428>"
    showText(mswkPRG1161, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1162 then
    mswkPRG1162 = "STWINFONT29/font000/I<429>"
    showText(mswkPRG1162, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1163 then
    mswkPRG1163 = "STWINFONT29/font000/I<430>"
    showText(mswkPRG1163, "STWINFONT29", "font000", "LEFT")
    mswkPRG1164 = "STWINFONT29/font001/I<431>"
    showText(mswkPRG1164, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1165 then
    mswkPRG1165 = "STWINFONT29/font000/I<432>"
    showText(mswkPRG1165, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1166 then
    mswkPRG1166 = "STWINFONT29/font000/I<433>"
    showText(mswkPRG1166, "STWINFONT29", "font000", "LEFT")
    mswkPRG1167 = "STWINFONT29/font001/I<434>"
    showText(mswkPRG1167, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1168 then
    mswkPRG1168 = "STWINFONT29/font100/I<435>"
    showText(mswkPRG1168, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1169 then
    mswkPRG1169 = "STWINFONT29/font000/I<436>"
    showText(mswkPRG1169, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1170 then
    mswkPRG1170 = "STWINFONT29/font000/I<437>"
    showText(mswkPRG1170, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1171 then
    mswkPRG1171 = "STWINFONT29/font000/I<438>"
    showText(mswkPRG1171, "STWINFONT29", "font000", "LEFT")
    mswkPRG1172 = "STWINFONT29/font001/I<439>"
    showText(mswkPRG1172, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 11730 then
    mswkPRG11730 = "STWINFONT41/font000/I<407>"
    showText(mswkPRG11730, "STWINFONT41", "font000", "LEFT")
    mswkPRG11731 = "STWINFONT41/font001/I<409>"
    showText(mswkPRG11731, "STWINFONT41", "font001", "LEFT")
    mswkPRG11732 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11732, "STWINFONT41", "font002", "LEFT")
    mswkPRG11733 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11733, "STWINFONT41", "font003", "LEFT")
    mswkPRG11734 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11734, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11735 then
    mswkPRG11735 = "STWINFONT41/font000/I<407>"
    showText(mswkPRG11735, "STWINFONT41", "font000", "LEFT")
    mswkPRG11736 = "STWINFONT41/font001/I<410>"
    showText(mswkPRG11736, "STWINFONT41", "font001", "LEFT")
    mswkPRG11737 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11737, "STWINFONT41", "font002", "LEFT")
    mswkPRG11738 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11738, "STWINFONT41", "font003", "LEFT")
    mswkPRG11739 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11739, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11740 then
    mswkPRG11740 = "STWINFONT41/font000/I<407>"
    showText(mswkPRG11740, "STWINFONT41", "font000", "LEFT")
    mswkPRG11741 = "STWINFONT41/font001/I<411>"
    showText(mswkPRG11741, "STWINFONT41", "font001", "LEFT")
    mswkPRG11742 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11742, "STWINFONT41", "font002", "LEFT")
    mswkPRG11743 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11743, "STWINFONT41", "font003", "LEFT")
    mswkPRG11744 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11744, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11745 then
    mswkPRG11745 = "STWINFONT41/font000/I<407>"
    showText(mswkPRG11745, "STWINFONT41", "font000", "LEFT")
    mswkPRG11746 = "STWINFONT41/font001/I<412>"
    showText(mswkPRG11746, "STWINFONT41", "font001", "LEFT")
    mswkPRG11747 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11747, "STWINFONT41", "font002", "LEFT")
    mswkPRG11748 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11748, "STWINFONT41", "font003", "LEFT")
    mswkPRG11749 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11749, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11750 then
    mswkPRG11750 = "STWINFONT41/font000/I<407>"
    showText(mswkPRG11750, "STWINFONT41", "font000", "LEFT")
    mswkPRG11751 = "STWINFONT41/font001/I<413>"
    showText(mswkPRG11751, "STWINFONT41", "font001", "LEFT")
    mswkPRG11752 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11752, "STWINFONT41", "font002", "LEFT")
    mswkPRG11753 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11753, "STWINFONT41", "font003", "LEFT")
    mswkPRG11754 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11754, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11755 then
    mswkPRG11755 = "STWINFONT41/font000/I<407>"
    showText(mswkPRG11755, "STWINFONT41", "font000", "LEFT")
    mswkPRG11756 = "STWINFONT41/font001/I<414>"
    showText(mswkPRG11756, "STWINFONT41", "font001", "LEFT")
    mswkPRG11757 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11757, "STWINFONT41", "font002", "LEFT")
    mswkPRG11758 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11758, "STWINFONT41", "font003", "LEFT")
    mswkPRG11759 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11759, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11760 then
    mswkPRG11760 = "STWINFONT41/font000/I<407>"
    showText(mswkPRG11760, "STWINFONT41", "font000", "LEFT")
    mswkPRG11761 = "STWINFONT41/font001/I<415>"
    showText(mswkPRG11761, "STWINFONT41", "font001", "LEFT")
    mswkPRG11762 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11762, "STWINFONT41", "font002", "LEFT")
    mswkPRG11763 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11763, "STWINFONT41", "font003", "LEFT")
    mswkPRG11764 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11764, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11765 then
    mswkPRG11765 = "STWINFONT41/font001/I<409>"
    showText(mswkPRG11765, "STWINFONT41", "font001", "LEFT")
    mswkPRG11766 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11766, "STWINFONT41", "font002", "LEFT")
    mswkPRG11767 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11767, "STWINFONT41", "font003", "LEFT")
    mswkPRG11768 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11768, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11769 then
    mswkPRG11769 = "STWINFONT41/font001/I<411>"
    showText(mswkPRG11769, "STWINFONT41", "font001", "LEFT")
    mswkPRG11770 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11770, "STWINFONT41", "font002", "LEFT")
    mswkPRG11771 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11771, "STWINFONT41", "font003", "LEFT")
    mswkPRG11772 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11772, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11773 then
    mswkPRG11773 = "STWINFONT41/font001/I<412>"
    showText(mswkPRG11773, "STWINFONT41", "font001", "LEFT")
    mswkPRG11774 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11774, "STWINFONT41", "font002", "LEFT")
    mswkPRG11775 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11775, "STWINFONT41", "font003", "LEFT")
    mswkPRG11776 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11776, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11777 then
    mswkPRG11777 = "STWINFONT41/font001/I<413>"
    showText(mswkPRG11777, "STWINFONT41", "font001", "LEFT")
    mswkPRG11778 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11778, "STWINFONT41", "font002", "LEFT")
    mswkPRG11779 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11779, "STWINFONT41", "font003", "LEFT")
    mswkPRG11780 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11780, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11781 then
    mswkPRG11781 = "STWINFONT41/font001/I<443>"
    showText(mswkPRG11781, "STWINFONT41", "font001", "LEFT")
    mswkPRG11782 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11782, "STWINFONT41", "font002", "LEFT")
    mswkPRG11783 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11783, "STWINFONT41", "font003", "LEFT")
    mswkPRG11784 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11784, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11785 then
    mswkPRG11785 = "STWINFONT41/font001/I<444>"
    showText(mswkPRG11785, "STWINFONT41", "font001", "LEFT")
    mswkPRG11786 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11786, "STWINFONT41", "font002", "LEFT")
    mswkPRG11787 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11787, "STWINFONT41", "font003", "LEFT")
    mswkPRG11788 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11788, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11789 then
    mswkPRG11789 = "STWINFONT41/font001/I<445>"
    showText(mswkPRG11789, "STWINFONT41", "font001", "LEFT")
    mswkPRG11790 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11790, "STWINFONT41", "font002", "LEFT")
    mswkPRG11791 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11791, "STWINFONT41", "font003", "LEFT")
    mswkPRG11792 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11792, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 11793 then
    mswkPRG11793 = "STWINFONT41/font001/I<446>"
    showText(mswkPRG11793, "STWINFONT41", "font001", "LEFT")
    mswkPRG11794 = "STWINFONT41/font002/I<440>"
    showText(mswkPRG11794, "STWINFONT41", "font002", "LEFT")
    mswkPRG11795 = "STWINFONT41/font003/I<441>"
    showText(mswkPRG11795, "STWINFONT41", "font003", "LEFT")
    mswkPRG11796 = "STWINFONT29/font002/I<442>"
    showText(mswkPRG11796, "STWINFONT29", "font002", "LEFT")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font011/V<0.0, 0.96, 1.0>")
    be:sd("TEXTCTL", nil, -1, "COLOR", "STWINFONT41/font012/V<0.94, 0.4, 0.25>")
elseif be:TXTgetCallNo() == 1200 then
    mswkPRG1200 = "STWINFONT12/font000/I<447>"
    showText(mswkPRG1200, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1201 then
    mswkPRG1201 = "STWINFONT13/font001/I<448>"
    showText(mswkPRG1201, "STWINFONT13", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1202 then
    mswkPRG1202 = "STWINFONT22/font000/I<414>"
    showText(mswkPRG1202, "STWINFONT22", "font000", "LEFT")
    mswkPRG1203 = "STWINFONT22/font001/I<415>"
    showText(mswkPRG1203, "STWINFONT22", "font001", "LEFT")
    mswkPRG1204 = "STWINFONT22/font010/I<409>"
    showText(mswkPRG1204, "STWINFONT22", "font010", "LEFT")
    mswkPRG1205 = "STWINFONT22/font011/I<410>"
    showText(mswkPRG1205, "STWINFONT22", "font011", "LEFT")
    mswkPRG1206 = "STWINFONT22/font012/I<411>"
    showText(mswkPRG1206, "STWINFONT22", "font012", "LEFT")
    mswkPRG1207 = "STWINFONT22/font013/I<412>"
    showText(mswkPRG1207, "STWINFONT22", "font013", "LEFT")
    mswkPRG1208 = "STWINFONT22/font014/I<413>"
    showText(mswkPRG1208, "STWINFONT22", "font014", "LEFT")
    mswkPRG1209 = "STWINFONT22/font020/I<449>"
    showText(mswkPRG1209, "STWINFONT22", "font020", "LEFT")
    mswkPRG1210 = "STWINFONT22/font021/I<450>"
    showText(mswkPRG1210, "STWINFONT22", "font021", "LEFT")
    mswkPRG1211 = "STWINFONT22/font022/I<451>"
    showText(mswkPRG1211, "STWINFONT22", "font022", "LEFT")
    mswkPRG1212 = "STWINFONT22/font023/I<452>"
    showText(mswkPRG1212, "STWINFONT22", "font023", "LEFT")
    mswkPRG1213 = "STWINFONT22/font024/I<453>"
    showText(mswkPRG1213, "STWINFONT22", "font024", "LEFT")
    mswkPRG1214 = "STWINFONT22/font025/I<454>"
    showText(mswkPRG1214, "STWINFONT22", "font025", "LEFT")
    mswkPRG1215 = "STWINFONT22/font026/I<455>"
    showText(mswkPRG1215, "STWINFONT22", "font026", "LEFT")
    mswkPRG1216 = "STWINFONT22/font027/I<456>"
    showText(mswkPRG1216, "STWINFONT22", "font027", "LEFT")
    mswkPRG1217 = "STWINFONT22/font028/I<457>"
    showText(mswkPRG1217, "STWINFONT22", "font028", "LEFT")
elseif be:TXTgetCallNo() == 1218 then
    mswkPRG1218 = "STWINFONT37/font000/I<458>"
    showText(mswkPRG1218, "STWINFONT37", "font000", "LEFT")
    mswkPRG1219 = "STWINFONT37/font001/I<448>"
    showText(mswkPRG1219, "STWINFONT37", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1250 then
    mswkPRG1250 = "TALKFONT01/font00/I<459>"
    showText(mswkPRG1250, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 1251 then
    mswkPRG1251 = "TALKFONT01/font01/I<460>"
    showText(mswkPRG1251, "TALKFONT01", "font01", "LEFT")
    mswkPRG1252 = "TALKFONT01/font02/I<461>"
    showText(mswkPRG1252, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 1253 then
    mswkPRG1253 = "TALKFONT01/font00/I<462>"
    showText(mswkPRG1253, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 1254 then
    mswkPRG1254 = "STWINFONT29/font100/I<463>"
    showText(mswkPRG1254, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1255 then
    mswkPRG1255 = "STWINFONT29/font000/I<464>"
    showText(mswkPRG1255, "STWINFONT29", "font000", "LEFT")
    mswkPRG1256 = "STWINFONT29/font001/I<465>"
    showText(mswkPRG1256, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1257 then
    mswkPRG1257 = "STWINFONT29/font000/I<466>"
    showText(mswkPRG1257, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1258 then
    mswkPRG1258 = "STWINFONT29/font000/I<467>"
    showText(mswkPRG1258, "STWINFONT29", "font000", "LEFT")
    mswkPRG1259 = "STWINFONT29/font001/I<468>"
    showText(mswkPRG1259, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1260 then
    mswkPRG1260 = "STWINFONT29/font100/I<469>"
    showText(mswkPRG1260, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1261 then
    mswkPRG1261 = "TALKFONT01/font00/I<470>"
    showText(mswkPRG1261, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 1262 then
    mswkPRG1262 = "TALKFONT01/font01/I<471>"
    showText(mswkPRG1262, "TALKFONT01", "font01", "LEFT")
    mswkPRG1263 = "TALKFONT01/font02/I<472>"
    showText(mswkPRG1263, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 1264 then
    mswkPRG1264 = "TALKFONT01/font00/I<473>"
    showText(mswkPRG1264, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 1265 then
    mswkPRG1265 = "TALKFONT01/font01/I<474>"
    showText(mswkPRG1265, "TALKFONT01", "font01", "LEFT")
    mswkPRG1266 = "TALKFONT01/font02/I<475>"
    showText(mswkPRG1266, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 1267 then
    mswkPRG1267 = "TALKFONT01/font00/I<476>"
    showText(mswkPRG1267, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 1268 then
    mswkPRG1268 = "TALKFONT01/font01/I<477>"
    showText(mswkPRG1268, "TALKFONT01", "font01", "LEFT")
    mswkPRG1269 = "TALKFONT01/font02/I<478>"
    showText(mswkPRG1269, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 1270 then
    mswkPRG1270 = "STWINFONT29/font000/I<479>"
    showText(mswkPRG1270, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1271 then
    mswkPRG1271 = "STWINFONT29/font000/I<480>"
    showText(mswkPRG1271, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1272 then
    mswkPRG1272 = "STWINFONT29/font000/I<471>"
    showText(mswkPRG1272, "STWINFONT29", "font000", "LEFT")
    mswkPRG1273 = "STWINFONT29/font001/I<472>"
    showText(mswkPRG1273, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1274 then
    mswkPRG1274 = "TALKFONT01/font00/I<481>"
    showText(mswkPRG1274, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 1275 then
    mswkPRG1275 = "TALKFONT01/font00/I<482>"
    showText(mswkPRG1275, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 1300 then
    mswkPRG1300 = "STWINFONT12/font000/I<483>"
    showText(mswkPRG1300, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1301 then
    mswkPRG1301 = "STWINFONT36/font000/I<484>"
    showText(mswkPRG1301, "STWINFONT36", "font000", "LEFT")
    mswkPRG1302 = "STWINFONT36/font001/I<485>"
    showText(mswkPRG1302, "STWINFONT36", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1303 then
    mswkPRG1303 = "STWINFONT13/font000/I<486>"
    showText(mswkPRG1303, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1350 then
    mswkPRG1350 = "STWINFONT29/font000/I<487>"
    showText(mswkPRG1350, "STWINFONT29", "font000", "LEFT")
    mswkPRG1351 = "STWINFONT29/font001/I<488>"
    showText(mswkPRG1351, "STWINFONT29", "font001", "LEFT")
    mswkPRG1352 = "STWINFONT29/font002/I<419>"
    showText(mswkPRG1352, "STWINFONT29", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1353 then
    mswkPRG1353 = "STWINFONT29/font000/I<489>"
    showText(mswkPRG1353, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1354 then
    mswkPRG1354 = "STWINFONT29/font000/I<490>"
    showText(mswkPRG1354, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1355 then
    mswkPRG1355 = "STWINFONT29/font000/I<491>"
    showText(mswkPRG1355, "STWINFONT29", "font000", "LEFT")
    mswkPRG1356 = "STWINFONT29/font001/I<492>"
    showText(mswkPRG1356, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1357 then
    mswkPRG1357 = "STWINFONT29/font100/I<493>"
    showText(mswkPRG1357, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1358 then
    mswkPRG1358 = "STWINFONT29/font000/I<494>"
    showText(mswkPRG1358, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1359 then
    mswkPRG1359 = "STWINFONT29/font100/I<495>"
    showText(mswkPRG1359, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1360 then
    mswkPRG1360 = "STWINFONT29/font100/I<496>"
    showText(mswkPRG1360, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1361 then
    mswkPRG1361 = "STWINFONT29/font000/I<497>"
    showText(mswkPRG1361, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1362 then
    mswkPRG1362 = "STWINFONT29/font000/I<498>"
    showText(mswkPRG1362, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1363 then
    mswkPRG1363 = "STWINFONT29/font001/I<499>"
    showText(mswkPRG1363, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1364 then
    mswkPRG1364 = "STWINFONT29/font100/I<500>"
    showText(mswkPRG1364, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1365 then
    mswkPRG1365 = "STWINFONT29/font000/I<501>"
    showText(mswkPRG1365, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1366 then
    mswkPRG1366 = "STWINFONT29/font100/I<502>"
    showText(mswkPRG1366, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1367 then
    mswkPRG1367 = "STWINFONT29/font100/I<503>"
    showText(mswkPRG1367, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1368 then
    mswkPRG1368 = "STWINFONT29/font000/I<504>"
    showText(mswkPRG1368, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1369 then
    mswkPRG1369 = "STWINFONT29/font000/I<505>"
    showText(mswkPRG1369, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1370 then
    mswkPRG1370 = "STWINFONT29/font001/I<499>"
    showText(mswkPRG1370, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1371 then
    mswkPRG1371 = "STWINFONT29/font000/I<506>"
    showText(mswkPRG1371, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1372 then
    mswkPRG1372 = "STWINFONT29/font000/I<507>"
    showText(mswkPRG1372, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1373 then
    mswkPRG1373 = "STWINFONT29/font001/I<508>"
    showText(mswkPRG1373, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1374 then
    mswkPRG1374 = "STWINFONT29/font000/I<509>"
    showText(mswkPRG1374, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1375 then
    mswkPRG1375 = "STWINFONT36/font000/I<484>"
    showText(mswkPRG1375, "STWINFONT36", "font000", "LEFT")
    mswkPRG1376 = "STWINFONT36/font001/I<510>"
    showText(mswkPRG1376, "STWINFONT36", "font001", "LEFT")
    mswkPRG1377 = "STWINFONT36/font002/I<485>"
    showText(mswkPRG1377, "STWINFONT36", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1378 then
    mswkPRG1378 = "STWINFONT36/font000/I<484>"
    showText(mswkPRG1378, "STWINFONT36", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1400 then
    mswkPRG1400 = "STWINFONT12/font000/I<511>"
    showText(mswkPRG1400, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1450 then
    mswkPRG1450 = "STWINFONT29/font100/I<512>"
    showText(mswkPRG1450, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1451 then
    mswkPRG1451 = "STWINFONT29/font000/I<513>"
    showText(mswkPRG1451, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1452 then
    mswkPRG1452 = "STWINFONT29/font000/I<514>"
    showText(mswkPRG1452, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1453 then
    mswkPRG1453 = "STWINFONT29/font000/I<515>"
    showText(mswkPRG1453, "STWINFONT29", "font000", "LEFT")
    mswkPRG1454 = "STWINFONT29/font001/I<516>"
    showText(mswkPRG1454, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1455 then
    mswkPRG1455 = "STWINFONT29/font000/I<517>"
    showText(mswkPRG1455, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1456 then
    mswkPRG1456 = "STWINFONT29/font000/I<507>"
    showText(mswkPRG1456, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1457 then
    mswkPRG1457 = "STWINFONT29/font001/I<518>"
    showText(mswkPRG1457, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1500 then
    mswkPRG1500 = "STWINFONT12/font000/I<519>"
    showText(mswkPRG1500, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1501 then
    mswkPRG1501 = "STWINFONT13/font000/I<519>"
    showText(mswkPRG1501, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1502 then
    mswkPRG1502 = "STWINFONT32/font010/I<520>"
    showText(mswkPRG1502, "STWINFONT32", "font010", "RIGHT")
    mswkPRG1503 = "STWINFONT32/font021/I<520>"
    showText(mswkPRG1503, "STWINFONT32", "font021", "RIGHT")
    mswkPRG1504 = "STWINFONT32/font020/I<521>"
    showText(mswkPRG1504, "STWINFONT32", "font020", "LEFT")
elseif be:TXTgetCallNo() == 1505 then
    mswkPRG1505 = "STWINFONT30/font010/I<520>"
    showText(mswkPRG1505, "STWINFONT30", "font010", "RIGHT")
    mswkPRG1506 = "STWINFONT30/font021/I<520>"
    showText(mswkPRG1506, "STWINFONT30", "font021", "RIGHT")
    mswkPRG1507 = "STWINFONT30/font020/I<521>"
    showText(mswkPRG1507, "STWINFONT30", "font020", "LEFT")
elseif be:TXTgetCallNo() == 1550 then
    mswkPRG1550 = "STWINFONT29/font000/I<522>"
    showText(mswkPRG1550, "STWINFONT29", "font000", "LEFT")
    mswkPRG1551 = "STWINFONT29/font001/I<523>"
    showText(mswkPRG1551, "STWINFONT29", "font001", "LEFT")
    mswkPRG1552 = "STWINFONT29/font002/I<419>"
    showText(mswkPRG1552, "STWINFONT29", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1553 then
    mswkPRG1553 = "STWINFONT29/font100/I<524>"
    showText(mswkPRG1553, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1554 then
    mswkPRG1554 = "STWINFONT29/font100/I<525>"
    showText(mswkPRG1554, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1555 then
    mswkPRG1555 = "STWINFONT29/font000/I<526>"
    showText(mswkPRG1555, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1556 then
    mswkPRG1556 = "STWINFONT29/font000/I<527>"
    showText(mswkPRG1556, "STWINFONT29", "font000", "LEFT")
    mswkPRG1557 = "STWINFONT29/font001/I<528>"
    showText(mswkPRG1557, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1558 then
    mswkPRG1558 = "STWINFONT29/font000/I<529>"
    showText(mswkPRG1558, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1559 then
    mswkPRG1559 = "STWINFONT29/font000/I<530>"
    showText(mswkPRG1559, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1560 then
    mswkPRG1560 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1560, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1561 then
    mswkPRG1561 = "STWINFONT29/font000/I<532>"
    showText(mswkPRG1561, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1562 then
    mswkPRG1562 = "STWINFONT29/font000/I<533>"
    showText(mswkPRG1562, "STWINFONT29", "font000", "LEFT")
    mswkPRG1563 = "STWINFONT29/font001/I<534>"
    showText(mswkPRG1563, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1564 then
    mswkPRG1564 = "STWINFONT29/font000/I<535>"
    showText(mswkPRG1564, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1565 then
    mswkPRG1565 = "STWINFONT29/font000/I<536>"
    showText(mswkPRG1565, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1566 then
    mswkPRG1566 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1566, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1567 then
    mswkPRG1567 = "STWINFONT29/font000/I<537>"
    showText(mswkPRG1567, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1568 then
    mswkPRG1568 = "STWINFONT29/font000/I<538>"
    showText(mswkPRG1568, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1569 then
    mswkPRG1569 = "STWINFONT29/font001/I<539>"
    showText(mswkPRG1569, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1570 then
    mswkPRG1570 = "STWINFONT29/font000/I<540>"
    showText(mswkPRG1570, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1571 then
    mswkPRG1571 = "STWINFONT29/font000/I<541>"
    showText(mswkPRG1571, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1572 then
    mswkPRG1572 = "STWINFONT29/font100/I<542>"
    showText(mswkPRG1572, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1573 then
    mswkPRG1573 = "STWINFONT29/font000/I<543>"
    showText(mswkPRG1573, "STWINFONT29", "font000", "LEFT")
    mswkPRG1574 = "STWINFONT29/font000/I<404>"
    showText(mswkPRG1574, "STWINFONT29", "font000", "LEFT")
    mswkPRG1575 = "STWINFONT29/font001/I<405>"
    showText(mswkPRG1575, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1576 then
    mswkPRG1576 = "STWINFONT29/font000/I<544>"
    showText(mswkPRG1576, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1600 then
    mswkPRG1600 = "STWINFONT12/font000/I<545>"
    showText(mswkPRG1600, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1601 then
    mswkPRG1601 = "STWINFONT13/font000/I<545>"
    showText(mswkPRG1601, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1602 then
    mswkPRG1602 = "STWINFONT30/font020/I<521>"
    showText(mswkPRG1602, "STWINFONT30", "font020", "LEFT")
elseif be:TXTgetCallNo() == 1650 then
    mswkPRG1650 = "STWINFONT29/font000/I<546>"
    showText(mswkPRG1650, "STWINFONT29", "font000", "LEFT")
    mswkPRG1651 = "STWINFONT29/font001/I<523>"
    showText(mswkPRG1651, "STWINFONT29", "font001", "LEFT")
    mswkPRG1652 = "STWINFONT29/font002/I<419>"
    showText(mswkPRG1652, "STWINFONT29", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1653 then
    mswkPRG1653 = "STWINFONT29/font100/I<547>"
    showText(mswkPRG1653, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1654 then
    mswkPRG1654 = "STWINFONT29/font100/I<525>"
    showText(mswkPRG1654, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1655 then
    mswkPRG1655 = "STWINFONT29/font000/I<548>"
    showText(mswkPRG1655, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1656 then
    mswkPRG1656 = "STWINFONT29/font000/I<549>"
    showText(mswkPRG1656, "STWINFONT29", "font000", "LEFT")
    mswkPRG1657 = "STWINFONT29/font001/I<550>"
    showText(mswkPRG1657, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1658 then
    mswkPRG1658 = "STWINFONT29/font000/I<551>"
    showText(mswkPRG1658, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1659 then
    mswkPRG1659 = "STWINFONT29/font000/I<530>"
    showText(mswkPRG1659, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1660 then
    mswkPRG1660 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1660, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1661 then
    mswkPRG1661 = "STWINFONT29/font000/I<532>"
    showText(mswkPRG1661, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1662 then
    mswkPRG1662 = "STWINFONT29/font000/I<533>"
    showText(mswkPRG1662, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1663 then
    mswkPRG1663 = "STWINFONT29/font001/I<534>"
    showText(mswkPRG1663, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1664 then
    mswkPRG1664 = "STWINFONT29/font000/I<535>"
    showText(mswkPRG1664, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1665 then
    mswkPRG1665 = "STWINFONT29/font000/I<536>"
    showText(mswkPRG1665, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1666 then
    mswkPRG1666 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1666, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1667 then
    mswkPRG1667 = "STWINFONT29/font000/I<552>"
    showText(mswkPRG1667, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1668 then
    mswkPRG1668 = "STWINFONT29/font000/I<538>"
    showText(mswkPRG1668, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1669 then
    mswkPRG1669 = "STWINFONT29/font001/I<553>"
    showText(mswkPRG1669, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1670 then
    mswkPRG1670 = "STWINFONT29/font000/I<554>"
    showText(mswkPRG1670, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1700 then
    mswkPRG1700 = "STWINFONT12/font000/I<555>"
    showText(mswkPRG1700, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1701 then
    mswkPRG1701 = "STWINFONT13/font000/I<555>"
    showText(mswkPRG1701, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1702 then
    mswkPRG1702 = "STWINFONT30/font020/I<521>"
    showText(mswkPRG1702, "STWINFONT30", "font020", "LEFT")
elseif be:TXTgetCallNo() == 1750 then
    mswkPRG1750 = "STWINFONT29/font000/I<556>"
    showText(mswkPRG1750, "STWINFONT29", "font000", "LEFT")
    mswkPRG1751 = "STWINFONT29/font001/I<523>"
    showText(mswkPRG1751, "STWINFONT29", "font001", "LEFT")
    mswkPRG1752 = "STWINFONT29/font002/I<419>"
    showText(mswkPRG1752, "STWINFONT29", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1753 then
    mswkPRG1753 = "STWINFONT29/font100/I<557>"
    showText(mswkPRG1753, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1754 then
    mswkPRG1754 = "STWINFONT29/font100/I<525>"
    showText(mswkPRG1754, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1755 then
    mswkPRG1755 = "STWINFONT29/font000/I<558>"
    showText(mswkPRG1755, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1756 then
    mswkPRG1756 = "STWINFONT29/font000/I<559>"
    showText(mswkPRG1756, "STWINFONT29", "font000", "LEFT")
    mswkPRG1757 = "STWINFONT29/font001/I<560>"
    showText(mswkPRG1757, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1758 then
    mswkPRG1758 = "STWINFONT29/font000/I<561>"
    showText(mswkPRG1758, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1759 then
    mswkPRG1759 = "STWINFONT29/font000/I<530>"
    showText(mswkPRG1759, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1760 then
    mswkPRG1760 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1760, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1761 then
    mswkPRG1761 = "STWINFONT29/font000/I<532>"
    showText(mswkPRG1761, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1762 then
    mswkPRG1762 = "STWINFONT29/font000/I<533>"
    showText(mswkPRG1762, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1763 then
    mswkPRG1763 = "STWINFONT29/font001/I<534>"
    showText(mswkPRG1763, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1764 then
    mswkPRG1764 = "STWINFONT29/font000/I<535>"
    showText(mswkPRG1764, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1765 then
    mswkPRG1765 = "STWINFONT29/font000/I<536>"
    showText(mswkPRG1765, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1766 then
    mswkPRG1766 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1766, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1767 then
    mswkPRG1767 = "STWINFONT29/font000/I<562>"
    showText(mswkPRG1767, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1768 then
    mswkPRG1768 = "STWINFONT29/font000/I<538>"
    showText(mswkPRG1768, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1769 then
    mswkPRG1769 = "STWINFONT29/font001/I<563>"
    showText(mswkPRG1769, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1800 then
    mswkPRG1800 = "STWINFONT12/font000/I<564>"
    showText(mswkPRG1800, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1801 then
    mswkPRG1801 = "STWINFONT13/font000/I<564>"
    showText(mswkPRG1801, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1802 then
    mswkPRG1802 = "STWINFONT30/font020/I<521>"
    showText(mswkPRG1802, "STWINFONT30", "font020", "LEFT")
elseif be:TXTgetCallNo() == 1850 then
    mswkPRG1850 = "STWINFONT29/font000/I<565>"
    showText(mswkPRG1850, "STWINFONT29", "font000", "LEFT")
    mswkPRG1851 = "STWINFONT29/font001/I<523>"
    showText(mswkPRG1851, "STWINFONT29", "font001", "LEFT")
    mswkPRG1852 = "STWINFONT29/font002/I<419>"
    showText(mswkPRG1852, "STWINFONT29", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1853 then
    mswkPRG1853 = "STWINFONT29/font100/I<566>"
    showText(mswkPRG1853, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1854 then
    mswkPRG1854 = "STWINFONT29/font100/I<525>"
    showText(mswkPRG1854, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1855 then
    mswkPRG1855 = "STWINFONT29/font000/I<567>"
    showText(mswkPRG1855, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1856 then
    mswkPRG1856 = "STWINFONT29/font000/I<568>"
    showText(mswkPRG1856, "STWINFONT29", "font000", "LEFT")
    mswkPRG1857 = "STWINFONT29/font001/I<569>"
    showText(mswkPRG1857, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1858 then
    mswkPRG1858 = "STWINFONT29/font000/I<570>"
    showText(mswkPRG1858, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1859 then
    mswkPRG1859 = "STWINFONT29/font000/I<530>"
    showText(mswkPRG1859, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1860 then
    mswkPRG1860 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1860, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1861 then
    mswkPRG1861 = "STWINFONT29/font000/I<532>"
    showText(mswkPRG1861, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1862 then
    mswkPRG1862 = "STWINFONT29/font000/I<533>"
    showText(mswkPRG1862, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1863 then
    mswkPRG1863 = "STWINFONT29/font001/I<534>"
    showText(mswkPRG1863, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1864 then
    mswkPRG1864 = "STWINFONT29/font000/I<535>"
    showText(mswkPRG1864, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1865 then
    mswkPRG1865 = "STWINFONT29/font000/I<536>"
    showText(mswkPRG1865, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1866 then
    mswkPRG1866 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1866, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1867 then
    mswkPRG1867 = "STWINFONT29/font000/I<571>"
    showText(mswkPRG1867, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1868 then
    mswkPRG1868 = "STWINFONT29/font000/I<538>"
    showText(mswkPRG1868, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1869 then
    mswkPRG1869 = "STWINFONT29/font001/I<572>"
    showText(mswkPRG1869, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1900 then
    mswkPRG1900 = "STWINFONT12/font000/I<573>"
    showText(mswkPRG1900, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1901 then
    mswkPRG1901 = "STWINFONT13/font000/I<573>"
    showText(mswkPRG1901, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1950 then
    mswkPRG1950 = "STWINFONT29/font000/I<574>"
    showText(mswkPRG1950, "STWINFONT29", "font000", "LEFT")
    mswkPRG1951 = "STWINFONT29/font001/I<575>"
    showText(mswkPRG1951, "STWINFONT29", "font001", "LEFT")
    mswkPRG1952 = "STWINFONT29/font002/I<419>"
    showText(mswkPRG1952, "STWINFONT29", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1953 then
    mswkPRG1953 = "STWINFONT29/font100/I<576>"
    showText(mswkPRG1953, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1954 then
    mswkPRG1954 = "STWINFONT29/font000/I<577>"
    showText(mswkPRG1954, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1955 then
    mswkPRG1955 = "STWINFONT29/font000/I<578>"
    showText(mswkPRG1955, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1956 then
    mswkPRG1956 = "STWINFONT29/font001/I<579>"
    showText(mswkPRG1956, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1957 then
    mswkPRG1957 = "STWINFONT29/font000/I<580>"
    showText(mswkPRG1957, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1958 then
    mswkPRG1958 = "STWINFONT29/font000/I<530>"
    showText(mswkPRG1958, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1959 then
    mswkPRG1959 = "STWINFONT29/font001/I<531>"
    showText(mswkPRG1959, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1960 then
    mswkPRG1960 = "STWINFONT29/font100/I<581>"
    showText(mswkPRG1960, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 1961 then
    mswkPRG1961 = "STWINFONT29/font000/I<582>"
    showText(mswkPRG1961, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1962 then
    mswkPRG1962 = "STWINFONT29/font000/I<583>"
    showText(mswkPRG1962, "STWINFONT29", "font000", "LEFT")
    mswkPRG1963 = "STWINFONT29/font001/I<584>"
    showText(mswkPRG1963, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1964 then
    mswkPRG1964 = "STWINFONT29/font000/I<585>"
    showText(mswkPRG1964, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1965 then
    mswkPRG1965 = "STWINFONT29/font000/I<538>"
    showText(mswkPRG1965, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1966 then
    mswkPRG1966 = "STWINFONT29/font001/I<586>"
    showText(mswkPRG1966, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1967 then
    mswkPRG1967 = "STWINFONT29/font000/I<587>"
    showText(mswkPRG1967, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1968 then
    mswkPRG1968 = "STWINFONT29/font000/I<588>"
    showText(mswkPRG1968, "STWINFONT29", "font000", "LEFT")
    mswkPRG1969 = "STWINFONT29/font001/I<589>"
    showText(mswkPRG1969, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1970 then
    mswkPRG1970 = "STWINFONT29/font000/I<590>"
    showText(mswkPRG1970, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 2000 then
    mswkPRG2000 = "STWINFONT12/font000/I<591>"
    showText(mswkPRG2000, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 2001 then
    mswkPRG2001 = "STWINFONT34/font000/I<592>"
    showText(mswkPRG2001, "STWINFONT34", "font000", "LEFT")
    mswkPRG2002 = "STWINFONT34/font001/I<593>"
    showText(mswkPRG2002, "STWINFONT34", "font001", "LEFT")
elseif be:TXTgetCallNo() == 2003 then
    mswkPRG2003 = "TALKFONT01/font01/I<594>"
    showText(mswkPRG2003, "TALKFONT01", "font01", "LEFT")
    mswkPRG2004 = "TALKFONT01/font02/I<419>"
    showText(mswkPRG2004, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 2005 then
    mswkPRG2005 = "TALKFONT01/font01/I<595>"
    showText(mswkPRG2005, "TALKFONT01", "font01", "LEFT")
    mswkPRG2006 = "TALKFONT01/font02/I<596>"
    showText(mswkPRG2006, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 2007 then
    mswkPRG2007 = "TALKFONT01/font00/I<597>"
    showText(mswkPRG2007, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 2008 then
    mswkPRG2008 = "TALKFONT01/font01/I<598>"
    showText(mswkPRG2008, "TALKFONT01", "font01", "LEFT")
    mswkPRG2009 = "TALKFONT01/font02/I<596>"
    showText(mswkPRG2009, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 2010 then
    mswkPRG2010 = "TALKFONT01/font00/I<599>"
    showText(mswkPRG2010, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 2011 then
    mswkPRG2011 = "TALKFONT01/font00/I<600>"
    showText(mswkPRG2011, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 2012 then
    mswkPRG2012 = "TALKFONT01/font00/I<601>"
    showText(mswkPRG2012, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 2013 then
    mswkPRG2013 = "TALKFONT01/font00/I<602>"
    showText(mswkPRG2013, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 2020 then
    mswkPRG2020 = "STWINFONT29/font000/I<603>"
    showText(mswkPRG2020, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 2021 then
    mswkPRG2021 = "STWINFONT29/font000/I<604>"
    showText(mswkPRG2021, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 2030 then
    mswkPRG2030 = "TALKFONT01/font01/I<460>"
    showText(mswkPRG2030, "TALKFONT01", "font01", "LEFT")
    mswkPRG2031 = "TALKFONT01/font02/I<605>"
    showText(mswkPRG2031, "TALKFONT01", "font02", "LEFT")
    mswkPRG2032 = "TALKFONT01/font03/I<594>"
    showText(mswkPRG2032, "TALKFONT01", "font03", "LEFT")
    mswkPRG2033 = "TALKFONT01/font04/I<419>"
    showText(mswkPRG2033, "TALKFONT01", "font04", "LEFT")
elseif be:TXTgetCallNo() == 2034 then
    mswkPRG2034 = "TALKFONT01/font01/I<460>"
    showText(mswkPRG2034, "TALKFONT01", "font01", "LEFT")
    mswkPRG2035 = "TALKFONT01/font02/I<605>"
    showText(mswkPRG2035, "TALKFONT01", "font02", "LEFT")
    mswkPRG2036 = "TALKFONT01/font03/I<419>"
    showText(mswkPRG2036, "TALKFONT01", "font03", "LEFT")
elseif be:TXTgetCallNo() == 2040 then
    mswkPRG2040 = "STWINFONT29/font000/I<606>"
    showText(mswkPRG2040, "STWINFONT29", "font000", "LEFT")
else
    be:MsgBox("error textSet", be:TXTgetCallNo())
end
