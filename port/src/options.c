#define _POSIX_C_SOURCE 200809L
#include "dw4/options.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#include <direct.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#else
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

static dw4_options g_options = {0, 1}, saved = {0, 1};
static char config_path[4096];
static const char *keys[] = {"camera", "light"};
static const char *values[][2] = {{"near", "far"}, {"soft", "hard"}};

dw4_options *dw4_options_get(void) { return &g_options; }
const char *dw4_options_path(void) { return config_path; }

#ifdef _WIN32
static wchar_t *wide(const char *s)
{
    int n = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, -1, NULL, 0);
    wchar_t *w = n ? malloc((size_t)n * sizeof(*w)) : NULL;
    if (w) MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s, -1, w, n);
    return w;
}
static FILE *open_file(const char *p, const char *mode)
{
    wchar_t *w = wide(p), *m = wide(mode);
    FILE *f = w && m ? _wfopen(w, m) : NULL;
    free(w); free(m); return f;
}
static int make_dir(const char *p)
{
    wchar_t *w = wide(p); int r = w ? _wmkdir(w) : -1; free(w); return r;
}
static int replace_file(const char *a, const char *b)
{
    wchar_t *wa = wide(a), *wb = wide(b);
    int r = wa && wb && MoveFileExW(wa, wb, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) ? 0 : -1;
    if (r < 0) errno = EIO;
    free(wa); free(wb); return r;
}
static void remove_file(const char *p) { wchar_t *w = wide(p); if (w) _wremove(w); free(w); }
#else
#define open_file fopen
#define make_dir(p) mkdir(p, 0700)
#define replace_file rename
#define remove_file remove
#endif

static int error(const char *operation)
{
    fprintf(stderr, "dw4: config %s failed: %s (%s)\n", operation, config_path, strerror(errno));
    return -1;
}

/* Keep raw bytes for writing: no normalization of comments, whitespace or line endings. */
static int read_file(char **out)
{
    FILE *f = open_file(config_path, "rb");
    size_t used = 0, cap = 4096;
    char *s;
    if (!f) {
        if (errno != ENOENT) return error("read");
        *out = calloc(1, 1); return *out ? 1 : error("allocate");
    }
    s = malloc(cap);
    if (!s) { fclose(f); return error("allocate"); }
    for (;;) {
        size_t n = fread(s + used, 1, cap - used - 1, f);
        used += n;
        if (ferror(f)) { free(s); fclose(f); return error("read"); }
        if (feof(f)) break;
        if (cap > (size_t)-1 / 2) { free(s); fclose(f); errno = ENOMEM; return error("allocate"); }
        cap *= 2;
        char *next = realloc(s, cap);
        if (!next) { free(s); fclose(f); return error("allocate"); }
        s = next;
    }
    fclose(f);
    if (memchr(s, 0, used)) { free(s); errno = EINVAL; return error("read (embedded NUL)"); }
    s[used] = 0; *out = s; return 0;
}

static const char *skip_space(const char *p, const char *end)
{ while (p < end && (*p == ' ' || *p == '\t' || *p == '\r')) ++p; return p; }
static int equal(const char *a, const char *end, const char *b)
{
    while (end > a && isspace((unsigned char)end[-1])) --end;
    return (size_t)(end - a) == strlen(b) && !memcmp(a, b, (size_t)(end - a));
}
/* Return known key index and the value span; comments start at ; or # after whitespace. */
static int parse_line(const char *line, const char *end, int *section,
                      const char **value, const char **value_end)
{
    const char *p = skip_space(line, end), *eq, *q;
    if (p == end || *p == ';' || *p == '#') return -1;
    if (*p == '[') {
        q = memchr(p, ']', (size_t)(end - p));
        *section = q && equal(p + 1, q, "options");
        return -1;
    }
    if (!*section || !(eq = memchr(p, '=', (size_t)(end - p)))) return -1;
    int key = equal(p, eq, keys[0]) ? 0 : equal(p, eq, keys[1]) ? 1 : -1;
    if (key < 0) return -1;
    *value = skip_space(eq + 1, end);
    q = *value;
    while (q < end && !((*q == ';' || *q == '#') && (q == *value || isspace((unsigned char)q[-1])))) ++q;
    while (q > *value && isspace((unsigned char)q[-1])) --q;
    *value_end = q;
    return key;
}

