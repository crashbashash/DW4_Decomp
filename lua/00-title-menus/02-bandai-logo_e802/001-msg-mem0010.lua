local showText = function(text, arg_1, arg_2, arg_3)
    be:sd("TEXTCTL", nil, -1, "ALIGN", arg_1 .. "/" .. arg_2 .. "/" .. arg_3)
    be:sd("TEXTCTL", nil, -1, "TEXTSET", text)
    be:sd("TEXTCTL", nil, -1, "SWITCH", arg_1 .. "/" .. arg_2 .. "/DISPON")
end
if be:TXTgetCallNo() == 10 then
    mswkMem0010 = "TITLEFONT01/font000/I<0>"
    showText(mswkMem0010, "TITLEFONT01", "font000", "CENTER")
    mswkMem0011 = "TITLEFONT01/font001/I<1>"
    showText(mswkMem0011, "TITLEFONT01", "font001", "CENTER")
    mswkMem0012 = "TITLEFONT01/font002/I<2>"
    showText(mswkMem0012, "TITLEFONT01", "font002", "CENTER")
    mswkMem0013 = "TITLEFONT01/font003/I<3>"
    showText(mswkMem0013, "TITLEFONT01", "font003", "CENTER")
    mswkMem0014 = "TITLEFONT01/font004/I<4>"
    showText(mswkMem0014, "TITLEFONT01", "font004", "CENTER")
    mswkMem0015 = "TITLEFONT01/font005/I<5>"
    showText(mswkMem0015, "TITLEFONT01", "font005", "CENTER")
    mswkMem0016 = "TITLEFONT01/font006/I<6>"
    showText(mswkMem0016, "TITLEFONT01", "font006", "CENTER")
    mswkMem0017 = "TITLEFONT01/font007/I<7>"
    showText(mswkMem0017, "TITLEFONT01", "font007", "LEFT")
    mswkMem0018 = "TITLEFONT01/font008/I<8>"
    showText(mswkMem0018, "TITLEFONT01", "font008", "LEFT")
    mswkMem0019 = "TITLEFONT01/font009/I<9>"
    showText(mswkMem0019, "TITLEFONT01", "font009", "LEFT")
elseif be:TXTgetCallNo() == 30 then
    mswkMem0030 = "TITLEFONT01/font100/I<0>"
    showText(mswkMem0030, "TITLEFONT01", "font100", "CENTER")
    mswkMem0031 = "TITLEFONT01/font101/I<1>"
    showText(mswkMem0031, "TITLEFONT01", "font101", "CENTER")
    mswkMem0032 = "TITLEFONT01/font106/I<6>"
    showText(mswkMem0032, "TITLEFONT01", "font106", "CENTER")
    mswkMem0033 = "TITLEFONT01/font107/I<7>"
    showText(mswkMem0033, "TITLEFONT01", "font107", "LEFT")
    mswkMem0034 = "TITLEFONT01/font108/I<8>"
    showText(mswkMem0034, "TITLEFONT01", "font108", "LEFT")
    mswkMem0035 = "TITLEFONT01/font109/I<9>"
    showText(mswkMem0035, "TITLEFONT01", "font109", "LEFT")
elseif be:TXTgetCallNo() == 40 then
    mswkMem0040 = "TITLEFONT01/font103/I<2>"
    showText(mswkMem0040, "TITLEFONT01", "font103", "CENTER")
elseif be:TXTgetCallNo() == 41 then
    mswkMem0041 = "TITLEFONT01/font103/I<3>"
    showText(mswkMem0041, "TITLEFONT01", "font103", "CENTER")
elseif be:TXTgetCallNo() == 42 then
    mswkMem0042 = "TITLEFONT01/font104/I<4>"
    showText(mswkMem0042, "TITLEFONT01", "font104", "CENTER")
elseif be:TXTgetCallNo() == 43 then
    mswkMem0043 = "TITLEFONT01/font104/I<5>"
    showText(mswkMem0043, "TITLEFONT01", "font104", "CENTER")
elseif be:TXTgetCallNo() == 44 then
    mswkMem0044 = "TITLEFONT01/font102/I<10>"
    showText(mswkMem0044, "TITLEFONT01", "font102", "CENTER")
elseif be:TXTgetCallNo() == 45 then
    mswkMem0045 = "TITLEFONT01/font105/I<11>"
    showText(mswkMem0045, "TITLEFONT01", "font105", "CENTER")
elseif be:TXTgetCallNo() == 46 then
    mswkMem0046 = "TITLEFONT01/font105/I<12>"
    showText(mswkMem0046, "TITLEFONT01", "font105", "CENTER")
elseif be:TXTgetCallNo() == 47 then
    mswkMem0047 = "TITLEFONT01/font105/I<13>"
    showText(mswkMem0047, "TITLEFONT01", "font105", "CENTER")
elseif be:TXTgetCallNo() == 48 then
    mswkMem0048 = "TITLEFONT01/font105/I<14>"
    showText(mswkMem0048, "TITLEFONT01", "font105", "CENTER")
elseif be:TXTgetCallNo() == 49 then
    mswkMem0049 = "TITLEFONT01/font105/I<15>"
    showText(mswkMem0049, "TITLEFONT01", "font105", "CENTER")
elseif be:TXTgetCallNo() == 50 then
    mswkMem0050 = "TITLEFONT01/font105/I<16>"
    showText(mswkMem0050, "TITLEFONT01", "font105", "CENTER")
elseif be:TXTgetCallNo() == 51 then
    mswkMem0051 = "TITLEFONT01/font105/I<17>"
    showText(mswkMem0051, "TITLEFONT01", "font105", "CENTER")
