mswkNPC025 = "TALKFONT03/font00/I<9>"
if be:PLAYERgetPos() == 0 then
    funcStageIn("stay")
end
funcPlayerStatusSet()
be:sd("SWITCHCTRL", nil, -1, "ALLON")
funcFirstLayerSet()
be:sd("MODELCTRL", "i_fadewn01", 0, "SQ_BLIN60", 5)
