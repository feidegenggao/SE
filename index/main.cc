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
 *    this_file's offset = next file's offset - this file's offset
 *
 *    [url.index] 's format:
 *    urlMD5            docId
 *    abcef1234567890e  0
 *    cbcef1234567890e  1
 *    ......
 *    bbcef1234567890e   28321
 *
 * NOTE:
 *    Every field was separte by ' '(space) an every line was terminated by '\n'
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
#include    "base/log.h"
#include    "base/types.h"
#include    <assert.h>
using namespace base;

int main()
{
    string raw_file_name("");

    int raw_file_fd = open(raw_file_name.c_str(), O_RDONLY);
    assert(raw_file_fd != -1);



    LOG_END;
    return SUCCESSFUL;
}
