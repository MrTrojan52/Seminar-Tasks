//
// Created by trojan52 on 27.09.2019.
//

#ifndef SPECSEM_LAB1_DEFINITIONS_H
#define SPECSEM_LAB1_DEFINITIONS_H

#include <string>

#define FILE_DEFAULT_EXTENSION    "txt"
#define FILE_DEFAULT_FILENAME     "task"

#define ATTR_ROD_LENGTH           "attr-rod-length"
#define ATTR_LENGHTS_ARRAY        "attr-lenghts-array"

#define SAVE_HTML_DEFAULT_FILENAME "saved_solution.html"

#define TABLE_DEFAULT_COLSPAN_FOR_STRATEGY 3
#define TABLE_DEFAULT_ROWSPAN_FOR_HEADER   2

enum etAlgorithm
{
    eALGORITHM_GREEDY = 0
};

enum etStrategy
{
    eSTRATEGY_UNKNOWN = -1,
    eSTRATEGY_AS_IS,
    eSTRATEGY_BASIC,
    eSTRATEGY_CUSTOM_SORTING,
    eSTRATEGY_CUSTOM_BRUTEFORCE,
    eSTRATEGY_ALL
};

std::string GetStrategyNameByEnum(etStrategy eStrategy);

etStrategy GetStrategyEnumByName(const std::string& sName);

#endif //SPECSEM_LAB1_DEFINITIONS_H
