#include <QCoreApplication>

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::setfill;
#include <string>
using std::string;
#include "dbpool.h"
bool process_res(MYSQL *, MYSQL_RES* res);
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DBPOOL dbpool;
    bool ret = dbpool.init_pool();
    if(!ret){
        cout<<"dbpool.init_pool"<<endl;
        a.exec();
        return 0;
    }

    DBCONN* dbconn = dbpool.new_conn();
    string stmt = "select * from test;";
    int length = (int)stmt.length();
    ret = dbconn->query(stmt.c_str(), length, process_res);
    if(!ret){
        cout<<"dbconn->query failed;\n"<<"sql:["<<stmt<<"]"<<endl;
    }
    return a.exec();
}
bool process_res(MYSQL *, MYSQL_RES* res){
    MYSQL_ROW row;
    while((row=mysql_fetch_row(res))!=NULL){
        if(row[0] == NULL || row[1] == NULL){
            return false;
        }
        cout<<setw(2)<<row[0]<<" <---> "<<row[1]<<endl;
    }
    return true;
}
//    MYSQL *mysql= mysql_init(NULL);
//    if(NULL == mysql){
//        cout<<"mysql handler is NULL,mybe OOM happened;"<<endl;
//        return 0;
//    }
//    if (mysql_real_connect (mysql, "localhost", "root", "123456",
//                            "tmp", 3306, NULL, CLIENT_MULTI_STATEMENTS) == NULL){
//        printf("mysql_real_connect() failed\n");
//        goto end;
//    }
//    if( mysql_query(mysql,"select * from test;")){
//        printf("mysql_query() failed\n");
//        goto end;
//    }
//    MYSQL_RES* res = mysql_store_result(mysql);
//    MYSQL_ROW row;
//    while((row=mysql_fetch_row(res))!=NULL){
//        if(row[0] != NULL && row[1]!=NULL){
//            std::cout<<setw(2)<<row[0]<<" <---> "<<row[1]<<std::endl;
//        }
//    }
//    mysql_free_result(res);
//end:

//    mysql_close(mysql);
//    cout<<"over"<<endl;
