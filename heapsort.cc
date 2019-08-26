#include <iostream>
#include <cmath>
#include <cstdlib>
#define parent(i) (i-1)/2
#define exchange(v,i,j) 

using namespace std;

void print_array(int v[], int n);
void heapsort(int v[], int n);

int main(){
    int n, *v = NULL;

    cin >> n;

    v = new int[n]();
    srand(time(NULL));

    for (int i = 0; i < n; ++i)
        //v[i] = rand()%10000+1;
        cin >> v[i];

    print_array(v,n);
    heapsort(v,n);
    print_array(v,n);

    delete v;
}

void print_array(int v[], int n){
    for (int i = 0; i < n; ++i)
        cout << v[i] << " ";

    cout << endl;
}

void heapsort(int v[], int n){
    int leaf, h, heap_size, up;

    for (int *aux = v; n; aux++, n--){
        h = (int) ceil(log2(n+1)-1);
        heap_size = pow(2,h+1) -1;

        for (leaf = (n-1)/2+1; leaf < n; leaf++)
            for (up = leaf; up > 0; up = parent(up))
                    if (aux[parent(up)] > aux[up])
                        swap(aux[parent(up)], aux[up]);
        
        //print_array(aux,n);
    }
}