#ifndef DBPOOL_H
#define DBPOOL_H
#include "dbconn.h"
#include <list>
using std::list;
#include <mutex>
const int init_conn_size_c = 20;
//应该是单例
class DBPOOL
{
public:
    DBPOOL();
    bool init_pool();//线程不安全
    void rel_pool();//线程不安全
    DBCONN* new_conn();
    void del_conn(DBCONN* pconn);
    ~DBPOOL();
private:
    list<DBCONN*> conns;
    std::mutex mtx;
};

#endif // DBPOOL_H
