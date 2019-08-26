#include <iostream>
#include <cstdlib> 
#include <queue>
#define LEFT true
#define RIGHT false

using namespace std;

class RbNode{
public:
    int key;
    RbNode *parent, *lchild, *rchild;
    bool isred;
    
    RbNode(int num){
        key = num;
        parent = lchild = rchild = NULL;
        isred = true;
    };
};


bool isred(RbNode *node);
bool isblack(RbNode *node);
//criei as duas acima
//so por conta do no nulo

//dado no e a direcao fornece o filho
//facilitar quanto a casos simetricos
RbNode* child(RbNode *node, bool dir);

class RbTree{
public:
    RbTree(void){
        root = NULL;
    };

    void insertnode(int num);
    void removenode(int num);
    void print(void);

private:
    RbNode *root;
    void rotate_left(RbNode *node);
    void rotate_right(RbNode *node);
    void rotate(RbNode *node, bool dir);
    void replacenode(RbNode *node, RbNode *sub);
};



int main(void){
    RbTree test;
    char action;
    int num;

    /*
        Q -> quit
        R -> remove node
        I -> insert node
     */


    while (cin >> action && action != 'Q'){
        cin >> num;
        cin.clear();

        if (action == 'R')
            test.removenode(num);
        else if (action == 'I')
            test.insertnode(num);

        test.print();
        cout << endl << endl;
    }

    return 0;
}

bool isred(RbNode *node){
    if (!node)
        return false;

    return node->isred;
};

bool isblack(RbNode *node){
    return not isred(node);
};

RbNode* child(RbNode *node, bool dir){
    if (node == NULL)
        exit(1);        

    if (dir)
        return node->lchild;
    else
        return node->rchild;
}

void RbTree :: rotate_left(RbNode *node){
    RbNode *tmp = NULL;

    if (!node || !node->rchild)
        return;
    
    tmp = node->parent; 
    node->parent = node->rchild; //pai do no eh o filho da dir
    node->rchild->parent = tmp; //pai do filho da direita eh o avo

    if (tmp){
        if (tmp->lchild && tmp->lchild == node)
            tmp->lchild = node->rchild;
        else
            tmp->rchild = node->rchild;
    }
    else
        root = node->rchild;


    if (node->rchild->lchild) //se houver filho a esquerda do filho a direira
        node->rchild->lchild->parent = node; //seu pai sera o no

    tmp = node->rchild;
    node->rchild = node->rchild->lchild; //filho a direita do no e o filho a esquerda do o a direita 
    tmp->lchild = node; //filho a esquerda do no a direita e o no
};

void RbTree :: rotate_right(RbNode *node){
    RbNode *tmp = NULL;
    
     if (!node || !node->lchild)
        return;

    tmp = node->parent; 
    node->parent = node->lchild; //pai do no eh o filho da esq
    node->lchild->parent = tmp; //pai do filho da esq eh o avo

    if (tmp){
        if (tmp->lchild && tmp->lchild == node)
            tmp->lchild = node->lchild;
        else
            tmp->rchild = node->lchild;   
    }else
        root = node->lchild;

    if (node->lchild->rchild) //se houver filho a dir do filho a esq
        node->lchild->rchild->parent = node; //seu pai sera o no

    tmp = node->lchild;
    node->lchild = node->lchild->rchild; //filho a esq do no e o filho a dir do o a direita 
    tmp->rchild = node; //filho a esquerda do no a direita e o no
};

void RbTree :: rotate(RbNode *node, bool dir){
    if (dir == LEFT)
        rotate_left(node);
    else
        rotate_right(node);
}

void RbTree :: insertnode(int num){
    RbNode* new_node = new RbNode(num);
    RbNode* tmp = NULL, *parent = NULL, *grand = NULL, *uncle = NULL;
    bool dir;

    if (root == NULL)
        root = new_node;
    else{
        for (tmp = root; tmp ; tmp = child(tmp,dir)){
           dir = (num < tmp->key) ? LEFT : RIGHT;

           if (!child(tmp,dir)) break;
        }

        new_node->parent = tmp;
        if (dir == LEFT)
            tmp->lchild = new_node;
        else
            tmp->rchild = new_node;
    }

    tmp = new_node;
    parent = tmp->parent;
    if (isred(parent)){
        grand = parent->parent;
        uncle = (grand->lchild == parent) ? grand->rchild : grand->lchild;

        if (isred(parent) && isred(uncle)){
            parent->isred = uncle->isred = false;
            grand->isred = true;
        }else{
            if ((grand->lchild == parent && parent->rchild == tmp) || (grand->rchild == parent && parent->lchild == tmp)){
                if (grand->lchild == parent)
                    rotate_left(parent);
                else
                    rotate_right(parent);
            }else
                tmp = parent;
            
            parent = tmp->parent;

            if (parent->lchild == tmp)
                rotate_right(parent);           
            else
                rotate_left(parent);

            tmp->isred = false;

            if (tmp->lchild)
                tmp->lchild->isred = true;

            if (tmp->rchild)
                tmp->rchild->isred = true; 

        }
    }

    root->isred = false;
}

