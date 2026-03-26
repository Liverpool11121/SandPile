#pragma once
#include "arg_parser.h"
#include "field.h"
#include "tsv_reader.h"
#include "bmp_writer.h"

class SandPile {
    public:
        Field field;
        SandPile(RequestMask& parsedArgs, Coords* coords, const int32_t size);
        void Collapse();

    private:
        uint64_t maxIterations;
        uint64_t frequence;
        uint64_t currentIteration;
        char* outputPath;
};


