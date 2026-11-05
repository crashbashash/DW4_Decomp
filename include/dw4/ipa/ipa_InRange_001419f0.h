static inline int InRange(float x, volatile float *lo, volatile float *hi) {
    return x >= *lo && x <= *hi;
}
