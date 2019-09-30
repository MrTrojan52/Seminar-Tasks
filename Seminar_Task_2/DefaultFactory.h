//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_2_DEFAULTFACTORY_H
#define SEMINAR_TASK_2_DEFAULTFACTORY_H

#include <memory>

#include "Definitions.h"
#include "IBranchingStrategy.h"
#include "ILowerBoundStrategy.h"
#include "IUpperBoundStrategy.h"

class DefaultFactory
{
    public:
        DefaultFactory(const DefaultFactory&) = delete;
        DefaultFactory& operator=(DefaultFactory&) = delete;
        static const DefaultFactory& Instance();

        static std::unique_ptr<IBranchingStrategy> GetBranchingStrategy(etBranchingStrategy eStrategy);
        static std::unique_ptr<ILowerBoundStrategy> GetLowerBoundStrategy(etLowerBoundStrategy eStrategy);
        static std::unique_ptr<IUpperBoundStrategy> GetUpperBoundStrategy(etUpperBoundStrategy eStrategy);

    private:
        DefaultFactory() = default;
};


#endif //SEMINAR_TASK_2_DEFAULTFACTORY_H
