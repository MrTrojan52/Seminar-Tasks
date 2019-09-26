//
// Created by Trojan on 27.09.2019.
//

#include "CuttingTask.h"

CCuttingTask::CCuttingTask(const IAlgorithm * pAlgorithm)
{
    m_pAlgorithm = std::make_shared<IAlgorithm>(pAlgorithm);
}

void CCuttingTask::SetTasksPath(const std::string& sPath)
{
    m_sTasksPath = sPath;
}

void CCuttingTask::Solve()
{
    bool b = IsValidTaskPath();

}

bool CCuttingTask::IsValidTaskPath() {
    bool bValid = false;
    if (!m_sTasksPath.empty())
    {
        std::filesystem::path spath(m_sTasksPath);
        bValid = spath.has_filename();
    }
    return bValid;
}
