/*
Copyright (c) 2019-2023 Alexander Scholz

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
#ifndef YGIF_TRAFO_H
#define YGIF_TRAFO_H

#include <string>
#include "yourgame/math/trafo.h"

namespace mygame
{
    class YgifTrafo : yourgame::math::Trafo
    {
    public:
        void rotateGlobal(float angle, std::string const &ax);
        void rotateLocal(float angle, std::string const &ax);
        void translateLocal(glm::vec3 const &trans);
        void translateGlobal(glm::vec3 const &trans);
        void setScaleLocal(glm::vec3 const &scale);
        glm::vec3 getAxisLocal(std::string const &ax);
        glm::vec3 getAxisGlobal(std::string const &ax);
    };
}

#endif
