#include "dw4/reflected.h"
int igMatrix44f_SetIdentity();
int FUN_003cafa0();
int FUN_0044c110();
int igObject_InitHeader();
extern int DAT_00541170[4];
extern void * DAT_00586dc8[4];
int igGuiSystemModel_GetVTable(void) {
    struct igGuiSystemModel s;
    char *p;
    int r;
    p = (char *)&s;
    igObject_InitHeader(p);
    s._views = 0;
    *(int **)&s._vtable = &DAT_00541170[0];
    igMatrix44f_SetIdentity(s._viewMatrix);
    igMatrix44f_SetIdentity(((struct igGuiSystemModel *)p)->_projectionMatrix);
    ((struct igGuiSystemModel *)p)->_rootComponent = 0;
    ((struct igGuiSystemModel *)p)->_focusedComponent = 0;
    ((struct igGuiSystemModel *)p)->_componentUnderMouse = 0;
    ((struct igGuiSystemModel *)p)->_pushedComponent = 0;
    r = *(int *)((char *)&s + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&s._vtable = &DAT_00541170[0];
    FUN_003cafa0(&s._pushedComponent, -1);
    FUN_003cafa0(&s._componentUnderMouse, -1);
    FUN_003cafa0(&s._focusedComponent, -1);
    FUN_003cafa0(&s._rootComponent, -1);
    FUN_0044c110(&s, 0);
    return r;
}
