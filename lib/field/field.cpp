#include "field.h"

#include <algorithm>

namespace {
const int16_t kMaxX = static_cast<int16_t>(65535);
const int16_t kMaxY = static_cast<int16_t>(65535);
}

uint64_t** Field::MakeEmptyField(const int32_t sizeX, const int32_t sizeY) {
    if (sizeX <= 0 || sizeY <= 0) {
        return nullptr;
    }

    uint64_t** retField = new uint64_t*[sizeX];
    for (int32_t i = 0; i < sizeX; i++) {
        retField[i] = new uint64_t[sizeY];
        for (int32_t j = 0; j < sizeY; j++) {
            retField[i][j] = 0;
        }
    }

    return retField;
}

void Field::DeleteField(uint64_t** data, int32_t rows) {
    if (data == nullptr) {
        return;
    }

    for (int32_t i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}

void Field::CopyMetadataFrom(const Field& other) {
    maxXCoordinate = other.maxXCoordinate;
    maxYCoordinate = other.maxYCoordinate;
    shiftX = other.shiftX;
    shiftY = other.shiftY;
    sizeX = other.sizeX;
    sizeY = other.sizeY;
}

uint64_t** Field::CloneField(uint64_t** source, int32_t rows, int32_t cols) const {
    if (source == nullptr || rows <= 0 || cols <= 0) {
        return nullptr;
    }

    uint64_t** copy = MakeEmptyField(rows, cols);
    for (int32_t i = 0; i < rows; i++) {
        for (int32_t j = 0; j < cols; j++) {
            copy[i][j] = source[i][j];
        }
    }

    return copy;
}

Field::Field()
    : sandPile(nullptr),
      maxXCoordinate(0),
      maxYCoordinate(0),
      shiftX(0),
      shiftY(0),
      sizeX(0),
      sizeY(0) {}

Field::Field(const Field& other)
    : sandPile(nullptr),
      maxXCoordinate(0),
      maxYCoordinate(0),
      shiftX(0),
      shiftY(0),
      sizeX(0),
      sizeY(0) {
    CopyMetadataFrom(other);
    sandPile = CloneField(other.sandPile, sizeX, sizeY);
}

Field::Field(Coords* coords, int32_t size)
    : sandPile(nullptr),
      maxXCoordinate(0),
      maxYCoordinate(0),
      shiftX(0),
      shiftY(0),
      sizeX(0),
      sizeY(0) {
    sandPile = CreateField(coords, size);
}

Field::~Field() {
    DeleteField(sandPile, sizeX);
}

uint64_t** Field::CreateField(Coords* coords, const int32_t size) {
    if (coords == nullptr || size <= 0) {
        sizeX = 1;
        sizeY = 1;
        return MakeEmptyField(sizeX, sizeY);
    }

    int16_t minX = kMaxX;
    int16_t maxX = 0;
    int16_t minY = kMaxY;
    int16_t maxY = 0;

    for (int32_t i = 0; i < size; i++) {
        minX = std::min(minX, coords[i].x);
        maxX = std::max(maxX, coords[i].x);
        minY = std::min(minY, coords[i].y);
        maxY = std::max(maxY, coords[i].y);
    }

    shiftX = -minX;
    shiftY = -minY;
    maxXCoordinate = maxX + shiftX + 1;
    maxYCoordinate = maxY + shiftY + 1;

    sizeX = maxXCoordinate;
    sizeY = maxYCoordinate;

    sizeX += (sizeX & 1);
    sizeY += (sizeY & 1);

    uint64_t** retField = MakeEmptyField(sizeX, sizeY);
    for (int32_t i = 0; i < size; i++) {
        retField[coords[i].x + shiftX][coords[i].y + shiftY] = coords[i].value;
    }

    return retField;
}

uint64_t** Field::ResizeUpImpl(uint64_t** oldField, const int16_t magnificationFactor) {
    const int32_t oldSizeX = sizeX;
    sizeX += magnificationFactor;
    uint64_t** retField = MakeEmptyField(sizeX, sizeY);

    for (int32_t i = magnificationFactor; i < sizeX; i++) {
        for (int32_t j = 0; j < sizeY; j++) {
            retField[i][j] = oldField[i - magnificationFactor][j];
        }
    }

    DeleteField(oldField, oldSizeX);
    return retField;
}

uint64_t** Field::ResizeDownImpl(uint64_t** oldField, const int16_t magnificationFactor) {
    const int32_t oldSizeX = sizeX;
    sizeX += magnificationFactor;
    uint64_t** retField = MakeEmptyField(sizeX, sizeY);

    for (int32_t i = 0; i < oldSizeX; i++) {
        for (int32_t j = 0; j < sizeY; j++) {
            retField[i][j] = oldField[i][j];
        }
    }

    DeleteField(oldField, oldSizeX);
    return retField;
}

uint64_t** Field::ResizeRightImpl(uint64_t** oldField, const int16_t magnificationFactor) {
    const int32_t oldSizeY = sizeY;
    sizeY += magnificationFactor;
    uint64_t** retField = MakeEmptyField(sizeX, sizeY);

    for (int32_t i = 0; i < sizeX; i++) {
        for (int32_t j = 0; j < oldSizeY; j++) {
            retField[i][j] = oldField[i][j];
        }
    }

    DeleteField(oldField, sizeX);
    return retField;
}

uint64_t** Field::ResizeLeftImpl(uint64_t** oldField, const int16_t magnificationFactor) {
    const int32_t oldSizeY = sizeY;
    sizeY += magnificationFactor;
    uint64_t** retField = MakeEmptyField(sizeX, sizeY);

    for (int32_t i = 0; i < sizeX; i++) {
        for (int32_t j = magnificationFactor; j < sizeY; j++) {
            retField[i][j] = oldField[i][j - magnificationFactor];
        }
    }

    DeleteField(oldField, sizeX);
    return retField;
}

int32_t Field::getSizeX() const {
    return sizeX;
}

int32_t Field::getSizeY() const {
    return sizeY;
}

uint64_t** Field::resizeUp(uint64_t** oldField, const int16_t magnificationFactor) {
    return ResizeUpImpl(oldField, magnificationFactor);
}

uint64_t** Field::resizeDown(uint64_t** oldField, const int16_t magnificationFactor) {
    return ResizeDownImpl(oldField, magnificationFactor);
}

uint64_t** Field::resizeRight(uint64_t** oldField, const int16_t magnificationFactor) {
    return ResizeRightImpl(oldField, magnificationFactor);
}

uint64_t** Field::resizeLeft(uint64_t** oldField, const int16_t magnificationFactor) {
    return ResizeLeftImpl(oldField, magnificationFactor);
}

Field& Field::operator=(const Field& other) {
    if (this == &other) {
        return *this;
    }

    DeleteField(sandPile, sizeX);
    sandPile = nullptr;

    CopyMetadataFrom(other);
    sandPile = CloneField(other.sandPile, sizeX, sizeY);
    return *this;
}