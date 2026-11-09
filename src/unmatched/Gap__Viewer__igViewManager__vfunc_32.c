#include "dw4/reflected.h"

typedef struct ViewModelEvent {
    int type;
    int arg;
    int data;
} ViewModelEvent;

extern int DAT_0058cd40;

void FUN_004578c0(igViewModel *model, ViewModelEvent *event);

int Gap__Viewer__igViewManager__vfunc_32(igViewManager *self, int width, int height)
{
    ViewModelEvent event;

    ((igViewModel *)self->_viewModel)->_ratio = (float)width / (float)height;
    event.type = 2;
    event.arg = 0;
    event.data = DAT_0058cd40;
    FUN_004578c0((igViewModel *)self->_viewModel, &event);
    return 0;
}
