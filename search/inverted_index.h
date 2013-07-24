/*
 * ============================================================================
 *
 *       Filename:  inverted_index.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/13 19:00:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     INVERTED_INDEX_HEADER
#define     INVERTED_INDEX_HEADER
#include    "base/singleton.h"
#include    "index_match/inverted_map.h"
#include    <fstream>
#include    <string>

#define     INVERTED_INDEX InvertedIndex::GetInstance()
class InvertedIndex : public base::Singleton<InvertedIndex>
{
    friend class base::Singleton<InvertedIndex>;
    private:
        InvertedIndex();

    public:
        DocSetT Query(const std::string &query_str);

    private:
        void Init();
        void OpenInvertedIndexFile(const std::string &file_name);
        std::string GetLine(FILE *fp_inverted_index);
        FILE *fp_inverted_index;
};
#endif
