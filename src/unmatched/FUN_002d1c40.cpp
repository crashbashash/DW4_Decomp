extern "C" {
int *getenv(...);
int FUN_002eb010(...);
void *StringPool_Construct(...);
char *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
extern int DAT_004f9460[4];
extern int DAT_004f9468[4];
extern int DAT_004f9470[4];
extern void *DAT_00586f20[4];
}
struct igString {
    char *p;
    igString() : p(0) {}
    ~igString() {
        char *s = p;
        if (s) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
    }
    void adopt(char *text) {
        char *s = p;
        if (s) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        p = text;
    }
    void assign(const igString &other) {
        char *o = other.p;
        char *s;
        if (o) {
            *(int *)(o - 4) = *(int *)(o - 4) + 1;
        }
        s = p;
        if (s) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        p = other.p;
    }
};
struct Pool { static inline void *get() {
    if (DAT_00586f20[0] == 0) {
        void *p = (void *)FUN_002eb010(16);
        if (p != 0) {
            p = StringPool_Construct(p);
        }
        DAT_00586f20[0] = p;
    }
    return DAT_00586f20[0];
} };
struct Obj { char p[920]; igString m920; igString m924; };
extern "C" void FUN_002d1c40(Obj *arg0);
void FUN_002d1c40(Obj *arg0) {
    igString env;
    char *text = (char *)getenv(DAT_004f9460);
    text = StringPool_Intern(Pool::get(), text);
    env.adopt(text);
    arg0->m920.assign(env);
    text = StringPool_Intern(Pool::get(), DAT_004f9468);
    arg0->m924.adopt(text);
    text = StringPool_Intern(Pool::get(), DAT_004f9470);
    arg0->m924.adopt(text);
}
