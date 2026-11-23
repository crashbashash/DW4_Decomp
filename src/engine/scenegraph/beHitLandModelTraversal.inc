namespace Gap {
namespace Sg {

long long igTraversal::getTimeAsLong()
{
    if (!_userTimeState) {
        return ((igTimer *)DAT_005871d8[0])->getTimeAsLong();
    }
    return _timeLong;
}
}
}

