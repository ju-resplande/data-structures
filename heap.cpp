#include <iostream>
#include <cmath>
#include <queue>

#define father(i) ((i-1)/2)
#define lchild(i) ((2*i) + 1)
#define rchild(i) ((2*i) + 2)

using namespace std;

void Swap(int v[], int a, int b);

class Heap{
private:
	int *v;
	int n, max;
	void ReHeapUp(int i){
		for (v[i] > v[father(i)]; v[i] > v[father(i)] and i > 0; i = father(i))
			Swap(v, i, father(i));
	};

	void ReHeapDown(void){
        int big_child;

        for (int i = 0;  lchild(i) < n; i = big_child){

            if (rchild(i) < n && v[rchild(i)] > v[lchild(i)])
                big_child = rchild(i);
            else
                big_child = lchild(i);

            if (v[big_child] < v[i])
                break;

            Swap(v, i, big_child);
        }
    };

public:
	Heap(int height){
		max = pow(2,height+1)-1;
		v = new int[max]();
		n = 0;
	};

	void Insert(int num){
		if (n == max)
			return;

		v[n] = num;
		
		ReHeapUp(n); n++;
	};

	void Insert_array(int v[], int size){
		for (int i = 0; i < size; ++i)
			Insert(v[i]);
	}

	int Remove(void){
        v[0] = v[--n];
        v[n] = 0;

        ReHeapDown();
    };

	void BFS(){
		int i;
		queue <int> numbers;

		if (n)
			numbers.push(0);
		

		while (!numbers.empty()){
			i = numbers.front();
			numbers.pop();

			cout << v[i] << endl;

			if (lchild(i) < n && v[lchild(i)])
				numbers.push(lchild(i));

			if (rchild(i) < n && v[rchild(i)])
				numbers.push(rchild(i));
		}
	}

	~Heap(){
		delete v;
	};
	
	
};

int main(){
	Heap test(2);
	int v[5] = {5,4,3,2,1};

	test.Insert_array(v, 5);
	test.BFS();
    test.Remove();
    test.BFS();

	return 0;
}

void Swap(int v[], int a, int b){
	int tmp;

	tmp = v[a];
	v[a] = v[b];
	v[b] = tmp;
};