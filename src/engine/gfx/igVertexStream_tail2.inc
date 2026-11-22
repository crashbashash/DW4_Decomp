namespace Gap {
namespace Gfx {

void igPsx2VertexStream::waitForSync()
{
    p2WaitDmaSequence(1, _syncSequence);
}
}
}

