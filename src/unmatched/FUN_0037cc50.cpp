extern "C" {
typedef struct L { char p8[8]; int n; char p12[4]; int *data; } L;
typedef struct O { char p32[32]; int f32; int f36; L *f40; } O;
int FUN_0037caf0(O *, int);
void FUN_0037cc50(O *arg0, int arg1);
}

void FUN_0037cc50(O *arg0, int arg1) {
    int i;
    int j;

    switch (arg1) {
    case 1:
        FUN_0037caf0(arg0, arg0->f32);
        break;
    case 2:
        FUN_0037caf0(arg0, arg0->f36);
        break;
    case 3:
    case 4:
        for (i = 0; i < arg0->f40->n; i++) {
            FUN_0037caf0(arg0, arg0->f40->data[i]);
        }
        break;
    case 5:
    default:
        FUN_0037caf0(arg0, arg0->f32);
        FUN_0037caf0(arg0, arg0->f36);
        for (j = 0; j < arg0->f40->n; j++) {
            FUN_0037caf0(arg0, arg0->f40->data[j]);
        }
        break;
    }
}
