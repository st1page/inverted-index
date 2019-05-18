#ifndef _SORTEDLIST_HPP_
#define _SORTEDLIST_HPP_
template<class T>
struct Node{
    T data;
    Node* nxt;
    Node(){
        nxt = nullptr;
    }
    Node(T x){
        data = x;
        nxt = nullptr;
    }
    Node(const Node<T> &other){
        data = other.data;
        nxt = other.nxt;
    }
    ~Node(){
        nxt = nullptr;
    }
};
template<class T>
class SortedList{
protected:
    typedef Node<T>* n_ptr;
    n_ptr _head;
    n_ptr _tail;
    int _size;
    
    void _clear(){
        n_ptr p = _head;
        n_ptr tmp = nullptr;
        while(p!=nullptr){
            tmp = p;
            p = p->nxt;
            delete(tmp);
        }
        _size = 0;
    }
    void _push_back(T x){
        _size++; 
        if(_head == nullptr) {
            _head = _tail = new Node<T>(x);
        } else {
            _tail->nxt = new Node<T>(x);
            _tail = _tail->nxt;
        }
    }
    void _insert(T x){
        _size++;
        n_ptr *p = &_head;
        while((*p)!=nullptr && *(p)->data<=x) p = &((*p)->nxt);
        if(*p==nullptr) {
            *p = new Node<T>(x);
            _tail = *p;
        } else {
            n_ptr tmp = (*p)->nxt;
            *p = new Node<T>(x);
            p->nxt = tmp;
        }
    }
    int _find(T x){
        for(n_ptr p = _head; p!=nullptr; p = p->nxt) 
            if(p->data == x) return 1;
        return 0;
    }
public:
    struct iterator{
        n_ptr ptr;
        iterator(){ ptr = nullptr;}
        iterator(n_ptr p){ ptr = p;}
        T& operator*()const{
            return *ptr;
        }
        T* operator->()const{
            return ptr;
        }
        iterator& operator++(){
            if(ptr!=nullptr) ptr = ptr->nxt;
            return *this;
        }
        iterator operator++(int){
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
        bool operator==(const iterator &iter){
            return ptr == iter.ptr;
        }
        bool operator!=(const iterator &iter){
            return !(*this == iter);
        }
    }; 
    iterator end(){
        return iterator(nullptr);
    }
    iterator begin(){
        return iterator(_head);
    }
    iterator rbegin(){
        return iterator(_tail);
    }
    SortedList(){
        _head = nullptr;
        _tail = nullptr;
    }
    SortedList(const SortedList<T> &other){
        _clear();
        for(iterator it = other.begin(); it!=other.end(); it++){
            _push_back(it->data);
        }
    }
    ~SortedList(){
        _clear();
    }
    void clear(){
        _clear();
    }
    bool empty(){
        return _head==nullptr;
    }
    void add(T x){
        _insert(x);
    }
    int find(T x){
        return _find(x);
    }
};
#endif
