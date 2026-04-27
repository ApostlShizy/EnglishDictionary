#include "wordinfo.h"

bool WordInfo:: operator ==(const WordInfo & other) const{
    return this->answerRatio == other.answerRatio;
}
bool WordInfo:: operator <(const WordInfo & other) const{
    return this->answerRatio < other.answerRatio;
}

size_t qHash(const WordInfo &key) {
    return qHash(key.answerRatio);
}