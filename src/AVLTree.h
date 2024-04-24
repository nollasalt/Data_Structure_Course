//
// Created by nolla on 24-4-14.
//

#ifndef DATA_STRUCTURE_COURSE_AVLTREE_H
#define DATA_STRUCTURE_COURSE_AVLTREE_H

#include <bits/stdc++.h>
using namespace std;
const char fileName[256]="data.bin";
template<typename T>
struct NODE
{
    NODE<T>* parent;
    NODE<T>* lchild;
    NODE<T>* rchild;
    T val;
    int depth;
    NODE(T val=T())
    {
        parent=nullptr;
        depth=0;
        lchild=rchild=nullptr;
        this->val=val;
    }
};
template<typename T>
class AVL
{
private:
    NODE<T>* rt= nullptr;
    NODE<T>* remove_val(NODE<T> *&root, NODE<T> *&node);
    NODE<T>* insert_val(NODE<T>*& root, NODE<T>* node, NODE<T>* parent);
    void update_depth(NODE<T>* node);
    NODE<T>* adjust(NODE<T>*& root, NODE<T>* node);
    NODE<T>* LL_rotate(NODE<T>*node);
    NODE<T>* RL_rotate(NODE<T>*node);
    NODE<T>* RR_rotate(NODE<T>*node);
    NODE<T>* LR_rotate(NODE<T>*node);
    int get_depth(NODE<T>*node);
    int get_balance(NODE<T>*node);
    NODE<T>* *Find_Min(NODE<T>*root);
    void save(NODE<T>* p, FILE* file);
    void load(NODE<T>* p,FILE* file);
public:
    ~AVL(){saveToFile();}
    NODE<T>* insert(T val);
    bool remove(T val);
    bool find(T val);
    void saveToFile();
    void loadFromFile();
};

template<typename T>
bool AVL<T>::find(T val) {
    NODE<T>* p = rt;
    while(p!=nullptr)
    {
        if(val==p->val)
            return true;
        if(val<p->val)
            p=p->lchild;
        else
            p=p->rchild;
    }
    return false;
}

template<typename T>
void AVL<T>::loadFromFile() {
    FILE* file=fopen(fileName,"r");
    T* temp=new T;
    while(fread(temp,sizeof(T),1,file))
    {
        insert(*temp);
    }
    fclose(file);
}

template<typename T>
void AVL<T>::save(NODE<T> *p, FILE* file) {
    if(!p)
        return;
    fwrite(&(p->val),sizeof(T),1,file);
    save(p->lchild, file);
    save(p->rchild, file);
}

template<typename T>
void AVL<T>::saveToFile() {
    FILE* file=fopen(fileName,"w");
    save(rt, file);
    fclose(file);
}

typedef pair<string,string> user;
template<>
void AVL<user>::save(NODE<user> *p, FILE *file) {
    if(!p)
        return;
    int n;
    n=p->val.first.length();
    fwrite(&n,sizeof(int),1,file);
    fwrite(p->val.first.c_str(),sizeof(char),n,file);
    n=p->val.second.length();
    fwrite(&n,sizeof(int),1,file);
    fwrite(p->val.second.c_str(),sizeof(char),n,file);

    save(p->lchild, file);
    save(p->rchild, file);
}
template<>
void AVL<user>::loadFromFile() {
    FILE* file=fopen(fileName,"r");
    int n;
    while(fread(&n,sizeof(int),1,file))
    {
        char buf[256];
        fread(buf,sizeof(char),n,file);
        string x=buf;
        fread(&n,sizeof(int),1,file);
        fread(buf,sizeof(char),n,file);
        string y=buf;
        insert({x,y});
    }
    fclose(file);
}

template<typename T>
NODE<T>* AVL<T>::insert(T val)
{
    NODE<T> *temp= nullptr;
    NODE<T>* node=new NODE<T>(val);
    temp=insert_val(rt,node,nullptr);
    if (temp)
    {
        update_depth(temp);
        rt=adjust(rt, temp);
    }
    else
        delete temp;
    return temp;
}
template<typename T>
NODE<T>* AVL<T>::insert_val(NODE<T>* &root, NODE<T>* node, NODE<T>* parent)
{
    if (root==nullptr)
    {
        root=node;
        node->parent=parent;
        return root;
    }
    if (node->val<root->val)
        return insert_val(root->lchild, node,root);
    else if(node->val>root->val)
        return insert_val(root->rchild, node,root);
    else
        return nullptr;
}

