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
#include "ygif_trafo.h"

namespace mygame
{
    void YgifTrafo::rotateGlobal(float angle, std::string const &ax)
    {
        if (ax == "X")
        {
            yourgame::math::Trafo::rotateGlobal(angle, yourgame::math::Axis::X);
        }
        else if (ax == "Y")
        {
            yourgame::math::Trafo::rotateGlobal(angle, yourgame::math::Axis::Y);
        }
        else if (ax == "Z")
        {
            yourgame::math::Trafo::rotateGlobal(angle, yourgame::math::Axis::Z);
        }
    }

    void YgifTrafo::rotateLocal(float angle, std::string const &ax)
    {
        if (ax == "X")
        {
            yourgame::math::Trafo::rotateLocal(angle, yourgame::math::Axis::X);
        }
        else if (ax == "Y")
        {
            yourgame::math::Trafo::rotateLocal(angle, yourgame::math::Axis::Y);
        }
        else if (ax == "Z")
        {
            yourgame::math::Trafo::rotateLocal(angle, yourgame::math::Axis::Z);
        }
    }

    void YgifTrafo::translateLocal(glm::vec3 const &trans)
    {
        yourgame::math::Trafo::translateLocal(trans);
    }

    void YgifTrafo::translateGlobal(glm::vec3 const &trans)
    {
        yourgame::math::Trafo::translateGlobal(trans);
    }

    void YgifTrafo::setScaleLocal(glm::vec3 const &scale)
    {
        yourgame::math::Trafo::setScaleLocal(scale);
    }

    glm::vec3 YgifTrafo::getAxisLocal(std::string const &ax)
    {
        if (ax == "Y")
        {
            return yourgame::math::Trafo::getAxisLocal(yourgame::math::Axis::Y);
        }
        else if (ax == "Z")
        {
            return yourgame::math::Trafo::getAxisLocal(yourgame::math::Axis::Z);
        }
        else
        {
            return yourgame::math::Trafo::getAxisLocal(yourgame::math::Axis::X);
        }
    }

    glm::vec3 YgifTrafo::getAxisGlobal(std::string const &ax)
    {
        if (ax == "Y")
        {
            return yourgame::math::Trafo::getAxisGlobal(yourgame::math::Axis::Y);
        }
        else if (ax == "Z")
        {
            return yourgame::math::Trafo::getAxisGlobal(yourgame::math::Axis::Z);
        }
        else
        {
            return yourgame::math::Trafo::getAxisGlobal(yourgame::math::Axis::X);
        }
    }
}
