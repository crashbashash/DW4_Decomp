int igPsx2Thread_GetMeta(void) {
    return (int)g_igPsx2Thread_metaObject;
}

/* Vtable slot 42 of igPsx2Thread: returns the constant 0x10. The adjacent slot 43 returns the same
 * constant. */
int igPsx2Thread_GetStackAlignment(void) {
    return 0x10;
}

/* Vtable slot 43 of igPsx2Thread: returns the constant 0x10. The adjacent slot 42 returns the same
 * constant. */
int Gap__Core__igPsx2Thread__vfunc_43(void) {
    return 0x10;
}

void igPsx2Thread_ReleaseDefaults(igPsx2Thread *self) {
    int stack;

    if (self->_userStack == 0) {
        stack = self->_stack;
        if (stack != 0) {
            ((Gap::Core::igObject *)self)->free((void *)stack);
        }
    }
}

/* IgPsx2Thread vtable slot 34, a plain getter that returns the reflected field _function (the raw
 * thread entry-function pointer, +40). */

int igPsx2Thread_GetFunction(igPsx2Thread *self) {
    return self->_function;
}

/* IgPsx2Thread vtable slot 36, a plain getter that returns the reflected field _arg (the raw
 * argument handed to the thread function, +28). */

int igPsx2Thread_GetArg(igPsx2Thread *self) {
    return self->_arg;
}

igResult igPsx2Thread_SetStack(igPsx2ThreadView *self, int stack, int size) {
    if (self->IsRunning() == 0) {
        if (stack & 0xF) {
            return igResult(g_resultFailure.v);
        }
        if (self->_userStack == 0) {
            int a1 = self->_stack;
            if (a1 != 0) {
                ((Gap::Core::igObject *)self)->free((void *)a1);
            }
        }
        self->_stack = stack;
        self->_userStack = 1;
        self->_stackSize = size;
        return igResult(g_resultSuccess.v);
    }
    return igResult(g_resultFailure.v);
}

/* IgPsx2Thread vtable slot 38, a plain getter that returns the reflected field _stack (the raw
 * stack pointer, +32). */

int igPsx2Thread_GetStack(igPsx2Thread *self) {
    return self->_stack;
}

/* IgPsx2Thread vtable slot 40, a plain getter that returns the reflected field _stackSize (the
 * stack size in bytes, +36). */

int igPsx2Thread_GetStackSize(igPsx2Thread *self) {
    return self->_stackSize;
}

void Gap__Core__igPsx2Thread__vfunc_52(int *result) {
    *result = g_resultFailure.v;
}

void Gap__Core__igPsx2Thread__vfunc_53(int *result) {
    *result = g_resultFailure.v;
}

void Gap__Core__igPsx2Thread__vfunc_54(int *result) {
    *result = g_resultFailure.v;
}