template<typename T>
NODE<T>* AVL<T>::adjust(NODE<T>* &root, NODE<T>* node)
{
    int balance=0;
    while (node!=nullptr)
    {
        update_depth(node);
        balance= get_balance(node);
        if (balance>1 || balance<-1)
        {
            if (balance>1)
            {
                if (get_balance(node->lchild) > 0)
                    node=LL_rotate(node);
                else
                    node=LR_rotate(node);
            }
            else
            {
                if (get_balance(node->rchild) < 0)
                    node=RR_rotate(node);
                else
                    node=RL_rotate(node);
            }
            if (node->parent==nullptr)
            {
                root=node;
                break;
            }
        }
        node=node->parent;
    }
    return root;
}

template<typename T>
NODE<T>** AVL<T>::Find_Min(NODE<T>* root)
{
    while (root->lchild)
        root=root->lchild;
    return &root;
}

template<typename T>
NODE<T>* AVL<T>::remove_val(NODE<T>* &root, NODE<T>* &node)
{
    NODE<T>* parent=node->parent;
    NODE<T>* temp=nullptr;
    if (node->rchild==nullptr && node->lchild!=nullptr)
    {
        temp=node;
        node=node->lchild;
        node->parent=temp->parent;
        delete temp;
        update_depth(node);
    }
    else if(node->lchild==nullptr && node->rchild!=nullptr)
    {
        temp=node;
        node=node->rchild;
        node->parent=temp->parent;
        delete temp;
        update_depth(node);
    }
    else if(node->rchild==nullptr && node->lchild==nullptr)
    {
        parent=node->parent;
        if (parent)
        {
            delete node;
            node=nullptr;
            update_depth(parent);
        }
        else
        {
            delete root;
            root=nullptr;
        }
    }
    else
    {
        NODE<T>* *tmp=Find_Min(node->rchild);
        node->val=(*tmp)->val;
        parent=(*tmp)->parent;
        delete *tmp;
        *tmp=nullptr;
        update_depth(parent);
    }
    return parent;
}

template<typename T>
bool AVL<T>::remove(T val)
{
    NODE<T> **p=&rt;
    while(p != nullptr)
    {
        if((*p)->val < val)
            p=&((*p)->rchild);
        else if((*p)->val > val)
            p=&((*p)->rchild);
        else break;
    }
    if(p == nullptr)
        return false;
    NODE<T>*tmp=remove_val(rt, *p);
    adjust(rt,tmp);
    return true;
}

template<typename T>
int AVL<T>::get_depth(NODE<T>*node)
{
    if (node==nullptr)
        return 0;
    return node->depth;
}

template<typename T>
int AVL<T>::get_balance(NODE<T>*node)
{
    if (node==nullptr)
        return 0;
    else
        return get_depth(node->lchild) - get_depth(node->rchild);
}

template<typename T>
void AVL<T>::update_depth(NODE<T>* node)
{
    if (node==nullptr)
        return;
    else
    {
        int depth_lchild= get_depth(node->lchild);
        int depth_rchild= get_depth(node->rchild);
        node->depth=max(depth_lchild, depth_rchild) + 1;
    }
}

template<typename T>
NODE<T>* AVL<T>::RR_rotate(NODE<T>* node)
{
    NODE<T>* parent=nullptr,*son;
    parent=node->parent;
    son=node->rchild;
    if (son->lchild!=nullptr)
        son->lchild->parent=node;
    node->rchild=son->lchild;
    update_depth(node);
    son->lchild=node;
    son->parent=parent;
    if (parent!=nullptr)
    {
        if (parent->lchild==node)
            parent->lchild=son;
        else
            parent->rchild=son;
    }
    node->parent=son;
    update_depth(son);
    return son;
}

template<typename T>
NODE<T>* AVL<T>::LL_rotate(NODE<T>* node)
{
    NODE<T>* parent=nullptr,*son;
    parent=node->parent;
    son=node->lchild;
    if (son->rchild!=nullptr)
        son->rchild->parent=node;
    node->lchild=son->rchild;
    update_depth(node);
    son->rchild=node;
    son->parent=parent;
    if (parent!=nullptr)
    {
        if (parent->lchild==node)
            parent->lchild=son;
        else
            parent->rchild=son;
    }
    node->parent=son;
    update_depth(son);
    return son;
}

template<typename T>
NODE<T>* AVL<T>::LR_rotate(NODE<T>* node)
{
    RR_rotate(node->lchild);
    return LL_rotate(node);
}

template<typename T>
NODE<T>* AVL<T>::RL_rotate(NODE<T>* node)
{
    LL_rotate(node->rchild);
    return RR_rotate(node);
}

#endif //DATA_STRUCTURE_COURSE_AVLTREE_H
