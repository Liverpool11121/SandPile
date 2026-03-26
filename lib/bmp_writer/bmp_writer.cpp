#define _CRT_SECURE_NO_WARNINGS

#include "bmp_writer.h"
#include <algorithm>
#include <string.h>
#include <iostream>
#include <fstream>

const uint8_t kByteSize = 1;
const uint8_t kHeaderFile = 14;
const uint8_t kInformationOfFile = 40;
const uint8_t kColorsSize = 20;
const int32_t kMaxInt16_t = 65535;
const uint8_t kOffsetSize = 74;

char* IntToCharptr(int64_t numberOfFile) {
    if (numberOfFile == 0) {
        char* ret = new char[2];
        ret[0] = '0';
        ret[1] = '\0';
        return ret;
    }

    int64_t size = 0;
    int64_t deg = 1;
    while (deg <= numberOfFile) {
        size++;
        deg *= 10;
    }
    char* ret = new char[size + 1];
    for (int64_t i = size-1; i >= 0; i--) {
        ret[i] = static_cast<char> (numberOfFile % 10 + '0');
        numberOfFile /= 10;
    }
    ret[size] = '\0';
    return ret;
}

char* GetOutputFile(char *outputPath, int64_t numberOfFile) {
    char* numberOfFileCopy = IntToCharptr(numberOfFile);
    char* ret = new char[strlen(outputPath) + strlen(numberOfFileCopy) + 5];
    size_t ind = 0;
    for (size_t i = 0; i < strlen(outputPath); i++) {
        ret[ind] = outputPath[i];
        ind++;
    }
    for (size_t i = 0; i < strlen(numberOfFileCopy); i++) {
        ret[ind] = numberOfFileCopy[i];
        ind++;
    }
    ret[ind] = '.';
    ind++;
    ret[ind] = 'b';
    ind++;
    ret[ind] = 'm';
    ind++;
    ret[ind] = 'p';
    ind++;
    ret[ind] = '\0';
    
    return ret;
}

void WriteToDir(char *outputPath, Field& field, int64_t numberOfFile) {
    char* result = GetOutputFile(outputPath, numberOfFile);
    std::ofstream outputFile(result, std::ios::binary);

    uint16_t width = static_cast<uint16_t> (std::min(field.getSizeY(), kMaxInt16_t));
    uint16_t height = static_cast<uint16_t> (std::min(field.getSizeX(), kMaxInt16_t));
    uint8_t padding = static_cast<uint8_t> ((4 - (width/2 + width%2)%4)%4);
    uint64_t fileSize = kOffsetSize + static_cast<uint64_t>(height * (width/2 + width%2) + padding);


    uint8_t bmpHeader [kHeaderFile];
    for (size_t i = 0; i < kHeaderFile; i++) {
        bmpHeader[i] = 0;
    }

    uint8_t informationHeader [kInformationOfFile];
    for (size_t i = 0; i < kInformationOfFile; i++) {
        informationHeader[i] = 0;
    }

    uint8_t colorHeader [kColorsSize];
    for (size_t i = 0; i < kColorsSize; i++) {
        colorHeader[i] = 0;
    }

    bmpHeader[0] = 'B';
    bmpHeader[1] = 'M';

    bmpHeader[2] = static_cast<uint8_t> (fileSize & 0xff);
    bmpHeader[3] = static_cast<uint8_t> (fileSize >> 8 & 0xff);
    bmpHeader[4] = static_cast<uint8_t> (fileSize >> 16 & 0xff);
    bmpHeader[5] = static_cast<uint8_t> (fileSize >> 24);

    bmpHeader[6] = 0;
    bmpHeader[7] = 0;
    bmpHeader[8] = 0;
    bmpHeader[9] = 0;

    bmpHeader[10] = kOffsetSize;
    bmpHeader[11] = 0;
    bmpHeader[12] = 0;
    bmpHeader[13] = 0;

    informationHeader[0] = kInformationOfFile;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    informationHeader[4] = static_cast<uint8_t> (width & 0xff);
    informationHeader[5] = static_cast<uint8_t> (width >> 8);
    informationHeader[6] = 0;
    informationHeader[7] = 0;

    informationHeader[8] = static_cast<uint8_t> (height & 0xff);
    informationHeader[9] = static_cast<uint8_t> (height >> 8);
    informationHeader[10] = 0;
    informationHeader[11] = 0;

    informationHeader[12] = 1;
    informationHeader[13] = 0;

    informationHeader[14] = 4;
    informationHeader[15] = 0;

    informationHeader[32] = 5;

    //White - #ffffff
    colorHeader[0] = 0xff;
    colorHeader[1] = 0xff;
    colorHeader[2] = 0xff;
    colorHeader[3] = 0x00;
    
    //Green - #99ff66
    colorHeader[4] = 0x66;
    colorHeader[5] = 0xff;
    colorHeader[6] = 0x99;
    colorHeader[7] = 0;
    
    //Cian - #6600cc
    colorHeader[8] = 0xcc;
    colorHeader[9] = 0x00;
    colorHeader[10] = 0x66;
    colorHeader[11] = 0x00;
    
    //Yellow - #ffff00
    colorHeader[12] = 0x00;
    colorHeader[13] = 0xff;
    colorHeader[14] = 0xff;
    colorHeader[15] = 0x00;

    //Black #000000
    colorHeader[16] = 0x00;
    colorHeader[17] = 0x00;
    colorHeader[18] = 0x00;
    colorHeader[19] = 0x00;

    outputFile.write(reinterpret_cast<char*>(bmpHeader), kHeaderFile);
    outputFile.write(reinterpret_cast<char*>(informationHeader), kInformationOfFile);
    outputFile.write(reinterpret_cast<char*>(colorHeader), kColorsSize);

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j+=2) {
            uint8_t firstPixel = ((static_cast<uint8_t>(std::min(field.sandPile[i][j], static_cast<uint64_t>(4)))) << 4); 
            uint8_t secondPixel = static_cast<uint8_t>(std::min(field.sandPile[i][j + 1], static_cast<uint64_t>(4)));
            uint8_t result = (firstPixel | secondPixel);
            
            outputFile.write(reinterpret_cast<char*>(&result), kByteSize);
        }
        for (size_t i = 0; i < padding; i++) {
            outputFile.write("\x00", kByteSize);
        }
    }
}