elseif be:TXTgetCallNo() == 116 then
    mswkMem0116 = "CHRSELFONT09/font001/I<18>"
    showText(mswkMem0116, "CHRSELFONT09", "font001", "LEFT")
elseif be:TXTgetCallNo() == 136 then
    mswkMem0136 = "CHRSELFONT09/font000/I<18>"
    showText(mswkMem0136, "CHRSELFONT09", "font000", "LEFT")
elseif be:TXTgetCallNo() == 150 then
    mswkMem0150 = "CHRSELFONT08/font000/I<18>"
    showText(mswkMem0150, "CHRSELFONT08", "font000", "LEFT")
elseif be:TXTgetCallNo() == 151 then
    mswkMem0151 = "CHRSELFONT08/font001/I<18>"
    showText(mswkMem0151, "CHRSELFONT08", "font001", "LEFT")
elseif be:TXTgetCallNo() == 152 then
    mswkMem0152 = "CHRSELFONT08/font002/I<18>"
    showText(mswkMem0152, "CHRSELFONT08", "font002", "LEFT")
elseif be:TXTgetCallNo() == 153 then
    mswkMem0153 = "CHRSELFONT08/font003/I<18>"
    showText(mswkMem0153, "CHRSELFONT08", "font003", "LEFT")
elseif be:TXTgetCallNo() == 160 then
    mswkMem0160 = "CHRSELFONT01/font000/I<19>"
    showText(mswkMem0160, "CHRSELFONT01", "font000", "LEFT")
elseif be:TXTgetCallNo() == 161 then
    mswkMem0161 = "CHRSELFONT02/font000/I<20>"
    showText(mswkMem0161, "CHRSELFONT02", "font000", "LEFT")
    mswkMem0162 = "CHRSELFONT02/font001/I<21>"
    showText(mswkMem0162, "CHRSELFONT02", "font001", "LEFT")
elseif be:TXTgetCallNo() == 163 then
    mswkMem0163 = "CHRSELFONT02/font000/I<22>"
    showText(mswkMem0163, "CHRSELFONT02", "font000", "LEFT")
    mswkMem0164 = "CHRSELFONT02/font001/I<5>"
    showText(mswkMem0164, "CHRSELFONT02", "font001", "LEFT")
elseif be:TXTgetCallNo() == 165 then
    mswkMem0165 = "CHRSELFONT15/font000/I<22>"
    showText(mswkMem0165, "CHRSELFONT15", "font000", "LEFT")
    mswkMem0166 = "CHRSELFONT15/font001/I<5>"
    showText(mswkMem0166, "CHRSELFONT15", "font001", "LEFT")
    mswkMem0167 = "CHRSELFONT15/font002/I<23>"
    showText(mswkMem0167, "CHRSELFONT15", "font002", "LEFT")
