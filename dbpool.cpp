#include "dbpool.h"

DBPOOL::DBPOOL()
{

}

bool DBPOOL::init_pool()
{
    for(int i = 0; i < init_conn_size_c; ++i){
        DBCONN* tmp = new DBCONN();
        if(tmp == NULL || !tmp->init()){
            return false;
        }
        conns.push_front(tmp);
    }
    return true;
}

DBCONN *DBPOOL::new_conn()
{
    if(conns.empty())
        return NULL;
    DBCONN * ret = conns.front();
    conns.pop_front();
    return ret;
}

void DBPOOL::del_conn(DBCONN *pconn)
{
    conns.push_front(pconn);
}

void DBPOOL::rel_pool()
{

}
