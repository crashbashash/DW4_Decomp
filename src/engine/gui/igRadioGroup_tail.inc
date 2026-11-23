namespace Gap {
namespace Gui {

void igRadioGroup::resetFields(int persistent)
{
    igObject::resetFields(persistent);
    _selectedObserver->setGroup(this);
    _selectedObserver->setModel(_model);
}
}
}