int dw4_options_load(const char *path)
{
    char *text;
    char requested[sizeof(config_path)];
    int section = 0, r;
    /* The caller may pass dw4_options_path() itself. */
    if (path) {
        if (strlen(path) >= sizeof(requested)) { errno = ENAMETOOLONG; return error("path"); }
        strcpy(requested, path);
    }
    config_path[0] = 0; g_options = (dw4_options){0, 1}; saved = g_options;
    if (!path) return 0;
    strcpy(config_path, requested);
    r = read_file(&text);
    if (r < 0) return -1;
    if (r == 1) { free(text); saved = (dw4_options){-1, -1}; return dw4_options_save(); }
    const char *p = text;
    if (!strncmp(p, "\xef\xbb\xbf", 3)) p += 3;
    while (*p) {
        const char *end = strchr(p, '\n'), *v, *ve;
        if (!end) end = p + strlen(p);
        int k = parse_line(p, end, &section, &v, &ve);
        if (k >= 0) {
            int n = equal(v, ve, values[k][0]) ? 0 : equal(v, ve, values[k][1]) ? 1 : -1;
            if (n < 0) {
                fprintf(stderr, "dw4: invalid [options] %s in %s; using %s\n", keys[k], config_path, values[k][k]);
                n = k; /* Near / Hard */
            }
            if (k == 0) g_options.camera_far = n; else g_options.light_hard = n;
        }
        p = *end ? end + 1 : end;
    }
    free(text); saved = g_options; return 0;
}

static int parents(void)
{
    char path[sizeof(config_path)]; strcpy(path, config_path);
    char *start = path + 1;
#ifdef _WIN32
    /* Redirected Known Folders can be UNC: the server/share is an existing root. */
    if ((path[0] == '\\' || path[0] == '/') && (path[1] == '\\' || path[1] == '/')) {
        start = path + 2;
        for (int part = 0; part < 2; ++part) {
            while (*start && *start != '/' && *start != '\\') ++start;
            if (*start) ++start;
        }
    }
#endif
    for (char *p = start; *p; ++p) {
#ifdef _WIN32
        if (*p != '/' && *p != '\\') continue;
        if (p == path + 2 && path[1] == ':') continue;
#else
        if (*p != '/') continue;
#endif
        char c = *p; *p = 0;
        if (make_dir(path) != 0 && errno != EEXIST) return error("mkdir");
        *p = c;
    }
    return 0;
}

