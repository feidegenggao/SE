/*
 * ============================================================================
 *
 *       Filename:  file.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/13 10:15:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/file.h"
#include    "base/log.h"
using namespace base;

#include    <assert.h>
#include    <string.h>

using namespace std;

File::File(const string &file_name, const string &mode)
{
    fp_ = fopen(file_name.data(), mode.data());
    assert(fp_ != NULL);
}

string File::GetLine() const
{
    assert(fp_ != NULL);

    string this_line;

    int read_buf_len = 512;

    do
    {
        char *read_buf = new char[read_buf_len];
        memset(read_buf, 0, read_buf_len);
        char* result_buf = fgets(read_buf, read_buf_len, fp_);

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
