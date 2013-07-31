/*
 * ============================================================================
 *
 *       Filename:  forward_index_index.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/13 11:01:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     FORWARD_INDEX_INDEX
#define     FORWARD_INDEX_INDEX
#include    "base/file.h"
#include    "base/singleton.h"

#include    <string>
#include    <map>

class ForwardIndexIndex : public base::Singleton<ForwardIndexIndex>
{
    friend class base::Singleton<ForwardIndexIndex>;
    private:
        ForwardIndexIndex();
        void Init();
        std::map<unsigned int, off_t> forward_index_index_map_;
        base::File forward_file;
        int forward_index_fd_;

        std::string GetForwardIndexString(unsigned int doc_id) const;
    public:
        std::string GetSummary(const std::string &key_words, unsigned int doc_id) const;
};

#endif
