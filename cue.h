/* File: cue.h
 * Author: Saeid Yazdani
 *
 *
 *
*/


/* TODO
 * + Add overloads member functions that accept int as time
 * + Add copy and move constructors
 */

#pragma once

#include <string>
#include <chrono>
#include <stdexcept>

using namespace std::chrono_literals;
using namespace std::chrono;

class Cue {

private:
    unsigned int mIndex = 0;   // Cue number
    milliseconds mBegin = 0ms;  // Begin time
    milliseconds mEnd = 0ms;    // End time
    std::string mText = {};          // Associated text

public:
    explicit Cue();
    Cue(unsigned int index,
        milliseconds begin,
             milliseconds end,
             const char* text) {
        if(end <=begin) {
            throw std::invalid_argument("End can not be smaller than Begin");
        }
        mIndex = index;
        mBegin = begin;
        mEnd = end;
        mText = std::string(text);
    };

    /**
     * @brief index Cue's index
     * @return index of this cue
     */
    unsigned int index() const {return mIndex;}
    /**
     * @brief begin Cue's start time
     * @return start time of cue in milliseconds
     */
    milliseconds begin() const { return mBegin;}
    /**
     * @brief begin Cue's start time
     * @return start time of cue in milliseconds
     */
    milliseconds end() const { return mEnd;}
    /**
     * @brief begin Cue's duration
     * @return duration of the cue in milliseconds
     */
    milliseconds duration() const;
    std::string text() const {return mText;}
    /**
     * @brief setText Set the text of this cue
     * @param text character array to be used as text
     */
    void setText(char* text);
    /**
     * @brief setText Set the text of this cue
     * @param text String to set as text
     */
    void setText(const std::string& text);
    /**
     * @brief setIndex Set the index of this cue
     * @param index value to be set as index
     */
    void setIndex(unsigned int index);
    /**
     * @brief setBegin Set the begin time
     * @param begin time in milliseconds
     */
    void setBegin(milliseconds begin);
    /**
     * @brief setEnd
     * @param end
     */
    void setEnd(milliseconds end);
    /**
     * @brief reduceBy Decrease the Cue time by a given value
     * @param millis Time to decrease in milliseconds
     */
    void reduceBy(milliseconds millis);
    /**
     * @brief increaseBy Increase the Cue time by a given value
     * @param millis Time to increase in milliseconds
     */
    void increaseBy(milliseconds millis);

};
