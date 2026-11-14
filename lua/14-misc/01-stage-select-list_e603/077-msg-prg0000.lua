local showText = function(text, arg_1, arg_2, arg_3)
    be:sd("TEXTCTL", nil, -1, "TEXTSET", text)
    be:sd("TEXTCTL", nil, -1, "ALIGN", arg_1 .. "/" .. arg_2 .. "/" .. arg_3)
    be:sd("TEXTCTL", nil, -1, "SWITCH", arg_1 .. "/" .. arg_2 .. "/DISPON")
end
if be:TXTgetCallNo() == 0 then
    mswkPRG0000 = "STWINFONT34/font000/I<208>"
    showText(mswkPRG0000, "STWINFONT34", "font000", "LEFT")
    mswkPRG0001 = "STWINFONT34/font001/I<209>"
    showText(mswkPRG0001, "STWINFONT34", "font001", "LEFT")
    mswkPRG0002 = "STWINFONT34/font002/I<210>"
    showText(mswkPRG0002, "STWINFONT34", "font002", "LEFT")
elseif be:TXTgetCallNo() == 3 then
    mswkPRG0003 = "STWINFONT06/font030/I<211>"
    showText(mswkPRG0003, "STWINFONT06", "font030", "LEFT")
    mswkPRG0004 = "STWINFONT06/font031/I<212>"
    showText(mswkPRG0004, "STWINFONT06", "font031", "LEFT")
    mswkPRG0005 = "STWINFONT06/font032/I<213>"
    showText(mswkPRG0005, "STWINFONT06", "font032", "LEFT")
    mswkPRG0006 = "STWINFONT06/font033/I<214>"
    showText(mswkPRG0006, "STWINFONT06", "font033", "LEFT")
    mswkPRG0007 = "STWINFONT06/font034/I<215>"
    showText(mswkPRG0007, "STWINFONT06", "font034", "LEFT")
    mswkPRG0008 = "STWINFONT06/font035/I<216>"
    showText(mswkPRG0008, "STWINFONT06", "font035", "LEFT")
    mswkPRG0009 = "STWINFONT06/font036/I<217>"
    showText(mswkPRG0009, "STWINFONT06", "font036", "LEFT")
    mswkPRG0010 = "STWINFONT06/font037/I<218>"
    showText(mswkPRG0010, "STWINFONT06", "font037", "LEFT")
    mswkPRG0011 = "STWINFONT06/font038/I<219>"
    showText(mswkPRG0011, "STWINFONT06", "font038", "LEFT")
    mswkPRG0012 = "STWINFONT06/font039/I<220>"
    showText(mswkPRG0012, "STWINFONT06", "font039", "LEFT")
    mswkPRG0013 = "STWINFONT06/font060/I<221>"
    showText(mswkPRG0013, "STWINFONT06", "font060", "LEFT")
    mswkPRG0014 = "STWINFONT06/font061/I<222>"
    showText(mswkPRG0014, "STWINFONT06", "font061", "LEFT")
elseif be:TXTgetCallNo() == 15 then
    mswkPRG0015 = "STWINFONT08/font000/I<223>"
    showText(mswkPRG0015, "STWINFONT08", "font000", "LEFT")
    mswkPRG0016 = "STWINFONT08/font001/I<224>"
    showText(mswkPRG0016, "STWINFONT08", "font001", "LEFT")
    mswkPRG0017 = "STWINFONT08/font002/I<225>"
    showText(mswkPRG0017, "STWINFONT08", "font002", "LEFT")
