/*
 * ============================================================================
 *
 *       Filename:  doc_index.h
 *
 *    Description:  read doc.index to get doc_id corresponding the doc off_set 
 *    int doc.raw
 *
 *        Version:  1.0
 *        Created:  07/29/13 21:46:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     DOC_INDEX_HEADER
#define     DOC_INDEX_HEADER
#include    "base/singleton.h"

#include    <string>
#include    <map>

#include    <stdio.h>

class DocIndex : public base::Singleton<DocIndex>
{
    friend class base::Singleton<DocIndex>;
    private:
        DocIndex();
        //read doc.index stored in ../index_match/doc.index
        void Init();
        FILE *doc_index_file_fp_;
        std::string GetLine(FILE *fp);
        std::map<unsigned int, off_t> doc_index_map_;

    public:
        std::string GetUrl(unsigned int doc_id) const;
        std::string GetTitle(unsigned int doc_id) const;
        std::string GetSummary(unsigned int doc_id) const;
};
#endif
