extern "C" {
typedef struct N { int p0; int p4; char *name; } N;
typedef struct L { int p0; int p4; int count; int pc; N **data; } L;
typedef struct S { int p0; int p4; char *name; L *parents; } S;
int strcat(char *, void *);
int strcpy(char *, char *);
extern int DAT_004e0858[4];
extern int DAT_004fff70[4];
void FUN_00333630(S *arg0, char *arg1) {
    int i;
    int off;
    if (arg1 != 0) {
        if (arg0->parents == 0) {
            strcpy(arg1, arg0->name ? arg0->name : (char *)&DAT_004e0858[0]);
            return;
        }
        *arg1 = 0;
        i = 0;
        if (0 < arg0->parents->count) {
            off = 0;
            do {
                N *nd = *(N **)((char *)arg0->parents->data + off);
                strcat(arg1, nd->name ? nd->name : (char *)&DAT_004e0858[0]);
                strcat(arg1, &DAT_004fff70[0]);
                i += 1;
                off += 4;
            } while (i < arg0->parents->count);
        }
        strcat(arg1, arg0->name ? arg0->name : (char *)&DAT_004e0858[0]);
    }
}
}