elseif be:TXTgetCallNo() == 30 then
    mswkPRG0030 = "STWINFONT12/font000/I<223>"
    showText(mswkPRG0030, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 31 then
    mswkPRG0031 = "STWINFONT09/font000/I<226>"
    showText(mswkPRG0031, "STWINFONT09", "font000", "LEFT")
    mswkPRG0032 = "STWINFONT09/font001/I<227>"
    showText(mswkPRG0032, "STWINFONT09", "font001", "LEFT")
    mswkPRG0033 = "STWINFONT09/font002/I<228>"
    showText(mswkPRG0033, "STWINFONT09", "font002", "LEFT")
    mswkPRG0034 = "STWINFONT29/font100/I<229>"
    showText(mswkPRG0034, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 35 then
    mswkPRG0035 = "STWINFONT29/font000/I<230>"
    showText(mswkPRG0035, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 36 then
    mswkPRG0036 = "STWINFONT29/font000/I<231>"
    showText(mswkPRG0036, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 37 then
    mswkPRG0037 = "STWINFONT29/font000/I<232>"
    showText(mswkPRG0037, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 38 then
    mswkPRG0038 = "STWINFONT10/font000/I<226>"
    showText(mswkPRG0038, "STWINFONT10", "font000", "LEFT")
    mswkPRG0039 = "STWINFONT10/font001/I<233>"
    showText(mswkPRG0039, "STWINFONT10", "font001", "LEFT")
elseif be:TXTgetCallNo() == 40 then
    mswkPRG0040 = "STWINFONT10/font000/I<227>"
    showText(mswkPRG0040, "STWINFONT10", "font000", "LEFT")
    mswkPRG0041 = "STWINFONT10/font001/I<233>"
    showText(mswkPRG0041, "STWINFONT10", "font001", "LEFT")
elseif be:TXTgetCallNo() == 42 then
    mswkPRG0042 = "STWINFONT10/font000/I<228>"
    showText(mswkPRG0042, "STWINFONT10", "font000", "LEFT")
elseif be:TXTgetCallNo() == 43 then
    mswkPRG0043 = "STWINFONT29/font100/I<234>"
    showText(mswkPRG0043, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 44 then
    mswkPRG0044 = "STWINFONT29/font100/I<235>"
    showText(mswkPRG0044, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 45 then
    mswkPRG0045 = "STWINFONT29/font100/I<236>"
    showText(mswkPRG0045, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 46 then
    mswkPRG0046 = "STWINFONT29/font000/I<237>"
    showText(mswkPRG0046, "STWINFONT29", "font000", "LEFT")
    mswkPRG0047 = "STWINFONT29/font001/I<238>"
    showText(mswkPRG0047, "STWINFONT29", "font001", "LEFT")
    mswkPRG0048 = "STWINFONT29/font002/I<239>"
    showText(mswkPRG0048, "STWINFONT29", "font002", "LEFT")
    mswkPRG0049 = "STWINFONT29/font100/I<240>"
    showText(mswkPRG0049, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 60 then
    mswkPRG0060 = "STWINFONT12/font000/I<224>"
    showText(mswkPRG0060, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 61 then
    mswkPRG0061 = "STWINFONT09/font000/I<241>"
    showText(mswkPRG0061, "STWINFONT09", "font000", "LEFT")
    mswkPRG0062 = "STWINFONT09/font001/I<242>"
    showText(mswkPRG0062, "STWINFONT09", "font001", "LEFT")
    mswkPRG0063 = "STWINFONT09/font002/I<243>"
    showText(mswkPRG0063, "STWINFONT09", "font002", "LEFT")
    mswkPRG0064 = "STWINFONT09/font003/I<244>"
    showText(mswkPRG0064, "STWINFONT09", "font003", "LEFT")
    mswkPRG0085 = "STWINFONT29/font100/I<245>"
    showText(mswkPRG0085, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 65 then
    mswkPRG0065 = "STWINFONT26/font000/I<246>"
    showText(mswkPRG0065, "STWINFONT26", "font000", "LEFT")
    mswkPRG0066 = "STWINFONT26/font001/I<247>"
    showText(mswkPRG0066, "STWINFONT26", "font001", "LEFT")
elseif be:TXTgetCallNo() == 67 then
    mswkPRG0067 = "STWINFONT26/font000/I<248>"
    showText(mswkPRG0067, "STWINFONT26", "font000", "LEFT")
    mswkPRG0068 = "STWINFONT26/font001/I<246>"
    showText(mswkPRG0068, "STWINFONT26", "font001", "LEFT")
    mswkPRG0069 = "STWINFONT26/font002/I<247>"
    showText(mswkPRG0069, "STWINFONT26", "font002", "LEFT")
elseif be:TXTgetCallNo() == 70 then
    mswkPRG0070 = "STWINFONT13/font000/I<241>"
    showText(mswkPRG0070, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 71 then
    mswkPRG0071 = "STWINFONT13/font000/I<242>"
    showText(mswkPRG0071, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 72 then
    mswkPRG0072 = "STWINFONT13/font000/I<243>"
    showText(mswkPRG0072, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 73 then
    mswkPRG0073 = "STWINFONT39/font000/I<249>"
    showText(mswkPRG0073, "STWINFONT39", "font000", "LEFT")
elseif be:TXTgetCallNo() == 74 then
    mswkPRG0074 = "STWINFONT39/font000/I<249>"
    showText(mswkPRG0074, "STWINFONT39", "font000", "LEFT")
    mswkPRG0075 = "STWINFONT39/font001/I<250>"
    showText(mswkPRG0075, "STWINFONT39", "font001", "LEFT")
elseif be:TXTgetCallNo() == 76 then
    mswkPRG0076 = "STWINFONT39/font000/I<249>"
    showText(mswkPRG0076, "STWINFONT39", "font000", "LEFT")
    mswkPRG0077 = "STWINFONT39/font001/I<251>"
    showText(mswkPRG0077, "STWINFONT39", "font001", "LEFT")
elseif be:TXTgetCallNo() == 78 then
    mswkPRG0078 = "STWINFONT29/font000/I<252>"
    showText(mswkPRG0078, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 79 then
    mswkPRG0079 = "STWINFONT29/font000/I<253>"
    showText(mswkPRG0079, "STWINFONT29", "font000", "LEFT")
    mswkPRG0080 = "STWINFONT29/font001/I<254>"
    showText(mswkPRG0080, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 81 then
    mswkPRG0081 = "STWINFONT29/font000/I<255>"
    showText(mswkPRG0081, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 82 then
    mswkPRG0082 = "STWINFONT29/font000/I<256>"
    showText(mswkPRG0082, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 83 then
    mswkPRG0083 = "STWINFONT29/font000/I<257>"
    showText(mswkPRG0083, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 84 then
    mswkPRG0084 = "STWINFONT29/font000/I<258>"
    showText(mswkPRG0084, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 87 then
    mswkPRG0087 = "STWINFONT29/font000/I<259>"
    showText(mswkPRG0087, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 88 then
    mswkPRG0088 = "STWINFONT29/font000/I<260>"
    showText(mswkPRG0088, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 90 then
    mswkPRG0090 = "STWINFONT12/font000/I<225>"
    showText(mswkPRG0090, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 91 then
    mswkPRG0091 = "STWINFONT09/font000/I<261>"
    showText(mswkPRG0091, "STWINFONT09", "font000", "LEFT")
    mswkPRG0092 = "STWINFONT09/font001/I<225>"
    showText(mswkPRG0092, "STWINFONT09", "font001", "LEFT")
    mswkPRG0093 = "STWINFONT09/font002/I<262>"
    showText(mswkPRG0093, "STWINFONT09", "font002", "LEFT")
    mswkPRG0094 = "STWINFONT29/font100/I<263>"
    showText(mswkPRG0094, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 95 then
    mswkPRG0095 = "STWINFONT13/font000/I<261>"
    showText(mswkPRG0095, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 96 then
    mswkPRG0096 = "STWINFONT13/font000/I<264>"
    showText(mswkPRG0096, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 97 then
    mswkPRG0097 = "STWINFONT13/font000/I<262>"
    showText(mswkPRG0097, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 98 then
    mswkPRG0098 = "STWINFONT29/font000/I<265>"
    showText(mswkPRG0098, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 99 then
    mswkPRG0099 = "STWINFONT29/font000/I<266>"
    showText(mswkPRG0099, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 100 then
    mswkPRG0100 = "STWINFONT29/font000/I<267>"
    showText(mswkPRG0100, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 101 then
    mswkPRG0101 = "STWINFONT14/font000/I<268>"
    showText(mswkPRG0101, "STWINFONT14", "font000", "LEFT")
    mswkPRG0102 = "STWINFONT14/font001/I<269>"
    showText(mswkPRG0102, "STWINFONT14", "font001", "LEFT")
    mswkPRG0103 = "STWINFONT14/font002/I<270>"
    showText(mswkPRG0103, "STWINFONT14", "font002", "LEFT")
    mswkPRG0104 = "STWINFONT14/font003/I<271>"
    showText(mswkPRG0104, "STWINFONT14", "font003", "LEFT")
    mswkPRG0105 = "STWINFONT14/font004/I<272>"
    showText(mswkPRG0105, "STWINFONT14", "font004", "LEFT")
    mswkPRG0106 = "STWINFONT14/font005/I<273>"
    showText(mswkPRG0106, "STWINFONT14", "font005", "LEFT")
    mswkPRG0107 = "STWINFONT14/font006/I<274>"
    showText(mswkPRG0107, "STWINFONT14", "font006", "LEFT")
    mswkPRG0108 = "STWINFONT14/font007/I<275>"
    showText(mswkPRG0108, "STWINFONT14", "font007", "LEFT")
    mswkPRG0109 = "STWINFONT14/font008/I<276>"
    showText(mswkPRG0109, "STWINFONT14", "font008", "LEFT")
elseif be:TXTgetCallNo() == 111 then
    mswkPRG0111 = "STWINFONT29/font000/I<277>"
    showText(mswkPRG0111, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 112 then
    mswkPRG0112 = "STWINFONT29/font000/I<278>"
    showText(mswkPRG0112, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 113 then
    mswkPRG0113 = "STWINFONT29/font000/I<279>"
    showText(mswkPRG0113, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 114 then
    mswkPRG0114 = "STWINFONT29/font000/I<280>"
    showText(mswkPRG0114, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 115 then
    mswkPRG0115 = "STWINFONT29/font000/I<281>"
    showText(mswkPRG0115, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 116 then
    mswkPRG0116 = "STWINFONT29/font000/I<282>"
    showText(mswkPRG0116, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 117 then
    mswkPRG0117 = "STWINFONT29/font000/I<283>"
    showText(mswkPRG0117, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 118 then
    mswkPRG0118 = "STWINFONT29/font000/I<284>"
    showText(mswkPRG0118, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 119 then
    mswkPRG0119 = "STWINFONT29/font000/I<285>"
    showText(mswkPRG0119, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 120 then
    mswkPRG0120 = "STWINFONT29/font000/I<286>"
    showText(mswkPRG0120, "STWINFONT29", "font000", "LEFT")
    mswkPRG0121 = "STWINFONT29/font001/I<238>"
    showText(mswkPRG0121, "STWINFONT29", "font001", "LEFT")
    mswkPRG0122 = "STWINFONT29/font002/I<239>"
    showText(mswkPRG0122, "STWINFONT29", "font002", "LEFT")
    mswkPRG0123 = "STWINFONT29/font100/I<240>"
    showText(mswkPRG0123, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 124 then
    mswkPRG0124 = "STWINFONT29/font000/I<287>"
    showText(mswkPRG0124, "STWINFONT29", "font000", "LEFT")
    mswkPRG0125 = "STWINFONT29/font001/I<238>"
    showText(mswkPRG0125, "STWINFONT29", "font001", "LEFT")
    mswkPRG0126 = "STWINFONT29/font100/I<240>"
    showText(mswkPRG0126, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 127 then
    mswkPRG0127 = "STWINFONT29/font000/I<288>"
    showText(mswkPRG0127, "STWINFONT29", "font000", "LEFT")
    mswkPRG0128 = "STWINFONT29/font001/I<289>"
    showText(mswkPRG0128, "STWINFONT29", "font001", "LEFT")
    mswkPRG0129 = "STWINFONT29/font100/I<240>"
    showText(mswkPRG0129, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 130 then
    mswkPRG0130 = "STWINFONT29/font000/I<290>"
    showText(mswkPRG0130, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 131 then
    mswkPRG0131 = "STWINFONT29/font000/I<291>"
    showText(mswkPRG0131, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 132 then
    mswkPRG0132 = "STWINFONT29/font000/I<292>"
    showText(mswkPRG0132, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 133 then
    mswkPRG0133 = "STWINFONT29/font000/I<293>"
    showText(mswkPRG0133, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 134 then
    mswkPRG0134 = "STWINFONT29/font100/I<294>"
    showText(mswkPRG0134, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 135 then
    mswkPRG0135 = "STWINFONT29/font100/I<295>"
    showText(mswkPRG0135, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 136 then
    mswkPRG0136 = "STWINFONT29/font100/I<296>"
    showText(mswkPRG0136, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 137 then
    mswkPRG0137 = "STWINFONT29/font100/I<297>"
    showText(mswkPRG0137, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 138 then
    mswkPRG0138 = "STWINFONT29/font100/I<298>"
    showText(mswkPRG0138, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 139 then
    mswkPRG0139 = "STWINFONT29/font100/I<299>"
    showText(mswkPRG0139, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 140 then
    mswkPRG0140 = "STWINFONT29/font100/I<300>"
    showText(mswkPRG0140, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 141 then
    mswkPRG0141 = "STWINFONT29/font000/I<301>"
    showText(mswkPRG0141, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 142 then
    mswkPRG0142 = "STWINFONT29/font000/I<302>"
    showText(mswkPRG0142, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 143 then
    mswkPRG0143 = "STWINFONT29/font000/I<303>"
    showText(mswkPRG0143, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 144 then
    mswkPRG0144 = "STWINFONT29/font000/I<304>"
    showText(mswkPRG0144, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 145 then
    mswkPRG0145 = "STWINFONT29/font000/I<305>"
    showText(mswkPRG0145, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 146 then
    mswkPRG0146 = "STWINFONT29/font000/I<306>"
    showText(mswkPRG0146, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 147 then
    mswkPRG0147 = "STWINFONT29/font000/I<307>"
    showText(mswkPRG0147, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 148 then
    mswkPRG0148 = "STWINFONT29/font000/I<308>"
    showText(mswkPRG0148, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 149 then
    mswkPRG0149 = "STWINFONT29/font000/I<309>"
    showText(mswkPRG0149, "STWINFONT29", "font000", "LEFT")
else
    be:MsgBox("error textSet", be:TXTgetCallNo())
end
