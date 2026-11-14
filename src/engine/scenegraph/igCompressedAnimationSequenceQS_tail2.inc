void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_44(QSSequenceView *arg0, QSSourceSequence *arg1) {
    float sp7C;
    float sp78;
    int n = arg1->v156();
    unsigned char fl = arg1->v240();
    int s0;
    int s5;
    int al;
    QSDataList *old;
    QSDataList *l;
    sp7C = 0.0f;
    sp78 = 0.0f;
    arg0->_animationDuration = arg1->v260();
    s0 = fl & 0xFF;
    s5 = s0 & 1;
    arg0->_playMode = arg1->f36;
    arg0->_channels = fl;
    if (s5 != 0) arg0->_interpolationMethod[0] = arg1->v236(1);
    s0 = s0 & 2;
    if (s0 != 0) arg0->_interpolationMethod[1] = arg1->v236(2);
    if (s5 != 0) {
        if (arg0->_compressedTranslationList == 0) {
            al = igObject_GetAllocator(arg0);
            old = arg0->_compressedTranslationList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if (((unsigned long long)((long long)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old);
            }
            arg0->_compressedTranslationList = igUnsignedShortList_Create(al);
        }
        int c = n * 3;
        l = arg0->_compressedTranslationList;
        if (c >= 0) {
            if (c <= l->_capacity) l->_count = c;
            else List_Resize(l, c, 2);
        }
        l = arg0->_compressedTranslationList;
        c = l->_count;
        if (c < l->_capacity) List_Reserve(l, c, 2);
        FUN_001e5f00(arg1->v172(), arg0->_compressedTranslationList->_data, &sp7C, &sp78);
        arg0->_translationBase = sp7C;
        arg0->_translationRangeOverMaxUShort = 1.52590219e-05f * sp78;
    }
    if (s0 != 0) {
        if (arg0->_compressedQuaternionList == 0) {
            al = igObject_GetAllocator(arg0);
            old = arg0->_compressedQuaternionList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if (((unsigned long long)((long long)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old);
            }
            arg0->_compressedQuaternionList = igUnsignedShortList_Create(al);
        }
        int c = n * 4;
        l = arg0->_compressedQuaternionList;
        if (c >= 0) {
            if (c <= l->_capacity) l->_count = c;
            else List_Resize(l, c, 2);
        }
        l = arg0->_compressedQuaternionList;
        c = l->_count;
        if (c < l->_capacity) List_Reserve(l, c, 2);
        FUN_001e6130(arg1->v184(), arg0->_compressedQuaternionList->_data, &sp7C, &sp78);
        arg0->_quaternionBase = sp7C;
        arg0->_quaternionRangeOverMaxUShort = 1.52590219e-05f * sp78;
    }
    if (arg0->_compressedTimeList == 0) {
        al = igObject_GetAllocator(arg0);
        old = arg0->_compressedTimeList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if (((unsigned long long)((long long)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old);
        }
        arg0->_compressedTimeList = igUnsignedShortList_Create(al);
    }
    l = arg0->_compressedTimeList;
    if (n >= 0) {
        if (n <= l->_capacity) l->_count = n;
        else List_Resize(l, n, 2);
    }
    l = arg0->_compressedTimeList;
    int c = l->_count;
    if (c < l->_capacity) { List_Reserve(l, c, 2); }
    for (s0 = 0; s0 < n; s0++) FUN_001bf400((int)arg0, s0, arg1->v224(s0));
}

