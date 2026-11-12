igMetaObject *Gap__Core__igPsx2LongTimer__vfunc_22(void) {
    return g_igPsx2LongTimer_metaObject[0];
}

void Gap__Core__igPsx2LongTimer__vfunc_23(void **arg0) {
    int temp_s0_2;
    int temp_v0;
    int temp_s0;

    temp_v0 = ((DW4VC_96_0 *)(arg0))->vX();
    temp_s0 = __floatdidf(__moddi3(temp_v0, 0x3B9ACA00));
    temp_s0_2 = dpdiv(temp_s0, litodp(0x3B9ACA00));
    dpadd(__floatdidf(__divdi3(temp_v0, 0x3B9ACA00)), temp_s0_2);
}

long long Gap__Core__igPsx2LongTimer__vfunc_26(igPsx2LongTimer *arg0) {
    if (arg0->_isStopped != 0) {
        return arg0->_additionalTime;
    }
    return (arg0->_additionalTime + ((DW4VC_148_0 *)(((char *)(arg0) + 0)))->vX()) - arg0->_startTime;
}

void Gap__Core__igPsx2LongTimer__vfunc_25(void **arg0) {
    int temp_s0_2;
    int temp_v0;
    int temp_s0;

    temp_v0 = ((DW4VC_104_0 *)(arg0))->vX();
    temp_s0 = __floatdidf(__moddi3(temp_v0, 0x3B9ACA00));
    temp_s0_2 = dpdiv(temp_s0, litodp(0x3B9ACA00));
    dpadd(__floatdidf(__divdi3(temp_v0, 0x3B9ACA00)), temp_s0_2);
}

void Gap__Core__igPsx2LongTimer__vfunc_27(S_330be0 *arg0) {
    if (arg0->f32 != 0) {
        arg0->f32 = 0;
        arg0->f8 = arg0->vX();
    }
}

void Gap__Core__igPsx2LongTimer__vfunc_28(F_330c20 *arg0) {
    if (arg0->done == 0) {
        arg0->b = arg0->b + (((VC_330c20 *)arg0)->vX() - arg0->a);
        arg0->done = 1;
    }
}

void Gap__Core__igPsx2LongTimer__vfunc_29(igPsx2LongTimer *arg0) {
    arg0->_additionalTime = (long long) arg0->_resetTime;
    if (arg0->_isStopped == 0) {
        arg0->_startTime = ((DW4VC_148_0 *)(((char *)(arg0) + 0)))->vX();
    }
}

/* Reset the timer. Marks it stopped and loads the accumulated `_additionalTime` from `_resetTime`
 * (vfunc_33 sets `_resetTime`, vfunc_35 reads it back, vfunc_36 reads `_isStopped`). */

void Gap__Core__igPsx2LongTimer__vfunc_30(igPsx2LongTimer *self) {
    self->_isStopped = 1;
    self->_additionalTime = (long long) self->_resetTime;
}

void Gap__Core__igPsx2LongTimer__vfunc_31(igPsx2LongTimer *arg0) {
    arg0->_isStopped = 0;
    arg0->_additionalTime = (long long) arg0->_resetTime;
    arg0->_startTime = ((DW4VC_148_0 *)(((char *)(arg0) + 0)))->vX();
}

void Gap__Core__igPsx2LongTimer__vfunc_32(void **self, int seconds_as_double) {
    ((DW4VC_132_1 *)(self))->vX((int)(__fixdfdi(dpmul(litodp(NANOSECONDS_PER_SECOND), seconds_as_double))));
}

/* Setter for the timer's reflected _resetTime field. */
void Gap__Core__igPsx2LongTimer__vfunc_33(igPsx2LongTimer *self, long long resetTime) {
    self->_resetTime = resetTime;
}

/* Slot 35 getter: returns the timer's _resetTime field (the reflected igLongMetaField). */
long long Gap__Core__igPsx2LongTimer__vfunc_35(igPsx2LongTimer *self) {
    return self->_resetTime;
}

void Gap__Core__igPsx2LongTimer__vfunc_34(void **self) {
    int remainderNsAsDouble; /* the EE soft-float helpers pass doubles as integer register pairs */
    int presetNs;
    int fractionSeconds;

    presetNs = ((DW4VC_140_0 *)(self))->vX();
    fractionSeconds = dpdiv((__floatdidf(__moddi3(presetNs, NANOSECONDS_PER_SECOND))), litodp(NANOSECONDS_PER_SECOND));
    dpadd(__floatdidf(__divdi3(presetNs, NANOSECONDS_PER_SECOND)), fractionSeconds);
}

/* Reports whether the timer is stopped: returns _isStopped (+32). */

unsigned char Gap__Core__igPsx2LongTimer__vfunc_36(igPsx2LongTimer *self) {
    return self->_isStopped;
}

