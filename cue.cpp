#include "cue.h"

Cue::Cue() : mIndex{0}, mBegin{0}, mEnd{0}, mText{}
{

}

milliseconds Cue::duration() const
{
    return mEnd - mBegin;
}

void Cue::setText(char* text)
{
    if(text != nullptr) {
        mText = text;
    }
}

void Cue::setIndex(unsigned int index)
{
    mIndex = index;
}

void Cue::setBegin(milliseconds begin)
{
    mBegin = begin;
}

void Cue::setEnd(milliseconds end)
{
    if(end <= mBegin) {
        throw std::out_of_range("Duration mismatch!");
    }

    mEnd = end;
}

void Cue::reduceBy(milliseconds millis)
{
    mBegin -= millis;
    if(mBegin.count() < 0) {
        throw std::invalid_argument("Begin will be negative!");
    }
    mEnd -= millis;
}

void Cue::increaseBy(milliseconds millis)
{
    mBegin += millis;
    mEnd += millis;
}
