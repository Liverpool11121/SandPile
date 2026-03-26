#pragma once
#include <iostream>
#include <cinttypes>

struct Coords {
    int16_t x = 0;
    int16_t y = 0;
    uint64_t value = 0;
};

class Field {
    public:
        uint64_t** sandPile;

        Field();
        Field(const Field& other);
        Field(Coords* coords, int32_t size);
        ~Field();

        int32_t getSizeX() const;
        int32_t getSizeY() const;

        uint64_t** resizeUp(uint64_t** oldField, const int16_t magnificationFactor);
        uint64_t** resizeDown(uint64_t** oldField, const int16_t magnificationFactor);
        uint64_t** resizeRight(uint64_t** oldField, const int16_t magnificationFactor);
        uint64_t** resizeLeft(uint64_t** oldField, const int16_t magnificationFactor);

        Field& operator=(const Field& other);

    private:
        int32_t maxXCoordinate;
        int32_t maxYCoordinate;
        int32_t shiftX;
        int32_t shiftY;
        int32_t sizeX;
        int32_t sizeY;
        
        static uint64_t** MakeEmptyField(const int32_t sizeX, const int32_t sizeY);
        static void DeleteField(uint64_t** data, int32_t rows);
        
        void CopyMetadataFrom(const Field& other);
        uint64_t** CloneField(uint64_t** source, int32_t rows, int32_t cols) const;
        uint64_t** CreateField(Coords* coords, const int32_t size);
        
        uint64_t** ResizeUpImpl(uint64_t** oldField, const int16_t magnificationFactor);
        uint64_t** ResizeDownImpl(uint64_t** oldField, const int16_t magnificationFactor);
        uint64_t** ResizeRightImpl(uint64_t** oldField, const int16_t magnificationFactor);
        uint64_t** ResizeLeftImpl(uint64_t** oldField, const int16_t magnificationFactor);
};
