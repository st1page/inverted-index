#ifndef _SORTEDLIST_HPP_
#define _SORTEDLIST_HPP_
template<class T>
struct Node{
    T data;
    Node* nxt;
    Node* pre;
    Node(){
        nxt = pre = nullptr;
    }
    Node(T x){
        data = x;
        nxt = pre = nullptr;
    }
    Node(const Node<T> &other){
        data = other.data;
        nxt = other.nxt;
        pre = other.pre;
    }
    ~Node(){
        nxt = pre = nullptr;
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
    void _ins_pre(n_ptr ptr, T x){
        ++_size;
        n_ptr p = new Node<T>(x);
        if(ptr->pre==nullptr){
            ptr->pre = p;
            p->nxt = ptr;
            _head = p;
        } else {
            ptr->pre->nxt = p;
            p->pre = ptr->pre;
            p->nxt = ptr;
            ptr->pre = p; 
        }
    }
    void _ins_nxt(n_ptr ptr, T x){
        ++_size;
        n_ptr p = new Node<T>(x);
        if(ptr->nxt==nullptr){
            ptr->nxt = p;
            p->pre = ptr;
            _tail = p;
        } else {
            ptr->nxt->pre = p;
            p->nxt = ptr->nxt;
            p->pre = ptr;
            ptr->nxt = p;
        }
    }
    void _push_back(T x){
        _size++;
        if(_head==nullptr) {
            _head = _tail = new Node<T>(x);
        } else {
            _tail->nxt = new Node<T>(x);
            _tail->nxt->pre = _tail;
            _tail = _tail->nxt;
        }
    }
    void _add(T x){
        if(_head==nullptr) {
            ++_size;
            _head = _tail = new Node<T>(x);
        } else if(_tail->data<x){
            _push_back(x);
        } else {
            n_ptr p = _head;
            for(;p!=nullptr;p++){
                if(p->data>x) {
                    _ins_pre(p,x);
                    break;
                }
            }
        }
    }
    n_ptr _find(T x){
        for(n_ptr p = _head; p!=nullptr; p = p->nxt) 
            if(p->data == x) return p;
        return nullptr;
    }
    void _erase(n_ptr ptr){
        if(ptr->pre!=nullptr) ptr->pre->nxt = ptr->nxt;
        else _head = ptr->nxt;
        if(ptr->nxt!=nullptr) ptr->nxt->pre = ptr->pre;
        else _tail = ptr->pre;
        delete ptr;
    }
    void _erase(T x){
        n_ptr ptr = _find(x);
        if(ptr!=nullptr) _erase(ptr);
    }
public:
    struct iterator{
        n_ptr ptr;
        iterator(){ ptr = nullptr;}
        iterator(n_ptr p){ ptr = p;}
        T& operator*()const{
            return ptr->data;
        }
        T* operator->()const{
            return &(ptr->data);
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
            push_back(it->data);
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
        _add(x);
    }
    void erase(T x){
        _erase(x);
    }
    int find(T x){
        return _find(x);
    }
};
#endif
