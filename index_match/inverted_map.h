/*
 * ============================================================================
 *
 *       Filename:  inverted_map.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/13 15:06:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     INVERTED_MAP_HEADER
#define     INVERTED_MAP_HEADER
#include    "base/singleton.h"

#include    <map>
#include    <string>
#include    <set>

typedef std::set<unsigned int> DocSetT;
typedef DocSetT::iterator DocSetTItor;
typedef std::map<std::string, DocSetT> InvertedMapT;
typedef std::pair<std::string, DocSetT > InvertedMapValueT;
typedef InvertedMapT::iterator InvertedMapTItor;

class InvertedMap : public base::Singleton<InvertedMap>
{
    friend class base::Singleton<InvertedMap>;
    private:
        InvertedMap(){}
    public:
        //Only in participle.cc can call this function
        void Insert(const std::string &key_word, unsigned int doc_id);
        DocSetT Search(const std::string &key_word);
        const InvertedMapT& GetInvertedMap() const { return inverted_map_;}

    private:
        InvertedMapT inverted_map_;
};
#endif
