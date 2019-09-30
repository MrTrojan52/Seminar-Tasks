//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_DEFINITIONS_H
#define SEMINAR_TASK_2_DEFINITIONS_H

#include <vector>

using nMatrix = std::vector<std::vector<int>>;

#define FILE_DEFAULT_EXTENSION          "txt"
#define FILE_DEFAULT_FILENAME           "task"

#define CONTAINER_BOUNDS(container) container.begin(),container.end()

enum etLowerBoundStrategy
{
    eLOWERBOUND_BASIC = 0,
    eLOWERBOUND_CUSTOM
};

enum etUpperBoundStrategy
{
    eUPPERBOUND_BASIC = 0,
    eUPPERBOUND_CUSTOM
};

enum etBranchingStrategy
{
    eBRANCHING_DEFAULT = 0,
    eBRANCHING_CUSTOM
};

#endif //SEMINAR_TASK_2_DEFINITIONS_H
