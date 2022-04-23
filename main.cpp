#include <QCoreApplication>

#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::setfill;
#include<mysql.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MYSQL *mysql= mysql_init(NULL);
    if(NULL == mysql){
        mysql_library_end();
        cout<<"mysql handler is NULL,mybe OOM happened;"<<endl;
        return 0;
    }
    if (mysql_real_connect (mysql, "localhost", "root", "123456",
                            "tmp", 3306, NULL, CLIENT_MULTI_STATEMENTS) == NULL){
        printf("mysql_real_connect() failed\n");
        goto end;
    }
    if( mysql_query(mysql,"select * from test;")){
        printf("mysql_query() failed\n");
        goto end;
    }
    MYSQL_RES* res = mysql_store_result(mysql);
    MYSQL_ROW row;
    while((row=mysql_fetch_row(res))!=NULL){
        if(row[0] != NULL && row[1]!=NULL){
            std::cout<<setw(2)<<row[0]<<" <---> "<<row[1]<<std::endl;
        }
    }
    mysql_free_result(res);
end:

    mysql_close(mysql);
    mysql_library_end();
    cout<<"over"<<endl;
    return a.exec();
}
