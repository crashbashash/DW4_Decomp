igMetaObject *igPsx2LongTimer_GetMeta(void) {
    return g_igPsx2LongTimer_metaObject[0];
}

double igPsx2LongTimer_GetResolutionSeconds(igLongTimerView *self) {
    long long nanoseconds = self->vfunc_24();
    return (double)(nanoseconds / NANOSECONDS_PER_SECOND) + (double)(nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_SECOND;
}

long long igPsx2LongTimer_GetElapsedTime(igPsx2LongTimer *self) {
    if (self->_isStopped != 0) {
        return self->_additionalTime;
    }
    return (self->_additionalTime + ((igLongTimerView *)self)->vfunc_37()) - self->_startTime;
}

double igPsx2LongTimer_GetElapsedSeconds(igLongTimerView *self) {
    long long nanoseconds = self->vfunc_26();
    return (double)(nanoseconds / NANOSECONDS_PER_SECOND) + (double)(nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_SECOND;
}

void igPsx2LongTimer_Start(igPsx2LongTimer *self) {
    if (self->_isStopped != 0) {
        self->_isStopped = 0;
        self->_startTime = ((igLongTimerView *)self)->vfunc_37();
    }
}

void igPsx2LongTimer_Stop(igPsx2LongTimer *self) {
    if (self->_isStopped == 0) {
        self->_additionalTime = self->_additionalTime + (((igLongTimerView *)self)->vfunc_37() - self->_startTime);
        self->_isStopped = 1;
    }
}

void igPsx2LongTimer_Reset(igPsx2LongTimer *self) {
    self->_additionalTime = self->_resetTime;
    if (self->_isStopped == 0) {
        self->_startTime = ((igLongTimerView *)self)->vfunc_37();
    }
}

/* Reset the timer. Marks it stopped and loads the accumulated `_additionalTime` from `_resetTime`
 * (vfunc_33 sets `_resetTime`, vfunc_35 reads it back, vfunc_36 reads `_isStopped`). */

void igPsx2LongTimer_ResetAndStop(igPsx2LongTimer *self) {
    self->_isStopped = 1;
    self->_additionalTime = self->_resetTime;
}

void igPsx2LongTimer_Restart(igPsx2LongTimer *self) {
    self->_isStopped = 0;
    self->_additionalTime = self->_resetTime;
    self->_startTime = ((igLongTimerView *)self)->vfunc_37();
}

void igPsx2LongTimer_SetResetTimeSeconds(igLongTimerView *self, double seconds) {
    self->setResetTime((long long)(NANOSECONDS_PER_SECOND * seconds));
}

/* Setter for the timer's reflected _resetTime field. */
void igPsx2LongTimer_SetResetTime(igPsx2LongTimer *self, long long resetTime) {
    self->_resetTime = resetTime;
}

/* Slot 35 getter: returns the timer's _resetTime field (the reflected igLongMetaField). */
long long igPsx2LongTimer_GetResetTime(igPsx2LongTimer *self) {
    return self->_resetTime;
}

double igPsx2LongTimer_GetResetTimeSeconds(igLongTimerView *self) {
    long long nanoseconds = self->getResetTime();
    return (double)(nanoseconds / NANOSECONDS_PER_SECOND) + (double)(nanoseconds % NANOSECONDS_PER_SECOND) / NANOSECONDS_PER_SECOND;
}

/* Reports whether the timer is stopped: returns _isStopped (+32). */

unsigned char igPsx2LongTimer_IsStopped(igPsx2LongTimer *self) {
    return self->_isStopped;
}

