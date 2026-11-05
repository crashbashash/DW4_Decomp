typedef struct N { int w[16]; } N;
int FUN_00330730(int, int);
int FUN_00330770(int, int);
extern int DAT_00490c70[4];
extern int DAT_00490cc0[4];
extern int DAT_0056ba48[4];
extern int DAT_0056ba50[4];
extern int DAT_0056ba58[4];
extern int DAT_0056ba60[4];
extern int DAT_0056ba68[4];
extern int DAT_0056ba70[4];
extern int DAT_0056ba80[4];
extern int DAT_0056bae0[4];
extern int *DAT_00568e58[4];
extern int *DAT_00562d88[4];
extern int *DAT_005691b8[4];
extern int *DAT_005691c0[4];
extern int *DAT_0056bee8[4];
extern int *DAT_0056bf50[4];
extern int *DAT_0056c0c8[4];
void FUN_00204950(unsigned int arg0) {
    switch (arg0) {
    case 11: {
        int *node; int *arr; int cnt; int b; int v1; int a0; int a0b; int *p; int i;
        arr = (int *)FUN_00330730(DAT_0056ba70[0] * 4, 9);
        cnt = 0;
        if (arr != 0) {
            b = 0;
            do {
                node = (int *)((int *)DAT_0056bae0)[b];
                while (node != 0) {
                    v1 = node[0];
                    if (v1 != 0) { arr[cnt] = v1; cnt++; }
                    a0 = node[164];
                    if (a0 != 0 && ((char *)node)[32] != 0) { FUN_00330770(a0, 25); node[164] = 0; }
                    node = (int *)node[1];
                }
                b++;
            } while (b < 256);
            p = DAT_0056bee8[0];
            while (p != 0) {
                a0b = p[0];
                if (a0b != 0) { arr[cnt] = a0b; cnt++; }
                p = (int *)p[1];
            }
        }
        for (i = 0; i < cnt; i++) FUN_00330770(arr[i], 25);
        FUN_00330770((int)arr, 9);
        return;
    }
    case 13: {
        int *p; int *arr; int cnt; int i;
        p = DAT_00568e58[0];
        arr = (int *)FUN_00330730(DAT_0056ba80[0] * 4, 9);
        cnt = 0;
        if (arr != 0) {
            while (p != 0) {
                if (p[2] != 0) { arr[cnt] = p[2]; cnt++; }
                p = (int *)p[5];
            }
        }
        for (i = 0; i < cnt; i++) FUN_00330770(arr[i], 25);
        FUN_00330770((int)arr, 9);
        return;
    }
    case 3: {
        int *p; int *arr; int cnt; int i;
        p = DAT_00562d88[0];
        arr = (int *)FUN_00330730(DAT_0056ba48[0] * 4, 9);
        cnt = 0;
        if (arr != 0) {
            while (p != 0) {
                if (p[0] != 0) { arr[cnt] = p[0]; cnt++; }
                p = (int *)p[1];
            }
        }
        for (i = 0; i < cnt; i++) FUN_00330770(arr[i], 25);
        FUN_00330770((int)arr, 9);
        return;
    }
    case 10: {
        int *p; int *arr; int cnt; int i;
        p = DAT_0056c0c8[0];
        arr = (int *)FUN_00330730(DAT_0056ba50[0] * 4, 9);
        cnt = 0;
        if (arr != 0) {
            while (p != 0) {
                if (p[10] != 0) { arr[cnt] = p[10]; cnt++; }
                p = (int *)p[6];
            }
        }
        for (i = 0; i < cnt; i++) FUN_00330770(arr[i], 25);
        FUN_00330770((int)arr, 9);
        return;
    }
    case 9: {
        int *p; int *arr; int cnt; int i;
        p = DAT_0056bf50[0];
        arr = (int *)FUN_00330730(DAT_0056ba58[0] * 4, 9);
        cnt = 0;
        if (arr != 0) {
            while (p != 0) {
                if (p[0] != 0) { arr[cnt] = p[0]; cnt++; }
                p = (int *)p[1];
            }
        }
        for (i = 0; i < cnt; i++) FUN_00330770(arr[i], 25);
        FUN_00330770((int)arr, 9);
        return;
    }
    case 7: {
        int *p; int *arr; int cnt; int i;
        p = DAT_005691b8[0];
        arr = (int *)FUN_00330730(DAT_0056ba60[0] * 4, 9);
        cnt = 0;
        if (arr != 0) {
            while (p != 0) {
                if (p[2] != 0) { arr[cnt] = p[2]; cnt++; }
                p = (int *)p[3];
            }
        }
        for (i = 0; i < cnt; i++) FUN_00330770(arr[i], 25);
        FUN_00330770((int)arr, 9);
        return;
    }
    case 8: {
        int *p; int *arr; int cnt; int i;
        p = DAT_005691c0[0];
        arr = (int *)FUN_00330730(DAT_0056ba68[0] * 4, 9);
        cnt = 0;
        if (arr != 0) {
            while (p != 0) {
                if (p[0] != 0) { arr[cnt] = p[0]; cnt++; }
                p = (int *)p[1];
            }
        }
        for (i = 0; i < cnt; i++) FUN_00330770(arr[i], 25);
        FUN_00330770((int)arr, 9);
        return;
    }
    case 0: case 1: case 2:
        DAT_00490cc0[arg0] = -1;
        return;
    case 4: case 5: case 6:
        DAT_00490c70[0] = -1;
    default:
        return;
    }
}
