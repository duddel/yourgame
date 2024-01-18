/*
Copyright (c) 2019-2024 Alexander Scholz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <map>
#include "ygif_motion.h"

namespace mygame
{
    yourgame::util::Motion &YgifMotion::addRamp(float dt, float val0, float val1, std::string const &easeStr)
    {
        const std::map<std::string, yourgame::util::Motion::SegmentEase> str2ease = {
            {"NONE", yourgame::util::Motion::SegmentEase::NONE},
            {"SQUARE", yourgame::util::Motion::SegmentEase::SQUARE},
            {"SQUAREDOWN", yourgame::util::Motion::SegmentEase::SQUAREDOWN},
            {"CUBE", yourgame::util::Motion::SegmentEase::CUBE},
            {"CUBEDOWN", yourgame::util::Motion::SegmentEase::CUBEDOWN},
            {"SINE", yourgame::util::Motion::SegmentEase::SINE},
            {"SINEDOWN", yourgame::util::Motion::SegmentEase::SINEDOWN},
            {"SMOOTH", yourgame::util::Motion::SegmentEase::SMOOTH},
            {"SMOOTH2", yourgame::util::Motion::SegmentEase::SMOOTH2}};

        auto i = str2ease.find(easeStr);
        yourgame::util::Motion::SegmentEase ease = (i == str2ease.end())
                                                       ? yourgame::util::Motion::SegmentEase::NONE
                                                       : i->second;

        return yourgame::util::Motion::addRamp(dt, val0, val1, ease);
    }
}
