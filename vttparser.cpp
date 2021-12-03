#include <exception>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <string_view>

#include "vttparser.h"
#include "cue.h"

using namespace std::filesystem;


constexpr int cueDurationLineNumColonChars = 4;
constexpr int cueDurationLineNumDotChars = 2;


bool getCues(const string& filePathAndName, std::vector<Cue>& cv) {

    auto p = path(filePathAndName);

    if(!exists(p) || !is_regular_file(p)) {
        return false;
    }

    std::fstream file(p, std::ios::in | std::ios::binary);

    if(!file.is_open()) {
        return false;
    }



    // Pass 1: Going through the file for sanity check
    struct CueChunk {
        int startLine = 0;
        int endLine = 0;
        string cueIndexLine;
        string cueDurationLine;
        string cueText;
    };

    std::vector<CueChunk> chunks(1000);

    int cueCount = 0;
    int lineCount = 0;
    string line;
    std::vector<std::pair<size_t,string>> tempLines;
    bool isWithinChunk = false;
    while(std::getline(file, line)) {

        if(isWithinChunk) {
            tempLines.push_back({lineCount, line});
        }

        if(line.empty() || line[0] == '\r') {
            isWithinChunk = false;
            if(tempLines.size() > 0) {
                tempLines.pop_back();
            }
        }

        if(durationLineValid(line)) { // Check for "-->", ':' and '.'
            cueCount++;
            isWithinChunk = true;
            tempLines.push_back({lineCount, line});
        }

        lineCount++;

    }

    // Pass 2:
    // Rewind the file
    file.clear();
    file.seekg (0, std::ios::beg);

    cv.resize(cueCount);

    while(std::getline(file, line)) {

    }



    file.close();
    return true;

}

bool durationLineValid(const string& line)
{

    if( line.find(" --> ", 0) != string::npos) {
        //see if there are 4x ':' and 2x '.
        auto colCount = std::count_if(line.begin(), line.end(),
                                      [](char c) {
                                          return c == ':';
                                      });
        auto dotCount = std::count_if(line.begin(), line.end(),
                                      [](char c) {
                                          return c == '.';
                                      });
        return (colCount == cueDurationLineNumColonChars
                && dotCount == cueDurationLineNumDotChars);
    }

    return false;


}
