int strlen(char *);
int strncmp(char *, char *, int);
char *FUN_0012aff0(char *, char *);
struct F { char pad12[12]; char *f12; };
struct O { char pad28[28]; char *f28; };
struct Ls { char pad8[8]; struct O **data; int n; };
struct R { char pad24[24]; struct Ls *f24; };
struct F *igMetaObject_GetFieldAt(struct O *, int);
int igMetaObject_GetFieldCount(struct O *);
int strcmp(char *, char *);
extern char *DAT_004c22b8[4];
extern char *DAT_004c22c0[4];
extern struct R *DAT_00586dc8[4];
struct F *igMetaField_FindByName(int arg0, char *arg1) {
    struct F *found; char *q; char *s8; int n; int i; int j; int fc; struct O *o; struct Ls *list; char *nm; struct F *f;
    found = 0;
    if (strncmp(arg1, DAT_004c22b8[0], strlen(DAT_004c22b8[0])) == 0) {
        arg1 = arg1 + strlen(DAT_004c22b8[0]);
        q = FUN_0012aff0(arg1, DAT_004c22c0[0]);
        if (q != 0) {
            s8 = q + strlen(DAT_004c22c0[0]);
            i = 0;
            list = DAT_00586dc8[0]->f24;
            n = list->n;
            goto test;
body:
            o = 0;
            if (i < list->n) { o = list->data[i]; }
            nm = o->f28;
            if (strncmp(nm, arg1, strlen(nm)) == 0) {
                fc = igMetaObject_GetFieldCount(o);
                j = 0;
                goto t2;
b2:
                f = igMetaObject_GetFieldAt(o, j);
                if (strcmp(f->f12, s8) == 0) {
                    found = f;
                    goto next;
                }
                j++;
t2:
                if (j < fc) goto b2;
            }
next:
            i++;
test:
            if (i < n) goto body;
        }
    }
    return found;
}
