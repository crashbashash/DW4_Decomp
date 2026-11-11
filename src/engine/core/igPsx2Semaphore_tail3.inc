int Gap__Core__igPsx2Semaphore__vfunc_22(void) {
    return ((int *)g_igPsx2Semaphore_metaObject)[0];
}

/* IgPsx2Semaphore vtable slot 25, tells whether the semaphore has been created. _semaID (+12)
 * holds the kernel semaphore id; -1 is the "no semaphore yet" value. */

int Gap__Core__igPsx2Semaphore__vfunc_25(igPsx2Semaphore *self) {
    return self->_semaID != -1;
}

void Gap__Core__igPsx2Semaphore__vfunc_12(void **arg0) {
    DW4SR4 sp2C;

    if (((DW4VC_100_0 *)(arg0))->vX() != 0) {
        sp2C = ((DW4VCSR_96_0 *)(arg0))->vX();
    }
    Gap__Core__igObject__vfunc_10((int)arg0);
}

