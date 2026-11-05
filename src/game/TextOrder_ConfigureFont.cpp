struct E { int w[20]; };
extern "C" {
int TextOrder_Configure(...);
extern E DAT_004ceb30[4];
void TextOrder_ConfigureFont(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
}
void TextOrder_ConfigureFont(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    TextOrder_Configure(arg0, arg1, DAT_004ceb30[arg2].w[arg3], arg4, arg5, arg6);
}
