#include "QString"
#include "QHash"

struct WordInfo {
    int answerRatio;
    QString ru;
    QString en;

    bool operator ==(const WordInfo & other) const;
    bool operator <(const WordInfo & other) const;

};

size_t qHash(const WordInfo &key);