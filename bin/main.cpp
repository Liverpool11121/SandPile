#include <iostream>

#include "arg_parser.h"
#include "sand_pile.h"
#include "tsv_reader.h"

int main(int argc, char* argv[]) {
    RequestMask parsedArgs;
    if (IsValidInput(argc, argv, &parsedArgs)) {   
        std::cout << "Enter the arguments again. There should not be --help among them - this is a separate argument for displaying a valid request.\n";
        return 1;
    }
    uint64_t coordsSize = 0;
    Coords* coords = readTSV(&parsedArgs, coordsSize);
    if (coords == nullptr) {
        return 1;
    }

    SandPile pile(parsedArgs, coords, coordsSize);
    pile.Collapse();

    delete[] coords;
    return 0;
}
