/* C++ virtual call; both operands of the third argument loaded into locals first. */
extern "C" { void igVirtualCFuncMetaField_SetToDefault(void *arg0, int arg1); }
extern "C" { extern void * DAT_00586dc8[4]; }
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int, int); };
void igVirtualCFuncMetaField_SetToDefault(void *arg0, int arg1) {
 if (arg1 != 0) {
int a = **(int **)((char *)(arg0) + 32);
 int b = *(int *)(arg1 + *(int *)((char *)(DAT_00586dc8[0]) + 916));
 ((VC *)arg0)->vX(arg1, b + a);
}
}

