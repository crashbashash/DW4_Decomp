int igMatrix44f_SetIdentity();
int FUN_001903d0();
int FUN_00191f30();
int FUN_001fbce0();
int List_Resize();
int Matrix44_Copy();
typedef struct St { char pad0[8]; int n; int cap; char *data; } St;
typedef struct O { char pad[972]; St *s972; St *s976; St *s980; St *s984; St *s988; St *s992; St *s996; St *s1000; St *s1004; St *s1008; St *s1012; St *s1016; } O;
#define SET(l, m) { \
    St *s = (l); \
    int n = s->n; \
    int n1; \
    if (n == 0) { \
        n1 = n + 1; \
        if (n < s->cap) ((volatile St *)s)->n = ((volatile St *)s)->n + 1; \
        else List_Resize(s, n1, 0x40); \
        Matrix44_Copy(s->data + (n << 6), m); \
    } else { \
        Matrix44_Copy(s->data + ((((volatile St *)s)->n - 1) << 6), m); \
    } }
#define SETB(l, m) { \
    int n; \
    St *s = (l); \
    int n1; \
    n = s->n; \
    if (n == 0) { \
        n1 = n + 1; \
        if (n < s->cap) ((volatile St *)s)->n = ((volatile St *)s)->n + 1; \
        else List_Resize(s, n1, 0x40); \
        Matrix44_Copy(s->data + (n << 6), m); \
    } else { \
        Matrix44_Copy(s->data + ((((volatile St *)s)->n - 1) << 6), m); \
    } }
void FUN_00172b00(O *arg0, int arg1, char *arg2) {
    int sp15C, sp158, sp154, sp150;
    char sp110[64];
    char spD0[64];
    char sp90[64];
    char sp50[64];
    St *t;
    switch (arg1) {
    case 0:
        SET(arg0->s972, arg2)
        t = arg0->s972;
        FUN_001fbce0(3, t->data + ((t->n - 1) << 6));
        break;
    case 1:
        SET(arg0->s976, arg2)
        t = arg0->s976;
        FUN_001fbce0(0, t->data + ((t->n - 1) << 6));
        break;
    case 2:
        SET(arg0->s980, arg2)
        t = arg0->s980;
        FUN_001fbce0(4, t->data + ((t->n - 1) << 6));
        break;
    case 10:
        igMatrix44f_SetIdentity(sp110);
        SETB(arg0->s988, arg2)
        FUN_00191f30(&sp15C, sp110, arg2);
        FUN_001903d0(sp110);
        SET(arg0->s1004, sp110)
        break;
    case 11:
        igMatrix44f_SetIdentity(spD0);
        SETB(arg0->s992, arg2)
        FUN_00191f30(&sp158, spD0, arg2);
        FUN_001903d0(spD0);
        SET(arg0->s1008, spD0)
        break;
    case 12:
        igMatrix44f_SetIdentity(sp90);
        SETB(arg0->s996, arg2)
        FUN_00191f30(&sp154, sp90, arg2);
        FUN_001903d0(sp90);
        SET(arg0->s1012, sp90)
        break;
    case 13:
        igMatrix44f_SetIdentity(sp50);
        SETB(arg0->s1000, arg2)
        FUN_00191f30(&sp150, sp50, arg2);
        FUN_001903d0(sp50);
        SET(arg0->s1016, sp50)
        break;
    }
}
