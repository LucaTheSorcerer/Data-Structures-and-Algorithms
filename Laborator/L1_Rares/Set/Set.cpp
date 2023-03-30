#include "Set.h"
#include "SetITerator.h"

Set::Set() {
    this->capacity = 1;
    this->length = 0;
    this->left = 0;
    this->right = 0;
    this->elements = new BElem[this->capacity];
}


void Set::resize() {
    auto* resized_array = new BElem[this->capacity * 2];

    for(int i = 0; i < this->right - this->left + 1; i++)
        resized_array[i] = this->elements[i];

    this->capacity *= 2;

    for(int i = this->right-this->left + 1; i < this->capacity; i++)
        resized_array[i] = false;

    delete[] this->elements;
    this->elements = resized_array;
}


bool Set::add(TElem elem){

    if(this->size() == 0){
        this->length = 1;
        this->left = elem;
        this->right = elem;
        this->elements[0] = true;
        return true;
    }
    if(search(elem))
        return false;

    if(this->capacity == this->right - this->left)
        resize();

    if(elem >= this->left && elem <= this->right){
        this->elements[elem - this->left] = true;
        this->length++;
        return true;
    }
    else if(elem < this->left){
        int pos = this->right - this->left;
        while(this->left > elem)
        {

            for(int i = pos; i >= 0; i--)
                this->elements[i+1] = this->elements[i];

            this->elements[0] = false;
            this->left--;
            pos++;

            if(this->capacity == this->right - this->left)
                resize();
        }

        this->elements[0] = true;
        this->left = elem;
        this->length++;
        return true;
    }
    else if(elem > this->right){
        int pos = this->right - this->left;
        while(this->right < elem){
            this->elements[++pos] = false;
            this->right++;

            if(this->capacity == this->right - this->left)
                resize();
        }

        this->elements[pos] = true;
        this->length++;

        return true;
    }

    return false;
}


bool Set::remove(TElem elem) {
    if(!search(elem))
        return false;

    int pos = elem - this->left;
    this->elements[pos] = false;
    this->length--;

    return true;
}

bool Set::search(TElem elem) const {
    if(elem >= this->left && elem <= this->right)
        if(this->elements[elem - this->left])
            return true;
    return false;
}

int Set::size() const {
    return this->length;
}

bool Set::isEmpty() const {
    if(this->length == 0)
        return true;
    return false;
}

SetIterator Set::iterator() const {
    return SetIterator(*this);
}

Set::~Set() {
    delete[] this->elements;
}
