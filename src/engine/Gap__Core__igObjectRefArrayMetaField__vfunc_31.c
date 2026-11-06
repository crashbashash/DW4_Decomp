struct T { int w0; int refs; };
struct A { char pad[52]; unsigned char f34; char pad2[3]; int f38; unsigned char f3c; char pad3[3]; char *f40; int f44; };
int FUN_00302780();
int Memory_GetAllocatorByName();
struct T *igMetaObject_CreateInstance();
int igObject_Destroy();
int igObject_GetAllocator();

void Gap__Core__igObjectRefArrayMetaField__vfunc_31(struct A *arg0, int arg1) {
    int var_s0;
    int var_s1;
    struct T *temp_v0;
    char *temp_a0;

    if (arg0->f34 != 0) {
        temp_a0 = arg0->f40;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s1 = Memory_GetAllocatorByName(temp_a0);
            if (var_s1 == 0) {
                var_s1 = igObject_GetAllocator(arg1);
            }
        } else {
            var_s1 = igObject_GetAllocator(arg1);
        }
        for (var_s0 = 0; var_s0 < arg0->f44; var_s0++) {
            temp_v0 = igMetaObject_CreateInstance(arg0->f38, var_s1);
            FUN_00302780(arg0, arg1, var_s0, temp_v0);
            if (arg0->f3c != 0) {
                temp_v0->refs = temp_v0->refs - 1;
                if (((unsigned long long) ((long long) temp_v0->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_v0);
                }
            }
        }
    }
}
