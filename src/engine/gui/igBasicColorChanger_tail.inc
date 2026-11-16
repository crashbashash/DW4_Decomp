void igBasicColorChanger_SetColor(igBasicColorChanger *changer, int highlighted, int on, int disabled, const igVec4f *color) {
    int var_v1;
    igBasicColorChanger *temp_v1;
    int idx;
    var_v1 = 0;
    if (disabled != 0) {
        *(float *)&changer->_disabledColor = (float) *(float *)((char *)(color) + 0);
        *(float *)((char *)(changer) + 76) = (float) *(float *)((char *)(color) + 4);
        *(float *)((char *)(changer) + 80) = (float) *(float *)((char *)(color) + 8);
        *(float *)((char *)(changer) + 84) = (float) *(float *)((char *)(color) + 12);
        return;
    }
    if (highlighted != 0) {
        var_v1 += 1;
    }
    if (on != 0) {
        var_v1 += 2;
    }
    idx = var_v1 * 0x10;
    temp_v1 = (igBasicColorChanger *)(idx + (int)changer);
    *(float *)&temp_v1->_colors[0] = (float) *(float *)((char *)(color) + 0);
    *(float *)&temp_v1->_colors[1] = (float) *(float *)((char *)(color) + 4);
    *(float *)&temp_v1->_colors[2] = (float) *(float *)((char *)(color) + 8);
    *(float *)&temp_v1->_colors[3] = (float) *(float *)((char *)(color) + 12);
}

int Gap__Gui__igBasicColorChanger__vfunc_23(int arg0, void *arg1) {
    int i;
    if (*(unsigned char *)((char *)(arg1) + 12) == 0) {
        return arg0 + 0x48;
    }
    i = 0;
    if (*(unsigned char *)((char *)(arg1) + 13) != 0) {
        i = i + 1;
    }
    if (*(unsigned char *)((char *)(arg1) + 15) != 0) {
        i = i + 2;
    }
    return arg0 + i * 0x10 + 8;
}

