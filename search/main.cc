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

void PrintDocSet(const DocSetT &result_doc_set)
{
    for (DocSetTConstItor it = result_doc_set.begin(); it != result_doc_set.end(); ++it)
    {
        LOG_DEBUG << "doc_id:" << *it;
    }
}

int main()
{
    DocSetT result_doc_set = InvertedIndex::GetInstance()->Query("高校");
    PrintDocSet(result_doc_set);
    result_doc_set = InvertedIndex::GetInstance()->Query("Hello Kityy");
    LOG_END;
    return 0;
}
