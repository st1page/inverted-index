#ifndef _INVERTEDLIST_HPP_
#define _INVERTEDLIST_HPP_
#include "SortedList.hpp"
class InvertedList:public SortedList<int>{
private:
    
public:
  
    InvertedList():SortedList(){    }
    InvertedList(const InvertedList &other):SortedList(other){    }
    
    void uni(InvertedList &other){
        n_ptr p = _head;
        iterator it = other.begin();
        while(p!=nullptr&&it!=other.end()){
            if(p->data<*it) {
                p = p->nxt;
            } else if(p->data==*it){
                p = p->nxt;
                ++it;
            } else {
                _ins_pre(p,*it); ++it;
            }
        }
        while(it!=other.end()){
            _push_back(*it); ++it;
        }
    }
    void intersec(InvertedList &other){
        n_ptr p = _head;
        iterator it = other.begin();
        while(p!=nullptr&&it!=other.end()){
            if(p->data<*it) {
                p = p->nxt;
                _erase(p->pre);
            } else if(p->data==*it){
                p = p->nxt;
                ++it;
            } 
        }
    }
};
#endif
