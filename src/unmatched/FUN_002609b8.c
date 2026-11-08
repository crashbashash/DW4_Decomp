/* FUN_002608b0 fills text from source, strncat appends DAT_004ed8c0 within size, then
 * FUN_002608b0 fills from extra at the end of the text with 4 - length. */
extern char DAT_004ed8c0[];
int strlen(const char *s);
void FUN_002608b0(void *source, char *text, int size);
void strncat(char *text, const char *suffix, int size);

void FUN_002609b8(void *source, void *extra, char *text, int size) {
    FUN_002608b0(source, text, size);
    strncat(text, DAT_004ed8c0, (size - strlen(text)) - 1);
    FUN_002608b0(extra, text + strlen(text), 4 - strlen(text));
}