elseif be:TXTgetCallNo() == 168 then
    mswkMem0168 = "CHRSELFONT06/font000/I<24>"
    showText(mswkMem0168, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0169 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem0169, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 200 then
    mswkMem0200 = "CHRSELFONT06/font000/I<26>"
    showText(mswkMem0200, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 201 then
    mswkMem0201 = "CHRSELFONT16/font000/I<27>"
    showText(mswkMem0201, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0202 = "CHRSELFONT16/font001/I<28>"
    showText(mswkMem0202, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0203 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0203, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 204 then
    mswkMem0204 = "CHRSELFONT06/font000/I<30>"
    showText(mswkMem0204, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 205 then
    mswkMem0205 = "CHRSELFONT06/font000/I<31>"
    showText(mswkMem0205, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0206 = "CHRSELFONT06/font001/I<32>"
    showText(mswkMem0206, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 208 then
    mswkMem0208 = "CHRSELFONT16/font000/I<33>"
    showText(mswkMem0208, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0209 = "CHRSELFONT16/font001/I<34>"
    showText(mswkMem0209, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0210 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0210, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 211 then
    mswkMem0211 = "CHRSELFONT06/font000/I<35>"
    showText(mswkMem0211, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0212 = "CHRSELFONT06/font001/I<36>"
    showText(mswkMem0212, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 213 then
    mswkMem0213 = "CHRSELFONT16/font000/I<37>"
    showText(mswkMem0213, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0214 = "CHRSELFONT16/font001/I<34>"
    showText(mswkMem0214, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0215 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0215, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 216 then
    mswkMem0216 = "CHRSELFONT06/font000/I<38>"
    showText(mswkMem0216, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0217 = "CHRSELFONT06/font001/I<39>"
    showText(mswkMem0217, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 218 then
    mswkMem0218 = "CHRSELFONT16/font000/I<40>"
    showText(mswkMem0218, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0219 = "CHRSELFONT16/font001/I<41>"
    showText(mswkMem0219, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0220 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0220, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 221 then
    mswkMem0221 = "CHRSELFONT06/font000/I<42>"
    showText(mswkMem0221, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 222 then
    mswkMem0222 = "CHRSELFONT16/font000/I<43>"
    showText(mswkMem0222, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0223 = "CHRSELFONT16/font001/I<44>"
    showText(mswkMem0223, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0224 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0224, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 225 then
    mswkMem0225 = "CHRSELFONT06/font000/I<45>"
    showText(mswkMem0225, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0226 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem0226, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 227 then
    mswkMem0227 = "CHRSELFONT06/font000/I<46>"
    showText(mswkMem0227, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0228 = "CHRSELFONT06/font001/I<47>"
    showText(mswkMem0228, "CHRSELFONT06", "font001", "LEFT")
    mswkMem0229 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem0229, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 230 then
    mswkMem0230 = "CHRSELFONT06/font000/I<48>"
    showText(mswkMem0230, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0231 = "CHRSELFONT06/font003/I<49>"
    showText(mswkMem0231, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 232 then
    mswkMem0232 = "CHRSELFONT06/font000/I<50>"
    showText(mswkMem0232, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0233 = "CHRSELFONT06/font001/I<51>"
    showText(mswkMem0233, "CHRSELFONT06", "font001", "LEFT")
    mswkMem0234 = "CHRSELFONT06/font003/I<52>"
    showText(mswkMem0234, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 235 then
    mswkMem0235 = "CHRSELFONT06/font000/I<53>"
    showText(mswkMem0235, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 236 then
    mswkMem0236 = "CHRSELFONT16/font000/I<54>"
    showText(mswkMem0236, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0237 = "CHRSELFONT16/font001/I<55>"
    showText(mswkMem0237, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0238 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0238, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 239 then
    mswkMem0239 = "CHRSELFONT06/font001/I<56>"
    showText(mswkMem0239, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 240 then
    mswkMem0240 = "CHRSELFONT06/font000/I<57>"
    showText(mswkMem0240, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0241 = "CHRSELFONT06/font001/I<58>"
    showText(mswkMem0241, "CHRSELFONT06", "font001", "LEFT")
    mswkMem0242 = "CHRSELFONT06/font003/I<59>"
    showText(mswkMem0242, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 243 then
    mswkMem0243 = "CHRSELFONT06/font000/I<57>"
    showText(mswkMem0243, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0244 = "CHRSELFONT06/font001/I<60>"
    showText(mswkMem0244, "CHRSELFONT06", "font001", "LEFT")
    mswkMem0245 = "CHRSELFONT06/font003/I<59>"
    showText(mswkMem0245, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 246 then
    mswkMem0246 = "CHRSELFONT06/font000/I<57>"
    showText(mswkMem0246, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0247 = "CHRSELFONT06/font001/I<58>"
    showText(mswkMem0247, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 248 then
    mswkMem0248 = "CHRSELFONT06/font000/I<57>"
    showText(mswkMem0248, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0249 = "CHRSELFONT06/font001/I<60>"
    showText(mswkMem0249, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 250 then
    mswkMem0250 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0250, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 251 then
    mswkMem0251 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem0251, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 252 then
    mswkMem0252 = "CHRSELFONT06/font000/I<61>"
    showText(mswkMem0252, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0253 = "CHRSELFONT06/font001/I<62>"
    showText(mswkMem0253, "CHRSELFONT06", "font001", "LEFT")
    mswkMem0254 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem0254, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 255 then
    mswkMem0255 = "CHRSELFONT06/font000/I<63>"
    showText(mswkMem0255, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0256 = "CHRSELFONT06/font001/I<36>"
    showText(mswkMem0256, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 257 then
    mswkMem0257 = "CHRSELFONT16/font000/I<64>"
    showText(mswkMem0257, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0258 = "CHRSELFONT16/font001/I<65>"
    showText(mswkMem0258, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0259 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem0259, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 260 then
    mswkMem0260 = "CHRSELFONT06/font000/I<66>"
    showText(mswkMem0260, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0261 = "CHRSELFONT06/font001/I<56>"
    showText(mswkMem0261, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 262 then
    mswkMem0262 = "CHRSELFONT06/font000/I<67>"
    showText(mswkMem0262, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0263 = "CHRSELFONT06/font001/I<36>"
    showText(mswkMem0263, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 264 then
    mswkMem0264 = "CHRSELFONT06/font000/I<68>"
    showText(mswkMem0264, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 265 then
    mswkMem0265 = "CHRSELFONT16/font000/I<69>"
    showText(mswkMem0265, "CHRSELFONT16", "font000", "LEFT")
    mswkMem0266 = "CHRSELFONT16/font001/I<70>"
    showText(mswkMem0266, "CHRSELFONT16", "font001", "LEFT")
    mswkMem0267 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem0267, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 268 then
    mswkMem0268 = "CHRSELFONT06/font000/I<71>"
    showText(mswkMem0268, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0269 = "CHRSELFONT06/font001/I<60>"
    showText(mswkMem0269, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 270 then
    mswkMem0270 = "CHRSELFONT06/font000/I<71>"
    showText(mswkMem0270, "CHRSELFONT06", "font000", "LEFT")
    mswkMem0271 = "CHRSELFONT06/font001/I<60>"
    showText(mswkMem0271, "CHRSELFONT06", "font001", "LEFT")
    mswkMem0272 = "CHRSELFONT06/font003/I<59>"
    showText(mswkMem0272, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 300 then
    mswkMem0300 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem0300, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 10116 then
    mswkMem10116 = "CHRSELFONT09/font101/I<18>"
    showText(mswkMem10116, "CHRSELFONT09", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10136 then
    mswkMem10136 = "CHRSELFONT09/font100/I<18>"
    showText(mswkMem10136, "CHRSELFONT09", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10150 then
    mswkMem10150 = "CHRSELFONT08/font100/I<18>"
    showText(mswkMem10150, "CHRSELFONT08", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10151 then
    mswkMem10151 = "CHRSELFONT08/font101/I<18>"
    showText(mswkMem10151, "CHRSELFONT08", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10152 then
    mswkMem10152 = "CHRSELFONT08/font102/I<18>"
    showText(mswkMem10152, "CHRSELFONT08", "font102", "LEFT")
elseif be:TXTgetCallNo() == 10153 then
    mswkMem10153 = "CHRSELFONT08/font103/I<18>"
    showText(mswkMem10153, "CHRSELFONT08", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10160 then
    mswkMem10160 = "CHRSELFONT01/font100/I<19>"
    showText(mswkMem10160, "CHRSELFONT01", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10161 then
    mswkMem10161 = "CHRSELFONT02/font100/I<20>"
    showText(mswkMem10161, "CHRSELFONT02", "font100", "LEFT")
    mswkMem10162 = "CHRSELFONT02/font101/I<21>"
    showText(mswkMem10162, "CHRSELFONT02", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10163 then
    mswkMem10163 = "CHRSELFONT02/font100/I<22>"
    showText(mswkMem10163, "CHRSELFONT02", "font100", "LEFT")
    mswkMem10164 = "CHRSELFONT02/font101/I<5>"
    showText(mswkMem10164, "CHRSELFONT02", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10165 then
    mswkMem10165 = "CHRSELFONT15/font100/I<22>"
    showText(mswkMem10165, "CHRSELFONT15", "font100", "LEFT")
    mswkMem10166 = "CHRSELFONT15/font101/I<5>"
    showText(mswkMem10166, "CHRSELFONT15", "font101", "LEFT")
    mswkMem10167 = "CHRSELFONT15/font102/I<23>"
    showText(mswkMem10167, "CHRSELFONT15", "font102", "LEFT")
elseif be:TXTgetCallNo() == 10168 then
    mswkMem10168 = "CHRSELFONT06/font100/I<24>"
    showText(mswkMem10168, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10169 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem10169, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10200 then
    mswkMem10200 = "CHRSELFONT06/font100/I<26>"
    showText(mswkMem10200, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10201 then
    mswkMem10201 = "CHRSELFONT16/font100/I<27>"
    showText(mswkMem10201, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10202 = "CHRSELFONT16/font101/I<28>"
    showText(mswkMem10202, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10203 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10203, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10204 then
    mswkMem10204 = "CHRSELFONT06/font100/I<30>"
    showText(mswkMem10204, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10205 then
    mswkMem10205 = "CHRSELFONT06/font100/I<31>"
    showText(mswkMem10205, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10206 = "CHRSELFONT06/font101/I<32>"
    showText(mswkMem10206, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10208 then
    mswkMem10208 = "CHRSELFONT16/font100/I<33>"
    showText(mswkMem10208, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10209 = "CHRSELFONT16/font101/I<34>"
    showText(mswkMem10209, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10210 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10210, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10211 then
    mswkMem10211 = "CHRSELFONT06/font100/I<35>"
    showText(mswkMem10211, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10212 = "CHRSELFONT06/font101/I<36>"
    showText(mswkMem10212, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10213 then
    mswkMem10213 = "CHRSELFONT16/font100/I<37>"
    showText(mswkMem10213, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10214 = "CHRSELFONT16/font101/I<34>"
    showText(mswkMem10214, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10215 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10215, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10216 then
    mswkMem10216 = "CHRSELFONT06/font100/I<38>"
    showText(mswkMem10216, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10217 = "CHRSELFONT06/font101/I<39>"
    showText(mswkMem10217, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10218 then
    mswkMem10218 = "CHRSELFONT16/font100/I<40>"
    showText(mswkMem10218, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10219 = "CHRSELFONT16/font101/I<41>"
    showText(mswkMem10219, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10220 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10220, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10221 then
    mswkMem10221 = "CHRSELFONT06/font100/I<42>"
    showText(mswkMem10221, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10222 then
    mswkMem10222 = "CHRSELFONT16/font100/I<43>"
    showText(mswkMem10222, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10223 = "CHRSELFONT16/font101/I<44>"
    showText(mswkMem10223, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10224 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10224, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10225 then
    mswkMem10225 = "CHRSELFONT06/font100/I<45>"
    showText(mswkMem10225, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10226 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem10226, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10227 then
    mswkMem10227 = "CHRSELFONT06/font100/I<46>"
    showText(mswkMem10227, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10228 = "CHRSELFONT06/font101/I<47>"
    showText(mswkMem10228, "CHRSELFONT06", "font101", "LEFT")
    mswkMem10229 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem10229, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10230 then
    mswkMem10230 = "CHRSELFONT06/font100/I<48>"
    showText(mswkMem10230, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10231 = "CHRSELFONT06/font103/I<49>"
    showText(mswkMem10231, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10232 then
    mswkMem10232 = "CHRSELFONT06/font100/I<50>"
    showText(mswkMem10232, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10233 = "CHRSELFONT06/font101/I<51>"
    showText(mswkMem10233, "CHRSELFONT06", "font101", "LEFT")
    mswkMem10234 = "CHRSELFONT06/font103/I<52>"
    showText(mswkMem10234, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10235 then
    mswkMem10235 = "CHRSELFONT06/font100/I<53>"
    showText(mswkMem10235, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10236 then
    mswkMem10236 = "CHRSELFONT16/font100/I<54>"
    showText(mswkMem10236, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10237 = "CHRSELFONT16/font101/I<55>"
    showText(mswkMem10237, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10238 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10238, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10239 then
    mswkMem10239 = "CHRSELFONT06/font101/I<56>"
    showText(mswkMem10239, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10240 then
    mswkMem10240 = "CHRSELFONT06/font100/I<57>"
    showText(mswkMem10240, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10241 = "CHRSELFONT06/font101/I<58>"
    showText(mswkMem10241, "CHRSELFONT06", "font101", "LEFT")
    mswkMem10242 = "CHRSELFONT06/font103/I<59>"
    showText(mswkMem10242, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10243 then
    mswkMem10243 = "CHRSELFONT06/font100/I<57>"
    showText(mswkMem10243, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10244 = "CHRSELFONT06/font101/I<60>"
    showText(mswkMem10244, "CHRSELFONT06", "font101", "LEFT")
    mswkMem10245 = "CHRSELFONT06/font103/I<59>"
    showText(mswkMem10245, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10246 then
    mswkMem10246 = "CHRSELFONT06/font100/I<57>"
    showText(mswkMem10246, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10247 = "CHRSELFONT06/font101/I<58>"
    showText(mswkMem10247, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10248 then
    mswkMem10248 = "CHRSELFONT06/font100/I<57>"
    showText(mswkMem10248, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10249 = "CHRSELFONT06/font101/I<60>"
    showText(mswkMem10249, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10250 then
    mswkMem10250 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10250, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10251 then
    mswkMem10251 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem10251, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10252 then
    mswkMem10252 = "CHRSELFONT06/font100/I<61>"
    showText(mswkMem10252, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10253 = "CHRSELFONT06/font101/I<62>"
    showText(mswkMem10253, "CHRSELFONT06", "font101", "LEFT")
    mswkMem10254 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem10254, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10255 then
    mswkMem10255 = "CHRSELFONT06/font100/I<63>"
    showText(mswkMem10255, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10256 = "CHRSELFONT06/font101/I<36>"
    showText(mswkMem10256, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10257 then
    mswkMem10257 = "CHRSELFONT16/font100/I<64>"
    showText(mswkMem10257, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10258 = "CHRSELFONT16/font101/I<65>"
    showText(mswkMem10258, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10259 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem10259, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10260 then
    mswkMem10260 = "CHRSELFONT06/font100/I<66>"
    showText(mswkMem10260, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10261 = "CHRSELFONT06/font101/I<56>"
    showText(mswkMem10261, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10262 then
    mswkMem10262 = "CHRSELFONT06/font100/I<67>"
    showText(mswkMem10262, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10263 = "CHRSELFONT06/font101/I<36>"
    showText(mswkMem10263, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10264 then
    mswkMem10264 = "CHRSELFONT06/font100/I<68>"
    showText(mswkMem10264, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 10265 then
    mswkMem10265 = "CHRSELFONT16/font100/I<69>"
    showText(mswkMem10265, "CHRSELFONT16", "font100", "LEFT")
    mswkMem10266 = "CHRSELFONT16/font101/I<70>"
    showText(mswkMem10266, "CHRSELFONT16", "font101", "LEFT")
    mswkMem10267 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem10267, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10268 then
    mswkMem10268 = "CHRSELFONT06/font100/I<71>"
    showText(mswkMem10268, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10269 = "CHRSELFONT06/font101/I<60>"
    showText(mswkMem10269, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 10270 then
    mswkMem10270 = "CHRSELFONT06/font100/I<71>"
    showText(mswkMem10270, "CHRSELFONT06", "font100", "LEFT")
    mswkMem10271 = "CHRSELFONT06/font101/I<60>"
    showText(mswkMem10271, "CHRSELFONT06", "font101", "LEFT")
    mswkMem10272 = "CHRSELFONT06/font103/I<59>"
    showText(mswkMem10272, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 10300 then
    mswkMem10300 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem10300, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 20116 then
    mswkMem20116 = "CHRSELFONT09/font201/I<18>"
    showText(mswkMem20116, "CHRSELFONT09", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20136 then
    mswkMem20136 = "CHRSELFONT09/font200/I<18>"
    showText(mswkMem20136, "CHRSELFONT09", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20150 then
    mswkMem20150 = "CHRSELFONT08/font200/I<18>"
    showText(mswkMem20150, "CHRSELFONT08", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20151 then
    mswkMem20151 = "CHRSELFONT08/font201/I<18>"
    showText(mswkMem20151, "CHRSELFONT08", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20152 then
    mswkMem20152 = "CHRSELFONT08/font202/I<18>"
    showText(mswkMem20152, "CHRSELFONT08", "font202", "LEFT")
elseif be:TXTgetCallNo() == 20153 then
    mswkMem20153 = "CHRSELFONT08/font203/I<18>"
    showText(mswkMem20153, "CHRSELFONT08", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20160 then
    mswkMem20160 = "CHRSELFONT01/font200/I<19>"
    showText(mswkMem20160, "CHRSELFONT01", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20161 then
    mswkMem20161 = "CHRSELFONT02/font200/I<20>"
    showText(mswkMem20161, "CHRSELFONT02", "font200", "LEFT")
    mswkMem20162 = "CHRSELFONT02/font201/I<21>"
    showText(mswkMem20162, "CHRSELFONT02", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20163 then
    mswkMem20163 = "CHRSELFONT02/font200/I<22>"
    showText(mswkMem20163, "CHRSELFONT02", "font200", "LEFT")
    mswkMem20164 = "CHRSELFONT02/font201/I<5>"
    showText(mswkMem20164, "CHRSELFONT02", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20165 then
    mswkMem20165 = "CHRSELFONT15/font200/I<22>"
    showText(mswkMem20165, "CHRSELFONT15", "font200", "LEFT")
    mswkMem20166 = "CHRSELFONT15/font201/I<5>"
    showText(mswkMem20166, "CHRSELFONT15", "font201", "LEFT")
    mswkMem20167 = "CHRSELFONT15/font202/I<23>"
    showText(mswkMem20167, "CHRSELFONT15", "font202", "LEFT")
elseif be:TXTgetCallNo() == 20168 then
    mswkMem20168 = "CHRSELFONT06/font200/I<24>"
    showText(mswkMem20168, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20169 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem20169, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 20200 then
    mswkMem20200 = "CHRSELFONT06/font200/I<26>"
    showText(mswkMem20200, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20201 then
    mswkMem20201 = "CHRSELFONT16/font200/I<27>"
    showText(mswkMem20201, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20202 = "CHRSELFONT16/font201/I<28>"
    showText(mswkMem20202, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20203 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20203, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20204 then
    mswkMem20204 = "CHRSELFONT06/font200/I<30>"
    showText(mswkMem20204, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20205 then
    mswkMem20205 = "CHRSELFONT06/font200/I<31>"
    showText(mswkMem20205, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20206 = "CHRSELFONT06/font201/I<32>"
    showText(mswkMem20206, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20208 then
    mswkMem20208 = "CHRSELFONT16/font200/I<33>"
    showText(mswkMem20208, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20209 = "CHRSELFONT16/font201/I<34>"
    showText(mswkMem20209, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20210 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20210, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20211 then
    mswkMem20211 = "CHRSELFONT06/font200/I<35>"
    showText(mswkMem20211, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20212 = "CHRSELFONT06/font201/I<36>"
    showText(mswkMem20212, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20213 then
    mswkMem20213 = "CHRSELFONT16/font200/I<37>"
    showText(mswkMem20213, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20214 = "CHRSELFONT16/font201/I<34>"
    showText(mswkMem20214, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20215 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20215, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20216 then
    mswkMem20216 = "CHRSELFONT06/font200/I<38>"
    showText(mswkMem20216, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20217 = "CHRSELFONT06/font201/I<39>"
    showText(mswkMem20217, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20218 then
    mswkMem20218 = "CHRSELFONT16/font200/I<40>"
    showText(mswkMem20218, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20219 = "CHRSELFONT16/font201/I<41>"
    showText(mswkMem20219, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20220 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20220, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20221 then
    mswkMem20221 = "CHRSELFONT06/font200/I<42>"
    showText(mswkMem20221, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20222 then
    mswkMem20222 = "CHRSELFONT16/font200/I<43>"
    showText(mswkMem20222, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20223 = "CHRSELFONT16/font201/I<44>"
    showText(mswkMem20223, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20224 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20224, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20225 then
    mswkMem20225 = "CHRSELFONT06/font200/I<45>"
    showText(mswkMem20225, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20226 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem20226, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20227 then
    mswkMem20227 = "CHRSELFONT06/font200/I<46>"
    showText(mswkMem20227, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20228 = "CHRSELFONT06/font201/I<47>"
    showText(mswkMem20228, "CHRSELFONT06", "font201", "LEFT")
    mswkMem20229 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem20229, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20230 then
    mswkMem20230 = "CHRSELFONT06/font200/I<48>"
    showText(mswkMem20230, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20231 = "CHRSELFONT06/font203/I<49>"
    showText(mswkMem20231, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20232 then
    mswkMem20232 = "CHRSELFONT06/font200/I<50>"
    showText(mswkMem20232, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20233 = "CHRSELFONT06/font201/I<51>"
    showText(mswkMem20233, "CHRSELFONT06", "font201", "LEFT")
    mswkMem20234 = "CHRSELFONT06/font203/I<52>"
    showText(mswkMem20234, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20235 then
    mswkMem20235 = "CHRSELFONT06/font200/I<53>"
    showText(mswkMem20235, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20236 then
    mswkMem20236 = "CHRSELFONT16/font200/I<54>"
    showText(mswkMem20236, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20237 = "CHRSELFONT16/font201/I<55>"
    showText(mswkMem20237, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20238 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20238, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20239 then
    mswkMem20239 = "CHRSELFONT06/font201/I<56>"
    showText(mswkMem20239, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20240 then
    mswkMem20240 = "CHRSELFONT06/font200/I<57>"
    showText(mswkMem20240, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20241 = "CHRSELFONT06/font201/I<58>"
    showText(mswkMem20241, "CHRSELFONT06", "font201", "LEFT")
    mswkMem20242 = "CHRSELFONT06/font203/I<59>"
    showText(mswkMem20242, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20243 then
    mswkMem20243 = "CHRSELFONT06/font200/I<57>"
    showText(mswkMem20243, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20244 = "CHRSELFONT06/font201/I<60>"
    showText(mswkMem20244, "CHRSELFONT06", "font201", "LEFT")
    mswkMem20245 = "CHRSELFONT06/font203/I<59>"
    showText(mswkMem20245, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20246 then
    mswkMem20246 = "CHRSELFONT06/font200/I<57>"
    showText(mswkMem20246, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20247 = "CHRSELFONT06/font201/I<58>"
    showText(mswkMem20247, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20248 then
    mswkMem20248 = "CHRSELFONT06/font200/I<57>"
    showText(mswkMem20248, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20249 = "CHRSELFONT06/font201/I<60>"
    showText(mswkMem20249, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20250 then
    mswkMem20250 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20250, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20251 then
    mswkMem20251 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem20251, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20252 then
    mswkMem20252 = "CHRSELFONT06/font200/I<61>"
    showText(mswkMem20252, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20253 = "CHRSELFONT06/font201/I<62>"
    showText(mswkMem20253, "CHRSELFONT06", "font201", "LEFT")
    mswkMem20254 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem20254, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20255 then
    mswkMem20255 = "CHRSELFONT06/font200/I<63>"
    showText(mswkMem20255, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20256 = "CHRSELFONT06/font201/I<36>"
    showText(mswkMem20256, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20257 then
    mswkMem20257 = "CHRSELFONT16/font200/I<64>"
    showText(mswkMem20257, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20258 = "CHRSELFONT16/font201/I<65>"
    showText(mswkMem20258, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20259 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem20259, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20260 then
    mswkMem20260 = "CHRSELFONT06/font200/I<66>"
    showText(mswkMem20260, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20261 = "CHRSELFONT06/font201/I<56>"
    showText(mswkMem20261, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20262 then
    mswkMem20262 = "CHRSELFONT06/font200/I<67>"
    showText(mswkMem20262, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20263 = "CHRSELFONT06/font201/I<36>"
    showText(mswkMem20263, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20264 then
    mswkMem20264 = "CHRSELFONT06/font200/I<68>"
    showText(mswkMem20264, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 20265 then
    mswkMem20265 = "CHRSELFONT16/font200/I<69>"
    showText(mswkMem20265, "CHRSELFONT16", "font200", "LEFT")
    mswkMem20266 = "CHRSELFONT16/font201/I<70>"
    showText(mswkMem20266, "CHRSELFONT16", "font201", "LEFT")
    mswkMem20267 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem20267, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20268 then
    mswkMem20268 = "CHRSELFONT06/font200/I<71>"
    showText(mswkMem20268, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20269 = "CHRSELFONT06/font201/I<60>"
    showText(mswkMem20269, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 20270 then
    mswkMem20270 = "CHRSELFONT06/font200/I<71>"
    showText(mswkMem20270, "CHRSELFONT06", "font200", "LEFT")
    mswkMem20271 = "CHRSELFONT06/font201/I<60>"
    showText(mswkMem20271, "CHRSELFONT06", "font201", "LEFT")
    mswkMem20272 = "CHRSELFONT06/font203/I<59>"
    showText(mswkMem20272, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 20300 then
    mswkMem20300 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem20300, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 30116 then
    mswkMem30116 = "CHRSELFONT09/font301/I<18>"
    showText(mswkMem30116, "CHRSELFONT09", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30136 then
    mswkMem30136 = "CHRSELFONT09/font300/I<18>"
    showText(mswkMem30136, "CHRSELFONT09", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30150 then
    mswkMem30150 = "CHRSELFONT08/font300/I<18>"
    showText(mswkMem30150, "CHRSELFONT08", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30151 then
    mswkMem30151 = "CHRSELFONT08/font301/I<18>"
    showText(mswkMem30151, "CHRSELFONT08", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30152 then
    mswkMem30152 = "CHRSELFONT08/font302/I<18>"
    showText(mswkMem30152, "CHRSELFONT08", "font302", "LEFT")
elseif be:TXTgetCallNo() == 30153 then
    mswkMem30153 = "CHRSELFONT08/font303/I<18>"
    showText(mswkMem30153, "CHRSELFONT08", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30160 then
    mswkMem30160 = "CHRSELFONT01/font300/I<19>"
    showText(mswkMem30160, "CHRSELFONT01", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30161 then
    mswkMem30161 = "CHRSELFONT02/font300/I<20>"
    showText(mswkMem30161, "CHRSELFONT02", "font300", "LEFT")
    mswkMem30162 = "CHRSELFONT02/font301/I<21>"
    showText(mswkMem30162, "CHRSELFONT02", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30163 then
    mswkMem30163 = "CHRSELFONT02/font300/I<22>"
    showText(mswkMem30163, "CHRSELFONT02", "font300", "LEFT")
    mswkMem30164 = "CHRSELFONT02/font301/I<5>"
    showText(mswkMem30164, "CHRSELFONT02", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30165 then
    mswkMem30165 = "CHRSELFONT15/font300/I<22>"
    showText(mswkMem30165, "CHRSELFONT15", "font300", "LEFT")
    mswkMem30166 = "CHRSELFONT15/font301/I<5>"
    showText(mswkMem30166, "CHRSELFONT15", "font301", "LEFT")
    mswkMem30167 = "CHRSELFONT15/font302/I<23>"
    showText(mswkMem30167, "CHRSELFONT15", "font302", "LEFT")
elseif be:TXTgetCallNo() == 30168 then
    mswkMem30168 = "CHRSELFONT06/font300/I<24>"
    showText(mswkMem30168, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30169 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem30169, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30200 then
    mswkMem30200 = "CHRSELFONT06/font300/I<26>"
    showText(mswkMem30200, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30201 then
    mswkMem30201 = "CHRSELFONT16/font300/I<27>"
    showText(mswkMem30201, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30202 = "CHRSELFONT16/font301/I<28>"
    showText(mswkMem30202, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30203 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30203, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30204 then
    mswkMem30204 = "CHRSELFONT06/font300/I<30>"
    showText(mswkMem30204, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30205 then
    mswkMem30205 = "CHRSELFONT06/font300/I<31>"
    showText(mswkMem30205, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30206 = "CHRSELFONT06/font301/I<32>"
    showText(mswkMem30206, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30208 then
    mswkMem30208 = "CHRSELFONT16/font300/I<33>"
    showText(mswkMem30208, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30209 = "CHRSELFONT16/font301/I<34>"
    showText(mswkMem30209, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30210 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30210, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30211 then
    mswkMem30211 = "CHRSELFONT06/font300/I<35>"
    showText(mswkMem30211, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30212 = "CHRSELFONT06/font301/I<36>"
    showText(mswkMem30212, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30213 then
    mswkMem30213 = "CHRSELFONT16/font300/I<37>"
    showText(mswkMem30213, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30214 = "CHRSELFONT16/font301/I<34>"
    showText(mswkMem30214, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30215 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30215, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30216 then
    mswkMem30216 = "CHRSELFONT06/font300/I<38>"
    showText(mswkMem30216, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30217 = "CHRSELFONT06/font301/I<39>"
    showText(mswkMem30217, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30218 then
    mswkMem30218 = "CHRSELFONT16/font300/I<40>"
    showText(mswkMem30218, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30219 = "CHRSELFONT16/font301/I<41>"
    showText(mswkMem30219, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30220 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30220, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30221 then
    mswkMem30221 = "CHRSELFONT06/font300/I<42>"
    showText(mswkMem30221, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30222 then
    mswkMem30222 = "CHRSELFONT16/font300/I<43>"
    showText(mswkMem30222, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30223 = "CHRSELFONT16/font301/I<44>"
    showText(mswkMem30223, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30224 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30224, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30225 then
    mswkMem30225 = "CHRSELFONT06/font300/I<45>"
    showText(mswkMem30225, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30226 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem30226, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30227 then
    mswkMem30227 = "CHRSELFONT06/font300/I<46>"
    showText(mswkMem30227, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30228 = "CHRSELFONT06/font301/I<47>"
    showText(mswkMem30228, "CHRSELFONT06", "font301", "LEFT")
    mswkMem30229 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem30229, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30230 then
    mswkMem30230 = "CHRSELFONT06/font300/I<48>"
    showText(mswkMem30230, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30231 = "CHRSELFONT06/font303/I<49>"
    showText(mswkMem30231, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30232 then
    mswkMem30232 = "CHRSELFONT06/font300/I<50>"
    showText(mswkMem30232, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30233 = "CHRSELFONT06/font301/I<51>"
    showText(mswkMem30233, "CHRSELFONT06", "font301", "LEFT")
    mswkMem30234 = "CHRSELFONT06/font303/I<52>"
    showText(mswkMem30234, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30235 then
    mswkMem30235 = "CHRSELFONT06/font300/I<53>"
    showText(mswkMem30235, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30236 then
    mswkMem30236 = "CHRSELFONT16/font300/I<54>"
    showText(mswkMem30236, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30237 = "CHRSELFONT16/font301/I<55>"
    showText(mswkMem30237, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30238 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30238, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30239 then
    mswkMem30239 = "CHRSELFONT06/font301/I<56>"
    showText(mswkMem30239, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30240 then
    mswkMem30240 = "CHRSELFONT06/font300/I<57>"
    showText(mswkMem30240, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30241 = "CHRSELFONT06/font301/I<58>"
    showText(mswkMem30241, "CHRSELFONT06", "font301", "LEFT")
    mswkMem30242 = "CHRSELFONT06/font303/I<59>"
    showText(mswkMem30242, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30243 then
    mswkMem30243 = "CHRSELFONT06/font300/I<57>"
    showText(mswkMem30243, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30244 = "CHRSELFONT06/font301/I<60>"
    showText(mswkMem30244, "CHRSELFONT06", "font301", "LEFT")
    mswkMem30245 = "CHRSELFONT06/font303/I<59>"
    showText(mswkMem30245, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30246 then
    mswkMem30246 = "CHRSELFONT06/font300/I<57>"
    showText(mswkMem30246, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30247 = "CHRSELFONT06/font301/I<58>"
    showText(mswkMem30247, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30248 then
    mswkMem30248 = "CHRSELFONT06/font300/I<57>"
    showText(mswkMem30248, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30249 = "CHRSELFONT06/font301/I<60>"
    showText(mswkMem30249, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30250 then
    mswkMem30250 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30250, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30251 then
    mswkMem30251 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem30251, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30252 then
    mswkMem30252 = "CHRSELFONT06/font300/I<61>"
    showText(mswkMem30252, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30253 = "CHRSELFONT06/font301/I<62>"
    showText(mswkMem30253, "CHRSELFONT06", "font301", "LEFT")
    mswkMem30254 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem30254, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30255 then
    mswkMem30255 = "CHRSELFONT06/font300/I<63>"
    showText(mswkMem30255, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30256 = "CHRSELFONT06/font301/I<36>"
    showText(mswkMem30256, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30257 then
    mswkMem30257 = "CHRSELFONT16/font300/I<64>"
    showText(mswkMem30257, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30258 = "CHRSELFONT16/font301/I<65>"
    showText(mswkMem30258, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30259 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem30259, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30260 then
    mswkMem30260 = "CHRSELFONT06/font300/I<66>"
    showText(mswkMem30260, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30261 = "CHRSELFONT06/font301/I<56>"
    showText(mswkMem30261, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30262 then
    mswkMem30262 = "CHRSELFONT06/font300/I<67>"
    showText(mswkMem30262, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30263 = "CHRSELFONT06/font301/I<36>"
    showText(mswkMem30263, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30264 then
    mswkMem30264 = "CHRSELFONT06/font300/I<68>"
    showText(mswkMem30264, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 30265 then
    mswkMem30265 = "CHRSELFONT16/font300/I<69>"
    showText(mswkMem30265, "CHRSELFONT16", "font300", "LEFT")
    mswkMem30266 = "CHRSELFONT16/font301/I<70>"
    showText(mswkMem30266, "CHRSELFONT16", "font301", "LEFT")
    mswkMem30267 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem30267, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30268 then
    mswkMem30268 = "CHRSELFONT06/font300/I<71>"
    showText(mswkMem30268, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30269 = "CHRSELFONT06/font301/I<60>"
    showText(mswkMem30269, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 30270 then
    mswkMem30270 = "CHRSELFONT06/font300/I<71>"
    showText(mswkMem30270, "CHRSELFONT06", "font300", "LEFT")
    mswkMem30271 = "CHRSELFONT06/font301/I<60>"
    showText(mswkMem30271, "CHRSELFONT06", "font301", "LEFT")
    mswkMem30272 = "CHRSELFONT06/font303/I<59>"
    showText(mswkMem30272, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 30300 then
    mswkMem30300 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem30300, "CHRSELFONT06", "font303", "LEFT")
else
    be:MsgBox("error textSet", be:TXTgetCallNo())
end