int dw4_options_save(void)
{
    int changed[2] = {g_options.camera_far != saved.camera_far, g_options.light_hard != saved.light_hard};
    int current[2] = {g_options.camera_far, g_options.light_hard};
    int seen[2] = {0, 0}, section = 0, found_section = 0, failed = 0;
    char *text, temporary[sizeof(config_path) + 40];
    FILE *f;
    if (!config_path[0] || (!changed[0] && !changed[1])) return 0;
    if ((current[0] != 0 && current[0] != 1) || (current[1] != 0 && current[1] != 1)) {
        errno = EINVAL; return error("validate");
    }
    /* Reread on write so external edits to untouched settings/annotations survive. */
    if (read_file(&text) < 0) return -1;
    if (parents() < 0) { free(text); return -1; }
#ifdef _WIN32
    snprintf(temporary, sizeof(temporary), "%s.tmp.%lu", config_path, (unsigned long)GetCurrentProcessId());
    wchar_t *wtemp = wide(temporary);
    int fd = wtemp ? _wopen(wtemp, _O_CREAT | _O_EXCL | _O_WRONLY | _O_BINARY, _S_IREAD | _S_IWRITE) : -1;
    free(wtemp);
    f = fd < 0 ? NULL : _fdopen(fd, "wb");
    if (fd >= 0 && !f) { _close(fd); remove_file(temporary); }
#else
    snprintf(temporary, sizeof(temporary), "%s.tmp.XXXXXX", config_path);
    int fd = mkstemp(temporary);
    f = fd < 0 ? NULL : fdopen(fd, "wb");
    if (fd >= 0 && !f) { close(fd); remove_file(temporary); }
#endif
    if (!f) { free(text); return error("create temporary file"); }
    const char *p = text;
    if (!strncmp(p, "\xef\xbb\xbf", 3)) { fwrite(p, 1, 3, f); p += 3; }
    while (*p) {
        const char *end = strchr(p, '\n'), *v, *ve;
        if (!end) end = p + strlen(p);
        int k = parse_line(p, end, &section, &v, &ve);
        if (section) found_section = 1;
        if (k >= 0) seen[k] = 1;
        if (k >= 0 && changed[k]) {
            fwrite(p, 1, (size_t)(v - p), f);
            fputs(values[k][current[k]], f);
            if (ve == v && ve < end && (*ve == ';' || *ve == '#')) fputc(' ', f);
            fwrite(ve, 1, (size_t)(end - ve), f);
        } else fwrite(p, 1, (size_t)(end - p), f);
        if (*end) fputc('\n', f);
        p = *end ? end + 1 : end;
    }
    if ((changed[0] && !seen[0]) || (changed[1] && !seen[1])) {
        size_t len = strlen(text);
        if (len && text[len - 1] != '\n') fputc('\n', f);
        /* A repeated section is valid; append missing keys without moving existing lines. */
        if (!section || !found_section) fputs("[options]\n", f);
        for (int k = 0; k < 2; ++k)
            if (changed[k] && !seen[k]) fprintf(f, "%s=%s\n", keys[k], values[k][current[k]]);
    }
    free(text);
    if (fflush(f) != 0 || ferror(f)) failed = 1;
#ifdef _WIN32
    if (!failed && _commit(_fileno(f)) != 0) failed = 1;
#else
    if (!failed && fsync(fileno(f)) != 0) failed = 1;
#endif
    if (fclose(f) != 0) failed = 1;
    if (!failed && replace_file(temporary, config_path) != 0) failed = 1;
    if (failed) { int e = errno; remove_file(temporary); errno = e; return error("write/replace"); }
    saved = g_options; return 0;
}

int dw4_options_init(int portable)
{
    char path[4096], base[4096];
#ifdef _WIN32
    wchar_t wbase[4096];
    if (portable) {
        DWORD n = GetModuleFileNameW(NULL, wbase, 4096);
        if (!n || n >= 4096) return -1;
        wchar_t *slash = wcsrchr(wbase, L'\\'); if (!slash) return -1; *slash = 0;
    } else {
        PWSTR folder = NULL;
        if (FAILED(SHGetKnownFolderPath(&FOLDERID_LocalAppData, 0, NULL, &folder))) return -1;
        if (wcslen(folder) >= 4096) { CoTaskMemFree(folder); return -1; }
        wcscpy(wbase, folder); CoTaskMemFree(folder);
    }
    if (!WideCharToMultiByte(CP_UTF8, 0, wbase, -1, base, sizeof(base), NULL, NULL)) return -1;
    int n = snprintf(path, sizeof(path), "%s/%s/config.ini", base, portable ? "userdata/config" : "DW4/config");
#else
    int n;
    if (portable) {
        ssize_t len = readlink("/proc/self/exe", base, sizeof(base) - 1);
        if (len <= 0 || len >= (ssize_t)sizeof(base) - 1) return -1;
        base[len] = 0; char *slash = strrchr(base, '/'); if (!slash) return -1; *slash = 0;
        n = snprintf(path, sizeof(path), "%s/userdata/config/config.ini", base);
    } else {
        const char *xdg = getenv("XDG_CONFIG_HOME"), *home = getenv("HOME");
        if (xdg && xdg[0] == '/') n = snprintf(path, sizeof(path), "%s/dw4/config.ini", xdg);
        else {
            if (!home || home[0] != '/') { struct passwd *pw = getpwuid(getuid()); home = pw ? pw->pw_dir : NULL; }
            if (!home) { fprintf(stderr, "dw4: cannot resolve home for configuration\n"); return -1; }
            n = snprintf(path, sizeof(path), "%s/.config/dw4/config.ini", home);
        }
    }
#endif
    if (n < 0 || n >= (int)sizeof(path)) { fprintf(stderr, "dw4: configuration path too long\n"); return -1; }
    return dw4_options_load(path);
}
