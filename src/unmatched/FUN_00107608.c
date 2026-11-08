typedef struct {
    char p0[340];
    int progressive_sequence;
    char p1[396 - 344];
    int picture_structure;
    int top_field_first;
    char p2[412 - 404];
    int repeat_first_field;
    char p3[420 - 416];
    int frame_center_horizontal_offset[3];
    int frame_center_vertical_offset[3];
} Ld;
unsigned int FUN_00106c88(Ld *ld, int n);

void FUN_00107608(Ld *ld) {
    int i;
    int number_of_frame_center_offsets;

    if (ld->progressive_sequence) {
        if (ld->repeat_first_field) {
            if (ld->top_field_first)
                number_of_frame_center_offsets = 3;
            else
                number_of_frame_center_offsets = 2;
        } else
            number_of_frame_center_offsets = 1;
    } else {
        if (ld->picture_structure != 3)
            number_of_frame_center_offsets = 1;
        else {
            if (ld->repeat_first_field)
                number_of_frame_center_offsets = 3;
            else
                number_of_frame_center_offsets = 2;
        }
    }

    for (i = 0; i < number_of_frame_center_offsets; i++) {
        ld->frame_center_horizontal_offset[i] = FUN_00106c88(ld, 16);
        FUN_00106c88(ld, 1);
        ld->frame_center_vertical_offset[i] = FUN_00106c88(ld, 16);
        FUN_00106c88(ld, 1);
    }
}
