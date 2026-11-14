local showText = function(text, arg_1, arg_2, arg_3)
    be:sd("TEXTCTL", nil, -1, "TEXTSET", text)
    be:sd("TEXTCTL", nil, -1, "ALIGN", arg_1 .. "/" .. arg_2 .. "/" .. arg_3)
    be:sd("TEXTCTL", nil, -1, "SWITCH", arg_1 .. "/" .. arg_2 .. "/DISPON")
end
if be:TXTgetCallNo() == 0 then
    mswkPRG0000 = "STWINFONT34/font000/I<882>"
    showText(mswkPRG0000, "STWINFONT34", "font000", "LEFT")
    mswkPRG0001 = "STWINFONT34/font001/I<883>"
    showText(mswkPRG0001, "STWINFONT34", "font001", "LEFT")
    mswkPRG0002 = "STWINFONT34/font002/I<884>"
    showText(mswkPRG0002, "STWINFONT34", "font002", "LEFT")
elseif be:TXTgetCallNo() == 3 then
    mswkPRG0003 = "STWINFONT06/font030/I<684>"
    showText(mswkPRG0003, "STWINFONT06", "font030", "LEFT")
    mswkPRG0004 = "STWINFONT06/font031/I<685>"
    showText(mswkPRG0004, "STWINFONT06", "font031", "LEFT")
    mswkPRG0005 = "STWINFONT06/font032/I<686>"
    showText(mswkPRG0005, "STWINFONT06", "font032", "LEFT")
    mswkPRG0006 = "STWINFONT06/font033/I<687>"
    showText(mswkPRG0006, "STWINFONT06", "font033", "LEFT")
    mswkPRG0007 = "STWINFONT06/font034/I<688>"
    showText(mswkPRG0007, "STWINFONT06", "font034", "LEFT")
    mswkPRG0008 = "STWINFONT06/font035/I<885>"
    showText(mswkPRG0008, "STWINFONT06", "font035", "LEFT")
    mswkPRG0009 = "STWINFONT06/font036/I<886>"
    showText(mswkPRG0009, "STWINFONT06", "font036", "LEFT")
    mswkPRG0010 = "STWINFONT06/font037/I<887>"
    showText(mswkPRG0010, "STWINFONT06", "font037", "LEFT")
    mswkPRG0011 = "STWINFONT06/font038/I<888>"
    showText(mswkPRG0011, "STWINFONT06", "font038", "LEFT")
    mswkPRG0012 = "STWINFONT06/font039/I<716>"
    showText(mswkPRG0012, "STWINFONT06", "font039", "LEFT")
    mswkPRG0013 = "STWINFONT06/font060/I<767>"
    showText(mswkPRG0013, "STWINFONT06", "font060", "LEFT")
    mswkPRG0014 = "STWINFONT06/font061/I<889>"
    showText(mswkPRG0014, "STWINFONT06", "font061", "LEFT")
elseif be:TXTgetCallNo() == 15 then
    mswkPRG0015 = "STWINFONT08/font000/I<890>"
    showText(mswkPRG0015, "STWINFONT08", "font000", "LEFT")
    mswkPRG0016 = "STWINFONT08/font001/I<891>"
    showText(mswkPRG0016, "STWINFONT08", "font001", "LEFT")
    mswkPRG0017 = "STWINFONT08/font002/I<892>"
    showText(mswkPRG0017, "STWINFONT08", "font002", "LEFT")
