/*
MIT License

Copyright (c) 2022 Ducktape

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

#ifndef DEBUG_H
#define DEBUG_H

#define FATAL_ERROR 8

#include <Ducktape/engine/vector2.h>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace DT
{
    namespace Debug
    {
        // valing
        void Log(std::string val);

        void LogError(std::string val);

        void LogFatalError(std::string val);

        void LogWarning(std::string val);

        void LogSuccess(std::string val);

        // float overload

        void Log(float val);

        void LogError(float val);

        void LogFatalError(float val);

        void LogWarning(float val);

        void LogSuccess(float val);

        void DrawLine(Vector2 start, Vector2 end, sf::Color color);

        void DrawRay(Vector2 start, Vector2 dir, sf::Color color);
    };
}

#endif