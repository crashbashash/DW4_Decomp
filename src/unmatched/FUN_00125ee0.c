/* Accepts only the "C" or "" locale, records category and locale in the reent block and returns
 * "C"; any other locale returns 0 (newlib _setlocale_r shape; name is a hypothesis). */
typedef struct Reent {
    char f0[48];
    int currentCategory;
    const char *currentLocale;
} Reent;

int igStrCmp(const char *a, const char *b);
extern char DAT_004d3ec0[]; /* "C" */
extern char DAT_004d3eb0[]; /* "" */

char *FUN_00125ee0(Reent *reent, int category, const char *locale) {
    if (locale) {
        if (igStrCmp(locale, DAT_004d3ec0) && igStrCmp(locale, DAT_004d3eb0)) {
            return 0;
        }
        reent->currentCategory = category;
        reent->currentLocale = locale;
    }
    return DAT_004d3ec0;
}
