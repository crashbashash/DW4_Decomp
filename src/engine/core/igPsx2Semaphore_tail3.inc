int igPsx2Semaphore_GetMeta(void) {
    return ((int *)g_igPsx2Semaphore_metaObject)[0];
}

/* IgPsx2Semaphore vtable slot 25, tells whether the semaphore has been created. _semaID (+12)
 * holds the kernel semaphore id; -1 is the "no semaphore yet" value. */

int igPsx2Semaphore_IsCreated(igPsx2Semaphore *self) {
    return self->_semaID != -1;
}

void igPsx2Semaphore_ReleaseDefaults(igSemaphoreView *self) {
    igResult destroyed;

    if (self->isCreated() != 0) {
        destroyed = self->destroy();
    }
    igObject_ReleaseDefaults((int)self);
}

