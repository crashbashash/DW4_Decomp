struct TripleVectorState {
  char pad[52];
  int v52[4]; char f68; char pad2[3];
  int v72[5]; char f92; char f93; char pad3[2];
  int v96[4]; char f112; char pad4[3];
  int s116[4]; int s132[5]; int s152[4];
};
void FUN_0027eed0(struct TripleVectorState *o){
{ int a, b, c, d;
 d=o->s116[3];
 c=o->s116[2];
 b=o->s116[1];
 a=o->s116[0];
 o->v52[0]=a;
 o->v52[1]=b;
 o->v52[2]=c;
 o->v52[3]=d;
 o->f68=0; }
{ int a, b, c, d, e;
 e=o->s132[4];
 d=o->s132[3];
 c=o->s132[2];
 b=o->s132[1];
 a=o->s132[0];
 o->v72[0]=a;
 o->v72[1]=b;
 o->v72[2]=c;
 o->v72[3]=d;
 o->v72[4]=e;
 o->f92=0; o->f93=0; }
{ int a, b, c, d;
 d=o->s152[3];
 c=o->s152[2];
 b=o->s152[1];
 a=o->s152[0];
 o->v96[0]=a;
 o->v96[1]=b;
 o->v96[2]=c;
 o->v96[3]=d;
 o->f112=0; }
}
