/* The rates are read as unsigned, so the unsigned-int to float conversion yields the srl/andi/or
 * fixup. */
typedef struct B { char pad[16]; long long *p; } B;
typedef struct A { char pad[56]; B *b; } A;
float fmodf(float, float);
void FUN_001df1d0(A *arg0, long long arg1, int *arg2, int *arg3, float *arg4) {
    float a = (float)(unsigned int)(arg1 >> 18);
    float b = (float)(unsigned int)(*arg0->b->p >> 18);
    *arg2 = (int)(a / b);
    *arg3 = *arg2 + 1;
    *arg4 = fmodf(a, b) / b;
}
