#pragma once
template<typename K, typename V>
class skipList;

template<typename K, typename V>
class Node {
    friend class skipList<K, V>;

    public:
    Node (){}//all in all write a constructor and destructor

    Node(K k, V v);
    //avoid duplicate names

    ~Node(){}

    K getKey();//cpp use Pascal naming way to avoid errors caused by duplicate names

    V getValue();

    private:
    K key;// used to search
    V value;
    Node<K, V> ** forwardPtr;
    int nodeLevel;
};

template<typename K, typename V>
Node<K, V>::Node(const K k, const V v) {
    key = k;
    value = v;
}

template<typename K, typename V>
K Node<K, V>::getKey() {
    return key;
}

template<typename K, typename V>
V Node<K, V>::getValue() {
    return value;
}