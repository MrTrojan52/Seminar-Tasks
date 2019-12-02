//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_ALGORITHMFACTORY_H
#define SEMINAR_TASK_4_ALGORITHMFACTORY_H

#include <memory>
#include "Definitions.h"
#include "IFlowTaskSolver.h"


class CAlgorithmFactory
{
    public:
        CAlgorithmFactory(const CAlgorithmFactory&) = delete;
        CAlgorithmFactory& operator=(CAlgorithmFactory&) = delete;
        static const CAlgorithmFactory& Instance();

        [[nodiscard]] std::unique_ptr<IFlowTaskSolver> GetAlgorithm(etAlgorithm eAlg) const;

    private:
        CAlgorithmFactory() = default;
};


#endif //SEMINAR_TASK_4_ALGORITHMFACTORY_H
