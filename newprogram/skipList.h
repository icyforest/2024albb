//大佬的大小简直就是依托...优化了哈大小和重名
#pragma once
#include "node.h"
#include<iostream>
#include<cstddef>
#include<cassert>
#include<ctime>
#include<random>
using namespace std;

template<typename K,typename V>
class skipList {
public:
    explicit skipList(K tailerKey) {
        level = 0;
        createList(tailerKey);
        nodeSize = 0;
    }

    ~skipList() {
        freeList();
    }

    int getNodeSize() const {
        return nodeSize;
    }

    Node<K,V>* search(K k) const;

    bool insert(K k, V v);

    bool remove(K k);

private:
    void createList(K tailerKey);
    void freeList();
    void createNode(int node_Level,Node<K, V>* &node);
    void createNode(int node_Level,Node<K, V>* &node, K k, V v);

    void printAllNodes();
    void printNode(Node<K, V>* node,int node_Level);
private:
    int level;
    Node<K,V>* header;
    Node<K,V>* tailer;
    static int LEVEL_MAX;
    size_t nodeSize;//cstddef
};

template<typename K,typename V>
int skipList<K, V>::LEVEL_MAX = 16;

template<typename K,typename V>
void skipList<K, V>::createList(K tailerkey) {
    createNode(0, tailer);

    tailer -> key = tailerkey;
    tailer->forwardPtr[0] = nullptr;

    createNode(LEVEL_MAX, header);
    for(int i = LEVEL_MAX; i >= 0; i--) {
        header->forwardPtr[i] = tailer;
    }
}

template<typename K,typename V>
void skipList<K, V>::createNode(int node_Level, Node<K, V>* &node) {
    node = new Node<K,V>(0,0);//actually 0
    node->forwardPtr = new Node<K,V>*[LEVEL_MAX + 1];
    node->nodeLevel = node_Level;

    assert(node != nullptr);//error when node equals to nullptr
}

template<typename K,typename V>
void skipList<K, V>::createNode(int node_Level, Node<K, V>* &node, K k, V v) {
    node = new Node<K,V>(k,v);

    if(node_Level > 0) {
        node->forwardPtr = new Node<K,V>*[node_Level + 1];
    }
    node->nodeLevel = node_Level;

    assert(node != nullptr);
}

template<typename K,typename V>
void skipList<K, V>::freeList() {
    Node<K,V>* p = header;
    Node<K,V>* after = nullptr;
    while(p != nullptr) {
        after = p -> forwardPtr[0];
        delete [] p->forwardPtr;
        delete p;
        p = after;
    }
}

template<typename K,typename V>
Node<K, V>* skipList<K, V>::search(const K k) const {
    Node<K,V>* p = header;
    for(int i = level; i >= 0; i--) {
        while(p->forwardPtr[i]->key < k) {
            p = p->forwardPtr[i];
        }
    }
    p = p->forwardPtr[0];
    if(p->key != k) {
        return nullptr;
    }
    return p;
}

template<typename K,typename V>
bool skipList<K, V>::insert(K k, V v) {
    Node<K,V>* update[LEVEL_MAX + 1];
    Node<K,V>* p = header;
    for(int i = level; i >= 0; i--) {
        while((p->forwardPtr[i])->key < k) {
            p = p->forwardPtr[i];
        }
        update[i] = p;
    }

    p = p->forwardPtr[0];

    if(p->key == k) {
        return false;
    }

    srand(static_cast<unsigned>(time(nullptr)));
    int templevel = rand() % LEVEL_MAX;

    if(templevel > level) {
        templevel = ++ level;
        update[level] = header;
    }

    Node<K,V>* temp;
    createNode(templevel, temp, k, v);

    cout << "templevel = " << templevel << endl;
    for(int i = templevel; i >= 0; i--) {
        p = update[i];
        temp->forwardPtr[i] = p->forwardPtr[i];
        p->forwardPtr[i] = temp;
    }

    cout << "templevel = " << templevel << endl;

    printAllNodes();

    nodeSize++;

    return true;
}

template<typename K,typename V>
void skipList<K, V>::printAllNodes() {
    Node<K,V>* p = header;
    while(p->forwardPtr[0] != tailer) {
        p = p->forwardPtr[0];
        printNode(p,p->nodeLevel);
    }
    printf("------------");
    printf("\n");
}

template<typename K,typename V>
void skipList<K, V>::printNode(Node<K,V>* node,int node_Level) {
    if(node == nullptr) {
        return;
    }
    cout << "node.key = " << node->key << " node.value = " << node->value << endl;
    for(int i = 0;i <= node_Level; i++) {
        cout << "forwardPtr[" << i << "]";
        cout << node->forwardPtr[i]->key << " " << node->forwardPtr[i]->value << endl;
    }
}

template<typename K, typename V>
bool skipList<K, V>::remove(K k) {
    Node<K,V>* update[LEVEL_MAX + 1];
    Node<K,V>* p = header;
    for(int i = level; i >= 0; i--) {
        while(p->forwardPtr[i]->key < k) {
            p = p->forwardPtr[i];
        }
        update[i] = p;
    }
    p = p->forwardPtr[0];

    if(p->key != k) {
        return false;
    }

    for(int i = 0;i <= level; i++) {
        if(update[i]->forwardPtr[i] != p) {
            break;
        }
        update[i]->forwardPtr[i] = p->forwardPtr[i];
    }
    delete p;
    while(level > 0 && header->forwardPtr[level] == tailer) {
        level --;
    }
    nodeSize--;
    return true;
}
