int List_Resize();

typedef struct L { char pad[8]; int count; int cap; int *data; } L;
typedef struct B { char pad[12]; L *f12; } B;
typedef struct A { char pad[8]; B *f8; char pad12[24]; int f36; int f40; } A;

static inline int count_of(const L *list) { return list->count; }
void FUN_001db500(A *arg0) {
    int temp_s0;
    int temp_s0_2;
    int temp_s2_2;
    int temp_s3;
    L *temp_s1;
    L *temp_s2;

    temp_s0 = arg0->f36;
    temp_s2 = arg0->f8->f12;
    temp_s3 = temp_s2->count;
    if (temp_s3 < temp_s2->cap) {
        temp_s2->count = count_of(temp_s2) + 1;
    } else {
        List_Resize(temp_s2, temp_s3 + 1, 4);
    }
    temp_s2->data[temp_s3] = temp_s0;
    temp_s0_2 = arg0->f40;
    temp_s1 = arg0->f8->f12;
    temp_s2_2 = temp_s1->count;
    if (temp_s2_2 < temp_s1->cap) {
        temp_s1->count = count_of(temp_s1) + 1;
    } else {
        List_Resize(temp_s1, temp_s2_2 + 1, 4);
    }
    temp_s1->data[temp_s2_2] = temp_s0_2;
}
