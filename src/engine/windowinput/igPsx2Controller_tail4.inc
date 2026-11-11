int Gap__igPsx2Controller__vfunc_22(void) {
    return DAT_0055f760[0];
}

int Gap__igPsx2Controller__vfunc_24(void *arg0) {
    return *(int *)((char *)(arg0) + 24);
}

void Gap__igPsx2Controller__vfunc_25(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 24) = arg1;
}

unsigned short Gap__igPsx2Controller__vfunc_26(void *arg0) {
    return *(int *)((char *)(arg0) + 28);
}

void Gap__igPsx2Controller__vfunc_27(void *arg0, short arg1) {
    *(short *)((char *)arg0 + 28) = arg1;
}

unsigned short Gap__igPsx2Controller__vfunc_32(void *arg0) {
    return *(int *)((char *)(arg0) + 16);
}

/* The field must be shifted as unsigned (srlv); (unsigned short) promotes to signed int, so the
 * (unsigned int) cast is needed or the compiler emits srav. */
int Gap__igPsx2Controller__vfunc_28(void *arg0, int arg1) {
    return (((unsigned int) * (unsigned short *)((char *)(arg0) + 68) >> arg1) & 1) == 0;
}

float Gap__igPsx2Controller__vfunc_29(O_149230 *arg0, int arg1) {
    int i;
    int t;
    unsigned v;
    long long d;
    unsigned char *p;
    float r;
    i = FUN_001480a0((O_1480a0 *)arg0, arg1);
    if (i >= 0) {
        p = (unsigned char *)(i + (int)arg0);
        v = p[97];
        r = (float)v / 255.0f;
    } else {
    t = arg0->vX(arg1);
    d = 0;
    if (t != 0) {
        d = (long long)0x3FF00000 << 0x20;
    }
    r = dptofp(d);
    }
    return r;
}

int Gap__igPsx2Controller__vfunc_30(void *arg0) {
    return ~*(unsigned short *)((char *)(arg0) + 68) & 0xFFFF;
}

/* Reports whether the controller is connected: returns _connected (+52). */

unsigned char Gap__igPsx2Controller__vfunc_34(igPsx2Controller *self) {
    return self->_connected;
}

/* IgPsx2Controller vtable slot 35, a plain getter that returns the reflected field _attachedWindow
 * (the window the controller is attached to, igPsx2Controller +32). */

int Gap__igPsx2Controller__vfunc_35(igPsx2Controller *self) {
    return self->_attachedWindow;
}

