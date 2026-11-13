void igBasicColorChanger_SetColor(igBasicColorChanger *arg0, int arg1, int arg2, int arg3, void *arg4) {
    int var_v1;
    igBasicColorChanger *temp_v1;
    int idx;
    var_v1 = 0;
    if (arg3 != 0) {
        *(float *)&arg0->_disabledColor = (float) *(float *)((char *)(arg4) + 0);
        *(float *)((char *)(arg0) + 76) = (float) *(float *)((char *)(arg4) + 4);
        *(float *)((char *)(arg0) + 80) = (float) *(float *)((char *)(arg4) + 8);
        *(float *)((char *)(arg0) + 84) = (float) *(float *)((char *)(arg4) + 12);
        return;
    }
    if (arg1 != 0) {
        var_v1 += 1;
    }
    if (arg2 != 0) {
        var_v1 += 2;
    }
    idx = var_v1 * 0x10;
    temp_v1 = (igBasicColorChanger *)(idx + (int)arg0);
    *(float *)&temp_v1->_colors[0] = (float) *(float *)((char *)(arg4) + 0);
    *(float *)&temp_v1->_colors[1] = (float) *(float *)((char *)(arg4) + 4);
    *(float *)&temp_v1->_colors[2] = (float) *(float *)((char *)(arg4) + 8);
    *(float *)&temp_v1->_colors[3] = (float) *(float *)((char *)(arg4) + 12);
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

