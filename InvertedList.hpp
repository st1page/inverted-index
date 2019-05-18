#ifndef _INVERTEDLIST_HPP_
#define _INVERTEDLIST_HPP_
#include<SortedList.hpp>
class InvertedList:public SortedList<int>{
private:
    
public:
  
    InvertedList():SortedList(){    }
    InvertedList(const InvertedList &other):SortedList(other){    }
    
    void uni(const InvertedList &other){
        iterator it = this.begin();
    }
    void intersec(){

    }
};
#endif
