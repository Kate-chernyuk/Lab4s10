﻿#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int N, L;
    cout << "Введите число элементов\n";
    cin >> N;
    //   cout << "Введите число цепей\n";
      // cin >> L;

    vector < vector <int> > matrix(N);
    vector <int> to_matrix(N);

    vector<int>::iterator it1, it0, it;
    vector<vector<int>>::iterator it2;

    int i = 1;
    for (it2 = matrix.begin(); it2 != matrix.end(); it2++) {
        cout << "Введите последовательно информацию о числе связей элемента v" << i << " с каждым из " << N << " элементов" << endl; i++;
        int kol_sv;
        for (it1 = to_matrix.begin(); it1 != to_matrix.end(); it1++) {
            cin >> kol_sv;
            (*it1) = kol_sv;
        }
        (*it2) = to_matrix;
    }

    cout << "\nВведённая матрица мультиграфа:\n    ";
    for (int j = 0; j < matrix[0].size(); j++) {
        cout << "v" << j + 1 << "\t";
    }
    cout << "\n";
    for (int i = 0; i < matrix.size(); i++) {
        cout << "v" << i + 1 << ": ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }

    int n, l;
    cout << "\nВведите максимально возможное число элементов, какое может быть на плате\n";
    cin >> n;

    map<int, vector<int>> plats;
    vector<int> to_plat;
    
    map<int, vector<int>>::iterator it3;

    vector <int> free_elems(N);
    iota(free_elems.begin(), free_elems.end(), 1);
    int elem;

    while (!free_elems.empty()) {
        if (to_plat.size() == 0) {
            cout << "Введите номер элемента, который хотите поместить на плату " << plats.size() + 1 << endl;
            cin >> elem;
            it1 = find(free_elems.begin(), free_elems.end(), elem);
            if (it1 != free_elems.end()) {
                to_plat.push_back(elem);
                free_elems.erase(it1);
            }
            else {
                cout << "Такого элемента не существует, либо он уже размещён на некоторой плате\n";
            }
        }
        else {
            if (to_plat.size() < n) {
                //int el=-1, max_el=0, sum_maxel=0;
                vector <int> sums(N,0);
                int sc0;

                for (int i = 0; i < matrix.size(); i++) {
                    it1 = find(free_elems.begin(), free_elems.end(), i + 1);
                    it0 = find(sums.begin(), sums.end(), 0);
                    sc0 = 0;
                    if (it1 != free_elems.end()) {
                        for (int j = 0; j != to_plat.size(); j++) {
                            if (matrix[i][to_plat[j] - 1] != 0) {
                                sc0 += matrix[i][to_plat[j] - 1];
                            }
                        }
                        if (sc0 > 0) {
                            *it0 = sc0;
                        }
                        else {
                            *it0 = -1;
                        }
                    }
                    else {
                        *it0 = -1;
                    }
                }


                it0 = max_element(sums.begin(), sums.end());
                int res = count(sums.begin(), sums.end(), *it0);
                if (res == 1) {
                    elem = distance(sums.begin(), it0) + 1;
                    it1 = find(free_elems.begin(), free_elems.end(), elem);
                    if (it1 != free_elems.end()) {
                        to_plat.push_back(elem);
                        free_elems.erase(it1);
                    }
                }
                else {
                    vector <int> sums_min(N, 0);

                    for (int i = 0; i < N; i++) {
                        it0 = find(sums_min.begin(), sums_min.end(), 0);
                        if (sums[i] > -1) {
                            it1 = find(free_elems.begin(), free_elems.end(), i + 1);
                            sc0 = 0;
                            if (it1 != free_elems.end()) {
                                for (int j = 0; j < N; j++) {
                                    it = find(free_elems.begin(), free_elems.end(), j + 1);
                                    if (it != free_elems.end()) {
                                        sc0 += matrix[i][j];
                                    }
                                }
                                if (sc0 > 0) {
                                    *it0 = sc0;
                                }
                                else {
                                    *it0 = pow(N, N);
                                }
                            }
                            else {
                                *it0 = pow(N, N);
                            }
                        }
                        else {
                            *it0 = pow(N, N);
                        }
                    }

                    it0 = min_element(sums_min.begin(), sums_min.end());
                    elem = distance(sums_min.begin(), it0) + 1;
                    it1 = find(free_elems.begin(), free_elems.end(), elem);
                    if (it1 != free_elems.end()) {
                        to_plat.push_back(elem);
                        free_elems.erase(it1);
                    }
                }
            } 
    
            else {
                plats[plats.size() + 1] = to_plat;
                to_plat.clear();
            }
        }

    }

    plats[plats.size() + 1] = to_plat;

    for (it3 = plats.begin(); it3 != plats.end(); it3++) {
        cout << "Плата" << (it3->first) << ": ";
        for (it1 = it3->second.begin(); it1 != it3->second.end(); it1++) {
            cout << (*it1) << "\t";
        }
        cout << "\n";
    }

}
