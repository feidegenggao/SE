/*
 * ============================================================================
 *
 *       Filename:  dict.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/22/13 16:17:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     DICT_HEADER
#define     DICT_HEADER
#include    <map>
#include    <string>
#include    "base/singleton.h"

const std::string DICT_FILE_NAME("/root/lxf/se/index_match/words.dict");
class Dict : public base::Singleton<Dict>
{
    friend class Singleton<Dict>;
    private:
        Dict();
    private:
        Dict(const Dict &);
        Dict& operator = (const Dict &);

    public:
        bool IsWord(const std::string &src_str);

    private:
        //key-word freq
        std::map<std::string, int> dict_map_;
        void OpenDict();
};
#endif
