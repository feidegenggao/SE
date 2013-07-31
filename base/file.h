/*
 * ============================================================================
 *
 *       Filename:  file.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/31/13 10:12:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     BASE_FILE_HEADER
#define     BASE_FILE_HEADER
#include    <string>
#include    <stdio.h>

namespace base
{
    class File
    {
        public:
            explicit File(const std::string &file_name, const std::string &mode = std::string("r"));
            std::string GetLine() const;

        private:
            File(const File &other_file);
            File& operator = (const File &other_file);

        private:
            FILE *fp_;
    };
}
#endif
