struct NodeProcEntry { int meta; int proc; };
struct NodeProcTable { NodeProcEntry e[34]; } __attribute__((aligned(16)));
extern const NodeProcTable DAT_0048d8f0;
extern int DAT_00561280;
extern int DAT_005612b0;
extern int DAT_005612d8;
extern int DAT_005612e0;
extern int DAT_00561308;
extern int DAT_00561570;
extern int DAT_00561578;
extern int DAT_005615d0;
extern int DAT_005615d8;
extern int DAT_00561620;
extern int DAT_005617a8;
extern int DAT_00561818;
extern int DAT_00561860;
extern int DAT_00561868;
extern int DAT_00561870;
extern int DAT_00561878;
extern int DAT_00561888;
extern int DAT_00561898;
extern int DAT_005618d8;
extern int DAT_005618e8;
extern int DAT_005618f8;
extern int DAT_00561908;
extern int DAT_00561910;
extern int DAT_00561920;
extern int DAT_00561a38;
extern int DAT_00561a98;
extern int DAT_00561bd8;
extern int DAT_00561ca0;
extern int DAT_00561e98;
extern int DAT_00561ee8;
extern int DAT_00561f38;
extern int DAT_00561f68;
extern int DAT_00562078;
extern int DAT_00562488;

extern "C" {
void FUN_001e02f0(void *, void *);
int igNode_GetMetaObject(void);
int FUN_002fe290(void *, int);
void FUN_001e06c0(void *, void *, int);
void FUN_001b68c0(void *self, void *meta);
}
void FUN_001b68c0(void *self, void *meta) {
    FUN_001e02f0(self, meta);
    if (FUN_002fe290(meta, igNode_GetMetaObject()) != 0) {
        NodeProcTable t = DAT_0048d8f0;
        int i;
        t.e[0].meta = DAT_00562488;
        t.e[1].meta = DAT_00561620;
        t.e[2].meta = DAT_005615d0;
        t.e[3].meta = DAT_00561bd8;
        t.e[4].meta = DAT_005615d8;
        t.e[5].meta = DAT_00561a98;
        t.e[6].meta = DAT_00561920;
        t.e[7].meta = DAT_00561908;
        t.e[8].meta = DAT_00561910;
        t.e[9].meta = DAT_00561860;
        t.e[10].meta = DAT_00561868;
        t.e[11].meta = DAT_00561e98;
        t.e[12].meta = DAT_00561ee8;
        t.e[13].meta = DAT_005618f8;
        t.e[14].meta = DAT_00561878;
        t.e[15].meta = DAT_00561870;
        t.e[16].meta = DAT_00561898;
        t.e[17].meta = DAT_005618d8;
        t.e[18].meta = DAT_005618e8;
        t.e[19].meta = DAT_00561a38;
        t.e[20].meta = DAT_005617a8;
        t.e[21].meta = DAT_00561578;
        t.e[22].meta = DAT_00561570;
        t.e[23].meta = DAT_00561f38;
        t.e[24].meta = DAT_00561818;
        t.e[25].meta = DAT_00562078;
        t.e[26].meta = DAT_005612b0;
        t.e[27].meta = DAT_00561f68;
        t.e[28].meta = DAT_00561308;
        t.e[29].meta = DAT_00561280;
        t.e[30].meta = DAT_005612d8;
        t.e[31].meta = DAT_00561ca0;
        t.e[32].meta = DAT_00561888;
        t.e[33].meta = DAT_005612e0;
        for (i = 0; i < 34; i++) {
            NodeProcEntry *e = &t.e[i];
            if (e->meta != 0 && FUN_002fe290(meta, e->meta) != 0) {
                FUN_001e06c0(self, meta, e->proc);
                return;
            }
        }
    }
}
