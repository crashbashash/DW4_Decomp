class igResult {
public:
    int v;
    igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
};

extern igResult DAT_004fb410;
extern "C" {
igResult FUN_0032d4b0(const char *path);
extern bool GPR_00554bec;
bool FUN_00259cd0(const char *path);
}

bool FUN_00259cd0(const char *path) {
    return GPR_00554bec = FUN_0032d4b0(path) == DAT_004fb410;
}
