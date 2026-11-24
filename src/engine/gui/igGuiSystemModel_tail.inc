namespace Gap {
namespace Gui {

void igGuiSystemModel::resetFields(int persistent)
{
    igObject::resetFields(persistent);
    if (persistent) {
        igMatrix44f_SetIdentity(_viewMatrix.m);
        igVec3f texelCenter(0.375f, 0.375f, -0.5f);
        igMatrix44f_SetTranslation(_viewMatrix.m, texelCenter.vec);
        igNotifyEvent event(k_viewMatrix);
        notifyAllViews(event);
    }
}
}
}

