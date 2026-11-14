local showText = function(text, arg_1, arg_2, arg_3)
    be:sd("TEXTCTL", nil, -1, "ALIGN", arg_1 .. "/" .. arg_2 .. "/" .. arg_3)
    be:sd("TEXTCTL", nil, -1, "TEXTSET", text)
    be:sd("TEXTCTL", nil, -1, "SWITCH", arg_1 .. "/" .. arg_2 .. "/DISPON")
end
if be:TXTgetCallNo() == 1000 then
    mswkMem1000 = "CHRSELFONT06/font000/I<72>"
    showText(mswkMem1000, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1001 = "CHRSELFONT06/font001/I<73>"
    showText(mswkMem1001, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1002 then
    mswkMem1002 = "CHRSELFONT16/font000/I<74>"
    showText(mswkMem1002, "CHRSELFONT16", "font000", "LEFT")
    mswkMem1003 = "CHRSELFONT16/font001/I<75>"
    showText(mswkMem1003, "CHRSELFONT16", "font001", "LEFT")
    mswkMem1004 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem1004, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1005 then
    mswkMem1005 = "CHRSELFONT06/font000/I<76>"
    showText(mswkMem1005, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1006 = "CHRSELFONT06/font001/I<77>"
    showText(mswkMem1006, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1007 then
    mswkMem1007 = "CHRSELFONT06/font000/I<78>"
    showText(mswkMem1007, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1008 = "CHRSELFONT06/font001/I<79>"
    showText(mswkMem1008, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1009 then
    mswkMem1009 = "CHRSELFONT06/font000/I<80>"
    showText(mswkMem1009, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1010 = "CHRSELFONT06/font001/I<81>"
    showText(mswkMem1010, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1012 then
    mswkMem1012 = "CHRSELFONT16/font000/I<82>"
    showText(mswkMem1012, "CHRSELFONT16", "font000", "LEFT")
    mswkMem1013 = "CHRSELFONT16/font001/I<83>"
    showText(mswkMem1013, "CHRSELFONT16", "font001", "LEFT")
    mswkMem1014 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem1014, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1015 then
    mswkMem1015 = "CHRSELFONT06/font000/I<84>"
    showText(mswkMem1015, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1016 = "CHRSELFONT06/font001/I<79>"
    showText(mswkMem1016, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1017 then
    mswkMem1017 = "CHRSELFONT06/font000/I<85>"
    showText(mswkMem1017, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1018 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem1018, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1019 then
    mswkMem1019 = "CHRSELFONT06/font000/I<86>"
    showText(mswkMem1019, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1020 = "CHRSELFONT06/font001/I<77>"
    showText(mswkMem1020, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1021 then
    mswkMem1021 = "CHRSELFONT06/font000/I<87>"
    showText(mswkMem1021, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1022 = "CHRSELFONT06/font001/I<79>"
    showText(mswkMem1022, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1050 then
    mswkMem1050 = "CHRSELFONT07/font000/I<88>"
    showText(mswkMem1050, "CHRSELFONT07", "font000", "LEFT")
    mswkMem1051 = "CHRSELFONT07/font001/I<89>"
    showText(mswkMem1051, "CHRSELFONT07", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1100 then
    mswkMem1100 = "CHRSELFONT06/font000/I<90>"
    showText(mswkMem1100, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1101 = "CHRSELFONT06/font001/I<91>"
    showText(mswkMem1101, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1102 then
    mswkMem1102 = "CHRSELFONT06/font000/I<92>"
    showText(mswkMem1102, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1103 = "CHRSELFONT06/font001/I<91>"
    showText(mswkMem1103, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1104 then
    mswkMem1104 = "CHRSELFONT06/font000/I<93>"
    showText(mswkMem1104, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1105 = "CHRSELFONT06/font001/I<94>"
    showText(mswkMem1105, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1106 then
    mswkMem1106 = "CHRSELFONT06/font000/I<95>"
    showText(mswkMem1106, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1107 = "CHRSELFONT06/font001/I<96>"
    showText(mswkMem1107, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1108 then
    mswkMem1108 = "CHRSELFONT06/font000/I<97>"
    showText(mswkMem1108, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1109 = "CHRSELFONT06/font001/I<98>"
    showText(mswkMem1109, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1110 then
    mswkMem1110 = "CHRSELFONT06/font000/I<99>"
    showText(mswkMem1110, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1111 = "CHRSELFONT06/font001/I<100>"
    showText(mswkMem1111, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1112 then
    mswkMem1112 = "CHRSELFONT06/font000/I<101>"
    showText(mswkMem1112, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1113 = "CHRSELFONT06/font001/I<102>"
    showText(mswkMem1113, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1114 then
    mswkMem1114 = "CHRSELFONT06/font000/I<103>"
    showText(mswkMem1114, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1115 = "CHRSELFONT06/font001/I<104>"
    showText(mswkMem1115, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1117 then
    mswkMem1117 = "CHRSELFONT06/font000/I<105>"
    showText(mswkMem1117, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1118 = "CHRSELFONT06/font001/I<106>"
    showText(mswkMem1118, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1119 then
    mswkMem1119 = "CHRSELFONT06/font001/I<107>"
    showText(mswkMem1119, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1120 then
    mswkMem1120 = "CHRSELFONT06/font000/I<108>"
    showText(mswkMem1120, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1121 = "CHRSELFONT06/font001/I<109>"
    showText(mswkMem1121, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1122 then
    mswkMem1122 = "CHRSELFONT16/font000/I<110>"
    showText(mswkMem1122, "CHRSELFONT16", "font000", "LEFT")
    mswkMem1123 = "CHRSELFONT16/font001/I<111>"
    showText(mswkMem1123, "CHRSELFONT16", "font001", "LEFT")
    mswkMem1124 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem1124, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1125 then
    mswkMem1125 = "CHRSELFONT06/font000/I<112>"
    showText(mswkMem1125, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1126 = "CHRSELFONT06/font001/I<36>"
    showText(mswkMem1126, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1127 then
    mswkMem1127 = "CHRSELFONT16/font000/I<113>"
    showText(mswkMem1127, "CHRSELFONT16", "font000", "LEFT")
    mswkMem1128 = "CHRSELFONT16/font001/I<114>"
    showText(mswkMem1128, "CHRSELFONT16", "font001", "LEFT")
    mswkMem1129 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem1129, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1130 then
    mswkMem1130 = "CHRSELFONT06/font000/I<115>"
    showText(mswkMem1130, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1131 = "CHRSELFONT06/font001/I<77>"
    showText(mswkMem1131, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1132 then
    mswkMem1132 = "CHRSELFONT06/font000/I<116>"
    showText(mswkMem1132, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1133 = "CHRSELFONT06/font001/I<77>"
    showText(mswkMem1133, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1134 then
    mswkMem1134 = "CHRSELFONT06/font000/I<117>"
    showText(mswkMem1134, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1135 then
    mswkMem1135 = "CHRSELFONT06/font000/I<118>"
    showText(mswkMem1135, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1136 = "CHRSELFONT06/font001/I<118>"
    showText(mswkMem1136, "CHRSELFONT06", "font001", "LEFT")
    mswkMem1137 = "CHRSELFONT06/font002/I<118>"
    showText(mswkMem1137, "CHRSELFONT06", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1138 then
    mswkMem1138 = "CHRSELFONT06/font000/I<118>"
    showText(mswkMem1138, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1139 = "CHRSELFONT06/font001/I<118>"
    showText(mswkMem1139, "CHRSELFONT06", "font001", "LEFT")
    mswkMem1140 = "CHRSELFONT06/font002/I<118>"
    showText(mswkMem1140, "CHRSELFONT06", "font002", "LEFT")
elseif be:TXTgetCallNo() == 1141 then
    mswkMem1141 = "CHRSELFONT16/font000/I<118>"
    showText(mswkMem1141, "CHRSELFONT16", "font000", "LEFT")
    mswkMem1142 = "CHRSELFONT16/font001/I<118>"
    showText(mswkMem1142, "CHRSELFONT16", "font001", "LEFT")
    mswkMem1143 = "CHRSELFONT06/font003/I<118>"
    showText(mswkMem1143, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1144 then
    mswkMem1144 = "CHRSELFONT06/font000/I<61>"
    showText(mswkMem1144, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1145 = "CHRSELFONT06/font001/I<119>"
    showText(mswkMem1145, "CHRSELFONT06", "font001", "LEFT")
    mswkMem1146 = "CHRSELFONT06/font003/I<25>"
    showText(mswkMem1146, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1147 then
    mswkMem1147 = "CHRSELFONT06/font000/I<103>"
    showText(mswkMem1147, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1148 = "CHRSELFONT06/font001/I<104>"
    showText(mswkMem1148, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1150 then
    mswkMem1150 = "CHRSELFONT06/font000/I<120>"
    showText(mswkMem1150, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1151 = "CHRSELFONT06/font001/I<121>"
    showText(mswkMem1151, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1152 then
    mswkMem1152 = "CHRSELFONT06/font000/I<122>"
    showText(mswkMem1152, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1153 = "CHRSELFONT06/font001/I<123>"
    showText(mswkMem1153, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1154 then
    mswkMem1154 = "CHRSELFONT06/font000/I<124>"
    showText(mswkMem1154, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1155 = "CHRSELFONT06/font001/I<125>"
    showText(mswkMem1155, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1156 then
    mswkMem1156 = "CHRSELFONT06/font000/I<99>"
    showText(mswkMem1156, "CHRSELFONT06", "font000", "LEFT")
    mswkMem1157 = "CHRSELFONT06/font001/I<126>"
    showText(mswkMem1157, "CHRSELFONT06", "font001", "LEFT")
elseif be:TXTgetCallNo() == 1200 then
    mswkMem1200 = "CHRSELFONT07/font010/I<88>"
    showText(mswkMem1200, "CHRSELFONT07", "font010", "LEFT")
elseif be:TXTgetCallNo() == 1201 then
    mswkMem1201 = "CHRSELFONT07/font010/I<89>"
    showText(mswkMem1201, "CHRSELFONT07", "font010", "LEFT")
elseif be:TXTgetCallNo() == 1202 then
    mswkMem1202 = "CHRSELFONT07/font010/I<127>"
    showText(mswkMem1202, "CHRSELFONT07", "font010", "LEFT")
elseif be:TXTgetCallNo() == 1203 then
    mswkMem1203 = "CHRSELFONT07/font010/I<128>"
    showText(mswkMem1203, "CHRSELFONT07", "font010", "LEFT")
elseif be:TXTgetCallNo() == 1204 then
    mswkMem1204 = "CHRSELFONT07/font010/I<129>"
    showText(mswkMem1204, "CHRSELFONT07", "font010", "LEFT")
elseif be:TXTgetCallNo() == 1205 then
    mswkMem1205 = "CHRSELFONT07/font010/I<130>"
    showText(mswkMem1205, "CHRSELFONT07", "font010", "LEFT")
elseif be:TXTgetCallNo() == 1300 then
    mswkMem1300 = "CHRSELFONT06/font000/I<131>"
    showText(mswkMem1300, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1301 then
    mswkMem1301 = "CHRSELFONT06/font000/I<132>"
    showText(mswkMem1301, "CHRSELFONT06", "font000", "LEFT")
elseif be:TXTgetCallNo() == 1302 then
    mswkMem1302 = "CHRSELFONT16/font000/I<133>"
    showText(mswkMem1302, "CHRSELFONT16", "font000", "LEFT")
    mswkMem1303 = "CHRSELFONT06/font003/I<29>"
    showText(mswkMem1303, "CHRSELFONT06", "font003", "LEFT")
elseif be:TXTgetCallNo() == 1304 then
    mswkMem1304 = "CHRSELFONT07/font011/I<134>"
    showText(mswkMem1304, "CHRSELFONT07", "font011", "LEFT")
elseif be:TXTgetCallNo() == 11000 then
    mswkMem11000 = "CHRSELFONT06/font100/I<72>"
    showText(mswkMem11000, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11001 = "CHRSELFONT06/font101/I<73>"
    showText(mswkMem11001, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11002 then
    mswkMem11002 = "CHRSELFONT16/font100/I<74>"
    showText(mswkMem11002, "CHRSELFONT16", "font100", "LEFT")
    mswkMem11003 = "CHRSELFONT16/font101/I<75>"
    showText(mswkMem11003, "CHRSELFONT16", "font101", "LEFT")
    mswkMem11004 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem11004, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11005 then
    mswkMem11005 = "CHRSELFONT06/font100/I<76>"
    showText(mswkMem11005, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11006 = "CHRSELFONT06/font101/I<77>"
    showText(mswkMem11006, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11007 then
    mswkMem11007 = "CHRSELFONT06/font100/I<78>"
    showText(mswkMem11007, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11008 = "CHRSELFONT06/font101/I<79>"
    showText(mswkMem11008, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11009 then
    mswkMem11009 = "CHRSELFONT06/font100/I<80>"
    showText(mswkMem11009, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11010 = "CHRSELFONT06/font101/I<81>"
    showText(mswkMem11010, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11012 then
    mswkMem11012 = "CHRSELFONT16/font100/I<82>"
    showText(mswkMem11012, "CHRSELFONT16", "font100", "LEFT")
    mswkMem11013 = "CHRSELFONT16/font101/I<83>"
    showText(mswkMem11013, "CHRSELFONT16", "font101", "LEFT")
    mswkMem11014 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem11014, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11015 then
    mswkMem11015 = "CHRSELFONT06/font100/I<84>"
    showText(mswkMem11015, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11016 = "CHRSELFONT06/font101/I<79>"
    showText(mswkMem11016, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11017 then
    mswkMem11017 = "CHRSELFONT06/font100/I<85>"
    showText(mswkMem11017, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11018 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem11018, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11019 then
    mswkMem11019 = "CHRSELFONT06/font100/I<86>"
    showText(mswkMem11019, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11020 = "CHRSELFONT06/font101/I<77>"
    showText(mswkMem11020, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11021 then
    mswkMem11021 = "CHRSELFONT06/font100/I<87>"
    showText(mswkMem11021, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11022 = "CHRSELFONT06/font101/I<79>"
    showText(mswkMem11022, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11050 then
    mswkMem11050 = "CHRSELFONT07/font100/I<88>"
    showText(mswkMem11050, "CHRSELFONT07", "font100", "LEFT")
    mswkMem11051 = "CHRSELFONT07/font101/I<89>"
    showText(mswkMem11051, "CHRSELFONT07", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11100 then
    mswkMem11100 = "CHRSELFONT06/font100/I<90>"
    showText(mswkMem11100, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11101 = "CHRSELFONT06/font101/I<91>"
    showText(mswkMem11101, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11102 then
    mswkMem11102 = "CHRSELFONT06/font100/I<92>"
    showText(mswkMem11102, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11103 = "CHRSELFONT06/font101/I<91>"
    showText(mswkMem11103, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11104 then
    mswkMem11104 = "CHRSELFONT06/font100/I<93>"
    showText(mswkMem11104, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11105 = "CHRSELFONT06/font101/I<94>"
    showText(mswkMem11105, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11106 then
    mswkMem11106 = "CHRSELFONT06/font100/I<95>"
    showText(mswkMem11106, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11107 = "CHRSELFONT06/font101/I<135>"
    showText(mswkMem11107, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11108 then
    mswkMem11108 = "CHRSELFONT06/font100/I<97>"
    showText(mswkMem11108, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11109 = "CHRSELFONT06/font101/I<98>"
    showText(mswkMem11109, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11110 then
    mswkMem11110 = "CHRSELFONT06/font100/I<99>"
    showText(mswkMem11110, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11111 = "CHRSELFONT06/font101/I<100>"
    showText(mswkMem11111, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11112 then
    mswkMem11112 = "CHRSELFONT06/font100/I<101>"
    showText(mswkMem11112, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11113 = "CHRSELFONT06/font101/I<102>"
    showText(mswkMem11113, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11114 then
    mswkMem11114 = "CHRSELFONT06/font100/I<103>"
    showText(mswkMem11114, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11115 = "CHRSELFONT06/font101/I<104>"
    showText(mswkMem11115, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11117 then
    mswkMem11117 = "CHRSELFONT06/font100/I<105>"
    showText(mswkMem11117, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11118 = "CHRSELFONT06/font101/I<106>"
    showText(mswkMem11118, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11119 then
    mswkMem11119 = "CHRSELFONT06/font101/I<107>"
    showText(mswkMem11119, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11120 then
    mswkMem11120 = "CHRSELFONT06/font100/I<108>"
    showText(mswkMem11120, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11121 = "CHRSELFONT06/font101/I<109>"
    showText(mswkMem11121, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11122 then
    mswkMem11122 = "CHRSELFONT16/font100/I<110>"
    showText(mswkMem11122, "CHRSELFONT16", "font100", "LEFT")
    mswkMem11123 = "CHRSELFONT16/font101/I<111>"
    showText(mswkMem11123, "CHRSELFONT16", "font101", "LEFT")
    mswkMem11124 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem11124, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11125 then
    mswkMem11125 = "CHRSELFONT06/font100/I<112>"
    showText(mswkMem11125, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11126 = "CHRSELFONT06/font101/I<36>"
    showText(mswkMem11126, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11127 then
    mswkMem11127 = "CHRSELFONT16/font100/I<113>"
    showText(mswkMem11127, "CHRSELFONT16", "font100", "LEFT")
    mswkMem11128 = "CHRSELFONT16/font101/I<114>"
    showText(mswkMem11128, "CHRSELFONT16", "font101", "LEFT")
    mswkMem11129 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem11129, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11130 then
    mswkMem11130 = "CHRSELFONT06/font100/I<115>"
    showText(mswkMem11130, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11131 = "CHRSELFONT06/font101/I<77>"
    showText(mswkMem11131, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11132 then
    mswkMem11132 = "CHRSELFONT06/font100/I<116>"
    showText(mswkMem11132, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11133 = "CHRSELFONT06/font101/I<77>"
    showText(mswkMem11133, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11134 then
    mswkMem11134 = "CHRSELFONT06/font100/I<117>"
    showText(mswkMem11134, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 11135 then
    mswkMem11135 = "CHRSELFONT06/font100/I<118>"
    showText(mswkMem11135, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11136 = "CHRSELFONT06/font101/I<118>"
    showText(mswkMem11136, "CHRSELFONT06", "font101", "LEFT")
    mswkMem11137 = "CHRSELFONT06/font102/I<118>"
    showText(mswkMem11137, "CHRSELFONT06", "font102", "LEFT")
elseif be:TXTgetCallNo() == 11138 then
    mswkMem11138 = "CHRSELFONT06/font100/I<118>"
    showText(mswkMem11138, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11139 = "CHRSELFONT06/font101/I<118>"
    showText(mswkMem11139, "CHRSELFONT06", "font101", "LEFT")
    mswkMem11140 = "CHRSELFONT06/font102/I<118>"
    showText(mswkMem11140, "CHRSELFONT06", "font102", "LEFT")
elseif be:TXTgetCallNo() == 11141 then
    mswkMem11141 = "CHRSELFONT16/font100/I<118>"
    showText(mswkMem11141, "CHRSELFONT16", "font100", "LEFT")
    mswkMem11142 = "CHRSELFONT16/font101/I<118>"
    showText(mswkMem11142, "CHRSELFONT16", "font101", "LEFT")
    mswkMem11143 = "CHRSELFONT06/font103/I<118>"
    showText(mswkMem11143, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11144 then
    mswkMem11144 = "CHRSELFONT06/font100/I<61>"
    showText(mswkMem11144, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11145 = "CHRSELFONT06/font101/I<119>"
    showText(mswkMem11145, "CHRSELFONT06", "font101", "LEFT")
    mswkMem11146 = "CHRSELFONT06/font103/I<25>"
    showText(mswkMem11146, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11147 then
    mswkMem11147 = "CHRSELFONT06/font100/I<103>"
    showText(mswkMem11147, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11148 = "CHRSELFONT06/font101/I<104>"
    showText(mswkMem11148, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11150 then
    mswkMem11150 = "CHRSELFONT06/font100/I<120>"
    showText(mswkMem11150, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11151 = "CHRSELFONT06/font101/I<121>"
    showText(mswkMem11151, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11152 then
    mswkMem11152 = "CHRSELFONT06/font100/I<122>"
    showText(mswkMem11152, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11153 = "CHRSELFONT06/font101/I<123>"
    showText(mswkMem11153, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11154 then
    mswkMem11154 = "CHRSELFONT06/font100/I<124>"
    showText(mswkMem11154, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11155 = "CHRSELFONT06/font101/I<125>"
    showText(mswkMem11155, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11156 then
    mswkMem11156 = "CHRSELFONT06/font100/I<99>"
    showText(mswkMem11156, "CHRSELFONT06", "font100", "LEFT")
    mswkMem11157 = "CHRSELFONT06/font101/I<126>"
    showText(mswkMem11157, "CHRSELFONT06", "font101", "LEFT")
elseif be:TXTgetCallNo() == 11200 then
    mswkMem11200 = "CHRSELFONT07/font110/I<88>"
    showText(mswkMem11200, "CHRSELFONT07", "font110", "LEFT")
elseif be:TXTgetCallNo() == 11201 then
    mswkMem11201 = "CHRSELFONT07/font110/I<89>"
    showText(mswkMem11201, "CHRSELFONT07", "font110", "LEFT")
elseif be:TXTgetCallNo() == 11202 then
    mswkMem11202 = "CHRSELFONT07/font110/I<127>"
    showText(mswkMem11202, "CHRSELFONT07", "font110", "LEFT")
elseif be:TXTgetCallNo() == 11203 then
    mswkMem11203 = "CHRSELFONT07/font110/I<128>"
    showText(mswkMem11203, "CHRSELFONT07", "font110", "LEFT")
elseif be:TXTgetCallNo() == 11204 then
    mswkMem11204 = "CHRSELFONT07/font110/I<129>"
    showText(mswkMem11204, "CHRSELFONT07", "font110", "LEFT")
elseif be:TXTgetCallNo() == 11205 then
    mswkMem11205 = "CHRSELFONT07/font110/I<130>"
    showText(mswkMem11205, "CHRSELFONT07", "font110", "LEFT")
elseif be:TXTgetCallNo() == 11300 then
    mswkMem11300 = "CHRSELFONT06/font100/I<131>"
    showText(mswkMem11300, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 11301 then
    mswkMem11301 = "CHRSELFONT06/font100/I<132>"
    showText(mswkMem11301, "CHRSELFONT06", "font100", "LEFT")
elseif be:TXTgetCallNo() == 11302 then
    mswkMem11302 = "CHRSELFONT16/font100/I<133>"
    showText(mswkMem11302, "CHRSELFONT16", "font100", "LEFT")
    mswkMem11303 = "CHRSELFONT06/font103/I<29>"
    showText(mswkMem11303, "CHRSELFONT06", "font103", "LEFT")
elseif be:TXTgetCallNo() == 11304 then
    mswkMem11304 = "CHRSELFONT07/font111/I<134>"
    showText(mswkMem11304, "CHRSELFONT07", "font111", "LEFT")
elseif be:TXTgetCallNo() == 21000 then
    mswkMem21000 = "CHRSELFONT06/font200/I<72>"
    showText(mswkMem21000, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21001 = "CHRSELFONT06/font201/I<73>"
    showText(mswkMem21001, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21002 then
    mswkMem21002 = "CHRSELFONT16/font200/I<74>"
    showText(mswkMem21002, "CHRSELFONT16", "font200", "LEFT")
    mswkMem21003 = "CHRSELFONT16/font201/I<75>"
    showText(mswkMem21003, "CHRSELFONT16", "font201", "LEFT")
    mswkMem21004 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem21004, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21005 then
    mswkMem21005 = "CHRSELFONT06/font200/I<76>"
    showText(mswkMem21005, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21006 = "CHRSELFONT06/font201/I<77>"
    showText(mswkMem21006, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21007 then
    mswkMem21007 = "CHRSELFONT06/font200/I<78>"
    showText(mswkMem21007, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21008 = "CHRSELFONT06/font201/I<79>"
    showText(mswkMem21008, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21009 then
    mswkMem21009 = "CHRSELFONT06/font200/I<80>"
    showText(mswkMem21009, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21010 = "CHRSELFONT06/font201/I<81>"
    showText(mswkMem21010, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21012 then
    mswkMem21012 = "CHRSELFONT16/font200/I<82>"
    showText(mswkMem21012, "CHRSELFONT16", "font200", "LEFT")
    mswkMem21013 = "CHRSELFONT16/font201/I<83>"
    showText(mswkMem21013, "CHRSELFONT16", "font201", "LEFT")
    mswkMem21014 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem21014, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21015 then
    mswkMem21015 = "CHRSELFONT06/font200/I<84>"
    showText(mswkMem21015, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21016 = "CHRSELFONT06/font201/I<79>"
    showText(mswkMem21016, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21017 then
    mswkMem21017 = "CHRSELFONT06/font200/I<85>"
    showText(mswkMem21017, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21018 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem21018, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21019 then
    mswkMem21019 = "CHRSELFONT06/font200/I<86>"
    showText(mswkMem21019, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21020 = "CHRSELFONT06/font201/I<77>"
    showText(mswkMem21020, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21021 then
    mswkMem21021 = "CHRSELFONT06/font200/I<87>"
    showText(mswkMem21021, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21022 = "CHRSELFONT06/font201/I<79>"
    showText(mswkMem21022, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21050 then
    mswkMem21050 = "CHRSELFONT07/font200/I<88>"
    showText(mswkMem21050, "CHRSELFONT07", "font200", "LEFT")
    mswkMem21051 = "CHRSELFONT07/font201/I<89>"
    showText(mswkMem21051, "CHRSELFONT07", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21100 then
    mswkMem21100 = "CHRSELFONT06/font200/I<90>"
    showText(mswkMem21100, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21101 = "CHRSELFONT06/font201/I<91>"
    showText(mswkMem21101, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21102 then
    mswkMem21102 = "CHRSELFONT06/font200/I<92>"
    showText(mswkMem21102, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21103 = "CHRSELFONT06/font201/I<91>"
    showText(mswkMem21103, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21104 then
    mswkMem21104 = "CHRSELFONT06/font200/I<93>"
    showText(mswkMem21104, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21105 = "CHRSELFONT06/font201/I<94>"
    showText(mswkMem21105, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21106 then
    mswkMem21106 = "CHRSELFONT06/font200/I<95>"
    showText(mswkMem21106, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21107 = "CHRSELFONT06/font201/I<135>"
    showText(mswkMem21107, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21108 then
    mswkMem21108 = "CHRSELFONT06/font200/I<97>"
    showText(mswkMem21108, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21109 = "CHRSELFONT06/font201/I<98>"
    showText(mswkMem21109, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21110 then
    mswkMem21110 = "CHRSELFONT06/font200/I<99>"
    showText(mswkMem21110, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21111 = "CHRSELFONT06/font201/I<100>"
    showText(mswkMem21111, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21112 then
    mswkMem21112 = "CHRSELFONT06/font200/I<101>"
    showText(mswkMem21112, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21113 = "CHRSELFONT06/font201/I<102>"
    showText(mswkMem21113, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21114 then
    mswkMem21114 = "CHRSELFONT06/font200/I<103>"
    showText(mswkMem21114, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21115 = "CHRSELFONT06/font201/I<104>"
    showText(mswkMem21115, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21117 then
    mswkMem21117 = "CHRSELFONT06/font200/I<105>"
    showText(mswkMem21117, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21118 = "CHRSELFONT06/font201/I<106>"
    showText(mswkMem21118, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21119 then
    mswkMem21119 = "CHRSELFONT06/font201/I<107>"
    showText(mswkMem21119, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21120 then
    mswkMem21120 = "CHRSELFONT06/font200/I<108>"
    showText(mswkMem21120, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21121 = "CHRSELFONT06/font201/I<109>"
    showText(mswkMem21121, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21122 then
    mswkMem21122 = "CHRSELFONT16/font200/I<110>"
    showText(mswkMem21122, "CHRSELFONT16", "font200", "LEFT")
    mswkMem21123 = "CHRSELFONT16/font201/I<111>"
    showText(mswkMem21123, "CHRSELFONT16", "font201", "LEFT")
    mswkMem21124 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem21124, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21125 then
    mswkMem21125 = "CHRSELFONT06/font200/I<112>"
    showText(mswkMem21125, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21126 = "CHRSELFONT06/font201/I<36>"
    showText(mswkMem21126, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21127 then
    mswkMem21127 = "CHRSELFONT16/font200/I<113>"
    showText(mswkMem21127, "CHRSELFONT16", "font200", "LEFT")
    mswkMem21128 = "CHRSELFONT16/font201/I<114>"
    showText(mswkMem21128, "CHRSELFONT16", "font201", "LEFT")
    mswkMem21129 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem21129, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21130 then
    mswkMem21130 = "CHRSELFONT06/font200/I<115>"
    showText(mswkMem21130, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21131 = "CHRSELFONT06/font201/I<77>"
    showText(mswkMem21131, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21132 then
    mswkMem21132 = "CHRSELFONT06/font200/I<116>"
    showText(mswkMem21132, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21133 = "CHRSELFONT06/font201/I<77>"
    showText(mswkMem21133, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21134 then
    mswkMem21134 = "CHRSELFONT06/font200/I<117>"
    showText(mswkMem21134, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 21135 then
    mswkMem21135 = "CHRSELFONT06/font200/I<118>"
    showText(mswkMem21135, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21136 = "CHRSELFONT06/font201/I<118>"
    showText(mswkMem21136, "CHRSELFONT06", "font201", "LEFT")
    mswkMem21137 = "CHRSELFONT06/font202/I<118>"
    showText(mswkMem21137, "CHRSELFONT06", "font202", "LEFT")
elseif be:TXTgetCallNo() == 21138 then
    mswkMem21138 = "CHRSELFONT06/font200/I<118>"
    showText(mswkMem21138, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21139 = "CHRSELFONT06/font201/I<118>"
    showText(mswkMem21139, "CHRSELFONT06", "font201", "LEFT")
    mswkMem21140 = "CHRSELFONT06/font202/I<118>"
    showText(mswkMem21140, "CHRSELFONT06", "font202", "LEFT")
elseif be:TXTgetCallNo() == 21141 then
    mswkMem21141 = "CHRSELFONT16/font200/I<118>"
    showText(mswkMem21141, "CHRSELFONT16", "font200", "LEFT")
    mswkMem21142 = "CHRSELFONT16/font201/I<118>"
    showText(mswkMem21142, "CHRSELFONT16", "font201", "LEFT")
    mswkMem21143 = "CHRSELFONT06/font203/I<118>"
    showText(mswkMem21143, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21144 then
    mswkMem21144 = "CHRSELFONT06/font200/I<61>"
    showText(mswkMem21144, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21145 = "CHRSELFONT06/font201/I<119>"
    showText(mswkMem21145, "CHRSELFONT06", "font201", "LEFT")
    mswkMem21146 = "CHRSELFONT06/font203/I<25>"
    showText(mswkMem21146, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21147 then
    mswkMem21147 = "CHRSELFONT06/font200/I<103>"
    showText(mswkMem21147, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21148 = "CHRSELFONT06/font201/I<104>"
    showText(mswkMem21148, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21150 then
    mswkMem21150 = "CHRSELFONT06/font200/I<120>"
    showText(mswkMem21150, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21151 = "CHRSELFONT06/font201/I<121>"
    showText(mswkMem21151, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21152 then
    mswkMem21152 = "CHRSELFONT06/font200/I<122>"
    showText(mswkMem21152, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21153 = "CHRSELFONT06/font201/I<123>"
    showText(mswkMem21153, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21154 then
    mswkMem21154 = "CHRSELFONT06/font200/I<124>"
    showText(mswkMem21154, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21155 = "CHRSELFONT06/font201/I<125>"
    showText(mswkMem21155, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21156 then
    mswkMem21156 = "CHRSELFONT06/font200/I<99>"
    showText(mswkMem21156, "CHRSELFONT06", "font200", "LEFT")
    mswkMem21157 = "CHRSELFONT06/font201/I<126>"
    showText(mswkMem21157, "CHRSELFONT06", "font201", "LEFT")
elseif be:TXTgetCallNo() == 21200 then
    mswkMem21200 = "CHRSELFONT07/font210/I<88>"
    showText(mswkMem21200, "CHRSELFONT07", "font210", "LEFT")
elseif be:TXTgetCallNo() == 21201 then
    mswkMem21201 = "CHRSELFONT07/font210/I<89>"
    showText(mswkMem21201, "CHRSELFONT07", "font210", "LEFT")
elseif be:TXTgetCallNo() == 21202 then
    mswkMem21202 = "CHRSELFONT07/font210/I<127>"
    showText(mswkMem21202, "CHRSELFONT07", "font210", "LEFT")
elseif be:TXTgetCallNo() == 21203 then
    mswkMem21203 = "CHRSELFONT07/font210/I<128>"
    showText(mswkMem21203, "CHRSELFONT07", "font210", "LEFT")
elseif be:TXTgetCallNo() == 21204 then
    mswkMem21204 = "CHRSELFONT07/font210/I<129>"
    showText(mswkMem21204, "CHRSELFONT07", "font210", "LEFT")
elseif be:TXTgetCallNo() == 21205 then
    mswkMem21205 = "CHRSELFONT07/font210/I<130>"
    showText(mswkMem21205, "CHRSELFONT07", "font210", "LEFT")
elseif be:TXTgetCallNo() == 21300 then
    mswkMem21300 = "CHRSELFONT06/font200/I<131>"
    showText(mswkMem21300, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 21301 then
    mswkMem21301 = "CHRSELFONT06/font200/I<132>"
    showText(mswkMem21301, "CHRSELFONT06", "font200", "LEFT")
elseif be:TXTgetCallNo() == 21302 then
    mswkMem21302 = "CHRSELFONT16/font200/I<133>"
    showText(mswkMem21302, "CHRSELFONT16", "font200", "LEFT")
    mswkMem21303 = "CHRSELFONT06/font203/I<29>"
    showText(mswkMem21303, "CHRSELFONT06", "font203", "LEFT")
elseif be:TXTgetCallNo() == 21304 then
    mswkMem21304 = "CHRSELFONT07/font211/I<134>"
    showText(mswkMem21304, "CHRSELFONT07", "font211", "LEFT")
elseif be:TXTgetCallNo() == 31000 then
    mswkMem31000 = "CHRSELFONT06/font300/I<72>"
    showText(mswkMem31000, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31001 = "CHRSELFONT06/font301/I<73>"
    showText(mswkMem31001, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31002 then
    mswkMem31002 = "CHRSELFONT16/font300/I<74>"
    showText(mswkMem31002, "CHRSELFONT16", "font300", "LEFT")
    mswkMem31003 = "CHRSELFONT16/font301/I<75>"
    showText(mswkMem31003, "CHRSELFONT16", "font301", "LEFT")
    mswkMem31004 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem31004, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31005 then
    mswkMem31005 = "CHRSELFONT06/font300/I<76>"
    showText(mswkMem31005, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31006 = "CHRSELFONT06/font301/I<77>"
    showText(mswkMem31006, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31007 then
    mswkMem31007 = "CHRSELFONT06/font300/I<78>"
    showText(mswkMem31007, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31008 = "CHRSELFONT06/font301/I<79>"
    showText(mswkMem31008, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31009 then
    mswkMem31009 = "CHRSELFONT06/font300/I<80>"
    showText(mswkMem31009, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31010 = "CHRSELFONT06/font301/I<81>"
    showText(mswkMem31010, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31012 then
    mswkMem31012 = "CHRSELFONT16/font300/I<82>"
    showText(mswkMem31012, "CHRSELFONT16", "font300", "LEFT")
    mswkMem31013 = "CHRSELFONT16/font301/I<83>"
    showText(mswkMem31013, "CHRSELFONT16", "font301", "LEFT")
    mswkMem31014 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem31014, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31015 then
    mswkMem31015 = "CHRSELFONT06/font300/I<84>"
    showText(mswkMem31015, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31016 = "CHRSELFONT06/font301/I<79>"
    showText(mswkMem31016, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31017 then
    mswkMem31017 = "CHRSELFONT06/font300/I<85>"
    showText(mswkMem31017, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31018 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem31018, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31019 then
    mswkMem31019 = "CHRSELFONT06/font300/I<86>"
    showText(mswkMem31019, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31020 = "CHRSELFONT06/font301/I<77>"
    showText(mswkMem31020, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31021 then
    mswkMem31021 = "CHRSELFONT06/font300/I<87>"
    showText(mswkMem31021, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31022 = "CHRSELFONT06/font301/I<79>"
    showText(mswkMem31022, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31050 then
    mswkMem31050 = "CHRSELFONT07/font300/I<88>"
    showText(mswkMem31050, "CHRSELFONT07", "font300", "LEFT")
    mswkMem31051 = "CHRSELFONT07/font301/I<89>"
    showText(mswkMem31051, "CHRSELFONT07", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31100 then
    mswkMem31100 = "CHRSELFONT06/font300/I<90>"
    showText(mswkMem31100, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31101 = "CHRSELFONT06/font301/I<91>"
    showText(mswkMem31101, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31102 then
    mswkMem31102 = "CHRSELFONT06/font300/I<92>"
    showText(mswkMem31102, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31103 = "CHRSELFONT06/font301/I<91>"
    showText(mswkMem31103, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31104 then
    mswkMem31104 = "CHRSELFONT06/font300/I<93>"
    showText(mswkMem31104, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31105 = "CHRSELFONT06/font301/I<94>"
    showText(mswkMem31105, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31106 then
    mswkMem31106 = "CHRSELFONT06/font300/I<95>"
    showText(mswkMem31106, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31107 = "CHRSELFONT06/font301/I<135>"
    showText(mswkMem31107, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31108 then
    mswkMem31108 = "CHRSELFONT06/font300/I<97>"
    showText(mswkMem31108, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31109 = "CHRSELFONT06/font301/I<98>"
    showText(mswkMem31109, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31110 then
    mswkMem31110 = "CHRSELFONT06/font300/I<99>"
    showText(mswkMem31110, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31111 = "CHRSELFONT06/font301/I<100>"
    showText(mswkMem31111, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31112 then
    mswkMem31112 = "CHRSELFONT06/font300/I<101>"
    showText(mswkMem31112, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31113 = "CHRSELFONT06/font301/I<102>"
    showText(mswkMem31113, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31114 then
    mswkMem31114 = "CHRSELFONT06/font300/I<103>"
    showText(mswkMem31114, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31115 = "CHRSELFONT06/font301/I<104>"
    showText(mswkMem31115, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31117 then
    mswkMem31117 = "CHRSELFONT06/font300/I<105>"
    showText(mswkMem31117, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31118 = "CHRSELFONT06/font301/I<106>"
    showText(mswkMem31118, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31119 then
    mswkMem31119 = "CHRSELFONT06/font301/I<107>"
    showText(mswkMem31119, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31120 then
    mswkMem31120 = "CHRSELFONT06/font300/I<108>"
    showText(mswkMem31120, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31121 = "CHRSELFONT06/font301/I<109>"
    showText(mswkMem31121, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31122 then
    mswkMem31122 = "CHRSELFONT16/font300/I<110>"
    showText(mswkMem31122, "CHRSELFONT16", "font300", "LEFT")
    mswkMem31123 = "CHRSELFONT16/font301/I<111>"
    showText(mswkMem31123, "CHRSELFONT16", "font301", "LEFT")
    mswkMem31124 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem31124, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31125 then
    mswkMem31125 = "CHRSELFONT06/font300/I<112>"
    showText(mswkMem31125, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31126 = "CHRSELFONT06/font301/I<36>"
    showText(mswkMem31126, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31127 then
    mswkMem31127 = "CHRSELFONT16/font300/I<113>"
    showText(mswkMem31127, "CHRSELFONT16", "font300", "LEFT")
    mswkMem31128 = "CHRSELFONT16/font301/I<114>"
    showText(mswkMem31128, "CHRSELFONT16", "font301", "LEFT")
    mswkMem31129 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem31129, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31130 then
    mswkMem31130 = "CHRSELFONT06/font300/I<115>"
    showText(mswkMem31130, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31131 = "CHRSELFONT06/font301/I<77>"
    showText(mswkMem31131, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31132 then
    mswkMem31132 = "CHRSELFONT06/font300/I<116>"
    showText(mswkMem31132, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31133 = "CHRSELFONT06/font301/I<77>"
    showText(mswkMem31133, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31134 then
    mswkMem31134 = "CHRSELFONT06/font300/I<117>"
    showText(mswkMem31134, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 31135 then
    mswkMem31135 = "CHRSELFONT06/font300/I<118>"
    showText(mswkMem31135, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31136 = "CHRSELFONT06/font301/I<118>"
    showText(mswkMem31136, "CHRSELFONT06", "font301", "LEFT")
    mswkMem31137 = "CHRSELFONT06/font302/I<118>"
    showText(mswkMem31137, "CHRSELFONT06", "font302", "LEFT")
elseif be:TXTgetCallNo() == 31138 then
    mswkMem31138 = "CHRSELFONT06/font300/I<118>"
    showText(mswkMem31138, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31139 = "CHRSELFONT06/font301/I<118>"
    showText(mswkMem31139, "CHRSELFONT06", "font301", "LEFT")
    mswkMem31140 = "CHRSELFONT06/font302/I<118>"
    showText(mswkMem31140, "CHRSELFONT06", "font302", "LEFT")
elseif be:TXTgetCallNo() == 31141 then
    mswkMem31141 = "CHRSELFONT16/font300/I<118>"
    showText(mswkMem31141, "CHRSELFONT16", "font300", "LEFT")
    mswkMem31142 = "CHRSELFONT16/font301/I<118>"
    showText(mswkMem31142, "CHRSELFONT16", "font301", "LEFT")
    mswkMem31143 = "CHRSELFONT06/font303/I<118>"
    showText(mswkMem31143, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31144 then
    mswkMem31144 = "CHRSELFONT06/font300/I<61>"
    showText(mswkMem31144, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31145 = "CHRSELFONT06/font301/I<119>"
    showText(mswkMem31145, "CHRSELFONT06", "font301", "LEFT")
    mswkMem31146 = "CHRSELFONT06/font303/I<25>"
    showText(mswkMem31146, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31147 then
    mswkMem31147 = "CHRSELFONT06/font300/I<103>"
    showText(mswkMem31147, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31148 = "CHRSELFONT06/font301/I<104>"
    showText(mswkMem31148, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31150 then
    mswkMem31150 = "CHRSELFONT06/font300/I<120>"
    showText(mswkMem31150, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31151 = "CHRSELFONT06/font301/I<121>"
    showText(mswkMem31151, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31152 then
    mswkMem31152 = "CHRSELFONT06/font300/I<122>"
    showText(mswkMem31152, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31153 = "CHRSELFONT06/font301/I<123>"
    showText(mswkMem31153, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31154 then
    mswkMem31154 = "CHRSELFONT06/font300/I<124>"
    showText(mswkMem31154, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31155 = "CHRSELFONT06/font301/I<125>"
    showText(mswkMem31155, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31156 then
    mswkMem31156 = "CHRSELFONT06/font300/I<99>"
    showText(mswkMem31156, "CHRSELFONT06", "font300", "LEFT")
    mswkMem31157 = "CHRSELFONT06/font301/I<126>"
    showText(mswkMem31157, "CHRSELFONT06", "font301", "LEFT")
elseif be:TXTgetCallNo() == 31200 then
    mswkMem31200 = "CHRSELFONT07/font310/I<88>"
    showText(mswkMem31200, "CHRSELFONT07", "font310", "LEFT")
elseif be:TXTgetCallNo() == 31201 then
    mswkMem31201 = "CHRSELFONT07/font310/I<89>"
    showText(mswkMem31201, "CHRSELFONT07", "font310", "LEFT")
elseif be:TXTgetCallNo() == 31202 then
    mswkMem31202 = "CHRSELFONT07/font310/I<127>"
    showText(mswkMem31202, "CHRSELFONT07", "font310", "LEFT")
elseif be:TXTgetCallNo() == 31203 then
    mswkMem31203 = "CHRSELFONT07/font310/I<128>"
    showText(mswkMem31203, "CHRSELFONT07", "font310", "LEFT")
elseif be:TXTgetCallNo() == 31204 then
    mswkMem31204 = "CHRSELFONT07/font310/I<129>"
    showText(mswkMem31204, "CHRSELFONT07", "font310", "LEFT")
elseif be:TXTgetCallNo() == 31205 then
    mswkMem31205 = "CHRSELFONT07/font310/I<130>"
    showText(mswkMem31205, "CHRSELFONT07", "font310", "LEFT")
elseif be:TXTgetCallNo() == 31300 then
    mswkMem31300 = "CHRSELFONT06/font300/I<131>"
    showText(mswkMem31300, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 31301 then
    mswkMem31301 = "CHRSELFONT06/font300/I<132>"
    showText(mswkMem31301, "CHRSELFONT06", "font300", "LEFT")
elseif be:TXTgetCallNo() == 31302 then
    mswkMem31302 = "CHRSELFONT16/font300/I<133>"
    showText(mswkMem31302, "CHRSELFONT16", "font300", "LEFT")
    mswkMem31303 = "CHRSELFONT06/font303/I<29>"
    showText(mswkMem31303, "CHRSELFONT06", "font303", "LEFT")
elseif be:TXTgetCallNo() == 31304 then
    mswkMem31304 = "CHRSELFONT07/font311/I<134>"
    showText(mswkMem31304, "CHRSELFONT07", "font311", "LEFT")
elseif be:TXTgetCallNo() == 91000 then
    mswkMem91000 = "TALKFONT01/font00/I<136>"
    showText(mswkMem91000, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 91001 then
    mswkMem91001 = "TALKFONT01/font01/I<137>"
    showText(mswkMem91001, "TALKFONT01", "font01", "LEFT")
    mswkMem91002 = "TALKFONT01/font02/I<138>"
    showText(mswkMem91002, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91010 then
    mswkMem91010 = "TALKFONT01/font02/I<139>"
    showText(mswkMem91010, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91011 then
    mswkMem91011 = "TALKFONT01/font01/I<137>"
    showText(mswkMem91011, "TALKFONT01", "font01", "LEFT")
    mswkMem91012 = "TALKFONT01/font02/I<140>"
    showText(mswkMem91012, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91020 then
    mswkMem91020 = "TALKFONT01/font02/I<141>"
    showText(mswkMem91020, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91021 then
    mswkMem91021 = "TALKFONT01/font01/I<137>"
    showText(mswkMem91021, "TALKFONT01", "font01", "LEFT")
    mswkMem91022 = "TALKFONT01/font02/I<140>"
    showText(mswkMem91022, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91030 then
    mswkMem91030 = "TALKFONT01/font02/I<142>"
    showText(mswkMem91030, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91031 then
    mswkMem91031 = "TALKFONT01/font01/I<82>"
    showText(mswkMem91031, "TALKFONT01", "font01", "LEFT")
    mswkMem91032 = "TALKFONT01/font02/I<83>"
    showText(mswkMem91032, "TALKFONT01", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91100 then
    mswkMem91100 = "TALKFONT01/font00/I<143>"
    showText(mswkMem91100, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 91200 then
    mswkMem91200 = "TALKFONT01/font00/I<144>"
    showText(mswkMem91200, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 91201 then
    mswkMem91201 = "TALKFONT01/font00/I<145>"
    showText(mswkMem91201, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 91202 then
    mswkMem91202 = "TALKFONT01/font00/I<146>"
    showText(mswkMem91202, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 91203 then
    mswkMem91203 = "TALKFONT01/font00/I<147>"
    showText(mswkMem91203, "TALKFONT01", "font00", "LEFT")
elseif be:TXTgetCallNo() == 91204 then
    mswkMem91204 = "TALKFONT01/font01/I<88>"
    showText(mswkMem91204, "TALKFONT01", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91205 then
    mswkMem91205 = "TALKFONT01/font01/I<89>"
    showText(mswkMem91205, "TALKFONT01", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91206 then
    mswkMem91206 = "TALKFONT01/font01/I<127>"
    showText(mswkMem91206, "TALKFONT01", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91207 then
    mswkMem91207 = "TALKFONT01/font01/I<128>"
    showText(mswkMem91207, "TALKFONT01", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91208 then
    mswkMem91208 = "TALKFONT01/font01/I<129>"
    showText(mswkMem91208, "TALKFONT01", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91209 then
    mswkMem91209 = "TALKFONT01/font01/I<130>"
    showText(mswkMem91209, "TALKFONT01", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91300 then
    mswkMem91300 = "TALKFONT06/font01/I<88>"
    showText(mswkMem91300, "TALKFONT06", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91301 then
    mswkMem91301 = "TALKFONT06/font02/I<89>"
    showText(mswkMem91301, "TALKFONT06", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91302 then
    mswkMem91302 = "TALKFONT06/font01/I<127>"
    showText(mswkMem91302, "TALKFONT06", "font01", "LEFT")
elseif be:TXTgetCallNo() == 91303 then
    mswkMem91303 = "TALKFONT06/font02/I<128>"
    showText(mswkMem91303, "TALKFONT06", "font02", "LEFT")
elseif be:TXTgetCallNo() == 91304 then
    mswkMem91304 = "TALKFONT06/font03/I<129>"
    showText(mswkMem91304, "TALKFONT06", "font03", "LEFT")
elseif be:TXTgetCallNo() == 91305 then
    mswkMem91305 = "TALKFONT06/font04/I<130>"
    showText(mswkMem91305, "TALKFONT06", "font04", "LEFT")
elseif be:TXTgetCallNo() == 91306 then
    mswkMem91306 = "TALKFONT06/font05/I<89>"
    showText(mswkMem91306, "TALKFONT06", "font05", "LEFT")
else
    be:MsgBox("error textSet", be:TXTgetCallNo())
end
