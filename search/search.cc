/*
 * ============================================================================
 *
 *       Filename:  search.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/29/13 10:39:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "search/search.h"
#include    "search/forward_index_index.h"
#include    "search/inverted_index.h"
#include    "search/doc_index.h"
#include    "base/log.h"
#include    "base/tools.h"
using namespace base;
#include    "net/socket.h"
#include    "net/sock_addr.h"
using namespace net;

#include    <assert.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <pthread.h>

#include    <string.h>
void WriteDataGram(Socket &accept_socket, 
        const string &cmd, const string &datalen, const string &arg1,
        const string &arg2, const string &arg3, const string &data_body);

static const int PORTAL_SEARCH_QUERY = 1;
static const int PORTAL_SEARCH_QUERY_OK = 2;
static const int PORTAL_SEARCH_QUERY_ARGUMENT_ILLEGAL = 3;
static const int PORTAL_SEARCH_QUERY_OTHER_ERROR = 4;
static const string PORTAL_SEARCH_DATA_SEPARATOR("\n");

void SendDataOfKeyWord(Socket &accept_socket, const std::string &key_word)
{
    DocSetT result_doc_set = InvertedIndex::GetInstance()->Query(key_word);
    if (result_doc_set.size() == 0)
    {
        WriteDataGram(accept_socket, Convert<string, int>(PORTAL_SEARCH_QUERY_OTHER_ERROR),
                "", "", "", "", PORTAL_SEARCH_DATA_SEPARATOR);
    }
    int i = 0;
    for (DocSetTConstItor it = result_doc_set.begin(); it != result_doc_set.end(); ++it)
    {
        string data_body;
        string url = DocIndex::GetInstance()->GetUrl(*it);
        string title = DocIndex::GetInstance()->GetTitle(*it); 
        string summary = ForwardIndexIndex::GetInstance()->GetSummary(key_word, *it);
        data_body = title + PORTAL_SEARCH_DATA_SEPARATOR +
            url + PORTAL_SEARCH_DATA_SEPARATOR +
            summary + PORTAL_SEARCH_DATA_SEPARATOR;

        int data_len = data_body.length();
        LOG_DEBUG << "cmd:" << PORTAL_SEARCH_QUERY_OK;
        LOG_DEBUG << "data_len:" << data_len;
        LOG_DEBUG << "all_num:" << result_doc_set.size();
        LOG_DEBUG << "index_num:" << ++i;
        LOG_DEBUG << "arg3:" << "";
        LOG_DEBUG << "get url:" << url; 
        LOG_DEBUG << "get title:" << title;
        WriteDataGram(accept_socket, Convert<string, int>(PORTAL_SEARCH_QUERY_OK),
                Convert<string, int>(data_len), Convert<string, int>(result_doc_set.size()),
                Convert<string, int>(i), "", data_body);
    }
}

//php-cgi send data use \n to separte every data-filed 
//And we will delete \n in GetDataGram(...) when we return every data-filed
static void GetDataGram(Socket &accept_socket, string &dst_str)
{
    do{
        char read_buf[2] = {0};
        accept_socket.Read(read_buf, sizeof(read_buf) - 1);
        string temp(read_buf);
        if (temp == PORTAL_SEARCH_DATA_SEPARATOR)
        {
            break;
        }
        else
        {
            dst_str += temp;
        }
    }while(true);
}

static void *HandleQuery(void *p_accept_fd)
{
    int accept_fd = *((int*)p_accept_fd);
    LOG_DEBUG << "accept_fd:" << accept_fd;
    Socket accept_socket(accept_fd);

    string cmd, datalen, arg1, arg2, arg3;
    GetDataGram(accept_socket, cmd);
    GetDataGram(accept_socket, datalen);
    GetDataGram(accept_socket, arg1);
    GetDataGram(accept_socket, arg2);
    GetDataGram(accept_socket, arg3);

    int cmd_int = Convert<int, string>(cmd);
    //FIXME:
    //support more cmd
    assert(cmd_int == PORTAL_SEARCH_QUERY);
    switch(cmd_int)
    {
        case PORTAL_SEARCH_QUERY:
            {
                int data_body_len = Convert<int, string>(datalen);
                char *data_body_buf = new char[data_body_len + 1];
                memset(data_body_buf, 0, data_body_len + 1);
                accept_socket.Read(data_body_buf, data_body_len);
                string data_body(data_body_buf);
                delete [] data_body_buf;
                LOG_DEBUG << "read:" << data_body << "EOF";
                SendDataOfKeyWord(accept_socket, data_body);
                break;
            }

        default:
            {
                break;
            }
    }

    //accept socket should shutdown the socket when send the data to php-cgi completely. 
    //But we close the socket, so php-cgi(portal) may be receive the RST before read all the datas. 
    //Currently, our socket class does not have the shutdown api, so, we add the end datagrame ,just say Bye
    string bye_words;
    GetDataGram(accept_socket, bye_words);
    
    return NULL;
}

void StartSearch()
{
    SockAddr listen_addr(SEARCH_LISTEN_PORT);
    Socket listen_socket(listen_addr);
    listen_socket.Listen();

    while(true)
    {
        const int accept_fd = listen_socket.Accept();
        pthread_t thread_id;
        int create_thread_rt = pthread_create(&thread_id, NULL, 
                &HandleQuery,(void*) &accept_fd);
        assert(create_thread_rt == 0);
    }
}


void WriteDataGram(Socket &accept_socket, 
        const string &cmd, const string &datalen, const string &arg1,
        const string &arg2, const string &arg3, const string &data_body)
{
    string send_data = cmd + PORTAL_SEARCH_DATA_SEPARATOR + 
        datalen + PORTAL_SEARCH_DATA_SEPARATOR + 
        arg1 + PORTAL_SEARCH_DATA_SEPARATOR + 
        arg2 + PORTAL_SEARCH_DATA_SEPARATOR + 
        arg3 + PORTAL_SEARCH_DATA_SEPARATOR + data_body;

    ssize_t write_n = accept_socket.Write(send_data.c_str(), send_data.length());
    LOG_DEBUG << "accept_socket send data:" << write_n;
}
