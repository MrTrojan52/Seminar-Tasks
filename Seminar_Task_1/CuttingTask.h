//
// Created by Trojan on 27.09.2019.
//

#ifndef SPECSEM_LAB1_CCUTTINGTASK_H
#define SPECSEM_LAB1_CCUTTINGTASK_H
#include <string>
#include <memory>
#include <filesystem>

#include "IAlgorithm.h"


class CCuttingTask {
public:
    explicit CCuttingTask(const IAlgorithm*);
    void SetTasksPath(const std::string&);
    virtual void Solve();

private:
    bool IsValidTaskPath();
    std::shared_ptr<IAlgorithm> m_pAlgorithm;
    std::string m_sTasksPath;
};


#endif //SPECSEM_LAB1_CCUTTINGTASK_H
