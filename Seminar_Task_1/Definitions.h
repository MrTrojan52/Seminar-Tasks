//
// Created by trojan52 on 27.09.2019.
//

#ifndef SPECSEM_LAB1_DEFINITIONS_H
#define SPECSEM_LAB1_DEFINITIONS_H


#define FILE_DEFAULT_EXTENSION    "txt"
#define FILE_DEFAULT_FILENAME     "task"

#define ATTR_ROD_LENGTH           "attr-rod-length"
#define ATTR_LENGHTS_ARRAY        "attr-lenghts-array"

enum etAlgorithm
{
    eALGORITHM_GREEDY = 0
};

enum etStrategy
{
    eSTRATEGY_AS_IS = -1,
    eSTRATEGY_BASIC,
    eSTRATEGY_CUSTOM_SORTING,
    eSTRATEGY_CUSTOM_BRUTEFORCE
};


#endif //SPECSEM_LAB1_DEFINITIONS_H
