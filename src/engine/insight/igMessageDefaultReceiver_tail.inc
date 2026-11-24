namespace Gap {
namespace Insight {

void igMessageDefaultReceiver::messageHandler(igMessage *msg)
{
    if (_msgHandler) {
        igMessageHandlerFunction handler = _msgHandlerFunc;

        (_msgHandler.get()->*handler)(msg);
    }
}
}
}

