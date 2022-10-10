/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * x = t;
    Node * y = t->right;

    x->right = y->left;
    y->left = x;
    t = y;

    x->height = std::max(heightOrNeg1(x->left), heightOrNeg1(x->right)) + 1;
    y->height = std::max(heightOrNeg1(y->left), heightOrNeg1(y->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * x = t;
    Node * y = t->left;

    x->left = y->right;
    y->right = x;
    t = y;
    x->height = std::max(heightOrNeg1(x->left), heightOrNeg1(x->right)) + 1;
    y->height = std::max(heightOrNeg1(y->left), heightOrNeg1(y->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) < -1) {
        int left = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (left == -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    } else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) > 1) {
        int right = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (right == 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }
    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (!subtree) {
        subtree = new Node(key, value);
    } else if (subtree->key > key) {
        insert(subtree->left, key, value);
    } else if (subtree->key < key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) return;
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* leftNode = subtree->left;
            if(leftNode != NULL){
                delete subtree;
                subtree = leftNode;
            }
            Node* rightNode = subtree->right;
            if(rightNode != NULL){
              delete subtree;
              subtree = rightNode;
            }
        }
    }
    // your code here
    if (subtree) {
        rebalance(subtree);
    }
}
