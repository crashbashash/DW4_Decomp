void Gap__Core__igMemoryPoolInfo__vfunc_26(int *arg0, int *arg1, int arg2, int arg3) {
    
    if (arg2 == 0) {
        arg2 = ((struct { char pad[56]; int i56; } * *)g_objectSystem)[0]->i56;
    }
    if (arg2 == 0) {
        *arg0 = g_resultFailure.v;
    } else {
        FUN_00306910(arg2, arg3, DAT_004c2230, (int **)(&arg1[2]), (char *)arg1[2], 0);
        FUN_00306910(arg2, arg3, DAT_004c2238, (int **)(&arg1[5]), (char *)arg1[5], 0);
        FUN_00306910(arg2, arg3, DAT_004c2240, (int **)(&arg1[6]), (char *)arg1[6], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2248, &arg1[7], arg1[7], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2250, &arg1[8], arg1[8], 0);
        FUN_003065f0(arg2, arg3, DAT_004c2258, &arg1[9], arg1[9], 0);
        FUN_00306910(arg2, arg3, DAT_004c2260, (int **)(&arg1[10]), (char *)arg1[10], 0);
        FUN_00306910(arg2, arg3, DAT_004c2268, (int **)(&arg1[11]), (char *)arg1[11], 0);
        FUN_00306910(arg2, arg3, DAT_004c2270, (int **)(&arg1[12]), (char *)arg1[12], 0);
        FUN_00306910(arg2, arg3, DAT_004c2278, (int **)(&arg1[13]), (char *)arg1[13], 0);
        FUN_00306910(arg2, arg3, DAT_004c2280, (int **)(&arg1[14]), (char *)arg1[14], 0);
        FUN_00306910(arg2, arg3, DAT_004c2288, (int **)(&arg1[15]), (char *)arg1[15], 0);
        FUN_00306910(arg2, arg3, DAT_004c2290, (int **)(&arg1[16]), (char *)arg1[16], 0);
        FUN_00306910(arg2, arg3, DAT_004c2298, (int **)(&arg1[17]), (char *)arg1[17], 0);
        FUN_00306910(arg2, arg3, DAT_004c22a0, (int **)(&arg1[18]), (char *)arg1[18], 0);
        FUN_00306910(arg2, arg3, DAT_004c22a8, (int **)(&arg1[19]), (char *)arg1[19], 0);
        FUN_003065f0(arg2, arg3, DAT_004c22b0, &arg1[20], arg1[20], 0);
        *arg0 = g_resultSuccess.v;
    }
}

void Gap__Core__igMemoryPoolInfo__vfunc_18(igMemoryPoolInfo *arg0) {
    Gap__Core__igObject__vfunc_16((int)arg0);
    SETSTR(_handleName)
    SETSTR(_aliasedTo)
    arg0->_size = 0;
    arg0->_maxSize = 0;
    arg0->_address = 0;
    SETSTR(_class)
    SETSTR(_arenaType)
    SETSTR(_source)
    SETSTR(_scope)
    SETSTR(_debugOptions)
    SETSTR(_releaseOptions)
    SETSTR(_debugChecking)
    SETSTR(_releaseChecking)
    SETSTR(_debugMessages)
    SETSTR(_releaseMessages)
    arg0->_eventTrackerCapacity = 0;
}

