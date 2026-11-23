void Gap__Gui__igTextElement__vfunc_23(igTextElement *self) {
}

void Gap__Gui__igTextElement__vfunc_24(O_457e10 *arg0) {
    int n;
    int i;
    struct Q_457e10 *q = (struct Q_457e10 *)arg0->m->obj;
    if (q != 0) {
        n = q->count;
        for (i = 0; i < n; i++) {
            arg0->m->obj->vX(i, arg0->buf);
        }
    }
}

namespace Gap {
namespace Gui {

void igView::setModel(igModel *model)
{
    if (_model) {
        _model->removeView(this);
    }
    _model = model;

    if (_model) {
        _model->appendView(this);
    }
}
}
}

