//
// Created by nolla on 24-4-18.
//

#ifndef DATA_STRUCTURE_COURSE_FILE_H
#define DATA_STRUCTURE_COURSE_FILE_H


#include <bits/stdc++.h>

#include <utility>
using namespace std;
const static string dataFile="data.dat";
struct file
{
    file* parent=nullptr;
    list<file> *firstChild=nullptr;
    string name;
    file(string _name,file *_parent)
    {
        name=std::move(_name);
        parent=_parent;
    }
};


class catalogTree
{
private:
    file *root= nullptr;
    file *now= nullptr;
    fstream data;
public:
    catalogTree()
    {
        loadFromFile();
    }
    ~catalogTree()
    {
        saveToFile();
    }
    void ls()
    {
        list<file> *child=now->firstChild;
        auto it=child->begin();
        while (it!=child->end())
        {
            cout<<it->name<<endl;
            ++it;
        }
        cd();
    }
    void dir()
    {
        list<file> *child=now->firstChild;
        auto it=child->begin();
        while (it!=child->end())
        {
            if(it->firstChild!=nullptr)
            {
                cout<<it->name<<endl;
            }
            ++it;
        }
        cd();
    }
    void cd()
    {
        file* temp=now;
        vector<string> path;
        while(temp!=nullptr)
        {
            path.push_back(temp->name);
            temp=temp->parent;
        }
        auto it=path.rbegin();
        while(it!=--path.rend())
        {
            cout<<*it<<"/";
            ++it;
        }
        cout<<*it<<"> "<<flush;
    }

    void cdUp()
    {
        if(now->parent != nullptr)
            now=now->parent;
        cd();
    }

    void cdOne(const string& dirName)
    {
        list<file> *dir=now->firstChild;
        if(dir== nullptr)
            return;
        auto it=dir->begin();
        while(it!=dir->end())
        {
            //名字相同且为文件夹
            if(it->name == dirName && it->firstChild != nullptr)
            {
                now=&*it;
                break;
            }
            ++it;
        }
    }

    void cd(const string& dirName)
    {
        int start=0;
        if(dirName[0]=='/')
        {
            now=root;
            start=1;
        }
        while(true){
            int end=dirName.find_first_of('/',start);
            if(end<0){
                string temp=dirName.substr(start);
                cdOne(temp);
                break;
            }
            string temp=dirName.substr(start,end-start);
            cdOne(temp);
            start=end+1;
        }
        cd();
    }

    void mkDirRecursion(string dirName)
    {
        int start=0;
        if(dirName[0]=='/')
        {
            now=root;
            start=1;
        }
        while(true){
            int end=dirName.find_first_of('/',start);
            if(end<0){
                string temp=dirName.substr(start);
                mkDir(temp);
                cdOne(temp);
                break;
            }
            string temp=dirName.substr(start,end-start);
            mkDir(temp);
            cdOne(temp);
            start=end+1;
        }
        cd();
    }

    void mkDir(string name)
    {
        list<file> *t;
        if(now->parent == nullptr){
            t=root->firstChild;
        }
        else t=now->parent->firstChild;
        auto it = t->begin();
        while(it!=t->end()){
            if(it->name==name){
                return;
            }
            ++it;
        }
        file temp(std::move(name),now);
        temp.firstChild=new list<file>;
        now->firstChild->emplace_back(std::move(temp));
    }

    void mkFile(string name)
    {
        list<file> *t;
        if(now->parent == nullptr){
            t=root->firstChild;
        }
        else t=now->parent->firstChild;
        auto it = t->begin();
        while(it!=t->end()){
            if(it->name==name){
                cd();
                return;
            }
            ++it;
        }
        file temp(std::move(name),now);
        now->firstChild->emplace_back(std::move(temp));
        cd();
    }

    void deleteFile(const string& name)
    {
        list<file> *temp=now->firstChild;
        auto it=temp->begin();
        while(it!=temp->end())
        {
            if(it->name==name)
            {
                deleteChild(it->firstChild);
                temp->erase(it);
                cd();
                return;
            }
            ++it;
        }
    }

    void deleteChild(list<file>* list)
    {
        if(list== nullptr)
        {
            return;
        }
        auto it=list->begin();
        while(it!=list->end())
        {
            deleteChild(it->firstChild);
            ++it;
        }
        delete list;
    }

    void saveToFile()
    {
        data.open(dataFile);
        if(!data.is_open())
        {
            cerr<<"Data save failed"<<endl;
            return;
        }
        save(root->firstChild, data);
        data.close();
    }
    void save(list<file>* list,fstream &out)
    {
        if(list == nullptr)
        {
            data<<"#"<<endl;
            return;
        }
        auto it=list->begin();
        while(it!=list->end())
        {
            data<<it->name<<endl;
            save(it->firstChild,out);
            ++it;
        }
        data<<"$"<<endl;
    }
    void loadFromFile()
    {
        data.open(dataFile);
        if(!data.is_open())
        {
            cerr<<"Data Load Failed"<<endl;
            return;
        }
        root=new file("", nullptr);
        load(root->firstChild,root);
        now=root;
        data.close();
    }
    void load(list<file> *&p,file *parent)
    {
        string line;
        while(getline(data,line))
        {
            if(line=="$")
            {
                if(parent->firstChild== nullptr)
                    parent->firstChild=new list<file>;
                return;
            }
            if(line=="#")
            {
                parent->firstChild=nullptr;
                return;
            }
            if(!parent->firstChild)
                parent->firstChild=new list<file>;
            file temp(line,parent);
            p->push_back(std::move(temp));
            load(p->rbegin()->firstChild,&*(p->rbegin()));
        }
    }

    void shell()
    {
        cd();
        while(true)
        {
            string line;
            getline(cin,line);
            stringstream lineStream(line);
            string inst;
            lineStream>>inst;
            string args;
            if(inst=="cd"){
                lineStream>>args;
                if(args.empty()){
                    cd();
                } else if(args==".."){
                    cdUp();
                }
                else cd(args);
            }else if(inst=="dir"){
                dir();
            }else if(inst=="mkdir"){
                lineStream>>args;
                mkDirRecursion(args);
            }else if(inst=="mkfile"){
                lineStream>>args;
                mkFile(args);
            }else if(inst=="delete"){
                lineStream>>args;
                deleteFile(args);
            }else if(inst=="ls"){
                ls();
            }else if(inst=="quit"){
                saveToFile();
                break;
            }
        }
    }
};

#endif //DATA_STRUCTURE_COURSE_FILE_H
