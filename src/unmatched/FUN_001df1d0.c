/* 0x001df1d0 - FUN_001df1d0. Divides two fixed-point rates read as unsigned (value >> 18 converted unsigned-int to float, which yields the srl/andi/or fixup), stores the integer quotient and quotient+1 and the fractional part via the float helper; alternate compiler -O3. */
typedef struct B { char pad[16]; long long *p; } B;
typedef struct A { char pad[56]; B *b; } A;
float FUN_00123658(float, float);
void FUN_001df1d0(A *arg0, long long arg1, int *arg2, int *arg3, float *arg4) {
    float a = (float)(unsigned int)(arg1 >> 18);
    float b = (float)(unsigned int)(*arg0->b->p >> 18);
    *arg2 = (int)(a / b);
    *arg3 = *arg2 + 1;
    *arg4 = FUN_00123658(a, b) / b;
}
