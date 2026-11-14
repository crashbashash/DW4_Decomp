int Gap__Core__igPsx2Semaphore__vfunc_22(void) {
    return ((int *)g_igPsx2Semaphore_metaObject)[0];
}

/* IgPsx2Semaphore vtable slot 25, tells whether the semaphore has been created. _semaID (+12)
 * holds the kernel semaphore id; -1 is the "no semaphore yet" value. */

int Gap__Core__igPsx2Semaphore__vfunc_25(igPsx2Semaphore *self) {
    return self->_semaID != -1;
}

void Gap__Core__igPsx2Semaphore__vfunc_12(igSemaphoreView *self) {
    igResult destroyed;

    if (self->isCreated() != 0) {
        destroyed = self->destroy();
    }
    Gap__Core__igObject__vfunc_10((int)self);
}

