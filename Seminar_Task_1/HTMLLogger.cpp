//
// Created by trojan52 on 29.09.2019.
//

#include <fstream>

#include "HTMLLogger.h"

#include "Definitions.h"

HTMLLogger::HTMLLogger(const std::string& rFileName)
: m_sFileName(rFileName)
{

}

void HTMLLogger::PrintData()
{
    std::ofstream oHTMLFile(m_sFileName);

    if (oHTMLFile.is_open())
    {
        std::string sHtml_data = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">\n \
                                <html>\n \
                                <head>\n \
                                <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\"/>\n \
                                <title></title>\n \
                                <style type=\"text/css\">\n \
                                body,div,table,thead,tbody,tfoot,tr,th,td,p { font-family:\"Liberation Sans\"; font-size:x-small }\n \
                                a.comment-indicator:hover + comment { background:#ffd; position:absolute; display:block; border:1px solid black; padding:0.5em;  }\n \
                                a.comment-indicator { background:red; display:inline-block; border:1px solid black; width:0.5em; height:0.5em;  }\n \
                                comment { display:none;  }\n \
                                </style>\n \
                                </head>\n \
                                <body>\n \
                                <table border=\"1\" width=\"100%\" >";
        sHtml_data += AddHeaders();

        for (auto& row : m_vRecords)
        {
            sHtml_data += AddRow(row);
        }

        sHtml_data += "</table>\n</body>\n</html>";

        oHTMLFile << sHtml_data;
        oHTMLFile.close();
    }
    else
    {
        throw std::invalid_argument("Incorrect file name for logging!");
    }
}

std::string HTMLLogger::AddRow(std::vector<std::string> &vRow)
{
    std::string sTableRowData = "<tr>\n";
    for (auto& value : vRow)
    {
        sTableRowData += AddValue(value);
    }
    sTableRowData += "</tr>\n";
    return sTableRowData;
}

std::string HTMLLogger::AddValue(std::string &sValue, size_t colspan, size_t rowspan)
{
    std::string sValueData = "<td colspan=\"" + std::to_string(colspan) + "\" rowspan=\"" + std::to_string(rowspan) + "\" align=\"center\">";
    sValueData += sValue;
    sValueData += "</td>\n";
    return sValueData;
}

std::string HTMLLogger::AddHeaders()
{
    std::string sHeaderRowData = "<tr>\n";
    int nStrategyCount = 0;
    for (auto& header : m_vHeaders)
    {
        if (GetStrategyEnumByName(header) != eSTRATEGY_UNKNOWN)
        {
            ++nStrategyCount;
            sHeaderRowData += AddValue(header, TABLE_DEFAULT_COLSPAN_FOR_STRATEGY);
        }
        else
        {
            sHeaderRowData += AddValue(header, 1, TABLE_DEFAULT_ROWSPAN_FOR_HEADER);
        }
    }
    sHeaderRowData += "</tr>\n";

    std::vector<std::string> vSubHeaders;
    for (;nStrategyCount > 0; --nStrategyCount)
    {
        vSubHeaders.emplace_back("res");
        vSubHeaders.emplace_back("(res - l) / l");
        vSubHeaders.emplace_back("(b - res) / b");
    }
    sHeaderRowData += AddRow(vSubHeaders);
    return sHeaderRowData;
}


