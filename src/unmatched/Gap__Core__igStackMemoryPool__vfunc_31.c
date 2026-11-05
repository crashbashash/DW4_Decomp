typedef struct S { char pad[116]; int f116; long long f120; unsigned f128; unsigned f132; int f136; } S;
void Gap__Core__igStackMemoryPool__vfunc_31(S *s) {
    s->f132 = s->f116;
    s->f136 = (int)(s->f132 + s->f120 + (long long)(unsigned __int128)(unsigned long long)-4LL);
    s->f136 = s->f136 - (s->f136 & 3);
}
