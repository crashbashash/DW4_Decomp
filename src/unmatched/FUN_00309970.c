typedef struct Ob { int w0; unsigned rc; } Ob;
typedef struct L { char pad[8]; int count; int pad2; Ob **data; } L;
typedef struct S { char pad[16]; L *list; } S;
int igObject_IsKindOf(Ob *, int);
int List_RemoveWordAt(L *, int);
int igObject_Destroy(Ob *);
extern int DAT_00586140[4];
void FUN_00309970(S *self) {
    int i;
    L *l;
    int off;
    Ob *o;
    for (i = self->list->count - 1; i >= 0; i--) {
        off = i * 4;
        if (igObject_IsKindOf(*(Ob **)((char *)self->list->data + off), DAT_00586140[0]) != 0) {
            l = self->list;
            o = *(Ob **)((char *)l->data + off);
            if (o != 0) {
                o->rc = o->rc - 1;
                if ((o->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt(l, i);
            *(Ob **)((char *)l->data + l->count * 4) = 0;
        }
    }
}
