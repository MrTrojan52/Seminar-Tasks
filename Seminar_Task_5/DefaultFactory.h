//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_5_DEFAULTFACTORY_H
#define SEMINAR_TASK_5_DEFAULTFACTORY_H


#include <memory>
#include "IReductionStrategy.h"

class CDefaultFactory
{
    public:
        CDefaultFactory(const CDefaultFactory&) = delete;
        CDefaultFactory& operator=(CDefaultFactory&) = delete;
        static const CDefaultFactory& Instance();

        [[nodiscard]] std::unique_ptr<IReductionStrategy> GetReductionStrategy(etREDUCTION eReduction) const;

    private:
        CDefaultFactory() = default;
};


#endif //SEMINAR_TASK_5_DEFAULTFACTORY_H
