#ifndef DW4_IGRESULT_H
#define DW4_IGRESULT_H

/* igResult: the status a call returns by value. */
class igResult {
public:
    int v;
    igResult() {}
    igResult(int x) : v(x) {}
    igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    bool operator!=(const igResult &o) const { return v != o.v; }
    inline bool failed() const;
    int get() { return v; }
};
extern "C" const igResult g_resultSuccess;
extern "C" const igResult g_resultFailure;

#endif
