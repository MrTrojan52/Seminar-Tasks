//
// Created by trojan52.
//

#include <fstream>
#include <numeric>

#include "SupplierTask.h"

void CSupplierTask::PopulateTaskFromFile(const std::string& sFile)
{
    ClearTaskData();
    std::ifstream iFile(sFile);

    if (iFile.is_open())
    {
        iFile >> m_nSuppliersCount >> m_nConsumersCount >> m_nTactsCount;

        std::string sLabel;
        while(iFile >> sLabel)
        {
            if (sLabel == "a:")
            {
                m_vSuppliersTotalProduct.resize(m_nSuppliersCount);
                for (int i = 0; i < m_nSuppliersCount; ++i)
                {
                    iFile >> m_vSuppliersTotalProduct[i];
                }
            }
            else if (sLabel == "b:")
            {
                m_mSuppliersProductPerTact.resize(m_nSuppliersCount);
                for (int i = 0; i < m_nSuppliersCount; ++i)
                {
                    m_mSuppliersProductPerTact[i].resize(m_nTactsCount);
                    for (int j = 0; j < m_nTactsCount; ++j)
                    {
                        iFile >> m_mSuppliersProductPerTact[i][j];
                    }
                }
            }
            else if (sLabel == "c:")
            {
                m_mConsumersUsedProductPerTact.resize(m_nConsumersCount);
                for (int i = 0; i < m_nConsumersCount; ++i)
                {
                    m_mConsumersUsedProductPerTact[i].resize(m_nTactsCount);
                    for (int j = 0; j < m_nTactsCount; ++j)
                    {
                        iFile >> m_mConsumersUsedProductPerTact[i][j];
                    }
                }
            }
            else if (sLabel == "D:")
            {
                m_slSuppliers.resize(m_nConsumersCount);
                int nCurrentVal = 0;
                iFile >> nCurrentVal;
                for (int i = 0; i < m_nConsumersCount; ++i)
                {
                    m_slSuppliers[i].insert(nCurrentVal);
                    int nPrevValue = nCurrentVal;
                    iFile >> nCurrentVal;
                    if (nCurrentVal > nPrevValue)
                    {
                        --i;
                    }
                }
            }
        }

        m_nBandwidth = std::accumulate(m_vSuppliersTotalProduct.begin(),
                m_vSuppliersTotalProduct.end(),
                0);
        ValidateTask();
    }
    else
    {
        throw std::invalid_argument("File can't be opened.");
    }
}

void CSupplierTask::ClearTaskData()
{
    m_nSuppliersCount = -1;
    m_nConsumersCount = -1;
    m_nTactsCount = -1;
    m_nSolution = -1;
    m_nBandwidth = -1;

    m_vSuppliersTotalProduct.clear();
    m_mConsumersUsedProductPerTact.clear();
    m_mSuppliersProductPerTact.clear();
    m_slSuppliers.clear();
}

void CSupplierTask::ValidateTask() const
{
    if ((m_nSuppliersCount <= 0) ||
        (m_nConsumersCount <= 0) ||
        (m_nTactsCount <= 0) ||
        (m_nBandwidth <= 0))
    {
        throw std::invalid_argument("Incorrect task!");
    }
}

void CSupplierTask::SolveTask()
{
    CreateFlowNetwork();
    m_nSolution = m_pSolver->SolveFlowTask(m_pFlowNetwork);
}

void CSupplierTask::CreateFlowNetwork()
{
    m_pFlowNetwork.reset(new CFlowNetwork);
    m_pFlowNetwork->SetSourceNode(new CFlowNetworkNode(eSOURCE));
    m_pFlowNetwork->SetStockNode(new CFlowNetworkNode(eSTOCK));

    m_vnSuppliersTotal.reserve(m_nSuppliersCount);
    for (int i = 0; i < m_nSuppliersCount; ++i)
    {
        m_vnSuppliersTotal.emplace_back(new CFlowNetworkNode(eSUPPLIER));
    }

    m_vnSuppliersPartial.reserve(m_nSuppliersCount * m_nTactsCount);
    for (int i = 0; i < m_nSuppliersCount; ++i)
    {
        for (int t = 0; t < m_nTactsCount; ++t)
        {
            m_vnSuppliersPartial.emplace_back(new CFlowNetworkNode(eSUPPLIER_PARTIAL));
            m_vnSuppliersTotal[i]->AddChild(m_vnSuppliersPartial.back(), m_mSuppliersProductPerTact[i][t]);
        }
    }

    m_vnConsumersPartial.reserve(m_nConsumersCount * m_nTactsCount);
    for (int i = 0; i < m_nConsumersCount; ++i)
    {
        for (int t = 0; t < m_nTactsCount; ++t)
        {
            m_vnConsumersPartial.emplace_back(new CFlowNetworkNode(eCONSUMER_PARTIAL));
            for (int avsupp : m_slSuppliers[i])
            {
                m_vnSuppliersPartial[(avsupp - 1) * m_nTactsCount + t]->AddChild(m_vnConsumersPartial.back(), m_nBandwidth);
            }
            m_vnConsumersPartial.back()->AddChild(m_pFlowNetwork->GetStockNode(), m_mConsumersUsedProductPerTact[i][t]);
        }
    }
}
