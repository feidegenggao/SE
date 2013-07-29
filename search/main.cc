/*
 * ============================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/13 16:10:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "inverted_index.h"
#include    "base/log.h"
using namespace base;

#include    <iostream>
using namespace std;

void PrintDocSet(const DocSetT &result_doc_set);

int main(int argc, char *argv[])
{
    string query_str;
    if (argc == 2)
    {
        query_str = string (argv[1]);
    }
    else if (argc == 1)
    {
        query_str = string ("电子科技大学");
    }
    else
    {
        LOG_ERROR << "Argument error";
        LOG_END;
        return -1;
    }

    DocSetT result_doc_set = InvertedIndex::GetInstance()->Query(query_str);
    PrintDocSet(result_doc_set);

    LOG_END;
    return 0;
}

void PrintDocSet(const DocSetT &result_doc_set)
{
    for (DocSetTConstItor it = result_doc_set.begin(); it != result_doc_set.end(); ++it)
    {
        cout << "doc_id:" << *it << endl;
    }
}
