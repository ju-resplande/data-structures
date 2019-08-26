#include <iostream>
#include <queue>
#include <cmath>
#define TYPE int

using namespace std;

class AvlNode{
public:
    AvlNode(TYPE data){
        key = data;
        lchild = rchild = parent = NULL;
        height = 1;
    };

    TYPE key;
    char height;
    AvlNode *parent, *lchild, *rchild;
};

char height(AvlNode *node){
    if (node)
        return node->height;
    else
        return 0;
}

void update_height(AvlNode* node){
    node->height = max(height(node->lchild), height(node->rchild)) + 1;
}


class Avl{
public:
    Avl(){root = NULL;};
    void insert_node(int key);
    void remove_node(int key);
    void print();

private:
    AvlNode *root;
    void rotate_left(AvlNode* node);
    void rotate_right(AvlNode* node);
    void replace_node(AvlNode* node, AvlNode *sub);
};

void Avl :: insert_node(int key){
    AvlNode *new_node = new AvlNode(key); 

    if (not root)
        root = new_node;
    else{
        AvlNode *p = root;

        while(true){
            if (key < p->key){
                if (p->lchild)
                    p = p->lchild;
                else{
                    p->lchild = new_node;
                    break;
                }
            }else{
                if (p->rchild)
                    p = p->rchild;
                else{
                    p->rchild = new_node;
                    break;
                }
            }
        }

        AvlNode *child = p, *grandchild = new_node;

        new_node->parent = p;
        p->height = max((char) 2,p->height);
        
        for (p = p->parent ; p != NULL; grandchild = child, child = p, p = p->parent){
            update_height(p);

            if (abs(height(p->lchild) - height(p->rchild)) > 1){
                if (p->lchild == child){
                    if (child->rchild == grandchild)
                        rotate_left(child);

                rotate_right(p);
                }else{
                    if (child->lchild == grandchild)
                        rotate_right(child);

                rotate_left(p);
                }

                break;
            }
        }
    }
}

void Avl :: remove_node(int key){
    AvlNode* p = NULL, *sub = NULL, *trash = NULL;

    p = root;
    while (true){
        if (not p)
            return;
        else if (key == p->key)
            break;
        
        p = (key < p->key) ? p->lchild : p->rchild;
    }

    if (not trash->lchild)
        replace_node(trash, trash->rchild);
    else if (not trash->rchild)
        replace_node(trash, trash->lchild);
    else{
        for (sub = trash->rchild; sub->lchild; sub = sub->lchild);

        replace_node(sub,sub->rchild);
        replace_node(trash, sub);

        sub->lchild = trash->lchild;
        sub->rchild = trash->rchild;

        sub->lchild->parent = sub;

        if (sub->rchild)
            sub->rchild->parent = sub;
    }

    delete trash;

    for (p = (sub? sub : trash)->parent ; p ; p = p->parent){
        update_height(p);

        if (abs(height(p->lchild) - height(p->rchild)) > 1){
            if (height(p->lchild) > height(p->rchild)){
                if (height(p->lchild->rchild) > height(p->lchild->lchild))
                    rotate_left(p->lchild);

                rotate_right(p);
            }else{
                if (height(p->rchild->lchild) > height(p->rchild->lchild))
                    rotate_right(p->rchild);

                rotate_left(p);
            }

            p = p->parent;
        }        
    }
}

void Avl :: replace_node(AvlNode *node, AvlNode *sub){
    if (sub)
        sub->parent = node->parent;

    if (node->parent){
        if (node->parent->lchild == node)
            node->parent->lchild = sub;
        else
            node->parent->rchild = sub;
    }else
        root = sub;
}

void Avl :: rotate_left(AvlNode *node){
    AvlNode *tmp = NULL;

    if (!node || !node->rchild)
        return;

    tmp = node->parent;
    node->parent = node->rchild;
    node->rchild->parent = tmp; 

    if (tmp){
        if (tmp->lchild && tmp->lchild == node)
            tmp->lchild = node->rchild;
        else
            tmp->rchild = node->rchild;
    }
    else
        root = node->rchild;

    tmp = node->rchild->lchild;
    node->rchild->lchild = node;
    node->rchild = tmp;

    if (tmp)
        tmp->parent = node;


    update_height(node);
    update_height(node->parent);
}

void Avl :: rotate_right(AvlNode *node){
    AvlNode *tmp = NULL;

    if (!node || !node->lchild)
        return;

    tmp = node->parent;
    node->parent = node->lchild;
    node->lchild->parent = tmp; 

    if (tmp){
        if (tmp->lchild && tmp->lchild == node)
            tmp->lchild = node->lchild;
        else
            tmp->rchild = node->lchild;
    }
    else
        root = node->lchild;

    tmp = node->lchild->rchild;
    node->lchild->rchild = node;
    node->lchild = tmp;

    if (tmp)
        tmp->parent = node;

    update_height(node);
    update_height(node->parent);
}

void Avl :: print(){
    queue <AvlNode*> nodes;
    AvlNode *tmp = NULL;

    if (root)
        nodes.push(root);

    while (not nodes.empty()){
        tmp = nodes.front();
        nodes.pop();

        cout << tmp->key << ' ' << (int) tmp->height << endl;

        if (tmp->lchild)
            nodes.push(tmp->lchild);

        if (tmp->rchild)
            nodes.push(tmp->rchild);
    }
}

int main(void){
    Avl test;
    int v[] ={1,2,3};

    for (int i = 0; i < 3; ++i)
        test.insert_node(v[i]);

    test.print();

    //cout << test.root->lchild->key << endl;
    
    return 0;
}