elseif be:TXTgetCallNo() == 30 then
    mswkPRG0030 = "STWINFONT12/font000/I<890>"
    showText(mswkPRG0030, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 31 then
    mswkPRG0031 = "STWINFONT09/font000/I<893>"
    showText(mswkPRG0031, "STWINFONT09", "font000", "LEFT")
    mswkPRG0032 = "STWINFONT09/font001/I<894>"
    showText(mswkPRG0032, "STWINFONT09", "font001", "LEFT")
    mswkPRG0033 = "STWINFONT09/font002/I<895>"
    showText(mswkPRG0033, "STWINFONT09", "font002", "LEFT")
    mswkPRG0034 = "STWINFONT29/font100/I<896>"
    showText(mswkPRG0034, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 35 then
    mswkPRG0035 = "STWINFONT29/font000/I<897>"
    showText(mswkPRG0035, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 36 then
    mswkPRG0036 = "STWINFONT29/font000/I<898>"
    showText(mswkPRG0036, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 37 then
    mswkPRG0037 = "STWINFONT29/font000/I<899>"
    showText(mswkPRG0037, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 38 then
    mswkPRG0038 = "STWINFONT10/font000/I<893>"
    showText(mswkPRG0038, "STWINFONT10", "font000", "LEFT")
    mswkPRG0039 = "STWINFONT10/font001/I<900>"
    showText(mswkPRG0039, "STWINFONT10", "font001", "LEFT")
elseif be:TXTgetCallNo() == 40 then
    mswkPRG0040 = "STWINFONT10/font000/I<894>"
    showText(mswkPRG0040, "STWINFONT10", "font000", "LEFT")
    mswkPRG0041 = "STWINFONT10/font001/I<900>"
    showText(mswkPRG0041, "STWINFONT10", "font001", "LEFT")
elseif be:TXTgetCallNo() == 42 then
    mswkPRG0042 = "STWINFONT10/font000/I<895>"
    showText(mswkPRG0042, "STWINFONT10", "font000", "LEFT")
elseif be:TXTgetCallNo() == 43 then
    mswkPRG0043 = "STWINFONT29/font100/I<901>"
    showText(mswkPRG0043, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 44 then
    mswkPRG0044 = "STWINFONT29/font100/I<902>"
    showText(mswkPRG0044, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 45 then
    mswkPRG0045 = "STWINFONT29/font100/I<903>"
    showText(mswkPRG0045, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 46 then
    mswkPRG0046 = "STWINFONT29/font000/I<904>"
    showText(mswkPRG0046, "STWINFONT29", "font000", "LEFT")
    mswkPRG0047 = "STWINFONT29/font001/I<905>"
    showText(mswkPRG0047, "STWINFONT29", "font001", "LEFT")
    mswkPRG0048 = "STWINFONT29/font002/I<906>"
    showText(mswkPRG0048, "STWINFONT29", "font002", "LEFT")
    mswkPRG0049 = "STWINFONT29/font100/I<907>"
    showText(mswkPRG0049, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 60 then
    mswkPRG0060 = "STWINFONT12/font000/I<891>"
    showText(mswkPRG0060, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 61 then
    mswkPRG0061 = "STWINFONT09/font000/I<679>"
    showText(mswkPRG0061, "STWINFONT09", "font000", "LEFT")
    mswkPRG0062 = "STWINFONT09/font001/I<908>"
    showText(mswkPRG0062, "STWINFONT09", "font001", "LEFT")
    mswkPRG0063 = "STWINFONT09/font002/I<680>"
    showText(mswkPRG0063, "STWINFONT09", "font002", "LEFT")
    mswkPRG0064 = "STWINFONT09/font003/I<759>"
    showText(mswkPRG0064, "STWINFONT09", "font003", "LEFT")
    mswkPRG0085 = "STWINFONT29/font100/I<909>"
    showText(mswkPRG0085, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 65 then
    mswkPRG0065 = "STWINFONT26/font000/I<910>"
    showText(mswkPRG0065, "STWINFONT26", "font000", "LEFT")
    mswkPRG0066 = "STWINFONT26/font001/I<911>"
    showText(mswkPRG0066, "STWINFONT26", "font001", "LEFT")
elseif be:TXTgetCallNo() == 67 then
    mswkPRG0067 = "STWINFONT26/font000/I<912>"
    showText(mswkPRG0067, "STWINFONT26", "font000", "LEFT")
    mswkPRG0068 = "STWINFONT26/font001/I<910>"
    showText(mswkPRG0068, "STWINFONT26", "font001", "LEFT")
    mswkPRG0069 = "STWINFONT26/font002/I<911>"
    showText(mswkPRG0069, "STWINFONT26", "font002", "LEFT")
elseif be:TXTgetCallNo() == 70 then
    mswkPRG0070 = "STWINFONT13/font000/I<679>"
    showText(mswkPRG0070, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 71 then
    mswkPRG0071 = "STWINFONT13/font000/I<908>"
    showText(mswkPRG0071, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 72 then
    mswkPRG0072 = "STWINFONT13/font000/I<680>"
    showText(mswkPRG0072, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 73 then
    mswkPRG0073 = "STWINFONT39/font000/I<913>"
    showText(mswkPRG0073, "STWINFONT39", "font000", "LEFT")
elseif be:TXTgetCallNo() == 74 then
    mswkPRG0074 = "STWINFONT39/font000/I<913>"
    showText(mswkPRG0074, "STWINFONT39", "font000", "LEFT")
    mswkPRG0075 = "STWINFONT39/font001/I<914>"
    showText(mswkPRG0075, "STWINFONT39", "font001", "LEFT")
elseif be:TXTgetCallNo() == 76 then
    mswkPRG0076 = "STWINFONT39/font000/I<913>"
    showText(mswkPRG0076, "STWINFONT39", "font000", "LEFT")
    mswkPRG0077 = "STWINFONT39/font001/I<915>"
    showText(mswkPRG0077, "STWINFONT39", "font001", "LEFT")
elseif be:TXTgetCallNo() == 78 then
    mswkPRG0078 = "STWINFONT29/font000/I<916>"
    showText(mswkPRG0078, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 79 then
    mswkPRG0079 = "STWINFONT29/font000/I<917>"
    showText(mswkPRG0079, "STWINFONT29", "font000", "LEFT")
    mswkPRG0080 = "STWINFONT29/font001/I<918>"
    showText(mswkPRG0080, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 81 then
    mswkPRG0081 = "STWINFONT29/font000/I<919>"
    showText(mswkPRG0081, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 82 then
    mswkPRG0082 = "STWINFONT29/font000/I<920>"
    showText(mswkPRG0082, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 83 then
    mswkPRG0083 = "STWINFONT29/font000/I<921>"
    showText(mswkPRG0083, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 84 then
    mswkPRG0084 = "STWINFONT29/font000/I<922>"
    showText(mswkPRG0084, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 87 then
    mswkPRG0087 = "STWINFONT29/font000/I<923>"
    showText(mswkPRG0087, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 88 then
    mswkPRG0088 = "STWINFONT29/font000/I<924>"
    showText(mswkPRG0088, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 90 then
    mswkPRG0090 = "STWINFONT12/font000/I<892>"
    showText(mswkPRG0090, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 91 then
    mswkPRG0091 = "STWINFONT09/font000/I<733>"
    showText(mswkPRG0091, "STWINFONT09", "font000", "LEFT")
    mswkPRG0092 = "STWINFONT09/font001/I<892>"
    showText(mswkPRG0092, "STWINFONT09", "font001", "LEFT")
    mswkPRG0093 = "STWINFONT09/font002/I<925>"
    showText(mswkPRG0093, "STWINFONT09", "font002", "LEFT")
    mswkPRG0094 = "STWINFONT29/font100/I<926>"
    showText(mswkPRG0094, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 95 then
    mswkPRG0095 = "STWINFONT13/font000/I<733>"
    showText(mswkPRG0095, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 96 then
    mswkPRG0096 = "STWINFONT13/font000/I<927>"
    showText(mswkPRG0096, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 97 then
    mswkPRG0097 = "STWINFONT13/font000/I<925>"
    showText(mswkPRG0097, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 98 then
    mswkPRG0098 = "STWINFONT29/font000/I<928>"
    showText(mswkPRG0098, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 99 then
    mswkPRG0099 = "STWINFONT29/font000/I<929>"
    showText(mswkPRG0099, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 100 then
    mswkPRG0100 = "STWINFONT29/font000/I<930>"
    showText(mswkPRG0100, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 101 then
    mswkPRG0101 = "STWINFONT14/font000/I<931>"
    showText(mswkPRG0101, "STWINFONT14", "font000", "LEFT")
    mswkPRG0102 = "STWINFONT14/font001/I<932>"
    showText(mswkPRG0102, "STWINFONT14", "font001", "LEFT")
    mswkPRG0103 = "STWINFONT14/font002/I<933>"
    showText(mswkPRG0103, "STWINFONT14", "font002", "LEFT")
    mswkPRG0104 = "STWINFONT14/font003/I<934>"
    showText(mswkPRG0104, "STWINFONT14", "font003", "LEFT")
    mswkPRG0105 = "STWINFONT14/font004/I<935>"
    showText(mswkPRG0105, "STWINFONT14", "font004", "LEFT")
    mswkPRG0106 = "STWINFONT14/font005/I<936>"
    showText(mswkPRG0106, "STWINFONT14", "font005", "LEFT")
    mswkPRG0107 = "STWINFONT14/font006/I<937>"
    showText(mswkPRG0107, "STWINFONT14", "font006", "LEFT")
    mswkPRG0108 = "STWINFONT14/font007/I<938>"
    showText(mswkPRG0108, "STWINFONT14", "font007", "LEFT")
    mswkPRG0109 = "STWINFONT14/font008/I<939>"
    showText(mswkPRG0109, "STWINFONT14", "font008", "LEFT")
elseif be:TXTgetCallNo() == 111 then
    mswkPRG0111 = "STWINFONT29/font000/I<940>"
    showText(mswkPRG0111, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 112 then
    mswkPRG0112 = "STWINFONT29/font000/I<941>"
    showText(mswkPRG0112, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 113 then
    mswkPRG0113 = "STWINFONT29/font000/I<942>"
    showText(mswkPRG0113, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 114 then
    mswkPRG0114 = "STWINFONT29/font000/I<943>"
    showText(mswkPRG0114, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 115 then
    mswkPRG0115 = "STWINFONT29/font000/I<944>"
    showText(mswkPRG0115, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 116 then
    mswkPRG0116 = "STWINFONT29/font000/I<945>"
    showText(mswkPRG0116, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 117 then
    mswkPRG0117 = "STWINFONT29/font000/I<946>"
    showText(mswkPRG0117, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 118 then
    mswkPRG0118 = "STWINFONT29/font000/I<947>"
    showText(mswkPRG0118, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 119 then
    mswkPRG0119 = "STWINFONT29/font000/I<948>"
    showText(mswkPRG0119, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 120 then
    mswkPRG0120 = "STWINFONT29/font000/I<949>"
    showText(mswkPRG0120, "STWINFONT29", "font000", "LEFT")
    mswkPRG0121 = "STWINFONT29/font001/I<905>"
    showText(mswkPRG0121, "STWINFONT29", "font001", "LEFT")
    mswkPRG0122 = "STWINFONT29/font002/I<906>"
    showText(mswkPRG0122, "STWINFONT29", "font002", "LEFT")
    mswkPRG0123 = "STWINFONT29/font100/I<907>"
    showText(mswkPRG0123, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 124 then
    mswkPRG0124 = "STWINFONT29/font000/I<950>"
    showText(mswkPRG0124, "STWINFONT29", "font000", "LEFT")
    mswkPRG0125 = "STWINFONT29/font001/I<905>"
    showText(mswkPRG0125, "STWINFONT29", "font001", "LEFT")
    mswkPRG0126 = "STWINFONT29/font100/I<907>"
    showText(mswkPRG0126, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 127 then
    mswkPRG0127 = "STWINFONT29/font000/I<951>"
    showText(mswkPRG0127, "STWINFONT29", "font000", "LEFT")
    mswkPRG0128 = "STWINFONT29/font001/I<952>"
    showText(mswkPRG0128, "STWINFONT29", "font001", "LEFT")
    mswkPRG0129 = "STWINFONT29/font100/I<907>"
    showText(mswkPRG0129, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 130 then
    mswkPRG0130 = "STWINFONT29/font000/I<953>"
    showText(mswkPRG0130, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 131 then
    mswkPRG0131 = "STWINFONT29/font000/I<954>"
    showText(mswkPRG0131, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 132 then
    mswkPRG0132 = "STWINFONT29/font000/I<955>"
    showText(mswkPRG0132, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 133 then
    mswkPRG0133 = "STWINFONT29/font000/I<956>"
    showText(mswkPRG0133, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 134 then
    mswkPRG0134 = "STWINFONT29/font100/I<957>"
    showText(mswkPRG0134, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 135 then
    mswkPRG0135 = "STWINFONT29/font100/I<958>"
    showText(mswkPRG0135, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 136 then
    mswkPRG0136 = "STWINFONT29/font100/I<959>"
    showText(mswkPRG0136, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 137 then
    mswkPRG0137 = "STWINFONT29/font100/I<960>"
    showText(mswkPRG0137, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 138 then
    mswkPRG0138 = "STWINFONT29/font100/I<961>"
    showText(mswkPRG0138, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 139 then
    mswkPRG0139 = "STWINFONT29/font100/I<962>"
    showText(mswkPRG0139, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 140 then
    mswkPRG0140 = "STWINFONT29/font100/I<963>"
    showText(mswkPRG0140, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 141 then
    mswkPRG0141 = "STWINFONT29/font000/I<964>"
    showText(mswkPRG0141, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 142 then
    mswkPRG0142 = "STWINFONT29/font000/I<965>"
    showText(mswkPRG0142, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 143 then
    mswkPRG0143 = "STWINFONT29/font000/I<966>"
    showText(mswkPRG0143, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 144 then
    mswkPRG0144 = "STWINFONT29/font000/I<967>"
    showText(mswkPRG0144, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 145 then
    mswkPRG0145 = "STWINFONT29/font000/I<968>"
    showText(mswkPRG0145, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 146 then
    mswkPRG0146 = "STWINFONT29/font000/I<969>"
    showText(mswkPRG0146, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 147 then
    mswkPRG0147 = "STWINFONT29/font000/I<970>"
    showText(mswkPRG0147, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 148 then
    mswkPRG0148 = "STWINFONT29/font000/I<971>"
    showText(mswkPRG0148, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 149 then
    mswkPRG0149 = "STWINFONT29/font000/I<972>"
    showText(mswkPRG0149, "STWINFONT29", "font000", "LEFT")
else
    be:MsgBox("error textSet", be:TXTgetCallNo())
end
