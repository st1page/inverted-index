#ifndef _DICTIONARY_HPP_
#define _DICTIONARY_HPP_

#include<string>
#include<unordered_map>
#include<algorithm>
#include<fstream>
#include<iostream>

#include "Utils.hpp"
#include "InvertedList.hpp"

struct Term{

    std::string data;
    size_t hash_code;
    InvertedList* index;
    Term(){index = nullptr;}
    Term(const std::string &s){
        data = s;
        std::hash<std::string> h;
	    hash_code = stl_hash(s);
        index = new InvertedList();  
    }
    ~Term(){
    }
};
class Dictionary{
private:
    const char* path = "./index";
    std::unordered_map<size_t,Term> mp;
    void _clear(){
        for(auto it = mp.begin(); it!=mp.end(); ++it){
            delete it->second.index;
        }
    }
public:
    Dictionary(){

    }
    ~Dictionary(){
        _clear();
    }
    void save(){
        std::ofstream outfile;
        outfile.open(path);
        for(auto iter = mp.begin(); iter!=mp.end(); ++iter){
            Term term = iter->second;
            outfile<< term.data<<" ";
            for(auto it = term.index->begin();it!=term.index->end();++it) {
                outfile<<*it<<" ";
            }
            outfile<<std::endl;
        }
        outfile.close();
    }
    void load(){
        _clear();
        std::ifstream infile; 
        infile.open(path);
        std::string line;
        while(getline(infile, line)){
            size_t pos = line.find(" ");
            size_t nx_pos;
            Term *term_p = new Term(line.substr(0,pos));
            while((nx_pos = line.find(" ",pos))!= std::string::npos){
                int x = std::stoi(line.substr(pos+1,nx_pos-pos-1));
                term_p->index->add(x);
                pos = nx_pos;
            }
            mp.insert(std::make_pair(term_p->hash_code, *term_p));
        }
    }
    Term getTerm(std::string s){
        size_t hash_code = stl_hash(s);
        auto it = mp.find(hash_code);
        if(it!=mp.end()){
            return it->second;
        } else {
            Term *term_p = new Term(s);
            mp.insert(std::make_pair(hash_code, *term_p));
            return *term_p;
        }
    }   
};
#endif