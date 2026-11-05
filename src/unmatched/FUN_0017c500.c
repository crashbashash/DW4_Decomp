typedef struct E { char pad4[4]; int f4; char pad8[72]; unsigned char f80; char pad81[55]; } E;
typedef struct L { char pad16[16]; E *f16; } L;
typedef struct S { char pad324[324]; L *f324; } S;
extern int DAT_00560a28[4];
void FUN_0017c500(S *arg0, int arg1, int arg2) {
    int temp_a3;

    temp_a3 = arg1 * 0x88;
    if (arg2 == *(int *)((char *)arg0->f324->f16 + temp_a3 + 4)) {
        DAT_00560a28[0] += 1;
    }
    *(int *)((char *)arg0->f324->f16 + temp_a3 + 4) = arg2;
    *(char *)((char *)arg0->f324->f16 + temp_a3 + 80) = 1;
}
