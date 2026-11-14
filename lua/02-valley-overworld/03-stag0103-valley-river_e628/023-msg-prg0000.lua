local showText = function(text, arg_1, arg_2, arg_3)
    be:sd("TEXTCTL", nil, -1, "TEXTSET", text)
    be:sd("TEXTCTL", nil, -1, "ALIGN", arg_1 .. "/" .. arg_2 .. "/" .. arg_3)
    be:sd("TEXTCTL", nil, -1, "SWITCH", arg_1 .. "/" .. arg_2 .. "/DISPON")
end
if be:TXTgetCallNo() == 0 then
    mswkPRG0000 = "STWINFONT34/font000/I<4>"
    showText(mswkPRG0000, "STWINFONT34", "font000", "LEFT")
    mswkPRG0001 = "STWINFONT34/font001/I<5>"
    showText(mswkPRG0001, "STWINFONT34", "font001", "LEFT")
    mswkPRG0002 = "STWINFONT34/font002/I<6>"
    showText(mswkPRG0002, "STWINFONT34", "font002", "LEFT")
elseif be:TXTgetCallNo() == 3 then
    mswkPRG0003 = "STWINFONT06/font030/I<7>"
    showText(mswkPRG0003, "STWINFONT06", "font030", "LEFT")
    mswkPRG0004 = "STWINFONT06/font031/I<8>"
    showText(mswkPRG0004, "STWINFONT06", "font031", "LEFT")
    mswkPRG0005 = "STWINFONT06/font032/I<9>"
    showText(mswkPRG0005, "STWINFONT06", "font032", "LEFT")
    mswkPRG0006 = "STWINFONT06/font033/I<10>"
    showText(mswkPRG0006, "STWINFONT06", "font033", "LEFT")
    mswkPRG0007 = "STWINFONT06/font034/I<11>"
    showText(mswkPRG0007, "STWINFONT06", "font034", "LEFT")
    mswkPRG0008 = "STWINFONT06/font035/I<12>"
    showText(mswkPRG0008, "STWINFONT06", "font035", "LEFT")
    mswkPRG0009 = "STWINFONT06/font036/I<13>"
    showText(mswkPRG0009, "STWINFONT06", "font036", "LEFT")
    mswkPRG0010 = "STWINFONT06/font037/I<14>"
    showText(mswkPRG0010, "STWINFONT06", "font037", "LEFT")
    mswkPRG0011 = "STWINFONT06/font038/I<15>"
    showText(mswkPRG0011, "STWINFONT06", "font038", "LEFT")
    mswkPRG0012 = "STWINFONT06/font039/I<16>"
    showText(mswkPRG0012, "STWINFONT06", "font039", "LEFT")
    mswkPRG0013 = "STWINFONT06/font060/I<17>"
    showText(mswkPRG0013, "STWINFONT06", "font060", "LEFT")
    mswkPRG0014 = "STWINFONT06/font061/I<18>"
    showText(mswkPRG0014, "STWINFONT06", "font061", "LEFT")
elseif be:TXTgetCallNo() == 15 then
    mswkPRG0015 = "STWINFONT08/font000/I<19>"
    showText(mswkPRG0015, "STWINFONT08", "font000", "LEFT")
    mswkPRG0016 = "STWINFONT08/font001/I<20>"
    showText(mswkPRG0016, "STWINFONT08", "font001", "LEFT")
    mswkPRG0017 = "STWINFONT08/font002/I<21>"
    showText(mswkPRG0017, "STWINFONT08", "font002", "LEFT")