void RbTree :: removenode(int num){
    RbNode *tmp = NULL, *sub = NULL;
    RbNode *extra_parent = NULL;
    bool dir, extra_dir, change_color = false;

    /*
        change_color -> se precisa fazer as mudancas de cor
        extra_parent -> o pai do no nulo ficticio
        extra_dir -> a direcao do filho com relacao ao pai
        LEFT (definido como true) e RIGHT (definido como false) 
     */

    if (root == NULL)
        return;

    for (tmp = root; tmp->key != num; tmp = child(tmp,dir)){
        dir = (num < tmp->key) ? LEFT : RIGHT;

        if (child(tmp,dir) == NULL)
            return;
    }

    if (!tmp->lchild){   
        if (tmp->parent){
			if (tmp->parent->rchild == tmp)
                extra_dir = RIGHT;
            else
                extra_dir = LEFT;
       }

        replacenode(tmp,tmp->rchild);

       	if (tmp->rchild){
		    extra_parent = tmp->rchild;
		    extra_dir = RIGHT;
    	}
	    else
		    extra_parent = tmp->parent;
    }
    else if(!tmp->rchild){
        replacenode(tmp,tmp->lchild);

        extra_parent = tmp->lchild;
	    extra_dir = LEFT;
    }
    else{
        for (sub = tmp->rchild; sub->lchild; sub = sub->lchild);

        if (sub->lchild){
            extra_parent = sub->lchild;
            extra_dir = LEFT;
            replacenode(sub,sub->lchild);
        }else{
            if (sub->parent->rchild == sub)
                extra_dir = RIGHT;
            else
                extra_dir = LEFT;

            replacenode(sub,sub->rchild);
            
            if (sub->rchild){
		        extra_parent = sub->rchild;
		        extra_dir = RIGHT;
        	}
	        else
		        extra_parent = sub->parent;
        }
        replacenode(tmp,sub);
        sub->lchild = tmp->lchild;
        if (sub->lchild)
            sub->lchild->parent = sub;
        
        sub->rchild = tmp->rchild;
        
        if (sub->rchild)
            sub->rchild->parent = sub;
    }

    if (isblack(tmp) &&  isred(sub)){
        sub->isred = tmp->isred;
        change_color = false;
    }
    else
        change_color = false;

    bool dir_sibling;
    RbNode *sibling = NULL;

    for (change_color and extra_parent; change_color;){

        if (isred(extra_parent)){
            extra_parent->isred = false;
            change_color = false;
        }

        dir_sibling = not extra_dir;
        sibling = child(extra_parent, dir_sibling);


        if (isred(sibling)){
            rotate(extra_parent, not dir_sibling);
                sibling->isred = false;
                extra_parent->isred = true;

                sibling = child(sibling,dir_sibling);
                extra_parent = sibling;
        }

        if (not sibling or (isblack(sibling->lchild) && isblack(sibling->rchild))){
            if (sibling)
                sibling->isred = true;

            if (not extra_parent->parent)
                break;
            else{
                extra_dir = extra_parent->parent->lchild == extra_parent ? LEFT : RIGHT;
                extra_parent = extra_parent->parent;
            }

            continue;
        }

        if (isblack(child(sibling, dir_sibling))){
            rotate(sibling,dir_sibling);
            sibling->parent->isred = false;
            sibling->isred = true;
            sibling = sibling->parent;
        }

        if(isred(child(sibling,dir_sibling))){
            rotate(extra_parent,not dir_sibling);
            sibling->isred = extra_parent->isred;
            sibling->lchild->isred = sibling->rchild->isred = false;
            break;
        }
    }

    delete tmp;
}

void RbTree :: replacenode(RbNode *node, RbNode *sub){
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

void RbTree :: print(void){
    queue <RbNode*> nodes;
    RbNode* tmp = NULL;

    if (root)
        nodes.push(root);

    while (!nodes.empty()){
        tmp = nodes.front();
        nodes.pop();

        cout << tmp->key;

        if (isred(tmp))
            cout << " red" << endl;
        else
            cout << " black" << endl;

        if (tmp->lchild)
            nodes.push(tmp->lchild);

        if (tmp->rchild)
            nodes.push(tmp->rchild);
    }
}
