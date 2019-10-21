//
// Created by trojan52.
//
#include <filesystem>
#include <algorithm>
#include <fstream>

#include "BaseKnapsackTask.h"

BaseKnapsackTask::BaseKnapsackTask()
: m_nPerfomance(0),
  m_nNumberOfOrders(0),
  m_nCalculatedProfit(0)
{

}

void BaseKnapsackTask::SetTasksPath(const std::string& sPath)
{
    m_sTasksPath = sPath;
}

std::vector<std::string> BaseKnapsackTask::ExtractFilesFromPath() const
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

void BaseKnapsackTask::PopulateTaskFromFile(const std::string& sFile)
{
    ClearTaskData();
    std::ifstream iFile(sFile);
    if (iFile.is_open())
    {
        // First number in a file is a Perfomance
        iFile >> m_nPerfomance;

        // Second number in a file is a Number of orders
        iFile >> m_nNumberOfOrders;

        m_vOrders.resize(m_nNumberOfOrders);
        m_vbX.resize(m_nNumberOfOrders);

        for (size_t i = 0; i < m_nNumberOfOrders; ++i)
        {
            iFile >> m_vOrders[i].m_nLaborInput;
        }

        for (size_t i = 0; i < m_nNumberOfOrders; ++i)
        {
            iFile >> m_vOrders[i].m_nProfit;
            m_vOrders[i].m_nOriginalIndex = i;
        }
    }
    else
    {
        throw std::invalid_argument("File can't be opened.");
    }
}

void BaseKnapsackTask::ClearTaskData()
{
    m_nPerfomance = 0;
    m_nNumberOfOrders = 0;
    m_nCalculatedProfit = 0;
    m_vOrders.clear();
    m_vbX.clear();
}

void BaseKnapsackTask::Solve()
{
    std::vector<std::string> vFiles = ExtractFilesFromPath();

    if (vFiles.empty())
    {
        throw std::invalid_argument("Incorrect tasks location path.");
    }

    for (auto& file : vFiles)
    {
        PopulateTaskFromFile(file);
        doSolve();
    }
}
