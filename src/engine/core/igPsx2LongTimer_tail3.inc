igMetaObject *Gap__Core__igPsx2LongTimer__vfunc_22(void) {
    return g_igPsx2LongTimer_metaObject[0];
}

double Gap__Core__igPsx2LongTimer__vfunc_23(igLongTimerView *self) {
    long long nanoseconds = self->vfunc_24();
    return (double)(nanoseconds / NANOSECONDS_PER_SECOND) + (double)(nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_SECOND;
}

long long Gap__Core__igPsx2LongTimer__vfunc_26(igPsx2LongTimer *self) {
    if (self->_isStopped != 0) {
        return self->_additionalTime;
    }
    return (self->_additionalTime + ((igLongTimerView *)self)->vfunc_37()) - self->_startTime;
}

double Gap__Core__igPsx2LongTimer__vfunc_25(igLongTimerView *self) {
    long long nanoseconds = self->vfunc_26();
    return (double)(nanoseconds / NANOSECONDS_PER_SECOND) + (double)(nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_SECOND;
}

void Gap__Core__igPsx2LongTimer__vfunc_27(igPsx2LongTimer *self) {
    if (self->_isStopped != 0) {
        self->_isStopped = 0;
        self->_startTime = ((igLongTimerView *)self)->vfunc_37();
    }
}

void Gap__Core__igPsx2LongTimer__vfunc_28(igPsx2LongTimer *self) {
    if (self->_isStopped == 0) {
        self->_additionalTime = self->_additionalTime + (((igLongTimerView *)self)->vfunc_37() - self->_startTime);
        self->_isStopped = 1;
    }
}

void Gap__Core__igPsx2LongTimer__vfunc_29(igPsx2LongTimer *self) {
    self->_additionalTime = self->_resetTime;
    if (self->_isStopped == 0) {
        self->_startTime = ((igLongTimerView *)self)->vfunc_37();
    }
}

/* Reset the timer. Marks it stopped and loads the accumulated `_additionalTime` from `_resetTime`
 * (vfunc_33 sets `_resetTime`, vfunc_35 reads it back, vfunc_36 reads `_isStopped`). */

void Gap__Core__igPsx2LongTimer__vfunc_30(igPsx2LongTimer *self) {
    self->_isStopped = 1;
    self->_additionalTime = self->_resetTime;
}

void Gap__Core__igPsx2LongTimer__vfunc_31(igPsx2LongTimer *self) {
    self->_isStopped = 0;
    self->_additionalTime = self->_resetTime;
    self->_startTime = ((igLongTimerView *)self)->vfunc_37();
}

void Gap__Core__igPsx2LongTimer__vfunc_32(igLongTimerView *self, double seconds) {
    self->setResetTime((long long)(NANOSECONDS_PER_SECOND * seconds));
}

/* Setter for the timer's reflected _resetTime field. */
void Gap__Core__igPsx2LongTimer__vfunc_33(igPsx2LongTimer *self, long long resetTime) {
    self->_resetTime = resetTime;
}

/* Slot 35 getter: returns the timer's _resetTime field (the reflected igLongMetaField). */
long long Gap__Core__igPsx2LongTimer__vfunc_35(igPsx2LongTimer *self) {
    return self->_resetTime;
}

double Gap__Core__igPsx2LongTimer__vfunc_34(igLongTimerView *self) {
    long long nanoseconds = self->getResetTime();
    return (double)(nanoseconds / NANOSECONDS_PER_SECOND) + (double)(nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_SECOND;
}

/* Reports whether the timer is stopped: returns _isStopped (+32). */

unsigned char Gap__Core__igPsx2LongTimer__vfunc_36(igPsx2LongTimer *self) {
    return self->_isStopped;
}

