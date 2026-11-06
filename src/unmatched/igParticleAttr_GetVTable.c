typedef struct Q { char pad4[4]; int f4; } Q;
int igObject_Destroy(void *);
typedef struct { int *vt; int w[3]; Q *s; int tail[4]; } Obj;
 int igObject_InitHeader(void *);
 extern int DAT_00523280[4];
extern void * DAT_00586dc8[4];
 int igParticleAttr_GetVTable(void) {
     Obj o;
     int r;
     Q *q;

     igObject_InitHeader(&o);
     o.vt = &DAT_00523280[0];
     o.s = 0;
     r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
     o.vt = &DAT_00523280[0];
     if (&o.s != 0) {
         q = o.s;
         if (q != 0) {
             q->f4 -= 1;
             if ((q->f4 & 0x7fffff) == 0) {
                 igObject_Destroy(q);
             }
         }
     }
     return r;
 }
 