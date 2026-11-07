struct O;
class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vX(O *); };
struct T { int word0; int references; int n; int cap; };
struct O { int p0; int p1; int n; char pad[32]; T *list; char pad2[232]; int f280; };
extern "C" {
T *FUN_002c9130(int);
E *FUN_002d7e90(O *, int);
int List_Resize(T *, int, int);
void igObject_Destroy(T *);
extern int DAT_004fb410[4];
}
extern "C" void FUN_002e78b0(int *arg0, O *arg1) {
    int temp_s1;
    int temp_s0;
    int i;
    T *temp_a0;
    T *temp_a0_2;
    temp_a0 = arg1->list;
    temp_s1 = arg1->n;
    temp_s0 = arg1->f280;
    if (temp_a0 != 0) {
        temp_a0->references = temp_a0->references - 1;
        if (((unsigned long long)(long long)temp_a0->references & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg1->list = FUN_002c9130(temp_s0);
    temp_a0_2 = arg1->list;
    if (temp_s1 >= 0) {
        if (temp_s1 <= temp_a0_2->cap) {
            temp_a0_2->n = temp_s1;
        } else {
            List_Resize(temp_a0_2, temp_s1, 4);
        }
    }
    for (i = 0; i < temp_s1; i++) {
        FUN_002d7e90(arg1, i)->vX(arg1);
    }
    *arg0 = DAT_004fb410[0];
}
