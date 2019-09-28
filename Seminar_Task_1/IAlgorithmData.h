//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_IALGORITHMDATA_H
#define SPECSEM_LAB1_IALGORITHMDATA_H


#include <variant>
#include <vector>
#include <string>

template<typename T>
class IAlgorithmData
{
    public:
        virtual std::variant<T, std::vector<T> > GetDataByAttribute(std::string sAttribute) = 0;
        virtual void SetDataByAttribute(std::string sAttribute, std::variant<T, std::vector<T> > data) = 0;
};

#endif //SPECSEM_LAB1_IALGORITHMDATA_H
