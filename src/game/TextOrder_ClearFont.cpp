/* 0x003ebdc0 — passes the first two arguments through and appends table[arg2].f[arg3] (80-byte rows) to the worker call.
 * C++ keeps the call a real jal. */
struct E { int f[20]; };
extern "C" {
int TextOrder_PublishLine(int, int, int);
extern E DAT_004ceb30[4];
void TextOrder_ClearFont(int arg0, int arg1, int arg2, int arg3);
}
void TextOrder_ClearFont(int arg0, int arg1, int arg2, int arg3) {
    TextOrder_PublishLine(arg0, arg1, DAT_004ceb30[arg2].f[arg3]);
}
