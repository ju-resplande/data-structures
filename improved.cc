#include <iostream>
#include <cstdlib>
#include <ctime> 
#define SIZE 100
#define DAD(i) (i-1)/2
#define LCHILD(i) (2*i)+1
#define RCHILD(i) (2*i)+2

using namespace std;

void exchange(int v[], int i, int j);

class Heap
{
public:
    Heap(void){n = 0;};

    void insert(int num);
    int remove(void);
    void print(void);
    bool check(void);
private:
    int tree[SIZE];
    int n;

    void print(int i);
    void reheap_up(void);
    void reheap_down(void);
};

void Heap :: insert(int num){
    if (n+1 == SIZE)
        return;

    tree[n++] = num;
    reheap_up();
}

void Heap :: reheap_up(void){
    for (int i = n-1; i > 0  && tree[i] > tree[DAD(i)]; i = DAD(i))
        exchange(tree,i,DAD(i));
}

int Heap :: remove(void){
    int tmp;

    tmp = tree[0]; 
    tree[0] = tree[--n];

    if (n > 1)
        reheap_down();

    return tmp;
}

void Heap :: reheap_down(void){
    int swap;

    for (int i = 0; LCHILD(i) < n  || RCHILD(i) < n; i = swap){
        if (RCHILD(i) < n)
            swap = (tree[RCHILD(i)] > tree[LCHILD(i)]) ? RCHILD(i) : LCHILD(i);
        else
            swap = LCHILD(i);

        if (tree[swap] > tree[i])
            exchange(tree,i,swap);
        else
            return;
    }
}

void Heap :: print(void){
    print(0);
    cout << endl;
}



void Heap :: print(int i){
    if (i >= n)
        return;

    cout << tree[i] <<"  (" << i << ") ";
    print(LCHILD(i));
    print(RCHILD(i));
}

bool Heap :: check(void){
    int i = 0;

    while (++i < n)
        if (tree[i] > tree[DAD(i)])
            return false;

    return true;
}

void heapsort(int v[], int n){
    Heap aux;

    for (int i = 0; i < n; ++i)
        aux.insert(v[i]);

    for (int i = 0; i < n; ++i)
        v[i] = aux.remove();
}

int main(){
    int v[10];

    srand(time(NULL));

    for (int i = 0; i < 10; ++i)
        v[i] = rand()%1000;

    for (int i = 0; i < 10; ++i)
        cout << v[i] << " ";
    cout << endl;

    heapsort(v,10);

    for (int i = 0; i < 10; ++i)
        cout << v[i] << " ";
    cout << endl;
}

void exchange(int v[], int i, int j){
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
