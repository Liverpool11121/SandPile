#pragma once
#include <iostream>
#include <cinttypes>

struct RequestMask {
    char* inputPath = nullptr;
    char* outputPath = nullptr;
    int64_t maxIter = 0;
    int64_t freq = 0;
};

bool IsValidInput(int argc, char** argv, RequestMask* paresedArgs);