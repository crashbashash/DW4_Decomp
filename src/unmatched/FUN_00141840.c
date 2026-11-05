typedef struct S { char pad[10]; short s10; char pad2[4]; int i16; } S;
void FUN_00141840(S *arg0) {
    arg0->s10 = arg0->i16;
}
