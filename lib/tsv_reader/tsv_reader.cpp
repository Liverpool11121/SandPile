#include "tsv_reader.h"
#include <fstream>

Coords* readTSV(RequestMask* parsedArgs, uint64_t& size) {
    std::ifstream inputFile (parsedArgs->inputPath);
    if (!inputFile) {
        std::cout << "There is a mistake with input path\n";
        size = 0;
        return nullptr;
    }
    
    uint64_t numberOfLines = 0;
    while (!inputFile.eof()) {
        int32_t coordX;
        int32_t coordY;
        uint64_t value;
        inputFile >> coordX >> coordY >> value;
        numberOfLines++;
    }
    numberOfLines--;
    size = numberOfLines;
    inputFile.close();
    inputFile.open(parsedArgs->inputPath);
    Coords* coords = new Coords[size];
    for (size_t i = 0; i < size; i++) {
        inputFile >> coords[i].x >> coords[i].y >> coords[i].value;
    }
    return coords;
}