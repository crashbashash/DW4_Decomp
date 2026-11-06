extern "C" {
/* `0 < n` on the inner guards, `n > 0` on the outer, and the reference is released through a local
 * object pointer. */
typedef struct T { int w0; int references; } T;
void *FUN_002b90e0(int);
int FUN_002ed2b0(int, int, int);
int Memory_FreeBufferWithAllocator(int, int);
int Memory_GetAllocatorByName(int *);
int igObject_Destroy(T *);
extern int DAT_004ffe68[4];
extern int DAT_005875e8[4];
extern int DAT_005875f0[4];
extern T *DAT_00587608[4];
void FUN_00332d20(int arg0) {
    int temp_a0;
    int temp_s2;
    int var_a0;
    int var_s1;
    int var_s0;
    int var_v1;
    T *object;

    temp_s2 = Memory_GetAllocatorByName(&DAT_004ffe68[0]);
    if (DAT_005875f0[0] != 0) {
        if (DAT_005875e8[0] > 0) {
            var_s1 = 0;
            if (0 < DAT_005875e8[0]) {
                var_s0 = 0;
                do {
                    temp_a0 = *(int *)(DAT_005875f0[0] + var_s0);
                    if (temp_a0 != 0) {
                        Memory_FreeBufferWithAllocator(temp_a0, temp_s2);
                    }
                    var_s1 += 1;
                    var_s0 += 4;
                } while (var_s1 < DAT_005875e8[0]);
            }
        }
        Memory_FreeBufferWithAllocator(DAT_005875f0[0], temp_s2);
    }
    DAT_005875e8[0] = arg0;
    if (arg0 > 0) {
        DAT_005875f0[0] = FUN_002ed2b0(arg0 * 4, 0x10, temp_s2);
        var_v1 = 0;
        if (0 < DAT_005875e8[0]) {
            var_a0 = 0;
            do {
                var_v1 += 1;
                *(int *)(DAT_005875f0[0] + var_a0) = 0;
                var_a0 += 4;
            } while (var_v1 < DAT_005875e8[0]);
        }
        object = DAT_00587608[0];
        if (object != 0) {
            --object->references;
            if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0) {
                igObject_Destroy(object);
            }
        }
        DAT_00587608[0] = (T *)FUN_002b90e0(temp_s2);
    }
}
}
