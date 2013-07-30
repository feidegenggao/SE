/*
 * ============================================================================
 *
 *       Filename:  doc_index.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/29/13 21:51:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
#include    "base/tools.h"
#include    "base/regex.h"
using namespace base;
#include    "doc_index.h"

#include    "index_match/doc_raw.h"

#include    <assert.h>
using namespace std;

#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <string.h>

DocIndex::DocIndex()
{
    Init();
}

void DocIndex::Init()
{
    const string doc_raw_file_name("../crawl/doc_2.raw");
    OpenDocRaw(doc_raw_file_name);

    const string doc_index_file_name("../index_match/doc.index");
    doc_index_file_fp_ = fopen(doc_index_file_name.c_str(), "r");
    assert(doc_index_file_fp_ != NULL);

    string this_line;
    do
    {
        this_line = GetLine(doc_index_file_fp_);
        if (this_line.length() == 0) break;

        RegexSearchResultType result;
        string regex_find_offset("^([\\d]+) ([\\d]+) .*$");
        RegexSearch(this_line, regex_find_offset, result);

        assert(2 == result.size());
        RegexSearchElementType doc_id = *result.begin();
        RegexSearchElementType off_set = *(++result.begin());
        doc_index_map_.insert(std::pair<unsigned int, off_t>
                (Convert<unsigned int, RegexSearchElementType>(doc_id),
                 Convert<off_t, RegexSearchElementType>(off_set)));
    }while(true);
}

string DocIndex::GetUrl(unsigned int doc_id) const
{
    LOG_DEBUG << "This doc_id:" << doc_id;
    LOG_DEBUG << "Get off_set:" << doc_index_map_.find(doc_id)->second ;
    SeekSet(doc_index_map_.find(doc_id)->second);
    string url;
    string data;
    if (GetRawDataAndUrl(data, url))
    {
        LOG_DEBUG << "url:" << url;
    }
    return url;
}

string DocIndex::GetTitle(unsigned int doc_id) const
{
    string title;
    return title;
}

string DocIndex::GetSummary(unsigned int doc_id) const
{
    string summary;
    return summary;
}

string DocIndex::GetLine(FILE *fp)
{
    assert(fp != NULL);

    string this_line;

    int read_buf_len = 512;

    do
    {
        char *read_buf = new char[read_buf_len];
        memset(read_buf, 0, read_buf_len);
        char* result_buf = fgets(read_buf, read_buf_len, fp);

        //If file read end or reach end of the file
        if (result_buf == NULL)
        {
            delete [] read_buf;
            return this_line;
        }

        this_line += string(read_buf);

        //This fgets not reach the \n and we should retry until reach the \n
        if ('\n' != *(--this_line.end()) )
        {
            delete [] read_buf;
            continue;
        }
        else
        {
            delete [] read_buf;
            break;
        }

    }while(true);
    
    return this_line;
}
