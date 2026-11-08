#include "dw4/newlib_reent.h"

int strcmp(const char *a, const char *b);
extern char C_locale[];
extern char empty_locale[];
extern struct lconv lconv;

char *_setlocale_r(struct _reent *ptr, int category, const char *locale)
{
    if (locale) {
        if (strcmp(locale, C_locale) && strcmp(locale, empty_locale)) {
            return 0;
        }
        ptr->_current_category = category;
        ptr->_current_locale = locale;
    }
    return C_locale;
}

struct lconv *_localeconv_r(struct _reent *ptr)
{
    return &lconv;
}

char *setlocale(int category, const char *locale)
{
    return _setlocale_r(_REENT, category, locale);
}

struct lconv *localeconv(void)
{
    return _localeconv_r(_REENT);
}
