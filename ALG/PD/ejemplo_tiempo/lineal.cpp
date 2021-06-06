#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

int main(int argc, char ** argv){
	ifstream fichero(argv[1]);
	int a,b;
	fichero >> a >> b;
	int d = a*b;
	vector<int> v(d);
	auto inicio = clock();
	for (int i=0; i < d; i++)
		fichero >> v[i];
	auto fin = clock();
	cout << d << " " << (double) (fin - inicio) / CLOCKS_PER_SEC << endl;

}
