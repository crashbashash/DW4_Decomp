mswkNPC001 = "TALKFONT03/font00/I<21>"
mswkNPC026 = "TALKFONT03/font00/I<22>"
mswkNPC027 = "TALKFONT03/font00/I<23>"
mswkNPC028 = "TALKFONT03/font00/I<24>"
mswkNPC029 = "TALKFONT03/font00/I<25>"
mswkNPC030 = "TALKFONT03/font00/I<26>"
mswkNPC031 = "TALKFONT03/font00/I<27>"
if be:PLAYERgetPos() == 0 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 1 then
    funcStageIn("stay")
elseif be:PLAYERgetPos() == 2 then
    funcStageIn("trans")
end
be:sd("MODELCTRL", "n_agumon", 0, "SQ_WALKON", 18)
be:sd("MODELCTRL", "n_vmon", 0, "SQ_WALKON", 34)
be:sd("MODELCTRL", "n_girumon", 0, "SQ_WALKON", 50)
be:sd("MODELCTRL", "n_dorumon", 0, "SQ_WALKON", 62)
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