elseif be:TXTgetCallNo() == 30 then
    mswkPRG0030 = "STWINFONT12/font000/I<19>"
    showText(mswkPRG0030, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 31 then
    mswkPRG0031 = "STWINFONT09/font000/I<22>"
    showText(mswkPRG0031, "STWINFONT09", "font000", "LEFT")
    mswkPRG0032 = "STWINFONT09/font001/I<23>"
    showText(mswkPRG0032, "STWINFONT09", "font001", "LEFT")
    mswkPRG0033 = "STWINFONT09/font002/I<24>"
    showText(mswkPRG0033, "STWINFONT09", "font002", "LEFT")
    mswkPRG0034 = "STWINFONT29/font100/I<25>"
    showText(mswkPRG0034, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 35 then
    mswkPRG0035 = "STWINFONT29/font000/I<26>"
    showText(mswkPRG0035, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 36 then
    mswkPRG0036 = "STWINFONT29/font000/I<27>"
    showText(mswkPRG0036, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 37 then
    mswkPRG0037 = "STWINFONT29/font000/I<28>"
    showText(mswkPRG0037, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 38 then
    mswkPRG0038 = "STWINFONT10/font000/I<22>"
    showText(mswkPRG0038, "STWINFONT10", "font000", "LEFT")
    mswkPRG0039 = "STWINFONT10/font001/I<29>"
    showText(mswkPRG0039, "STWINFONT10", "font001", "LEFT")
elseif be:TXTgetCallNo() == 40 then
    mswkPRG0040 = "STWINFONT10/font000/I<23>"
    showText(mswkPRG0040, "STWINFONT10", "font000", "LEFT")
    mswkPRG0041 = "STWINFONT10/font001/I<29>"
    showText(mswkPRG0041, "STWINFONT10", "font001", "LEFT")
elseif be:TXTgetCallNo() == 42 then
    mswkPRG0042 = "STWINFONT10/font000/I<24>"
    showText(mswkPRG0042, "STWINFONT10", "font000", "LEFT")
elseif be:TXTgetCallNo() == 43 then
    mswkPRG0043 = "STWINFONT29/font100/I<30>"
    showText(mswkPRG0043, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 44 then
    mswkPRG0044 = "STWINFONT29/font100/I<31>"
    showText(mswkPRG0044, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 45 then
    mswkPRG0045 = "STWINFONT29/font100/I<32>"
    showText(mswkPRG0045, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 46 then
    mswkPRG0046 = "STWINFONT29/font000/I<33>"
    showText(mswkPRG0046, "STWINFONT29", "font000", "LEFT")
    mswkPRG0047 = "STWINFONT29/font001/I<34>"
    showText(mswkPRG0047, "STWINFONT29", "font001", "LEFT")
    mswkPRG0048 = "STWINFONT29/font002/I<35>"
    showText(mswkPRG0048, "STWINFONT29", "font002", "LEFT")
    mswkPRG0049 = "STWINFONT29/font100/I<36>"
    showText(mswkPRG0049, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 60 then
    mswkPRG0060 = "STWINFONT12/font000/I<20>"
    showText(mswkPRG0060, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 61 then
    mswkPRG0061 = "STWINFONT09/font000/I<37>"
    showText(mswkPRG0061, "STWINFONT09", "font000", "LEFT")
    mswkPRG0062 = "STWINFONT09/font001/I<38>"
    showText(mswkPRG0062, "STWINFONT09", "font001", "LEFT")
    mswkPRG0063 = "STWINFONT09/font002/I<39>"
    showText(mswkPRG0063, "STWINFONT09", "font002", "LEFT")
    mswkPRG0064 = "STWINFONT09/font003/I<40>"
    showText(mswkPRG0064, "STWINFONT09", "font003", "LEFT")
    mswkPRG0085 = "STWINFONT29/font100/I<41>"
    showText(mswkPRG0085, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 65 then
    mswkPRG0065 = "STWINFONT26/font000/I<42>"
    showText(mswkPRG0065, "STWINFONT26", "font000", "LEFT")
    mswkPRG0066 = "STWINFONT26/font001/I<43>"
    showText(mswkPRG0066, "STWINFONT26", "font001", "LEFT")
elseif be:TXTgetCallNo() == 67 then
    mswkPRG0067 = "STWINFONT26/font000/I<44>"
    showText(mswkPRG0067, "STWINFONT26", "font000", "LEFT")
    mswkPRG0068 = "STWINFONT26/font001/I<42>"
    showText(mswkPRG0068, "STWINFONT26", "font001", "LEFT")
    mswkPRG0069 = "STWINFONT26/font002/I<43>"
    showText(mswkPRG0069, "STWINFONT26", "font002", "LEFT")
elseif be:TXTgetCallNo() == 70 then
    mswkPRG0070 = "STWINFONT13/font000/I<37>"
    showText(mswkPRG0070, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 71 then
    mswkPRG0071 = "STWINFONT13/font000/I<38>"
    showText(mswkPRG0071, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 72 then
    mswkPRG0072 = "STWINFONT13/font000/I<39>"
    showText(mswkPRG0072, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 73 then
    mswkPRG0073 = "STWINFONT39/font000/I<45>"
    showText(mswkPRG0073, "STWINFONT39", "font000", "LEFT")
elseif be:TXTgetCallNo() == 74 then
    mswkPRG0074 = "STWINFONT39/font000/I<45>"
    showText(mswkPRG0074, "STWINFONT39", "font000", "LEFT")
    mswkPRG0075 = "STWINFONT39/font001/I<46>"
    showText(mswkPRG0075, "STWINFONT39", "font001", "LEFT")
elseif be:TXTgetCallNo() == 76 then
    mswkPRG0076 = "STWINFONT39/font000/I<45>"
    showText(mswkPRG0076, "STWINFONT39", "font000", "LEFT")
    mswkPRG0077 = "STWINFONT39/font001/I<47>"
    showText(mswkPRG0077, "STWINFONT39", "font001", "LEFT")
elseif be:TXTgetCallNo() == 78 then
    mswkPRG0078 = "STWINFONT29/font000/I<48>"
    showText(mswkPRG0078, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 79 then
    mswkPRG0079 = "STWINFONT29/font000/I<49>"
    showText(mswkPRG0079, "STWINFONT29", "font000", "LEFT")
    mswkPRG0080 = "STWINFONT29/font001/I<50>"
    showText(mswkPRG0080, "STWINFONT29", "font001", "LEFT")
elseif be:TXTgetCallNo() == 81 then
    mswkPRG0081 = "STWINFONT29/font000/I<51>"
    showText(mswkPRG0081, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 82 then
    mswkPRG0082 = "STWINFONT29/font000/I<52>"
    showText(mswkPRG0082, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 83 then
    mswkPRG0083 = "STWINFONT29/font000/I<53>"
    showText(mswkPRG0083, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 84 then
    mswkPRG0084 = "STWINFONT29/font000/I<54>"
    showText(mswkPRG0084, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 87 then
    mswkPRG0087 = "STWINFONT29/font000/I<55>"
    showText(mswkPRG0087, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 88 then
    mswkPRG0088 = "STWINFONT29/font000/I<56>"
    showText(mswkPRG0088, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 90 then
    mswkPRG0090 = "STWINFONT12/font000/I<21>"
    showText(mswkPRG0090, "STWINFONT12", "font000", "LEFT")
elseif be:TXTgetCallNo() == 91 then
    mswkPRG0091 = "STWINFONT09/font000/I<57>"
    showText(mswkPRG0091, "STWINFONT09", "font000", "LEFT")
    mswkPRG0092 = "STWINFONT09/font001/I<21>"
    showText(mswkPRG0092, "STWINFONT09", "font001", "LEFT")
    mswkPRG0093 = "STWINFONT09/font002/I<58>"
    showText(mswkPRG0093, "STWINFONT09", "font002", "LEFT")
    mswkPRG0094 = "STWINFONT29/font100/I<59>"
    showText(mswkPRG0094, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 95 then
    mswkPRG0095 = "STWINFONT13/font000/I<57>"
    showText(mswkPRG0095, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 96 then
    mswkPRG0096 = "STWINFONT13/font000/I<60>"
    showText(mswkPRG0096, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 97 then
    mswkPRG0097 = "STWINFONT13/font000/I<58>"
    showText(mswkPRG0097, "STWINFONT13", "font000", "LEFT")
elseif be:TXTgetCallNo() == 98 then
    mswkPRG0098 = "STWINFONT29/font000/I<61>"
    showText(mswkPRG0098, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 99 then
    mswkPRG0099 = "STWINFONT29/font000/I<62>"
    showText(mswkPRG0099, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 100 then
    mswkPRG0100 = "STWINFONT29/font000/I<63>"
    showText(mswkPRG0100, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 101 then
    mswkPRG0101 = "STWINFONT14/font000/I<64>"
    showText(mswkPRG0101, "STWINFONT14", "font000", "LEFT")
    mswkPRG0102 = "STWINFONT14/font001/I<65>"
    showText(mswkPRG0102, "STWINFONT14", "font001", "LEFT")
    mswkPRG0103 = "STWINFONT14/font002/I<66>"
    showText(mswkPRG0103, "STWINFONT14", "font002", "LEFT")
    mswkPRG0104 = "STWINFONT14/font003/I<67>"
    showText(mswkPRG0104, "STWINFONT14", "font003", "LEFT")
    mswkPRG0105 = "STWINFONT14/font004/I<68>"
    showText(mswkPRG0105, "STWINFONT14", "font004", "LEFT")
    mswkPRG0106 = "STWINFONT14/font005/I<69>"
    showText(mswkPRG0106, "STWINFONT14", "font005", "LEFT")
    mswkPRG0107 = "STWINFONT14/font006/I<70>"
    showText(mswkPRG0107, "STWINFONT14", "font006", "LEFT")
    mswkPRG0108 = "STWINFONT14/font007/I<71>"
    showText(mswkPRG0108, "STWINFONT14", "font007", "LEFT")
    mswkPRG0109 = "STWINFONT14/font008/I<72>"
    showText(mswkPRG0109, "STWINFONT14", "font008", "LEFT")
elseif be:TXTgetCallNo() == 111 then
    mswkPRG0111 = "STWINFONT29/font000/I<73>"
    showText(mswkPRG0111, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 112 then
    mswkPRG0112 = "STWINFONT29/font000/I<74>"
    showText(mswkPRG0112, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 113 then
    mswkPRG0113 = "STWINFONT29/font000/I<75>"
    showText(mswkPRG0113, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 114 then
    mswkPRG0114 = "STWINFONT29/font000/I<76>"
    showText(mswkPRG0114, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 115 then
    mswkPRG0115 = "STWINFONT29/font000/I<77>"
    showText(mswkPRG0115, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 116 then
    mswkPRG0116 = "STWINFONT29/font000/I<78>"
    showText(mswkPRG0116, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 117 then
    mswkPRG0117 = "STWINFONT29/font000/I<79>"
    showText(mswkPRG0117, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 118 then
    mswkPRG0118 = "STWINFONT29/font000/I<80>"
    showText(mswkPRG0118, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 119 then
    mswkPRG0119 = "STWINFONT29/font000/I<81>"
    showText(mswkPRG0119, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 120 then
    mswkPRG0120 = "STWINFONT29/font000/I<82>"
    showText(mswkPRG0120, "STWINFONT29", "font000", "LEFT")
    mswkPRG0121 = "STWINFONT29/font001/I<34>"
    showText(mswkPRG0121, "STWINFONT29", "font001", "LEFT")
    mswkPRG0122 = "STWINFONT29/font002/I<35>"
    showText(mswkPRG0122, "STWINFONT29", "font002", "LEFT")
    mswkPRG0123 = "STWINFONT29/font100/I<36>"
    showText(mswkPRG0123, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 124 then
    mswkPRG0124 = "STWINFONT29/font000/I<83>"
    showText(mswkPRG0124, "STWINFONT29", "font000", "LEFT")
    mswkPRG0125 = "STWINFONT29/font001/I<34>"
    showText(mswkPRG0125, "STWINFONT29", "font001", "LEFT")
    mswkPRG0126 = "STWINFONT29/font100/I<36>"
    showText(mswkPRG0126, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 127 then
    mswkPRG0127 = "STWINFONT29/font000/I<84>"
    showText(mswkPRG0127, "STWINFONT29", "font000", "LEFT")
    mswkPRG0128 = "STWINFONT29/font001/I<85>"
    showText(mswkPRG0128, "STWINFONT29", "font001", "LEFT")
    mswkPRG0129 = "STWINFONT29/font100/I<36>"
    showText(mswkPRG0129, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 130 then
    mswkPRG0130 = "STWINFONT29/font000/I<86>"
    showText(mswkPRG0130, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 131 then
    mswkPRG0131 = "STWINFONT29/font000/I<87>"
    showText(mswkPRG0131, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 132 then
    mswkPRG0132 = "STWINFONT29/font000/I<88>"
    showText(mswkPRG0132, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 133 then
    mswkPRG0133 = "STWINFONT29/font000/I<89>"
    showText(mswkPRG0133, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 134 then
    mswkPRG0134 = "STWINFONT29/font100/I<90>"
    showText(mswkPRG0134, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 135 then
    mswkPRG0135 = "STWINFONT29/font100/I<91>"
    showText(mswkPRG0135, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 136 then
    mswkPRG0136 = "STWINFONT29/font100/I<92>"
    showText(mswkPRG0136, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 137 then
    mswkPRG0137 = "STWINFONT29/font100/I<93>"
    showText(mswkPRG0137, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 138 then
    mswkPRG0138 = "STWINFONT29/font100/I<94>"
    showText(mswkPRG0138, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 139 then
    mswkPRG0139 = "STWINFONT29/font100/I<95>"
    showText(mswkPRG0139, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 140 then
    mswkPRG0140 = "STWINFONT29/font100/I<96>"
    showText(mswkPRG0140, "STWINFONT29", "font100", "LEFT")
elseif be:TXTgetCallNo() == 141 then
    mswkPRG0141 = "STWINFONT29/font000/I<97>"
    showText(mswkPRG0141, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 142 then
    mswkPRG0142 = "STWINFONT29/font000/I<98>"
    showText(mswkPRG0142, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 143 then
    mswkPRG0143 = "STWINFONT29/font000/I<99>"
    showText(mswkPRG0143, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 144 then
    mswkPRG0144 = "STWINFONT29/font000/I<100>"
    showText(mswkPRG0144, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 145 then
    mswkPRG0145 = "STWINFONT29/font000/I<101>"
    showText(mswkPRG0145, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 146 then
    mswkPRG0146 = "STWINFONT29/font000/I<102>"
    showText(mswkPRG0146, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 147 then
    mswkPRG0147 = "STWINFONT29/font000/I<103>"
    showText(mswkPRG0147, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 148 then
    mswkPRG0148 = "STWINFONT29/font000/I<104>"
    showText(mswkPRG0148, "STWINFONT29", "font000", "LEFT")
elseif be:TXTgetCallNo() == 149 then
    mswkPRG0149 = "STWINFONT29/font000/I<105>"
    showText(mswkPRG0149, "STWINFONT29", "font000", "LEFT")
else
    be:MsgBox("error textSet", be:TXTgetCallNo())
end
