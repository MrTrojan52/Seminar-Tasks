//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_DEFAULTFACTORY_H
#define SEMINAR_TASK_3_DEFAULTFACTORY_H

#include <memory>

#include "Definitions.h"
#include "ISortingStrategy.h"

class DefaultFactory
{
    public:
        DefaultFactory(const DefaultFactory&) = delete;
        DefaultFactory& operator=(DefaultFactory&) = delete;
        static const DefaultFactory& Instance();

        [[nodiscard]] std::unique_ptr<ISortingStrategy> GetSortingStrategy(etSORTING_STRATEGY eStrategy) const;
    private:
        DefaultFactory() = default;
};


#endif //SEMINAR_TASK_3_DEFAULTFACTORY_H
