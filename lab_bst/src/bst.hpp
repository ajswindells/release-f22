/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node*& n = find(root, key);
    if (n == NULL) {
        return V();
    }
    return n->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == NULL || subtree->key == key) {
        return subtree;
    }
    if (subtree->key < key) {
        return find(subtree->right, key);
    }
    return find(subtree->left, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    Node*& n = find(root, key);
    if (n == NULL) {
        Node* insert = new Node(key, value);
        n = insert;
    }
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;
    }
    if (subtree->left == NULL && subtree->right == NULL) {
        if (value < subtree->value) {
            subtree->left = new Node(key, value);
            return;
        } else {
            subtree->right = new Node(key, value);
            return;
        }
    }
    if (subtree->left != NULL && subtree->right == NULL) {
        if (value < subtree->value) {
            insert(subtree->left, key, value);
        } else {
            subtree->right = new Node(key, value);
            return;
        }
    }
    if (subtree->left == NULL && subtree->right != NULL) {
        if (value > subtree->value) {
            insert(subtree->right, key, value);
        } else {
            subtree->left = new Node(key, value);
            return;
        }
    }
    if (value < subtree->value) {
        insert(subtree->left, key, value);
    }
    if (value > subtree->value) {
        insert(subtree->right, key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K k_hold = first->key;
    V v_hold = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = k_hold;
    second->value = v_hold;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    Node*& n = find(subtree, key);
    if (n == NULL) {
        return;
    } else if (n->left == NULL && n->right == NULL) {
        delete n;
        n = NULL;
    } else if (n->left != NULL && n->right == NULL) {
        Node* del = n;
        n = n->left;
        delete del;
    } else if (n->left == NULL && n->right != NULL) {
        Node* del = n;
        n = n->right;
        delete del;
    } else {
        Node* predecessor = n->left;
        while (predecessor->right != NULL) {
            predecessor = predecessor->right;
        }
        swap(n, predecessor);
        remove(n->left, key);
    }
}

template <class K, class V>
BST<K, V> listBuild(std::
vector<std::pair<K, V>> inList){
    // your code here
    BST<K,V> tree;
    for(unsigned int i = 0; i < inList.size(); i++) {
        tree.insert(inList[i].first, inList[i].second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::sort(inList.begin(), inList.end());
    std::map<int, int> m;
    do {
        BST<K,V> list = listBuild(inList);
        if(m.find(list.height()) != m.end()) {
            m.at(list.height())++;
        } else {
            m.insert({list.height(), 1});
        }

    }
    while (std::next_permutation(inList.begin(), inList.end()));
    int max = 0;
    for(auto i : m) {
        if(i.first > max) {
            max=i.first;
        }
    }
    ++max;
    std::vector<int> arr(max);
    for( int i =0; i < max; i++) {
        if(m.find(i) != m.end()) {
            arr.at(i) = m.at(i);
        }
    }
    return arr;
}