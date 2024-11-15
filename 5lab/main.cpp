#include <iostream>
#include <string>

template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T (*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T (*) (T,T);

template <class T>
void printElem(ELEM<T> &v) {
	if ((int)v.size() > 1) {
		std::cout << "(";
	}

	for (int i = 0; i < (int)v.size(); i++) {
		std::cout << v[i] << " ";
		if (i != (int)v.size()-1) std::cout << ", ";
	}

	if ((int)v.size() > 1) {
		std::cout << ") ";
	}
}

template <class T>
void initVec(VEC<T> &v, ELEM<T> &&cons) {
	v.resize(cons.size(), ELEM<T>(1));
	for (int i = 0; i < (int)v.size(); i++) {
		for (int j = 0; j < (int)v[i].size(); j++) {
			v[i][j] = cons[i];
		}
	}
}

template <class T>
void printVec(VEC<T> &v) {
	if ((int)v.size() > 1) std::cout << "[ ";
	for (int i = 0; i < (int)v.size(); i++) {
		printElem(v[i]);
		if (i != (int)v.size()-1) std::cout << ", ";
	}
	if ((int)v.size() > 1) std::cout << "]";
	std::cout << std::endl;
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {
	VEC<T> newVEC;
	newVEC.resize(N, ELEM<T>(1));

	for (int i = 0; i < N; i++) {
		newVEC[i][0] = f(i);
	}
	return newVEC;
}

template<class T>
VEC<T> zip(VEC<T> &v,VEC<T> &w ) {
	int newL = (int)v.size();
	int width = v[0].size();
	int newW = width * 2;

	VEC<T> newVEC;
	newVEC.resize(newL, ELEM<T>(newW));
	for (int i = 0; i < newL; i++) {
		int vIdx = 0;
		int wIdx = 0;
		for (int j = 0; j < newW; j++) {
			if (j < width) {
				newVEC[i][j] = v[i][vIdx++];
			} else {
				newVEC[i][j] = w[i][wIdx++];
			}
		}
	}
	return newVEC;
}

template<class T>
VEC<T> filter(VEC<T> &v, pred_t<T> f) {
	int max = 0;
	for (int i = 0; i < (int)v.size(); i++) {
		for (int j = 0; j < (int)v[i].size(); j++) {
			if (f(v[i][j])) max++;
		}
	}

	VEC<T> newVEC;
	newVEC.resize(max, ELEM<T>(1));

	int curr = 0;
	for (int i = 0; i < (int)v.size(); i++) {
		for (int j = 0; j < (int)v[i].size(); j++) {
			if (f(v[i][j])) {
				newVEC[curr++][0] = v[i][j];
			}
		}
	}
	return newVEC;
}

template<class T>
VEC<T> map(VEC<T> &v, action_t<T> f) {
	VEC<T> newVEC;
	newVEC.resize((int)v.size(), ELEM<T>(1));
	for (int i = 0; i < (int)v.size(); i++) {
		for (int j = 0; j < (int)v[i].size(); j++) {
			newVEC[i][j] = f(v[i][j]);
		}
	}
	return newVEC;
}

template<class T>
ELEM<T> reduce( VEC<T> &v, map_t<T> f, ELEM<T> ident) {
	T sum = ident[0];
	
	for (int i = 0; i < (int)v.size(); i++) {
		for (int j = 0; j < (int)v[i].size(); j++) {
			sum = f(sum, v[i][j]);
		}
	}
	ELEM<T> newELEM;
	newELEM.push_back(sum);
	return newELEM;
}

int f(int i) {
	return i * i;
}

bool g(int i) {
	return i > 0;
}

int h(int i) {
	return i > 0;
}

template<class T>
T k(T x, T y) {
	return x + y;
}



int main(void) {
	VEC<int> v;
	initVec(v, ELEM<int>{1,2,3,4});
	VEC<int> w;
	initVec(w, ELEM<int>{-1,3,-3,4});
	printVec(v);
	std::cout << std::string(10, '*') << std::endl;
	printVec(w);
	std::cout << std::string(10, '*') << std::endl;
	VEC<int> z = zip(v, w);
	printVec(z);
	std::cout << std::string(10, '*') << std::endl;
	VEC<int> x = zip(z, z);
	printVec(x);
	std::cout << std::string(10, '*') << std::endl;
	VEC<int> a = generate(10, f);	// f is func that squares
	printVec(a);
	VEC<int> y = filter(w, g);	// g is a func returns arg > 0
	printVec(y);
	VEC<int> u = map(w, h);		// h is like g but returns 1 or 0
	printVec(u);
	ELEM<int> e = reduce(u, k, ELEM<int>{0});
	printElem(e);

	std::cout << std::endl << std::string(10, '$') << std::endl;
	VEC<std::string> ws;
	initVec(ws, ELEM<std::string>{"hello", "there", "franco", "carlacci"});
	printVec(ws);
	ELEM<std::string> es = reduce(ws, k, ELEM<std::string>{""});
	printElem(es);

	VEC<char> wc;
	initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
	std::cout << std::endl << std::string(10, '$') << std::endl;
	printVec(wc);
	ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
	std::cout << std::endl << std::string(10, '$') << std::endl;
	printElem(ec);

	return 0;
}
