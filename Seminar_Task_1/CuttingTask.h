//
// Created by Trojan on 27.09.2019.
//

#ifndef SPECSEM_LAB1_CCUTTINGTASK_H
#define SPECSEM_LAB1_CCUTTINGTASK_H
#include <string>
#include <memory>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <exception>
#include <iterator>
#include <numeric>

#include "Definitions.h"
#include "IAlgorithm.h"
#include "DefaultFactory.h"
#include "BaseAlgorithmData.h"

namespace fs = std::filesystem;


template<typename T = int>
class CCuttingTask
{
    static_assert(std::is_arithmetic<T>::value, "The template parameter for CuttingTask should be an arithmetic type!");
public:
    explicit CCuttingTask(etAlgorithm eAlgorithm, etStrategy = eSTRATEGY_AS_IS);
    void SetTasksPath(const std::string& sPath);
    virtual void Solve();
    [[nodiscard]] int GetLowerBound() const;

private:
    IAlgorithmData<T>* GetAlgorithmData(std::vector<T>& vLenghts);
    void PopulateTaskFromFile(const std::string& sFilePath);
    void ClearTaskData();
    int CalcCrit(const std::vector<int>& vSolution) const;
    [[nodiscard]] std::vector<std::string> ExtractFilesFromPath() const;
    etAlgorithm m_eAlgorithm;
    etStrategy m_eStrategy;
    IAlgorithm<T>* m_pAlgorithm;
    IStrategy<T>* m_pStrategy;
    std::string m_sTasksPath;
    std::vector<T> m_vLenghts;
    std::vector<int> m_vSolution;
    T m_nRodLength;
};

template<typename T>
CCuttingTask<T>::CCuttingTask(etAlgorithm eAlgorithm, etStrategy eStrategy)
: m_nRodLength(0),
  m_eAlgorithm(eAlgorithm),
  m_eStrategy(eStrategy)

{
    m_pAlgorithm = DefaultFactory<T>::GetAlgorithmByEnum(m_eAlgorithm);
    m_pStrategy = DefaultFactory<T>::GetStrategyByEnum(m_eStrategy);
}

template<typename T>
void CCuttingTask<T>::SetTasksPath(const std::string& sPath)
{
    m_sTasksPath = sPath;
}

template<typename T>
void CCuttingTask<T>::Solve()
{
    std::vector<std::string> vFiles = ExtractFilesFromPath();
    if (vFiles.empty())
    {
        throw std::logic_error("Incorrect path.");
    }

    for (auto& file : vFiles)
    {
        PopulateTaskFromFile(file);
        if (m_eStrategy == eSTRATEGY_AS_IS)
        {
            m_vSolution = m_pAlgorithm->GetSolution(GetAlgorithmData(m_vLenghts));
            continue;
        }
        
        std::vector<std::vector<T> > vvUpdatedLenghts = m_pStrategy->GetUpdatedLengths(m_vLenghts);
        int nMinCrit = m_vLenghts.size() + 1;
        for (auto vLenghts : vvUpdatedLenghts)
        {
            std::vector<int> vSolution = m_pAlgorithm->GetSolution(GetAlgorithmData(vLenghts));
            int nCurrentCrit = CalcCrit(vSolution);
            if (nCurrentCrit < nMinCrit)
            {
                nMinCrit = nCurrentCrit;
                m_vSolution = vSolution;
            }
        }

    }
    // TODO: Realize solving


}

template<typename T>
std::vector<std::string> CCuttingTask<T>::ExtractFilesFromPath() const
{
    std::vector<std::string> vFiles;
    if (!m_sTasksPath.empty())
    {
        fs::path sPath(m_sTasksPath);

        if (sPath.has_filename())
        {
            // If we have only one file then make sure that this file
            // exists and add it to vector.
            if (fs::exists(sPath))
            {
                vFiles.push_back(m_sTasksPath);
            }
        }
        else
        {
            // If we have a directory as a path then we should
            // add all FILE_DEFAULT_EXTENSION files whose names begins with FILE_DEFAULT_FILENAME
            for (auto& p : fs::directory_iterator(sPath))
            {
                const fs::path& filepath = p.path();
                if (filepath.has_filename() &&
                    filepath.has_extension() &&
                    filepath.extension().compare(FILE_DEFAULT_EXTENSION))
                {
                    std::string filename = filepath.filename().string();
                    if (filename.find(FILE_DEFAULT_FILENAME) != std::string::npos)
                    {
                        vFiles.push_back(filepath.string());
                    }
                }
            }
        }
    }
    vFiles.shrink_to_fit();
    std::sort(vFiles.begin(), vFiles.end());
    return vFiles;
}

template<typename T>
void CCuttingTask<T>::ClearTaskData()
{
    m_nRodLength = 0;
    m_vLenghts.clear();
}

template<typename T>
void CCuttingTask<T>::PopulateTaskFromFile(const std::string& sFilePath)
{
    // Clear previously populated data
    ClearTaskData();
    std::ifstream iFile(sFilePath);
    if (iFile.is_open())
    {
        // The first number in a file is a Rod Length
        iFile >> m_nRodLength;
        std::copy(std::istream_iterator<T>(iFile), {}, std::back_inserter(m_vLenghts));
        m_vLenghts.shrink_to_fit();
    }
    else
    {
        throw std::logic_error("Cannot open the file!");
    }
}

template<typename T>
int CCuttingTask<T>::GetLowerBound() const
{
    auto sum = std::accumulate(m_vLenghts.begin(), m_vLenghts.end(), T());
    int relation = static_cast<int>(sum / m_nRodLength);
    return (sum % m_nRodLength > 0 ? relation + 1 : relation);
}

template<typename T>
IAlgorithmData<T>* CCuttingTask<T>::GetAlgorithmData(std::vector<T>& vLengths)
{
    IAlgorithmData<T>* pAlgorithmData = nullptr;
    switch(m_eAlgorithm)
    {
        case eALGORITHM_GREEDY:
            pAlgorithmData = new BaseAlgorithmData<T>;
            pAlgorithmData->SetDataByAttribute(ATTR_ROD_LENGTH, m_nRodLength);
            if (vLengths.empty())
            {
                pAlgorithmData->SetDataByAttribute(ATTR_LENGHTS_ARRAY, m_vLenghts);
            }
            else
            {
                pAlgorithmData->SetDataByAttribute(ATTR_LENGHTS_ARRAY, vLengths);
            }
            break;
        default:
            break;
    }
    return pAlgorithmData;
}

template<typename T>
int CCuttingTask<T>::CalcCrit(const std::vector<int>& vSolution) const
{
    return *std::max_element(vSolution.begin(), vSolution.end()) + 1;
}


#endif //SPECSEM_LAB1_CCUTTINGTASK_H
