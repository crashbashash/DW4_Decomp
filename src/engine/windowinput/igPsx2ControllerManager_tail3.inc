int Gap__igPsx2ControllerManager__vfunc_25(igPsx2ControllerManager *arg0) {
    int r;
    switch (arg0->_multitap) {
    case 0: r = 2; break;
    case 0xFFFF: r = 8; break;
    default: r = 5; break;
    }
    return r;
}

void igPsx2ControllerManager_userDestruct(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 16) != 0) {
        g_igPsx2ControllerManager_initialized = 0;
    }
}

