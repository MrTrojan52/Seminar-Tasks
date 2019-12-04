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
    m_nSolution = m_pSolver->SolveFlowTask(m_pFlowNetwork, GetTaskData()).second;
}

void CSupplierTask::CreateFlowNetwork()
{
    m_pFlowNetwork.reset(new CFlowNetwork);

    m_pFlowNetwork->AddNode(new CFlowNode(eSOURCE));


    // Suppliers
    for (int i = 0; i < m_nSuppliersCount; ++i)
    {
       m_pFlowNetwork->AddNode(new CFlowNode(eSUPPLIER));
       auto pFArc = new CFlowArc(0, (i + 1), m_vSuppliersTotalProduct[i]);
       auto pBArc = new CFlowArc((i + 1), 0, 0);
       m_pFlowNetwork->GetNodeByIndex(0)->AddArc(pFArc, pBArc);
       m_pFlowNetwork->GetNodeByIndex(i + 1)->AddArc(pBArc, pFArc);
    }

    // Suppliers per tact

    for (int i = 0; i < m_nSuppliersCount; ++i)
    {
        for (int t = 0; t < m_nTactsCount; ++t)
        {
            int nFrom = i + 1;
            int nTo = m_nSuppliersCount + m_nTactsCount * i + t + 1;
            m_pFlowNetwork->AddNode(new CFlowNode(eSUPPLIER_PARTIAL));
            auto pFArc = new CFlowArc(nFrom, nTo, m_mSuppliersProductPerTact[i][t]);
            auto pBArc = new CFlowArc(nTo, nFrom, 0);
            m_pFlowNetwork->GetNodeByIndex(nFrom)->AddArc(pFArc, pBArc);
            m_pFlowNetwork->GetNodeByIndex(nTo)->AddArc(pBArc, pFArc);
        }
    }

    // Consumers

    for (int i = 0; i < m_nConsumersCount; ++i)
    {
        for (int t = 0; t < m_nTactsCount; ++t)
        {
            m_pFlowNetwork->AddNode(new CFlowNode(eCONSUMER_PARTIAL));
        }
    }

    for (int i = 0; i < m_nConsumersCount; ++i)
    {
        for (int t = 0; t < m_nTactsCount; ++t)
        {
            for (auto suppl : m_slSuppliers[i])
            {
                int nNum = m_nSuppliersCount * m_nTactsCount + m_nSuppliersCount + 1;
                int nFrom = m_nSuppliersCount + m_nTactsCount * (suppl - 1) + t + 1;
                int nTo = nNum + m_nTactsCount * i + t;

                auto pFArc = new CFlowArc(nFrom, nTo, m_mSuppliersProductPerTact[suppl - 1][t]);
                auto pBArc = new CFlowArc(nTo, nFrom, 0);

                m_pFlowNetwork->GetNodeByIndex(nFrom)->AddArc(pFArc, pBArc);
                m_pFlowNetwork->GetNodeByIndex(nTo)->AddArc(pBArc, pFArc);
            }
        }
    }

    // Stock

    m_pFlowNetwork->AddNode(new CFlowNode(eSTOCK));
    for (int i = 0; i < m_nConsumersCount; ++i)
    {
        for (int t = 0; t < m_nTactsCount; ++t)
        {
            int nFrom = m_nSuppliersCount * m_nTactsCount + m_nSuppliersCount + 1 + m_nTactsCount * i + t;
            int nTo = m_pFlowNetwork->GetNodesCount() - 1;

            auto pFArc = new CFlowArc(nFrom, nTo, m_mConsumersUsedProductPerTact[i][t]);
            auto pBArc = new CFlowArc(nTo, nFrom, 0);

            m_pFlowNetwork->GetNodeByIndex(nFrom)->AddArc(pFArc, pBArc);
            m_pFlowNetwork->GetNodeByIndex(nTo)->AddArc(pBArc, pFArc);
        }
    }

}

int CSupplierTask::GetMaxFlow() const
{
    int nMaxFlow = 0;
    for (int i = 0; i < m_nConsumersCount; ++i)
    {
        for (int t = 0; t < m_nTactsCount; ++t)
        {
            nMaxFlow += m_mConsumersUsedProductPerTact[i][t];
        }
    }

    return nMaxFlow;
}

TaskData CSupplierTask::GetTaskData() const
{
    TaskData Data;
    Data.nSuppliersCount = m_nSuppliersCount;
    Data.nConsumersCount = m_nConsumersCount;
    Data.nTactsCount = m_nTactsCount;
    Data.m_mSuppliersProductPerTact = &m_mSuppliersProductPerTact;
    Data.m_mConsumersUsedProductPerTact = &m_mConsumersUsedProductPerTact;
    Data.m_vSuppliersTotalProduct = &m_vSuppliersTotalProduct;
    Data.nMaxFlow = GetMaxFlow();

    return Data;
}
