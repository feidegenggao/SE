/*
 * ============================================================================
 *
 *       Filename:  index.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/13 16:51:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     INDEX_HEADER
#define     INDEX_HEADER
#include    <string>
#include    <sys/types.h>
#include    "base/singleton.h"

#define INDEX Index::GetInstance()

class Index : public base::Singleton<Index>
{
    friend class Singleton<Index>;
    private:
        Index(){OpenAllIndexFiles();}

    public:
        void OpenAllIndexFiles();
        //If doc_md5 is null, we can guess that this is the end of doc.indx
        void WriteToDocIndex(const unsigned int doc_id, const off_t doc_offset, const std::string &doc_md5 = std::string(""));
        void WriteToUrlIndex(const unsigned int doc_id, const std::string &url_md5);
        void WriteToForwardIndex(const unsigned int doc_id, const std::string &html_data);
        void WriteToInvertedIndex();

    private:
        //store the doc_id--off_set of doc.raw named:doc.index
        int doc_index_file_fd_;
        //store the url--doc_id named:url.index
        int url_index_file_fd_;
        //store the doc_id--Particile_words named:forward.index
        int forward_index_file_fd_;
        //store the doc_id--off_set of forward.index named:forward_index.index
        int forward_index_index_file_fd_;
        //store the Particile_words--doc_id named:inverted.index
        int inverted_index_file_fd_;

        int OpenFile(const std::string &filename);

        int Write(int file_fd, const void *write_buf, size_t count);
};
#endif
