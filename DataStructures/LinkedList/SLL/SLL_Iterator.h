#pragma once

#include "SLL.h"

class SLLIterator {
    friend class SLL;

private:
    const SLL &sll;

    SLLNode *node;

    explicit SLLIterator(const SLL &s);

public:
    void first();

    void next();

    [[nodiscard]] bool valid() const;

    [[nodiscard]] TComp getCurrent() const;
};