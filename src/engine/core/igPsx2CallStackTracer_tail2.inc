static inline int tracerCount(const igCallStackTracerView *tracer) { return tracer->_count; }

int Gap__Core__igPsx2CallStackTracer__vfunc_24(igCallStackTracerView *tracer) {
    int index;

    index = tracerCount(tracer);
    if (index < tracer->_capacity) {
        tracer->_count = tracer->_count + 1;
    } else {
        List_Resize(tracer, index + 1, 4);
    }
    *(int *)((char *)tracer->_data + (index * 4)) = DAT_004c2618[0];
    return (int)tracer->_data;
}

/* J-thunk for igCallStackTracer virtual slot 25, forwarding to the slot body. The callee takes the
 * caller's registers untouched, so the thunk has no arguments of its own. */
void thunk_Gap__Core__igCallStackTracer__vfunc_25(void) {
    Gap__Core__igCallStackTracer__vfunc_25();
}

unsigned int *Gap__Core__igPsx2CallStackTracer__vfunc_31(igCallStackTracerView *tracer) {
    int index = tracerCount(tracer);
    if (index < tracer->_capacity) {
        tracer->_count = tracer->_count + 1;
    } else {
        List_Resize(tracer, index + 1, 4);
    }
    tracer->_data[index] = DAT_004c2620;
    return tracer->_data;
}

