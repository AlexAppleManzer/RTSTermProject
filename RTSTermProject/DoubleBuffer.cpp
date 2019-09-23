#include "DoubleBuffer.h"

DoubleBuffer::DoubleBuffer(Position position) {
    bag = new Position();
    nextBag = new Position();
    pushItem(position);
}

DoubleBuffer::~DoubleBuffer() {
    delete bag;
    delete nextBag;
}

Position DoubleBuffer::getItem() {
    return *bag;
}

void DoubleBuffer::pushItem(Position position) {
    *nextBag = position;
    Position* oldBag = bag;
    bag = nextBag;
    nextBag = oldBag;
}