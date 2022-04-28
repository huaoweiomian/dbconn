#ifndef DBCONN_H
#define DBCONN_H
#include<mysql.h>
typedef bool (*PROCESS_RES)(MYSQL *mysql, MYSQL_RES* res);
class DBCONN
{
public:
    DBCONN();
    bool init();
    void rel();

    bool query(const char* stmt_str, unsigned long length, PROCESS_RES pr);
    MYSQL_RES *query(const char* stmt_str, unsigned long length);
    void rel_res(MYSQL_RES *res);
    ~DBCONN(){
        if(mysql == NULL)
            return;
        rel();
    }

    MYSQL *mysql;
};

#endif // DBCONN_H
