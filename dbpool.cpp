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
    std::lock_guard<std::mutex> lck (mtx);
    if(conns.empty()&&!init_pool()){
            return NULL;
    }
    DBCONN * ret = conns.front();
    conns.pop_front();
    return ret;
}

void DBPOOL::del_conn(DBCONN *pconn)
{
    std::lock_guard<std::mutex> lck (mtx);
    conns.push_front(pconn);
}

DBPOOL::~DBPOOL()
{
    rel_pool();
}

void DBPOOL::rel_pool()
{
    while (!conns.empty()) {
        DBCONN * ret = conns.front();
        conns.pop_front();
        delete ret;
    }
}
