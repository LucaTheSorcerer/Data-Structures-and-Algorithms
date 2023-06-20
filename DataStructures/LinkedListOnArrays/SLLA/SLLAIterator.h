#pragma once

#include "SLLA.h"

class SLLAIterator {
    friend class SingleLinkedListOnArrays;

private:
    int current;
    const SingleLinkedListOnArrays &singleLinkedListOnArrays;

    explicit SLLAIterator(const SingleLinkedListOnArrays &slla);

public:
    void first();

    void next();

    [[nodiscard]] bool valid() const;

    TComp getCurrent();
};