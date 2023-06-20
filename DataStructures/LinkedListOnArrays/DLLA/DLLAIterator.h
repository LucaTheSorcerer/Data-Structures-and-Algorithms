#pragma once

#include "DLLA.h"

class DLLA;

class DLLAIterator {
    friend class DLLA;

private:
    const DLLA &dlla;

    explicit DLLAIterator(const DLLA &d);

    int current;

public:
    void first();

    void next();

    bool valid() const;

    TComp getCurrent();
};