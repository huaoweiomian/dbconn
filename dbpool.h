#ifndef DBPOOL_H
#define DBPOOL_H
#include "dbconn.h"
#include <list>
using std::list;
const int init_conn_size_c = 20;
class DBPOOL
{
public:
    DBPOOL();
    bool init_pool();
    DBCONN* new_conn();
    void del_conn(DBCONN* pconn);
    void rel_pool();
private:
    list<DBCONN*> conns;
};

#endif // DBPOOL_H
