extern "C" {
int __fixunsdfdi(...);
int fptodp(float);
int dpmul(...);
int litodp(...);
void FUN_001c0ea0(void *arg0);
}
class DW4VC_24_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual float vX(); };
void FUN_001c0ea0(void *arg0) {
    int temp_s0;
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 32));
    temp_s0 = fptodp(((DW4VC_24_0 *)(temp_a0))->vX());
    __fixunsdfdi(dpmul(litodp(0x3B9ACA00), temp_s0));
}
