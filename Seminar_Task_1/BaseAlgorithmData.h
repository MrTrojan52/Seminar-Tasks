//
// Created by trojan52 on 28.09.2019.
//

#ifndef SPECSEM_LAB1_BASEALGORITHMDATA_H
#define SPECSEM_LAB1_BASEALGORITHMDATA_H

#include "IAlgorithmData.h"
#include <unordered_map>

template<typename T>
class BaseAlgorithmData : public IAlgorithmData<T>
{
    public:
        std::variant<T, std::vector<T> > GetDataByAttribute(std::string sAttribute) override;
        void SetDataByAttribute(std::string sAttribute, std::variant<T, std::vector<T> > data) override;
    private:
        std::unordered_map<std::string, std::variant<T, std::vector<T> > > m_mData;
};

template<typename T>
std::variant<T, std::vector<T> > BaseAlgorithmData<T>::GetDataByAttribute(std::string sAttribute)
{
    std::variant<T, std::vector<T> > vReturn;
    if (m_mData.find(sAttribute) != m_mData.end())
    {
        vReturn =  m_mData[sAttribute];
    }
    else
    {
        throw std::invalid_argument("Undefined attribute name: " + sAttribute);
    }
    return vReturn;
}

template<typename T>
void BaseAlgorithmData<T>::SetDataByAttribute(std::string sAttribute, std::variant<T, std::vector<T> > data)
{
    m_mData[sAttribute] = data;
}

#endif //SPECSEM_LAB1_BASEALGORITHMDATA_H
