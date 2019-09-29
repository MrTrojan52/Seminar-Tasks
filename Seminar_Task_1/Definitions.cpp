//
// Created by trojan52.
//

#include "Definitions.h"

std::string GetStrategyNameByEnum(etStrategy eStrategy)
{
    std::string sName;
    switch(eStrategy)
    {
        case eSTRATEGY_AS_IS:
            sName = "AS IS";
            break;
        case eSTRATEGY_BASIC:
            sName = "Basic";
            break;
        case eSTRATEGY_CUSTOM_SORTING:
            sName = "Sorting";
            break;
        case eSTRATEGY_CUSTOM_BRUTEFORCE:
            sName = "Bruteforce";
            break;
        default:
            break;
    }
    return sName;
}

etStrategy GetStrategyEnumByName(const std::string& sName)
{
    etStrategy eStrategy = eSTRATEGY_UNKNOWN;
    if (sName == "AS IS")
    {
        eStrategy = eSTRATEGY_AS_IS;
    }
    else if (sName == "Basic")
    {
        eStrategy = eSTRATEGY_BASIC;
    }
    else if (sName == "Sorting")
    {
        eStrategy = eSTRATEGY_CUSTOM_SORTING;
    }
    else if (sName == "Bruteforce")
    {
        eStrategy = eSTRATEGY_CUSTOM_BRUTEFORCE;
    }

    return eStrategy;
}