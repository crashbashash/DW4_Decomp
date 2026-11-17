#ifndef DW4_BETIME_H
#define DW4_BETIME_H

/* The length of `frames` 60 Hz frames in the insight clock's nanoseconds. The parameter is const: b52 binds an
 * inlined function's const parameter to its argument before the body, so the caller's field is loaded ahead
 * of the body's other operands. */
static inline long long FramesToTime(const float frames) { return (long long)(1e9f * frames / 60.0f); }

#endif
