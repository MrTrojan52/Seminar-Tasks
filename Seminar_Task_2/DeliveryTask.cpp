//
// Created by trojan52.
//



#include <filesystem>
#include <algorithm>
#include <fstream>
#include <limits>
#include <iostream>

#include "DeliveryTask.h"
#include "DefaultFactory.h"
#include "HTMLLogger.h"

void DeliveryTask::SetTasksPath(const std::string &sPath)
{
    m_sTasksPath = sPath;
}

std::vector<std::string> DeliveryTask::ExtractFilesFromPath() const
{
    namespace fs = std::filesystem;
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

void DeliveryTask::Solve()
{
    std::vector<std::string> vFiles = ExtractFilesFromPath();

    if (vFiles.empty())
    {
        throw std::invalid_argument("Incorrect tasks location path.");
    }
    int nTask = 0;
    InitializeLoggerData();
    double dAverage = 0.0f;
    for (auto& file : vFiles)
    {
        ++nTask;
        std::cout << "Task #" << nTask << std::endl;
        std::vector<std::string> vRow;
        vRow.push_back(std::to_string(nTask));
        PopulateTaskFromFile(file);
        if (IsUsedBasicStrategies())
        {
            FindSolution(false);
            vRow.push_back(std::to_string(m_nCount));
        }
        else
        {
            FindSolution(true);
            int nBasic = m_nCount;
            vRow.push_back(std::to_string(nBasic));

            ClearVariables();
            FindSolution(false);
            PopulateRowForSolution(vRow, nBasic, m_nCount);
            dAverage += (nBasic - (double)m_nCount) / (float)nBasic;
        }
        m_pLogger->AddRow(vRow);
    }
    // Add footer row for custom strategies
    if (!IsUsedBasicStrategies())
    {
        if (!vFiles.empty())
        {
            dAverage /= vFiles.size();
        }
        else
        {
            dAverage = 0.0;
        }
        std::vector<std::string> vRow = {"Total", "", "", std::to_string(dAverage)};
        m_pLogger->AddRow(vRow);
    }
}

void DeliveryTask::PopulateTaskFromFile(const std::string &sFile)
{
    // Clear previously populated data
    ClearTaskData();
    std::ifstream iFile(sFile);
    if (iFile.is_open())
    {
        // First number in file is a Task size
        iFile >> m_nTaskSize;

        // Next <task_size> numbers is a deadlines
        m_vDeadlines.resize(m_nTaskSize);
        for (size_t i = 0; i < m_nTaskSize; ++i)
        {
            iFile >> m_vDeadlines[i];
        }

        // Next <task_size + 1> x <task_size + 1> numbers is a
        // delivery times
        m_mTimes.resize(m_nTaskSize + 1);
        for (size_t row = 0; row <= m_nTaskSize; ++row)
        {
            m_mTimes[row].resize(m_nTaskSize + 1);
            for (size_t col = 0; col <= m_nTaskSize; ++col)
            {
                iFile >> m_mTimes[row][col];
            }
        }
    }
    else
    {
        throw std::invalid_argument("File can't be opened.");
    }
}

void DeliveryTask::ClearTaskData()
{
    m_nTaskSize = 0;
    m_mTimes.clear();
    m_vDeadlines.clear();
}

void DeliveryTask::UpdateBounds()
{
    m_viRecord = VertexInfo({}, std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    for (VertexInfo& info : m_vVertexes)
    {
        info.nLowerBound = m_pLowerBoundStrategy->GetLowerBound(info.vVertex, m_vDeadlines, m_mTimes);
        info.nUpperBound = m_pUpperBoundStrategy->GetUpperBound(info.vVertex, m_vDeadlines, m_mTimes);
        UpdateRecord(info);
    }
}


void DeliveryTask::UpdateBounds(VertexInfo& rVertex)
{
    rVertex.nLowerBound = m_pLowerBoundStrategy->GetLowerBound(rVertex.vVertex, m_vDeadlines, m_mTimes);
    rVertex.nUpperBound = m_pUpperBoundStrategy->GetUpperBound(rVertex.vVertex, m_vDeadlines, m_mTimes);
    UpdateRecord(rVertex);
}

DeliveryTask::DeliveryTask(etBranchingStrategy eBranching,
                           etLowerBoundStrategy eLower,
                           etUpperBoundStrategy eUpper)
: m_nTaskSize(0),
  m_nCount(0),
  m_viRecord({}, std::numeric_limits<int>::max(), std::numeric_limits<int>::max())
{
    SetBranchingStrategy(eBranching);
    SetLowerBoundStrategy(eLower);
    SetUpperBoundStrategy(eUpper);
    m_pLogger = std::make_unique<HTMLLogger>(SAVE_HTML_DEFAULT_FILENAME);
}

void DeliveryTask::SetBranchingStrategy(etBranchingStrategy eBranchingStrategy)
{
    m_eBranchingStrategy = eBranchingStrategy;
    m_pBranchingStrategy = DefaultFactory::Instance().GetBranchingStrategy(m_eBranchingStrategy);
}

void DeliveryTask::SetLowerBoundStrategy(etLowerBoundStrategy eLowerBoundStrategy)
{
    m_eLowerBoundStrategy = eLowerBoundStrategy;
    m_pLowerBoundStrategy = DefaultFactory::Instance().GetLowerBoundStrategy(m_eLowerBoundStrategy);
}

void DeliveryTask::SetUpperBoundStrategy(etUpperBoundStrategy eUpperBoundStrategy)
{
    m_eUpperBoundStrategy = eUpperBoundStrategy;
    m_pUpperBoundStrategy = DefaultFactory::Instance().GetUpperBoundStrategy(m_eUpperBoundStrategy);

}

void DeliveryTask::DoBoundsAndTrees()
{
    VertexInfo viVertex;
    while (true)
    {
        viVertex = m_pBranchingStrategy->Branching(m_vVertexes);
        AddVertexesAfterBranching(viVertex);
        if ((viVertex.vVertex.size() == m_nTaskSize) && viVertex.IsBoundsEqual())
        {
            break;
        }
        ClipVertexes();
    }
}

void DeliveryTask::AddVertexesAfterBranching(VertexInfo& rVertex)
{
    bool bRecordDeleted = (m_viRecord == rVertex);
    for (size_t i = 0; i < m_nTaskSize; ++i)
    {
        if (std::find(CONTAINER_BOUNDS(rVertex.vVertex), (i + 1)) == rVertex.vVertex.end())
        {
            ++m_nCount;
            rVertex.vVertex.push_back((i + 1));
            UpdateBounds(rVertex);
            m_vVertexes.emplace_back(rVertex);
            rVertex.vVertex.pop_back();
        }
    }
    if (bRecordDeleted)
    {
        UpdateBounds();
    }
}

void DeliveryTask::ClipVertexes()
{
    for (int i = 0; i < m_vVertexes.size(); ++i)
    {
        if (m_vVertexes[i].nLowerBound >= m_viRecord.nUpperBound)
        {
            if (m_vVertexes[i] != m_viRecord)
            {
                std::swap(m_vVertexes[i], m_vVertexes.back());
                m_vVertexes.pop_back();
                --i;
            }
        }
    }
}

void DeliveryTask::UpdateRecord(VertexInfo& rVertex)
{
    if (rVertex.nUpperBound < m_viRecord.nUpperBound)
    {
        m_viRecord = rVertex;
    }
}

void DeliveryTask::PrintData()
{
    m_pLogger->PrintData();
}

void DeliveryTask::InitializeLoggerData()
{
    m_pLogger->AddHeader("#");
    m_pLogger->AddHeader("BASIC");
    if (!IsUsedBasicStrategies())
    {
        m_pLogger->AddHeader("CUSTOM");
        m_pLogger->AddHeader("(BASIC - CUSTOM) / BASIC");
    }

}

void DeliveryTask::PopulateRowForSolution(std::vector<std::string>& vRow, int nBasic, int nCustom)
{
    vRow.push_back(std::to_string(nCustom));
    vRow.push_back(std::to_string((double)(nBasic - nCustom) / nBasic));
}

bool DeliveryTask::IsUsedBasicStrategies()
{
    return ((m_eBranchingStrategy == eBRANCHING_BASIC) &&
            (m_eLowerBoundStrategy == eLOWERBOUND_BASIC) &&
            (m_eUpperBoundStrategy == eUPPERBOUND_BASIC));
}

void DeliveryTask::FindSolution(bool bBaseForce)
{
    etBranchingStrategy eCurrentBranching = m_eBranchingStrategy;
    etUpperBoundStrategy eCurrentUpper = m_eUpperBoundStrategy;
    etLowerBoundStrategy eCurrentLower = m_eLowerBoundStrategy;

    if (bBaseForce)
    {
        SetBranchingStrategy(eBRANCHING_BASIC);
        SetUpperBoundStrategy(eUPPERBOUND_BASIC);
        SetLowerBoundStrategy(eLOWERBOUND_BASIC);
    }

    m_vVertexes.resize(m_nTaskSize);
    for (size_t i = 0; i < m_nTaskSize; ++i)
    {
        m_vVertexes[i] = VertexInfo({static_cast<int>(i + 1)});
    }
    UpdateBounds();
    DoBoundsAndTrees();

    if (bBaseForce)
    {
        SetBranchingStrategy(eCurrentBranching);
        SetUpperBoundStrategy(eCurrentUpper);
        SetLowerBoundStrategy(eCurrentLower);
    }
}

void DeliveryTask::ClearVariables()
{
    m_nCount = 0;
    m_viRecord = VertexInfo({}, std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    m_vVertexes.clear();
}

