#include "dbconn.h"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::setfill;

DBCONN::DBCONN()
{
    mysql = NULL;
}

bool DBCONN::init()
{
    mysql= mysql_init(NULL);
    if(NULL == mysql){
        cout<<"mysql handler is NULL,mybe OOM happened;"<<endl;
        return false;
    }
    if (mysql_real_connect (mysql, "localhost", "root", "123456",
                            "tmp", 3306, NULL, CLIENT_MULTI_STATEMENTS) == NULL){
        printf("mysql_real_connect() failed\n");
        return false;
    }
    return true;
}

void DBCONN::rel(){
    mysql_close(mysql);
    mysql = NULL;
}

bool DBCONN::query(const char* stmt_str, unsigned long length, PROCESS_RES prf)
{
    if(prf == NULL)
        return false;
    int status = mysql_real_query(mysql, stmt_str, length);
    if (status){
        return false;
    }

    MYSQL_RES* result = mysql_store_result(mysql);
    if (!result){
        return false;
    }
    bool ret = prf(mysql, result);
    mysql_free_result(result);
    return ret;
}

MYSQL_RES *DBCONN::query(const char *stmt_str, unsigned long length)
{
    int status = mysql_real_query(mysql, stmt_str, length);
    if (status){
        return NULL;
    }
    return mysql_store_result(mysql);
}

void DBCONN::rel_res(MYSQL_RES *res)
{
    mysql_free_result(res);
}
