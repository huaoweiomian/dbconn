#ifndef DBPOOL_H
#define DBPOOL_H
#include "dbconn.h"
#include <list>
using std::list;
#include <mutex>
const int init_conn_size_c = 20;
//Ӧ���ǵ���
class DBPOOL
{
public:
    DBPOOL();
    bool init_pool();//�̲߳���ȫ
    void rel_pool();//�̲߳���ȫ
    DBCONN* new_conn();
    void del_conn(DBCONN* pconn);
    ~DBPOOL();
private:
    list<DBCONN*> conns;
    std::mutex mtx;
};

#endif // DBPOOL_H
