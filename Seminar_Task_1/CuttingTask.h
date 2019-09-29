//
// Created by Trojan.
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
#include "ILogger.h"
#include "HTMLLogger.h"

namespace fs = std::filesystem;


template<typename T = int>
class CCuttingTask
{
    static_assert(std::is_arithmetic<T>::value, "The template parameter for CuttingTask should be an arithmetic type!");
public:
    explicit CCuttingTask(etAlgorithm eAlgorithm, etStrategy = eSTRATEGY_AS_IS);
    void SetTasksPath(const std::string& sPath);
    virtual void Solve();
    void PrintData();
    [[nodiscard]] int GetLowerBound() const;

private:
    std::unique_ptr<IAlgorithmData<T>> GetAlgorithmData(std::vector<T>& vLengths);
    void PopulateTaskFromFile(const std::string& sFilePath);
    void ClearTaskData();
    void FindSolution(etStrategy eStrategy = eSTRATEGY_UNKNOWN);
    void FillRowForSolution(std::vector<std::string>& vRow, int nSolution, int nLowerBound, int nBasicSolution);
    void SetStrategy(etStrategy eStrategy);
    void InitializeLoggerData();
    [[nodiscard]] int CalcCrit(const std::vector<int>& vSolution) const;
    [[nodiscard]] std::vector<std::string> ExtractFilesFromPath() const;
    etAlgorithm m_eAlgorithm;
    etStrategy m_eStrategy;

    std::unique_ptr<IAlgorithm<T>>  m_pAlgorithm;
    std::unique_ptr<IStrategy<T>> m_pStrategy;
    std::unique_ptr<ILogger>  m_pLogger;

    std::string m_sTasksPath;
    std::vector<T> m_vLengths;
    std::vector<int> m_vSolution;
    T m_nRodLength;
};

template<typename T>
CCuttingTask<T>::CCuttingTask(etAlgorithm eAlgorithm, etStrategy eStrategy)
: m_nRodLength(0),
  m_eAlgorithm(eAlgorithm)
{
    m_pAlgorithm = DefaultFactory<T>::GetAlgorithmByEnum(m_eAlgorithm);
    m_pLogger.reset(new HTMLLogger(SAVE_HTML_DEFAULT_FILENAME));
    SetStrategy(eStrategy);
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
    InitializeLoggerData();
    int nTaskNumber = 0;
    for (auto& file : vFiles)
    {
        ++nTaskNumber;
        PopulateTaskFromFile(file);
        std::vector<std::string> vRow;
        vRow.push_back(std::to_string(nTaskNumber));
        vRow.push_back(std::to_string(GetLowerBound()));
        int nLowerBound = GetLowerBound();
        int nBasicSolution = 0;
        if (m_eStrategy == eSTRATEGY_ALL)
        {
            FindSolution(eSTRATEGY_BASIC);
            nBasicSolution = CalcCrit(m_vSolution);
            FillRowForSolution(vRow, nBasicSolution, nLowerBound, nBasicSolution);
            for (size_t nStrategy = eSTRATEGY_BASIC + 1; nStrategy < eSTRATEGY_ALL; ++nStrategy)
            {
                SetStrategy(static_cast<etStrategy>(nStrategy));
                FindSolution();
                int nSolution = CalcCrit(m_vSolution);
                FillRowForSolution(vRow, nSolution, nLowerBound, nBasicSolution);
            }
        }
        else
        {
            FindSolution(eSTRATEGY_BASIC);
            nBasicSolution = CalcCrit(m_vSolution);
            FillRowForSolution(vRow, nBasicSolution, nLowerBound, nBasicSolution);
            FindSolution();
            int nSolution = CalcCrit(m_vSolution);
            FillRowForSolution(vRow, nSolution, nLowerBound, nBasicSolution);
        }
        m_pLogger->AddRow(vRow);
    }
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
    m_vLengths.clear();
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
        std::copy(std::istream_iterator<T>(iFile), {}, std::back_inserter(m_vLengths));
        m_vLengths.shrink_to_fit();
    }
    else
    {
        throw std::logic_error("Cannot open the file!");
    }
}

