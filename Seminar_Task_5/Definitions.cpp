//
// Created by trojan52.
//

#include "Definitions.h"


std::string GetReductionNameByEnum(etREDUCTION eReduction)
{
    std::string sName;
    switch (eReduction)
    {
        case eUNDEFINED_REDUCTION:
            sName = "Undefined reduction";
            break;

        case eDEFAULT_REDUCTION:
            sName = "Default reduction";
            break;

        case eCENTER_RECALC_REDUCTION:
            sName = "Center recalculation reduction";
            break;

        default:
            break;
    }

    return sName;
}