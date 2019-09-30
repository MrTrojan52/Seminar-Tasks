//
// Created by trojan52.
//

#include "DeliveryTask.h"

#include <filesystem>
#include <algorithm>
#include <fstream>

#include "Definitions.h"

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
    for (auto& file : vFiles)
    {
        PopulateTaskFromFile(file);
        return;
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
    m_vVertexes.clear();
}
