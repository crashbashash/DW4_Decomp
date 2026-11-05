typedef struct T{int w;int references;}T;
void igObject_Destroy(T*);
extern T *DAT_00561118[4];
extern T *DAT_00561120[4];
extern T *DAT_00561128[4];
extern T *DAT_00561130[4];
extern T *DAT_00561138[4];
extern T *DAT_00561140[4];
extern T *DAT_00561148[4];
extern T *DAT_00561150[4];
extern T *DAT_00561158[4];
extern T *DAT_00561160[4];
extern T *DAT_00561168[4];
extern T *DAT_00561170[4];
#define REL(g) { T *o=g[0]; if(o){ --o->references; if(((unsigned long long)(long long)o->references & 0x7fffffULL)==0) igObject_Destroy(o);} }
void FUN_0018f4a0(void){
  REL(DAT_00561118)
  REL(DAT_00561120)
  REL(DAT_00561128)
  REL(DAT_00561130)
  REL(DAT_00561138)
  REL(DAT_00561140)
  REL(DAT_00561148)
  REL(DAT_00561150)
  REL(DAT_00561158)
  REL(DAT_00561160)
  REL(DAT_00561168)
  REL(DAT_00561170)
}
