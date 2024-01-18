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
#ifndef YGIF_MOTION_H
#define YGIF_MOTION_H

#include <string>
#include "yourgame/util/motion.h"

namespace mygame
{
    class YgifMotion : yourgame::util::Motion
    {
    private:
        static yourgame::util::Motion::FlowType str2FlowType(std::string const &str)
        {
            if (str == "ONCE")
            {
                return yourgame::util::Motion::FlowType::ONCE;
            }
            else if (str == "REPEAT")
            {
                return yourgame::util::Motion::FlowType::REPEAT;
            }
            else if (str == "PINGPONG")
            {
                return yourgame::util::Motion::FlowType::PINGPONG;
            }
            else
            {
                return yourgame::util::Motion::FlowType::ONCE;
            }
        }

    public:
        YgifMotion(std::string const &flowTypeStr) : yourgame::util::Motion(str2FlowType(flowTypeStr)) {}
        yourgame::util::Motion &addRamp(float dt, float val0, float val1, const std::string &easeStr);
    };
}

#endif
