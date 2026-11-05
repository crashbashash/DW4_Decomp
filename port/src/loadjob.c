#include "dw4/loadjob.h"
#include <pthread.h>
#include <stdlib.h>

struct dw4_loadjob {
    pthread_t thread;
    pthread_mutex_t mutex;
    dw4_load_work work;
    void *context, *result;
    int threaded, done;
};

static void *run(void *arg)
{
    dw4_loadjob *j = arg;
    void *result = j->work(j->context);
    pthread_mutex_lock(&j->mutex);
    j->result = result;
    j->done = 1;
    pthread_mutex_unlock(&j->mutex);
    return NULL;
}

dw4_loadjob *dw4_loadjob_start(dw4_load_work work, void *context, int threaded)
{
    dw4_loadjob *j;
    if (!work || !(j = calloc(1, sizeof *j))) return NULL;
    j->work = work; j->context = context;
    if (pthread_mutex_init(&j->mutex, NULL)) { free(j); return NULL; }
    j->threaded = threaded;
    if (threaded && pthread_create(&j->thread, NULL, run, j)) {
        pthread_mutex_destroy(&j->mutex); free(j); return NULL;
    }
    return j;
}

int dw4_loadjob_poll(dw4_loadjob *j, void **result)
{
    int done;
    if (!j) return 0;
    if (!j->threaded && !j->done) run(j);
    pthread_mutex_lock(&j->mutex);
    done = j->done;
    if (done && result) *result = j->result;
    pthread_mutex_unlock(&j->mutex);
    return done;
}

void *dw4_loadjob_close(dw4_loadjob *j)
{
    void *result;
    if (!j) return NULL;
    if (j->threaded) pthread_join(j->thread, NULL);
    result = j->result;
    pthread_mutex_destroy(&j->mutex);
    free(j);
    return result;
}
