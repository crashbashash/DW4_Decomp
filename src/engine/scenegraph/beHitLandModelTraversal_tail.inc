void FUN_001ce660(int arg0) {
    FUN_001ce790(((int)DAT_00562790[0]), arg0);
}

void Gap__Bec__beHitLandModelTraversal__vfunc_07(beHitLandModelTraversal *arg0, int arg1) {
    igObject *temp_a0;
    igObject *temp_s0;

    Gap__Sg__igTraversal__vfunc_09((A_1e0380 *)arg0, arg1);
    if (arg1 == 0) {
        temp_s0 = DAT_00562790[0];
        if (temp_s0 != 0) {
            temp_s0->_refCount = temp_s0->_refCount + 1;
        }
        temp_a0 = (igObject *)arg0->_travProcs;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if (((unsigned long long)(long long)temp_a0->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        arg0->_travProcs = (int)temp_s0;
    }
}

