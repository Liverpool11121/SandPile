#include <cstring>

#include "arg_parser.h"

void PrintValidArguments() {
    std::cout << "\nOPTIONS:\n";
    std::cout << "<Short argument> <Long argument> <Default value> <Description>\n\n";
    std::cout << "-i <path> --input=<path> <no> Path to tsv-file with coordinates of grains of sand\n";
    std::cout << "-o <path>  --output=<path>  <no>  Path to the directory for saving pictures\n";
    std::cout << "-m <n> --max_iter=<n>  0  Maximum number of model iterations\n";
    std::cout << "-f <n>  --freq=<n>  0  Frequency at which pictures should be saved (if 0, then only the last state is saved)\n";
    std::cout << std::endl;
}

long long int GetIntValue (char* str) {
    long long int ret = 0;
    long long int digit = 1;
    for (int i = static_cast<int>(strlen(str)) - 1; i >= 0; i--) {
        if (str[i] >= '0' && str[i] <= '9') {
            ret += (str[i] -'0') * digit;
            digit *= 10;
        }
        else if (str[i] == '\0' || str[i] == '\n') {
            continue;
        }
        else {
            return -1;
        }
    }
    return ret;
}



bool IsValidInput(int argc, char** argv, RequestMask* parsedArgs) {
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            PrintValidArguments();
            std::cout << "\n";
            return true;    
        }
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            std::cout << "Incorrect input.\n";
            return true;
        }        

        argv[i] = (argv[i] + 1);
        if (argv[i][0] == '-') {
            argv[i] = (argv[i] + 1);
        }
        
        if (strncmp(argv[i], "output=", 7) == 0) {
            if (strlen(argv[i]) == 7) {
                std::cout << "There is a mistake with \'output path\'.\n";
                return true;
            }
            char* path = (argv[i]+7);
            parsedArgs->outputPath = path;
        }
        else if (strcmp(argv[i], "output") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'output path\'.\n";
                return true;
            }
            parsedArgs->outputPath = argv[i+1];
            i++;
        }
        else if (strncmp(argv[i], "input=", 6) == 0) {
            if (strlen(argv[i]) == 6) {
                std::cout << "There is a mistake with \'input file\'.\n";
                return true;
            }
            char* path = (argv[i]+6);
            parsedArgs->inputPath = path;
        }
        else if (strcmp(argv[i], "input") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'input file\'.\n";
                return true;
            }
            parsedArgs->inputPath = argv[i+1];
            i++;
        }
        else if (strncmp(argv[i], "max_iter=", 9) == 0) {
            long long int value = GetIntValue(argv[i] + 9);
            if (value < 0 || strlen(argv[i]) == 9) {
                std::cout << "There is a mistake with \'max_iter\'\n";
                return true;
            }
            parsedArgs->maxIter = value;
        }
        else if (strcmp(argv[i], "max_iter") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'max_iter\'.\n";
                return true;
            }
            long long int value = GetIntValue(argv[i+1]);
            if (value < 0) {
                std::cout << "There is a mistake with \'max_iter\'\n";
                return true;
            }
            parsedArgs->maxIter = value;
            i++;
        }
        else if (strncmp(argv[i], "freq=", 5) == 0) {
            long long int value = GetIntValue(argv[i] + 5);
            if (value < 0 || strlen(argv[i]) == 5) {
                std::cout << "There is a mistake with \'freq\'\n";
                return true;
            }
            parsedArgs->freq = value;
        }
        else if (strcmp(argv[i], "freq") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'freq\'.\n";
                return true;
            }
            long long int value = GetIntValue(argv[i+1]);
            if (value < 0) {
                std::cout << "There is a mistake with \'freq\'\n";
                return true;
            }
            parsedArgs->freq = value;
            i++;
        }
        
        else if (strncmp(argv[i], "o=", 2) == 0) {
            if (strlen(argv[i]) == 2){
                std::cout << "There is a mistake with \'output file\'.\n";
                return true;
            }
            char* path = (argv[i]+2);
            parsedArgs->outputPath = path;
        }
        else if (strcmp(argv[i], "o") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'output file\'.\n";
                return true;
            }
            parsedArgs->outputPath = argv[i+1];
            i++;
        }
        else if (strncmp(argv[i], "i=", 2) == 0) {
            if (strlen(argv[i]) == 2) {
                std::cout << "There is a mistake with \'input file\'.\n";
                return true;
            }
            char* path = (argv[i]+2);
            parsedArgs->inputPath = path;
        }
        else if (strcmp(argv[i], "i") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'input file\'.\n";
                return true;
            }
            parsedArgs->inputPath = argv[i+1];
            i++;
        }
        else if (strncmp(argv[i], "m=", 2) == 0) {
            long long int value = GetIntValue(argv[i] + 2);
            if (value < 0 || strlen(argv[i]) == 2) {
                std::cout << "There is a mistake with \'max_iter\'\n";
                return true;
            }
            parsedArgs->maxIter = value;
        }
        else if (strcmp(argv[i], "m") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'max_iter\'.\n";
                return true;
            }
            long long int value = GetIntValue(argv[i+1]);
            if (value < 0) {
                std::cout << "There is a mistake with \'max_iter\'\n";
                return true;
            }
            parsedArgs->maxIter = value;
            i++;
        }
        else if (strncmp(argv[i], "f=", 2) == 0) {
            long long int value = GetIntValue(argv[i] + 2);
            if (value < 0 || strlen(argv[i]) == 2) {
                std::cout << "There is a mistake with \'freq\'\n";
                return true;
            }
            parsedArgs->freq = value;
        }
        else if (strcmp(argv[i], "f") == 0) {
            if (i == argc) {
                std::cout << "There is a mistake with \'freq\'.\n";
                return true;
            }
            long long int value = GetIntValue(argv[i+1]);
            if (value < 0) {
                std::cout << "There is a mistake with \'freq\'\n";
                return true;
            }
            parsedArgs->freq = value;
            i++;
        }
        else {
            std::cout << "Unknown argument\n";
            return true;
        }
    }


    if (parsedArgs->inputPath == nullptr) {
        std::cout << "Wrong input. No input path.\n";
        return true;
    }
    if (parsedArgs->outputPath == nullptr) {
        std::cout << "Wrong input. No output path.\n";
        return true;
    }
    if (strcmp(parsedArgs->outputPath, parsedArgs->inputPath) == 0) {
        std::cout << parsedArgs->outputPath << " " << parsedArgs->inputPath << '\n';
        std::cout << strcmp(parsedArgs->outputPath, parsedArgs->inputPath) << '\n';
        std::cout << "Wrong input. Input file can not be Output path (directory).\n";
        return true;
    }
    return false;
}

