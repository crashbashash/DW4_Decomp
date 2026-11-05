#define _POSIX_C_SOURCE 200809L
#include "dw4/options.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void put(const char *path, const char *text)
{
    FILE *f = fopen(path, "wb"); assert(f); assert(fputs(text, f) >= 0); assert(!fclose(f));
}
static void expect(const char *path, const char *text)
{
    char buffer[8192]; FILE *f = fopen(path, "rb"); assert(f);
    size_t n = fread(buffer, 1, sizeof(buffer) - 1, f); buffer[n] = 0;
    assert(!ferror(f)); fclose(f); assert(!strcmp(buffer, text));
}
int main(int argc, char **argv)
{
    if (argc > 1) {
        int r = dw4_options_init(!strcmp(argv[1], "portable"));
        printf("%s\n", dw4_options_path()); return r < 0;
    }
    char root[] = "/tmp/dw4-options-XXXXXX", path[4096], blocker[4096];
    assert(mkdtemp(root)); snprintf(path, sizeof(path), "%s/config.ini", root);
    assert(!dw4_options_load(path));
    expect(path, "[options]\ncamera=near\nlight=hard\n");
    assert(dw4_options_get()->camera_far == 0 && dw4_options_get()->light_hard == 1);
    dw4_options_get()->camera_far = 1; dw4_options_get()->light_hard = 0;
    assert(!dw4_options_save()); assert(!dw4_options_load(path));
    assert(!dw4_options_load(dw4_options_path()));
    assert(dw4_options_get()->camera_far == 1 && dw4_options_get()->light_hard == 0);
    const char *annotated = "\xef\xbb\xbf; my config\r\n[options]\r\n  camera = far  ; keep this\r\nlight=soft # lighting\r\nextra=yes\r\n[future]\r\nx=123";
    put(path, annotated); assert(!dw4_options_load(path)); assert(!dw4_options_save()); expect(path, annotated);
    /* External edits since startup must survive when only the other setting changes. */
    put(path, "\xef\xbb\xbf; my config\r\n[options]\r\n  camera = far  ; keep this\r\nlight=hard # edited outside\r\nextra=yes\r\n[future]\r\nx=123");
    dw4_options_get()->camera_far = 0; assert(!dw4_options_save());
    expect(path, "\xef\xbb\xbf; my config\r\n[options]\r\n  camera = near  ; keep this\r\nlight=hard # edited outside\r\nextra=yes\r\n[future]\r\nx=123");
    put(path, "[options]\ncamera=far\nlight=INVALID\n"); assert(!dw4_options_load(path));
    assert(dw4_options_get()->camera_far == 1 && dw4_options_get()->light_hard == 1);
    dw4_options_get()->camera_far = 0; assert(!dw4_options_save());
    expect(path, "[options]\ncamera=near\nlight=INVALID\n");
    put(path, "[options]\ncamera= ; empty with comment\nlight=hard\n");
    assert(!dw4_options_load(path)); dw4_options_get()->camera_far = 1;
    assert(!dw4_options_save());
    expect(path, "[options]\ncamera= far ; empty with comment\nlight=hard\n");
    assert(!dw4_options_load(path)); assert(dw4_options_get()->camera_far == 1);
    put(path, "[options]\ncamera=far\ncamera=near ; last wins\n[other]\ncustom=123\n");
    assert(!dw4_options_load(path)); assert(dw4_options_get()->camera_far == 0);
    dw4_options_get()->camera_far = 1; dw4_options_get()->light_hard = 0; assert(!dw4_options_save());
    expect(path, "[options]\ncamera=far\ncamera=far ; last wins\n[other]\ncustom=123\n[options]\nlight=soft\n");
    /* Long unknown lines are preserved rather than truncated by a line buffer. */
    char long_text[7000]; memset(long_text, 'x', sizeof(long_text));
    memcpy(long_text, ";", 1); strcpy(long_text + 6000, "\n[options]\ncamera=far\nlight=soft\n");
    put(path, long_text); assert(!dw4_options_load(path)); dw4_options_get()->camera_far = 0;
    assert(!dw4_options_save()); strcpy(long_text + 6000, "\n[options]\ncamera=near\nlight=soft\n"); expect(path, long_text);
    /* Replacement failure retains original bytes and can be retried. */
    assert(!unlink(path)); assert(!mkdir(path, 0700)); assert(dw4_options_load(path) < 0);
    assert(!rmdir(path)); put(path, "[options]\ncamera=near\nlight=hard\n"); assert(!dw4_options_load(path));
    dw4_options_get()->camera_far = 1;
    snprintf(blocker, sizeof(blocker), "%s/old.ini", root); assert(!rename(path, blocker)); assert(!mkdir(path, 0700));
    assert(dw4_options_save() < 0); expect(blocker, "[options]\ncamera=near\nlight=hard\n");
    assert(!rmdir(path)); assert(!rename(blocker, path)); assert(!dw4_options_save());
    expect(path, "[options]\ncamera=far\nlight=hard\n");
    if (geteuid() != 0) {
        dw4_options_get()->camera_far = 0;
        assert(!chmod(root, 0500)); assert(dw4_options_save() < 0);
        expect(path, "[options]\ncamera=far\nlight=hard\n");
        assert(!chmod(root, 0700)); assert(!dw4_options_save());
        expect(path, "[options]\ncamera=near\nlight=hard\n");
    }
    /* Entirely unreadable input cannot be rewritten silently. */
    FILE *f = fopen(path, "wb"); assert(f); assert(fwrite("bad\0data", 1, 8, f) == 8); fclose(f);
    assert(dw4_options_load(path) < 0);
    assert(!dw4_options_load(NULL)); assert(!dw4_options_save());
    unlink(path); rmdir(root); puts("options persistence: ok"); return 0;
}
