void Gap__Gui__igDefaultAspect__vfunc_24(igDefaultAspect *arg0, int *arg1) {
    int temp_a2;

    temp_a2 = *arg1;
    switch (temp_a2) {
    case 0:
        ((DW4VC_100_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        return;
    case 1:
        ((DW4VC_104_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        return;
    default:
        if (arg0->_model != 0) {
            ((DW4VC_108_1 *)(((char *)(arg0) + 0)))->vX((int)(arg1));
        }
        return;
    }
}

