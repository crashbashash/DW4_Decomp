int FUN_001b11b0();
int FUN_001b1250();
int FUN_001e07a0();
extern int DAT_0055ec68[4];
extern int DAT_0055efe8[4];

int FUN_001bc050(void *arg0, char *a, char *b){
  int r;
  void *q=*(void*volatile*)(b+52); int x=*(int volatile*)(a+96); 
  r=FUN_001e07a0(b);
  if(x==0) { FUN_001b11b0(q,DAT_0055efe8[0]); } else { FUN_001b1250(q,DAT_0055ec68[0],x-1); }
  return r==2?2:0;}
