class Alloc {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void *Alloc53(int size, int align);
};
class Sink {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void Sink50(void *buf, int n);
};
struct Item { char p[20]; char *name; };
struct IList { int p0; int p4; int count; int p12; Item **data; };
struct Self {
    char p0[24]; IList *list;
    char p1[140]; unsigned char flag168;
    char p2[35]; Sink *sink204;
    char p3[5]; unsigned char b213;
    char p4[10]; int *buf224; int size228;
    char p5[48]; Alloc *alloc280;
};
extern "C" {
extern int DAT_004fb410[4];
int strcpy(char *, char *);
int strlen(char *);
void FUN_002e4c90(int *out, Self *self) {
    IList *l = self->list;
    int n, i, k;
    if (l != 0) { n = l->count; if (n > 0) {
        char *p;
        int *q;
        int total;
        self->b213 = 1;
        total = (n + 3) * 4;
        self->size228 = total;
        for (i = 0; i < n; i++) {
            self->size228 = self->size228 + (strlen(self->list->data[i]->name) + 1);
        }
        self->buf224 = (int *)self->alloc280->Alloc53(self->size228, 16);
        self->buf224[0] = self->size228;
        self->buf224[1] = 1;
        self->buf224[2] = n;
        q = self->buf224 + 3;
        for (i = 0; i < n; i++) {
            q[i] = strlen(self->list->data[i]->name) + 1;
        }
        p = (char *)self->buf224 + total;
        for (k = 0; k < n; k++) {
            strcpy(p, self->list->data[k]->name);
            p += strlen(p) + 1;
        }
        if (self->flag168 != 0) {
            self->sink204->Sink50(self->buf224, n + 2);
        }
    goto done; } } self->b213 = 0; done:
    *out = DAT_004fb410[0];
}
}
