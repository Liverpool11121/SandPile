#include "sand_pile.h"

static const int16_t kWidening = 10;

SandPile::SandPile(RequestMask& parsedArgs, Coords* coords, const int32_t size)
    : field(coords, size) {
    maxIterations = parsedArgs.maxIter;
    frequence = parsedArgs.freq;
    currentIteration = 0;
    outputPath = parsedArgs.outputPath;
}   


void SandPile::Collapse() {
    bool stable = false;
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    for (size_t i = 0; i < field.getSizeX(); i++) {
        for (size_t j = 0; j < field.getSizeY(); j++) {
            if (field.sandPile[i][j] < 4) {
                continue;
            }
            if (i == 0) {
                upFlag = true;
            }
            if (i == field.getSizeX() - 1) {
                downFlag = true;
            }
            if (j == 0) {
                leftFlag = true;
            }
            if (j == field.getSizeY() - 1) {
                rightFlag = true;
            }
        }
    }

    if (upFlag) {
        field.sandPile = field.resizeUp(field.sandPile, kWidening);
    }
    if (downFlag) {
        field.sandPile = field.resizeDown(field.sandPile, kWidening);
    }
    if (leftFlag) {
        field.sandPile = field.resizeLeft(field.sandPile, kWidening);
    }
    if (rightFlag) {
        field.sandPile = field.resizeRight(field.sandPile, kWidening);
    }

    Field newField(field);
    for (size_t iter = 0; iter < maxIterations && !stable; iter++) {
        stable = true;
        upFlag = false;
        downFlag = false;
        leftFlag = false;
        rightFlag = false;
        newField = field;

        for (size_t i = 0; i < field.getSizeX(); i++) {
            for (size_t j = 0; j < field.getSizeY(); j++) {
                if (field.sandPile[i][j] >= 4) {
                    stable = false;
                    newField.sandPile[i][j] -= 4;
                    newField.sandPile[i - 1][j]++;
                    newField.sandPile[i][j - 1]++;
                    newField.sandPile[i + 1][j]++;
                    newField.sandPile[i][j + 1]++;
                
                    if (i - 1 == 0) {
                        upFlag = true;
                    }
                    if (i + 1 == newField.getSizeX() - 1) {
                        downFlag = true;
                    }
                    if (j - 1 == 0) {
                        leftFlag = true;
                    }
                    if (j + 1 == newField.getSizeY() - 1) {
                        rightFlag = true;
                    }
                }
            }
        }
        if (upFlag) {
            newField.sandPile = newField.resizeUp(newField.sandPile, kWidening);
        }
        if (downFlag) {
            newField.sandPile = newField.resizeDown(newField.sandPile, kWidening);
        }
        if (leftFlag) {
            newField.sandPile = newField.resizeLeft(newField.sandPile, kWidening);
        }
        if (rightFlag) {
            newField.sandPile = newField.resizeRight(newField.sandPile, kWidening);
        }

        field = newField;
        currentIteration = iter + 1;

        if (frequence == 0) {
            if (iter + 1 == maxIterations || stable) {
                WriteToDir(outputPath, field, currentIteration);
            }
        } 
        else if ((iter + 1) % frequence == 0 || iter + 1 == maxIterations || stable) {
            WriteToDir(outputPath, field, currentIteration);
        }
    }
}