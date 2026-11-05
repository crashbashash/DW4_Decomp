/* Test adapter for the recovered title controller. Events mirror externally
 * visible calls, not compiler registers. See verify_title_menu.py. */
#include "title-menu.h"
#include <string.h>
typedef struct { int code, arg[4]; } Event;
static Event events[128];
static int count, query[6];
static void emit(int code, int a, int b, int c, int d) {
    if (count < 128) events[count++] = (Event){code,{a,b,c,d}};
}
static void cb_model_tick(void *user) {
    (void)user; emit(0,0,0,0,0);
}
static int cb_opening_done(void *user) {
    (void)user; emit(1,0,0,0,0); return query[1];
}
static int cb_closing_done(void *user) {
    (void)user; emit(2,0,0,0,0); return query[2];
}
static int cb_model_exists(void *user, int a, int b) {
    (void)user; emit(3,a,b,0,0); return query[3];
}
static void cb_model_start(void *user, int a, int b, int c, int d) {
    (void)user; emit(4,a,b,c,d);
}
static void cb_model_play(void *user, int a, int b, int c, int d) {
    (void)user; emit(5,a,b,c,d);
}
static void cb_model_close(void *user, int a, int b, int c, int d) {
    (void)user; emit(6,a,b,c,d);
}
static void cb_text_show(void *user, int a, int b) {
    (void)user; emit(7,a,b,0,0);
}
static void cb_text_hide(void *user, int a) {
    (void)user; emit(8,a,0,0,0);
}
static void cb_message_begin(void *user, int a, int b, int c) {
    (void)user; emit(9,a,b,c,0);
}
static void cb_message_target(void *user, int a) {
    (void)user; emit(10,a,0,0,0);
}
static void cb_message_common(void *user, int a, int b) {
    (void)user; emit(11,a,b,0,0);
}
static void cb_push_string(void *user, int a) {
    (void)user; emit(12,a,0,0,0);
}
static void cb_push_int(void *user, int a) {
    (void)user; emit(13,a,0,0,0);
}
static void cb_message_end(void *user, int a) {
    (void)user; emit(14,a,0,0,0);
}
static void cb_message_send(void *user, int a, int b, int c, int d) {
    (void)user; emit(15,a,b,c,d);
}
static int cb_read_bool(void *user, int a) {
    (void)user; emit(16,a,0,0,0); return query[4];
}
static int cb_read_object(void *user, int a) {
    (void)user; emit(17,a,0,0,0); return query[5];
}
static void cb_set_record(void *user, int a, int b, int c) {
    (void)user; emit(18,a,b,c,0);
}
static void cb_options_valid(void *user) {
    (void)user; emit(19,0,0,0,0);
}
static const Dw4TitleApi api = {0, cb_model_tick, cb_opening_done, cb_closing_done, cb_model_exists, cb_model_start, cb_model_play, cb_model_close, cb_text_show, cb_text_hide, cb_message_begin, cb_message_target, cb_message_common, cb_push_string, cb_push_int, cb_message_end, cb_message_send, cb_read_bool, cb_read_object, cb_set_record, cb_options_valid};
int title_test_tick(Dw4TitleCtrl *ctrl, Dw4TitleOption *option, const Dw4TitleInput *pad,
                    int run, const int *answers, Event *out) {
    count=0; memcpy(query, answers, sizeof(query));
    dw4_title_tick(ctrl, option, pad, run, &api);
    memcpy(out, events, count*sizeof(Event)); return count;
}
