#pragma once

#include <string>
#include <vector>


class Cue;

using string = std::string;

bool getCues(const string& filePathAndName, std::vector<Cue>& cv);
/**
 * @brief durationLineValid Check for occurances of ':' and '.' in a line
 * Normally, a Cue timeline is like: "00:00:16.529 --> 00:00:21.630" So there
 * should be a "-->" string and 4x ':' and 2x '.' characters in the line
 * @param line The string to be veridied
 * @return true if vaild, false if not
 */
inline bool durationLineValid(const string& line);
