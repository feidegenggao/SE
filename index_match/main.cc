/*
 * ============================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *    Create doc.index and url.index and forward.index and inverted.index
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
 *    [forward.index]'s format:
 *    docId1 key-word-1 key-word-2 ......
 *    docId2 key-word-1 key-word-2 ......
 *    docId3 key-word-2 ......
 *    ......
 *
 *    [inverted.index]'s format:
 *    key-word-1 docId1 docId2 ......
 *    key-word-2 docId1 docId2 docId3 ......
 *    ......
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
#include    "index.h"
#include    "inverted_map.h"
#include    "doc_raw.h"
using namespace base;

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

    OpenDocRaw(raw_file_name);

    unsigned int doc_id = 0;
    while(true)
    {
        string raw_data;
        string url;
        off_t current_offset = GetRawFileOffset();
        if (!GetRawDataAndUrl(raw_data, url)) break;


        INDEX->WriteToDocIndex(doc_id, current_offset, MD5(raw_data));
        INDEX->WriteToUrlIndex(doc_id, MD5(url));
        INDEX->WriteToForwardIndex(doc_id, raw_data);

        doc_id++;
    }

    INDEX->WriteToDocIndex(doc_id, GetRawFileOffset());
    INDEX->WriteTheLastIndeToForwardIndexIndex(doc_id);
    INDEX->WriteToInvertedIndex();

    LOG_END;
    return SUCCESSFUL;
}
