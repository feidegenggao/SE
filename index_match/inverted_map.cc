/*
 * ============================================================================
 *
 *       Filename:  inverted_map.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/24/13 15:16:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "inverted_map.h"
#include    "index.h"
#include    "base/log.h"
#include    "base/tools.h"
using namespace base;

void InvertedMap::Insert(const std::string &key_word, unsigned int doc_id)
{
    InvertedMapTItor find_it = inverted_map_.find(key_word);
    if (find_it == inverted_map_.end())
    {
        //add this key and doc_id
        DocSetT temp_set;
        temp_set.insert(doc_id);
        inverted_map_.insert(InvertedMapValueT(key_word, temp_set));
    }
    else
    {
        //insert this doc_id to the key
        find_it->second.insert(doc_id);
    }
}

void InvertedMap::WriteToFile()
{
    LOG_DEBUG << "WriteToFile";
    for (InvertedMapTItor start = inverted_map_.begin(); start != inverted_map_.end(); ++start)
    {
        std::string dst_str = start->first;
        std::string doc_id_str;
        for (DocSetTItor doc_set_it = start->second.begin(); doc_set_it != start->second.end(); ++doc_set_it)
        {
            doc_id_str = doc_id_str + ' ' + Convert<string, unsigned int>(*doc_set_it);
        }
        doc_id_str += '\n';

        dst_str += doc_id_str;
        Index::WriteToInvertedIndex(dst_str);
    }
}
