int Gap__Core__igPsx2Thread__vfunc_22(void) {
    return ((int *)g_igPsx2Thread_metaObject)[0];
}

/* Vtable slot 42 of igPsx2Thread: returns the constant 0x10. The adjacent slot 43 returns the same
 * constant. */
int Gap__Core__igPsx2Thread__vfunc_42(void) {
    return 0x10;
}

/* Vtable slot 43 of igPsx2Thread: returns the constant 0x10. The adjacent slot 42 returns the same
 * constant. */
int Gap__Core__igPsx2Thread__vfunc_43(void) {
    return 0x10;
}

void Gap__Core__igPsx2Thread__vfunc_12(void *arg0) {
    int temp_a1;

    if (*(unsigned char *)((char *)(arg0) + 45) == 0) {
        temp_a1 = *(int *)((char *)(arg0) + 32);
        if (temp_a1 != 0) {
            FUN_00300f50((int)arg0, temp_a1);
        }
    }
}

/* IgPsx2Thread vtable slot 34, a plain getter that returns the reflected field _function (the raw
 * thread entry-function pointer, +40). */

int Gap__Core__igPsx2Thread__vfunc_34(igPsx2Thread *self) {
    return self->_function;
}

/* IgPsx2Thread vtable slot 36, a plain getter that returns the reflected field _arg (the raw
 * argument handed to the thread function, +28). */

int Gap__Core__igPsx2Thread__vfunc_36(igPsx2Thread *self) {
    return self->_arg;
}

R_3308a0 Gap__Core__igPsx2Thread__vfunc_37(C_3308a0 *arg1, int arg2, int arg3) {
    if (arg1->v30() == 0) {
        if (arg2 & 0xF) {
            return R_3308a0(g_allocatorFailureStatus.v);
        }
        if (arg1->f45 == 0) {
            int a1 = arg1->f32;
            if (a1 != 0) {
                FUN_00300f50((int)arg1, a1);
            }
        }
        arg1->f32 = arg2;
        arg1->f45 = 1;
        arg1->f36 = arg3;
        return R_3308a0(g_statusSucceeded.v);
    }
    return R_3308a0(g_allocatorFailureStatus.v);
}

/* IgPsx2Thread vtable slot 38, a plain getter that returns the reflected field _stack (the raw
 * stack pointer, +32). */

int Gap__Core__igPsx2Thread__vfunc_38(igPsx2Thread *self) {
    return self->_stack;
}

/* IgPsx2Thread vtable slot 40, a plain getter that returns the reflected field _stackSize (the
 * stack size in bytes, +36). */

int Gap__Core__igPsx2Thread__vfunc_40(igPsx2Thread *self) {
    return self->_stackSize;
}

void Gap__Core__igPsx2Thread__vfunc_52(int *result) {
    *result = g_allocatorFailureStatus.v;
}

void Gap__Core__igPsx2Thread__vfunc_53(int *result) {
    *result = g_allocatorFailureStatus.v;
}

void Gap__Core__igPsx2Thread__vfunc_54(int *result) {
    *result = g_allocatorFailureStatus.v;
}

