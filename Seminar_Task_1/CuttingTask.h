//
// Created by Trojan on 27.09.2019.
//

#ifndef SPECSEM_LAB1_CCUTTINGTASK_H
#define SPECSEM_LAB1_CCUTTINGTASK_H
#include <string>
#include <memory>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <exception>

#include "Definitions.h"
#include "IAlgorithm.h"

namespace fs = std::filesystem;


template<typename T = int>
class CCuttingTask
{
    static_assert(std::is_arithmetic<T>::value, "The template parameter for CuttingTask should be an arithmetic type!");
public:
    explicit CCuttingTask(IAlgorithm<T>*);
    void SetTasksPath(const std::string& sPath);
    virtual void Solve();

private:
    void PopulateTaskFromFile(const std::string& sFilePath);
    [[nodiscard]] std::vector<std::string> ExtractFilesFromPath() const;
    IAlgorithm<T>* m_pAlgorithm;
    std::string m_sTasksPath;
    std::vector<T> m_vLenghts;
    T m_nRodLength;
};

template<typename T>
CCuttingTask<T>::CCuttingTask(IAlgorithm<T>* pAlgorithm)
: m_nRodLength(0)
{
    m_pAlgorithm = pAlgorithm;
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
void CCuttingTask<T>::PopulateTaskFromFile(const std::string& sFilePath)
{
    std::ifstream iFile(sFilePath);
    if (iFile.is_open())
    {
        bool bFirstNumber = true;
        T length;
        while (iFile >> length)
        {
            if (bFirstNumber)
            {
                m_nRodLength = length;
                bFirstNumber = false;
            }
            else
            {
                m_vLenghts.push_back(length);
            }
        }
        m_vLenghts.shrink_to_fit();
    }
    else
    {
        throw std::logic_error("Cannot open the file!");
    }

}



#endif //SPECSEM_LAB1_CCUTTINGTASK_H
