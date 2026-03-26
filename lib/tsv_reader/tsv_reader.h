#pragma once
#include <iostream>
#include "arg_parser.h"
#include "field.h"

Coords* readTSV(RequestMask* parsedArgs, uint64_t& size);