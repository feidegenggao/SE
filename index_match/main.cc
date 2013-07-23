/*
 * ============================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  Create doc.index and url.index
 *    [doc.index] 's  format:
 *    docId     docOffset       docMD5
 *    0         0               abcef1234567890e
 *    1         100             cbcef1234567890e
 *    ......
 *    28321     876568          bbcef1234567890e
 *
 *    We do not store doc's length, we can calculate the length of doc :
 *    this_file's length = next file's offset - this file's offset
 *
 *    [url.index] 's format:
 *    urlMD5            docId
 *    abcef1234567890e  0
 *    cbcef1234567890e  1
 *    ......
 *    bbcef1234567890e   28321
 *
 * NOTE:
 *    Every field was separte by ' '(space) and every line was terminated by '\n'
 *
 *
 *        Version:  1.0
 *        Created:  07/19/13 16:43:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/md5.h"
#include    "base/log.h"
#include    "base/types.h"
#include    "base/regex.h"
#include    "base/tools.h"
#include    "index.h"
#include    <assert.h>
using namespace base;
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <fcntl.h>
#include    <string.h>
#include    <stdio.h>
#include    <errno.h>

namespace detail
{
    int raw_file_fd = 0;
}

bool GetRawDataAndUrl(string &raw_data, string &url);
off_t GetRawFileOffset();
int main(int argc, char *argv[])
{
    if (argc != 2 and argc != 1)
    {
        LOG_ERROR << "Usage:" << argv[0] << "[raw_file_name]";
        return -1;
    }

    string raw_file_name;
    if (argc == 1)
    {
        raw_file_name = string("../crawl/doc_2.raw");
    }
    else
    {
        raw_file_name = string(argv[1]);
    }

    detail::raw_file_fd = open(raw_file_name.c_str(), O_RDONLY);
    if (detail::raw_file_fd == -1)
    {
        LOG_ERROR << "Open raw_file(" << raw_file_name << ") error: " << strerror(errno);
    }
    assert(detail::raw_file_fd != -1);

    unsigned int doc_id = 0;
    while(true)
    {
        string raw_data;
        string url;
        off_t current_offset = GetRawFileOffset();
        if (!GetRawDataAndUrl(raw_data, url)) break;

        LOG_DEBUG << "url" << url;

        Index::WriteToDocIndex(doc_id, current_offset, MD5(raw_data));
        Index::WriteToUrlIndex(MD5(url), doc_id);
        LOG_DEBUG << "url:" << url;
        LOG_DEBUG << "MD5:" << MD5(url);

        doc_id++;
    }

    Index::WriteToDocIndex(doc_id, GetRawFileOffset());

    LOG_END;
    return SUCCESSFUL;
}

bool GetRawDataAndUrl(string &raw_data, string &url)
{
    string raw_header_length_str;
    char read_buf = '\0';

    //1.read raw_header_length:1234
    while(read_buf != ' ')
    {
        ssize_t readnum = read(detail::raw_file_fd, &read_buf, 1);
        if (readnum == 0 or readnum == -1) return false;
        raw_header_length_str += read_buf;
    }
    //2.get raw_header_length 
    RegexSearchResultType result;
    string regex_find_length_num("^raw_header_length:(\\d+) $");
    RegexSearch(raw_header_length_str, regex_find_length_num, result);
    assert(result.size() == 1);
    unsigned int raw_header_length_num = Convert<unsigned int, string>(*result.begin());

    //3.read raw_header
    char *raw_header_buf = new char[raw_header_length_num];
    memset(raw_header_buf, 0, sizeof(raw_header_buf));
    read(detail::raw_file_fd, raw_header_buf, raw_header_length_num);
    string raw_header_str(raw_header_buf, raw_header_length_num);
    delete [] raw_header_buf;

    //4.get url adn raw_data_length
    string regex_find_url_and_raw_data_length("^version:0\\.1url:(.+)date:.*raw_data_length:(\\d+).*$");
    RegexSearch(raw_header_str, regex_find_url_and_raw_data_length, result);
    assert(result.size() == 2);
    url = *result.begin();
    unsigned int raw_data_length_num = Convert<unsigned int, string>(*(++result.begin()));

    //5.read raw_data
    char *raw_data_buf = new char[raw_data_length_num];
    memset(raw_data_buf, 0, sizeof(raw_data_buf));
    read(detail::raw_file_fd, raw_data_buf, raw_data_length_num);
    raw_data = string(raw_data_buf, raw_data_length_num);
    delete [] raw_data_buf;

    return true;
}

off_t GetRawFileOffset()
{
    return lseek(detail::raw_file_fd, 0, SEEK_CUR);
}
