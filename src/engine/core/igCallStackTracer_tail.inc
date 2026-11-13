int *Gap__Core__igCallStackTracer__vfunc_24(int *arg0) {
    int t;
    if (arg0[3] > 0) {
        arg0[2] = 1;
    } else {
        List_Resize(arg0, 1, 4);
    }
    t = arg0[2];
    if (t != 0 && 0 < t) {
        *(int *)arg0[4] = DAT_004c1ea0[0];
    }
    return (int *)arg0[4];
}

int Gap__Core__igCallStackTracer__vfunc_25(void) {
    DW4VC_92_0 *temp_a0;
    temp_a0 = (DW4VC_92_0 *)(*(int *)((char *)(((void * *)g_objectSystem)[0]) + 80));
    if (temp_a0 != 0) {
        if (temp_a0->vX() != 0) {
            return 1;
        }
    }
    return 0;
}

void Gap__Core__igCallStackTracer__vfunc_26(int *arg0, VC_2d43a0 *arg1, int arg2, int arg3, long long arg4, long long arg5) {
    char b1[256];
    char b2[256];
    int o1;
    int o2;
    R_2d43a0 r1 = arg1->vX1(arg2, b1, 255, &o1, b2, 255, &o2);
    R_2d43a0 r2 = arg1->vX2(arg2, b1, o1, b2, o2, arg3, arg4, arg5);
    *arg0 = r1.v;
}

R_2d4470 Gap__Core__igCallStackTracer__vfunc_27(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line) {
    Resolver *r = *(Resolver **)(((char * *)g_objectSystem)[0] + 80);
    if (r != 0 && r->IsReady() != 0) {
        int base = 0;
        int other = 0;
        if (r->Lookup(addr, buf, size, &base, &other, name, nameSize, line) == ((R_2d4470 *)&g_statusSucceeded)[0]) {
            *offset = addr - base;
            return ((R_2d4470 *)&g_statusSucceeded)[0];
        }
    }
    if (buf != 0) {
        char tmp[20];
        sprintf(tmp, ((char *)text_0x_08x), addr);
        strncpy(buf, tmp, size);
    }
    *offset = 0;
    if (name != 0) {
        *name = 0;
    }
    *line = 0;
    return ((R_2d4470 *)&g_allocatorFailureStatus)[0];
}

void Gap__Core__igCallStackTracer__vfunc_29(void) {

}

void Gap__Core__igCallStackTracer__vfunc_30(void) {

}

