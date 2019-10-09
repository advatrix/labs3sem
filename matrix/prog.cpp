#include <iostream>
#include "prog.h"

namespace prog {
	int print(const char* msg) {
		if (msg) std::cout << msg << std::endl;
		return 0;
	}

	int menu() {
		print("create matrix");
		print("choose the way of creating");
		print("0: enter only non-zero elements, their count is known");
		print("1: enter only non-zero elements, their count is unknown");
		print("2: enter all elements");
		int ans = 0;
		print("so what is your answer?");
		input(ans);
		return ans;
	}

	int add(SparseMatrix& mx, int i = -1, int j = -1) {
		double v = 0;
		if (i == -1) {
			print("enter i");
			input(i);
			if (!check(i, mx.m)) {
				print("incorrect i");
				return 1;
			}
			print("enter j");
			input(j);
			if (!check(j, mx.n)) {
				print("incorrect j");
				return 2;
			}
			print("enter value");
		}
		input(v);
		if (v) insert(mx, i-1, j-1, v);
		return 0;
	}

	int insert(SparseMatrix& mx, int i, int j, double v) {
		if (!v) return 1;
		if (i < 0 || j < 0) return 2;
		if (i > mx.m - 1 || j > mx.n - 1) return 3;
		if (mx.mx[i].first) {
			mx.mx[i].last->next = new Point;
			mx.mx[i].last = mx.mx[i].last->next;
			mx.mx[i].last->i = i;
			mx.mx[i].last->j = j;
			mx.mx[i].last->v = v;
			mx.mx[i].last->next = nullptr;
		}
		else {
			mx.mx[i].first = new Point;
			mx.mx[i].last = mx.mx[i].first;
			mx.mx[i].first->i = i;
			mx.mx[i].first->j = j;
			mx.mx[i].first->v = v;
			mx.mx[i].first->next = nullptr;
		}
		return 0;
	}
	
	int create(SparseMatrix& mx, int mode) {
		print("enter m");
		input(mx.m);
		try { mx.mx = new Item[mx.m]; }
		catch (std::bad_alloc& ba) {
			print(ba.what());
			delete[] mx.mx;
			return 2;
		}
		for (int i = 0; i < mx.m; i++) {
			mx.mx[i].first = nullptr;
			mx.mx[i].last = nullptr;
		}
		print("enter n");
		input(mx.n);
		if (!mx.n || !mx.m) return 0;
		if (!mode) {
			int nzCount = 0, res = 0;
			print("how many non zero elements?");
			input(nzCount);
			print("add elements row by row from left to right");
			for (int i = 0; i < nzCount; i++) {
				do {
					res = add(mx);
				} while (res);
			}
		}
		else if (mode == 1) {
			int d = 0;
			print("add elements row by row from left to right");
			do {
				add(mx);
				print("continue? 0/1");
				input(d);
			} while (d);
		}
		else if (mode == 2) {
			for (int i = 0; i < mx.m; i++)
				for (int j = 0; j < mx.n; j++) {
					std::cout << "enter elem [" << i << "][" << j << "]" << std::endl;
					add(mx, i, j);
				}
		}
		else {
			print("incorrect mode");
			return 1;
		}
		return 0;
	}

	int print(SparseMatrix mx) {
		Point* tmp;
		for (int i = 0; i < mx.m; i++) {
			tmp = mx.mx[i].first;
			for (int j = 0; j < mx.n; j++) {
				if (tmp && tmp->j == j) {
					std::cout << tmp->v << " ";
					tmp = tmp->next;
				}
				else std::cout << "0 ";
				
			}
			std::cout << std::endl;
		}
		return 0;
	}

	int erase(SparseMatrix& mx) {
		for (int i = 0; i < mx.m; i++) {
			Point* tmp = mx.mx[i].first;
			while (tmp) {
				Point* t = tmp;
				tmp = t->next;
				delete t;
			}
		}
		delete[] mx.mx;
		return 0;
	}

	Vector form(SparseMatrix mx) {
		Vector b = { 0, nullptr };
		if (mx.m < 1 || !mx.mx) return b;
		b.n = mx.m;
		b.a = new double[b.n];
		for (int i = 0; i < b.n; i++) b.a[i] = sum(mx, i);
		return b;
	}

	int erase(Vector& b) {
		delete[] b.a;
		return 0;
	}

	int print(Vector b) {
		for (int i = 0; i < b.n; i++) std::cout << b.a[i] << ' ';
		std::cout << std::endl;
		return 0;
	}

	double sum(SparseMatrix mx, int i) {
		if (mx.m < 1 || mx.n < 1 || !mx.mx) return 0;
		int pr = prev(i, mx.m);
		int s = 0;
		Point* tmp = mx.mx[i].first;
		Point* tmppr = mx.mx[pr].first;
		while (tmp) {
			if (!tmppr) {
				if (tmp->v > 0) s += tmp->v;
				tmp = tmp->next;
			}
			else if (tmp->j == tmppr->j && tmp->v >= tmppr->v) {
				s += tmp->v;
				tmp = tmp->next;
				tmppr = tmppr->next;
			}
			else if (tmp->j < tmppr->j) {
				if (tmp->v > 0) s += tmp->v;
				tmp = tmp->next;
			}
			else if (tmp->j > tmppr->j) {
				while (tmppr && tmppr->j < tmp->j) tmppr = tmppr->next;
			}
			else tmp = tmp->next;
		}
		return s;
	}
}