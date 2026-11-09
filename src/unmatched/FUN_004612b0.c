#include "dw4/reflected.h"
typedef struct ViewerMessage { int kind; int arg; int id; } ViewerMessage;
extern int DAT_0058ca30[4];
extern int DAT_0058cb08[4];
void FUN_004578c0(igViewerParameters *parameters, ViewerMessage *message);
/* matching construct: 360 declaration and 120 statement orders */
void FUN_004612b0(igViewerSceneInfoManager *self) {
    ViewerMessage rising;
    ViewerMessage falling;
    ViewerMessage changed;
    int *operation;
    long long time;
    long long begin;
    long long end;
    long long length;
    igViewerParameters *parameters;
    parameters = (igViewerParameters *)self->_parameters;
    end = parameters->_endTime;
    begin = parameters->_beginTime;
    time = ((igInsightCore *)self->_insight)->_worldTime;
    length = end - begin;
    if (end != 0) {
        switch (parameters->_loopMode) {
        case 0:
            while (time > end) {
                time -= length;
            }
            while (time < begin) {
                time += length;
            }
            break;
        case 1:
            while (time > end + length) {
                time -= length * 2;
            }
            while (time < begin - length) {
                time += length * 2;
            }
            operation = &parameters->_timeOperation;
            if (*operation == 1 && time > end) {
                time = end * 2 - time;
                *operation = 2;
                rising.kind = 2;
                rising.arg = 0;
                rising.id = DAT_0058cb08[0];
                FUN_004578c0((igViewerParameters *)self->_parameters, &rising);
            }
            operation = &((igViewerParameters *)self->_parameters)->_timeOperation;
            if (*operation == 2 && time < begin) {
                time = begin * 2 - time;
                *operation = 1;
                falling.kind = 2;
                falling.arg = 0;
                falling.id = DAT_0058cb08[0];
                FUN_004578c0((igViewerParameters *)self->_parameters, &falling);
            }
            break;
        }
    }
    ((igViewerParameters *)self->_parameters)->_drawTime = time;
    changed.kind = 2;
    changed.arg = 0;
    changed.id = DAT_0058ca30[0];
    FUN_004578c0((igViewerParameters *)self->_parameters, &changed);
    ((igInsightCore *)self->_insight)->_worldTime = time;
}
