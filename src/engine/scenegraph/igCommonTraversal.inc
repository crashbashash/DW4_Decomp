igMetaObject *igCommonTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igCommonTraversal_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a3dd0();
    return g_igCommonTraversal_metaObject[0];
}

int igCommonTraversal_GetVTable(void) {
    struct O_1a38e0 o; int t; int *p; int *q4; int *q3; int *q2; int *q1; int *q0; int *q6; int *q7; int *q8;
    p = (int*)&o;
    FUN_001a3d90((igTraversal *)p);
    o.vt = (int)&DAT_005293c0[0];
    FUN_001a3d80((char*)&o + 32);
    FUN_001a3d70((char*)&o + 36);
    FUN_001a3d60((char*)&o + 52);
    FUN_001a3d50((char*)&o + 56);
    FUN_001a3d40((char*)&o + 60);
    FUN_00197330((int *)((char*)&o + 64));
    q8 = (int*)((char*)&o + 68);
    FUN_001a3d30(q8);
    q7 = (int*)((char*)&o + 72);
    FUN_001a3d20(q7);
    q6 = (int*)((char*)&o + 76);
    FUN_001a3d10(q6);
    q0 = (int*)((char*)&o + 80);
    FUN_001a3d00(q0);
    q1 = (int*)((char*)&o + 84);
    FUN_001a3cf0(q1);
    q2 = (int*)((char*)&o + 88);
    FUN_001a3ce0(q2);
    q3 = (int*)((char*)&o + 92);
    FUN_001a3cd0(q3);
    q4 = (int*)((char*)&o + 96);
    FUN_001a3cc0(q4);
    FUN_001510a0((char*)&o + 100);
    FUN_001510a0(p + 41);
    FUN_001a2c50((int *)(p + 58));
    FUN_001a3cb0(p + 59);
    FUN_001a3ca0(p + 60);
    FUN_001a3160((int *)(p + 61));
    FUN_001a3150((int *)(p + 62));
    FUN_001a3150((int *)(p + 63));
    FUN_001510d0(p + 64);
    FUN_001a3c90(p + 65);
    FUN_001a3c80(p + 66);
    FUN_001a3c70(p + 67);
    FUN_001510a0(p + 68);
    FUN_001a3c60(p + 84);
    FUN_001510a0(p + 86);
    FUN_001510a0(p + 102);
    t = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = (int)&D_005293c0[0];
    FUN_001a0890((ObjectRefWord *)((char*)&o + 336), -1);
    FUN_001a0810((O *)((char*)&o + 268), -1);
    FUN_00194830((struct Ref * *)((char*)&o + 264), -1);
    FUN_001a0790((void * *)((char*)&o + 260), -1);
    FUN_00150eb0((char*)&o + 256, -1);
    FUN_001a0710((struct Ref * *)((char*)&o + 252), -1);
    FUN_001a0710((struct Ref * *)((char*)&o + 248), -1);
    FUN_001a0690((void * *)((char*)&o + 244), -1);
    FUN_001a0610((void * *)((char*)&o + 240), -1);
    FUN_001a0590((ObjectRefWord *)((char*)&o + 236), -1);
    FUN_001a0510((struct R * *)((char*)&o + 232), -1);
    FUN_001a0490((ObjectRefWord *)q4, -1);
    FUN_001a0410((void * *)q3, -1);
    FUN_001a0390((ObjectRefWord *)q2, -1);
    FUN_001a0310((void * *)q1, -1);
    FUN_001a0290((void * *)q0, -1);
    FUN_001a0210((O *)q6, -1);
    FUN_001a0190((void * *)q7, -1);
    FUN_001a0110((struct Ref * *)q8, -1);
    FUN_001380e0((char*)&o + 64, -1);
    FUN_00130140((char*)&o + 60, -1);
    FUN_001a0090((void * *)((char*)&o + 56), -1);
    FUN_001a0010((void * *)((char*)&o + 52), -1);
    FUN_0019ff90((struct T_19fde0 * *)((char*)&o + 36), -1);
    FUN_0019ff10((struct R * *)((char*)&o + 32), -1);
    FUN_00194490((struct S *)&o, 0);
    return t;
}

