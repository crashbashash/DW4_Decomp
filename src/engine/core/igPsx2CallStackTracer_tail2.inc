static inline int tracerCount(const igCallStackTracerView *tracer) { return tracer->_count; }

int igPsx2CallStackTracer_CaptureCallStack(igCallStackTracerView *tracer) {
    int index;

    index = tracerCount(tracer);
    if (index < tracer->_capacity) {
        tracer->_count = tracer->_count + 1;
    } else {
        ((Gap::Core::igDataList *)tracer)->resizeAndSetCount(index + 1, 4);
    }
    tracer->_data[index] = g_igPsx2CallStackTracer_terminatorAddress[0];
    return (int)tracer->_data;
}

/* J-thunk for igCallStackTracer virtual slot 25, forwarding to the slot body. The callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
void igPsx2CallStackTracer_HasSymbols(void) {
    igCallStackTracer_HasSymbols();
}

unsigned int *Gap__Core__igPsx2CallStackTracer__vfunc_31(igCallStackTracerView *tracer) {
    int index = tracerCount(tracer);
    if (index < tracer->_capacity) {
        tracer->_count = tracer->_count + 1;
    } else {
        ((Gap::Core::igDataList *)tracer)->resizeAndSetCount(index + 1, 4);
    }
    tracer->_data[index] = DAT_004c2620;
    return tracer->_data;
}