template<typename T>
int CCuttingTask<T>::GetLowerBound() const
{
    auto sum = std::accumulate(m_vLengths.begin(), m_vLengths.end(), T());
    int relation = static_cast<int>(sum / m_nRodLength);
    return (sum % m_nRodLength > 0 ? relation + 1 : relation);
}

template<typename T>
std::unique_ptr<IAlgorithmData<T>> CCuttingTask<T>::GetAlgorithmData(std::vector<T>& vLengths)
{
    std::unique_ptr<IAlgorithmData<T>> pAlgorithmData = nullptr;
    switch(m_eAlgorithm)
    {
        case eALGORITHM_GREEDY:
            pAlgorithmData.reset(new BaseAlgorithmData<T>);
            pAlgorithmData->SetDataByAttribute(ATTR_ROD_LENGTH, m_nRodLength);
            if (vLengths.empty())
            {
                pAlgorithmData->SetDataByAttribute(ATTR_LENGHTS_ARRAY, m_vLengths);
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

template<typename T>
void CCuttingTask<T>::SetStrategy(etStrategy eStrategy)
{
    m_eStrategy = eStrategy;
    m_pStrategy = DefaultFactory<T>::GetStrategyByEnum(eStrategy);
}

template<typename T>
void CCuttingTask<T>::FindSolution(etStrategy eStrategy)
{
    etStrategy CurrentStrategy = (eStrategy == eSTRATEGY_UNKNOWN) ? m_eStrategy : eStrategy;
    if (CurrentStrategy == eSTRATEGY_AS_IS)
    {
        m_vSolution = m_pAlgorithm->GetSolution(GetAlgorithmData(m_vLengths));
        return;
    }

    std::unique_ptr<IStrategy<T>> pOldStrategy = nullptr;
    if (CurrentStrategy != m_eStrategy)
    {
        pOldStrategy = std::move(m_pStrategy);
        m_pStrategy = DefaultFactory<T>::GetStrategyByEnum(CurrentStrategy);
    }

    m_pStrategy->SetLengths(m_vLengths);
    int nMinCrit = m_vLengths.size() + 1;
    while (!m_pStrategy->IsDone())
    {
        std::vector<T> vCurrentLengths = std::move(m_pStrategy->GetNextLengths());
        std::vector<int> vSolution = m_pAlgorithm->GetSolution(GetAlgorithmData(vCurrentLengths));
        int nCurrentCrit = CalcCrit(vSolution);
        if (nCurrentCrit < nMinCrit)
        {
            nMinCrit = nCurrentCrit;
            m_vSolution = vSolution;
        }
    }

    if (CurrentStrategy != m_eStrategy)
    {
        if (pOldStrategy)
        {
            m_pStrategy = std::move(pOldStrategy);
        }
        else
        {
            m_pStrategy = DefaultFactory<T>::GetStrategyByEnum(m_eStrategy);
        }
    }
}

template<typename T>
void CCuttingTask<T>::InitializeLoggerData()
{
    m_pLogger->AddHeader("#");
    m_pLogger->AddHeader("Lower bound");
    if (m_eStrategy == eSTRATEGY_ALL)
    {
        for (size_t nStrategy = eSTRATEGY_BASIC; nStrategy < eSTRATEGY_ALL; ++nStrategy)
        {
            m_pLogger->AddHeader(GetStrategyNameByEnum(static_cast<etStrategy>(nStrategy)));
        }
    }
    else
    {
        m_pLogger->AddHeader(GetStrategyNameByEnum(eSTRATEGY_BASIC));
        m_pLogger->AddHeader(GetStrategyNameByEnum(m_eStrategy));
    }
}

template<typename T>
void CCuttingTask<T>::FillRowForSolution(std::vector<std::string> &vRow, int nSolution, int nLowerBound, int nBasic)
{
    vRow.push_back(std::to_string(nSolution));
    vRow.push_back(std::to_string((double)(nSolution - nLowerBound) / nLowerBound));
    vRow.push_back(std::to_string((double)(nBasic - nSolution) / nBasic));
}

template<typename T>
void CCuttingTask<T>::PrintData()
{
    m_pLogger->PrintData();
}


#endif //SPECSEM_LAB1_CCUTTINGTASK_H
