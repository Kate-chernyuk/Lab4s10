#include <iostream>
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

    vector<int>::iterator it1, it0, it, itp;
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
    cout << "Введите число контактов разъёма платы\n";
    cin >> l;

    map<int, vector<int>> plats;
    vector<int> to_plat;

    map<int, vector<int>>::iterator it3;

    vector <int> free_elems(N);
    iota(free_elems.begin(), free_elems.end(), 1);
    int elem;

    vector <int> ban;

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
                vector <int> sums(N, 0);
                int sc0;

                for (int i = 0; i < matrix.size(); i++) {
                    it1 = find(free_elems.begin(), free_elems.end(), i + 1);
                    //it0 = find(sums.begin(), sums.end(), 0);
                    sc0 = 0;
                    if (it1 != free_elems.end()) {
                        for (int j = 0; j != to_plat.size(); j++) {
                            sc0 += matrix[i][to_plat[j] - 1];

                        }
                        sums[i] = sc0;
                    }
                    else {
                        sums[i] = -1;
                    }
                }


                vector<int> diff;
                sort(ban.begin(), ban.end());
                set_difference(free_elems.begin(), free_elems.end(), ban.begin(), ban.end(), back_inserter(diff));

                for (int i = 0; i < sums.size(); i++) {
                    it = find(diff.begin(), diff.end(), i + 1);
                    if (it == diff.end()) {
                        sums[i] = -1;
                    }
                }

                it0 = max_element(sums.begin(), sums.end());

                int res = count(sums.begin(), sums.end(), *it0);
                if (res == 1) {
                    it = find(sums.begin(), sums.end(), *it0);
                    elem = distance(sums.begin(), it) + 1;
                    it1 = find(diff.begin(), diff.end(), elem);

                    // cout << elem << " ";

                    if (it1 != diff.end()) {
                        it1 = find(free_elems.begin(), free_elems.end(), elem);
                        int nrm = 0;

                        for (int j = 0; j < N; j++) {
                            it = find(to_plat.begin(), to_plat.end(), j + 1);
                            if (!(it != to_plat.end()) && (j != elem - 1)) {
                                nrm += matrix[elem - 1][j];
                            }
                        }

                        for (int i = 0; i < to_plat.size(); i++) {
                            for (int j = 0; j < N; j++) {
                                if ((elem - 1 != j) && (to_plat[i] - 1 != j)) {
                                    nrm += matrix[to_plat[i] - 1][j];
                                }
                            }
                        }

                        // cout << nrm << endl;

                        if (nrm <= l) {
                            if (it1 != free_elems.end()) {
                                to_plat.push_back(elem);
                                free_elems.erase(it1);
                                ban.clear();
                                diff.clear();
                            }
                        }
                        else {
                            ban.push_back(elem);
                        }

                        if (ban.size() == free_elems.size()) {
                            plats[plats.size() + 1] = to_plat;
                            to_plat.clear();
                            ban.clear();
                            diff.clear();
                        }
                    }
                }
                else {
                    vector <int> sums_min(N, 0);
                    int mx = *it0;

                    for (int i = 0; i < N; i++) {
                        if (sums[i] == mx) {
                            it1 = find(free_elems.begin(), free_elems.end(), i + 1);
                            sc0 = 0;
                            if (it1 != free_elems.end()) {
                                for (int j = 0; j < N; j++) {
                                    it = find(free_elems.begin(), free_elems.end(), j + 1);
                                    if (it != free_elems.end()) {
                                        sc0 += matrix[i][j];
                                    }
                                }
                                if (sc0 >= 0) {
                                    sums_min[i] = sc0;
                                }
                            }
                            else {
                                sums_min[i] = N * N * N;
                            }
                        }
                        else {
                            sums_min[i] = N * N * N;
                        }
                    }


                    it0 = min_element(sums_min.begin(), sums_min.end());
                    elem = distance(sums_min.begin(), it0) + 1;
                    it1 = find(diff.begin(), diff.end(), elem);


                    if (it1 != diff.end()) {
                        it1 = find(free_elems.begin(), free_elems.end(), elem);
                        int nrm = 0;

                        for (int j = 0; j < N; j++) {
                            it = find(to_plat.begin(), to_plat.end(), j + 1);
                            if (!(it != to_plat.end()) && (j != elem - 1)) {
                                nrm += matrix[elem - 1][j];
                            }
                        }

                        for (int i = 0; i < to_plat.size(); i++) {
                            for (int j = 0; j < N; j++) {
                                if ((elem - 1 != j) && (to_plat[i] - 1 != j)) {
                                    nrm += matrix[to_plat[i] - 1][j];
                                }
                            }
                        }

                        if (nrm <= l) {
                            if (it1 != free_elems.end()) {
                                to_plat.push_back(elem);
                                free_elems.erase(it1);
                                ban.clear();
                                diff.clear();
                            }
                        }
                        else {
                            ban.push_back(elem);
                        }

                        if (ban.size() == free_elems.size()) {
                            plats[plats.size() + 1] = to_plat;
                            to_plat.clear();
                            ban.clear();
                            diff.clear();
                        }
                    }
                }
            }

            else {
                plats[plats.size() + 1] = to_plat;
                to_plat.clear();
                ban.clear();
            }
        }

    }

    if (to_plat.size() > 0) {
        plats[plats.size() + 1] = to_plat;
    }

    for (it3 = plats.begin(); it3 != plats.end(); it3++) {
        cout << "Плата" << (it3->first) << ": ";
        for (it1 = it3->second.begin(); it1 != it3->second.end(); it1++) {
            cout << (*it1) << "\t";
        }
        cout << "\n";
    }

    if (plats.size() == 2) {
        //vector <int> first_plat;
        vector <int> first_plat{1, 2, 3, 4, 5};
        /*it3 = plats.begin();
        for (it1 = it3->second.begin(); it1 != it3->second.end(); it1++) {
            first_plat.push_back(*it1);
        }*/
        //vector <int> second_plat;
        vector <int> second_plat{6, 7, 8, 9, 10};
        /*it3++;
        for (it1 = it3->second.begin(); it1 != it3->second.end(); it1++) {
            second_plat.push_back(*it1);
        }*/

        int p_max = 1;

        cout << "Количество связей между платами до перестановок ";
        int kol_sv = 0;
        for (int i = 0; i < first_plat.size(); i++) {
            for (int j = 0; j < second_plat.size(); j++) {
                kol_sv += matrix[first_plat[i] - 1][second_plat[j] - 1];
            }
        }
        cout << "равняется " << kol_sv;

        while (p_max > 0) {
            vector <int> first_coefOfExtCom(first_plat.size()), second_coefOfExtCom(second_plat.size());


            int sc1;
            for (int i = 0; i < first_plat.size(); i++) {
                sc1 = 0;
                for (int j = 0; j < N; j++) {
                    it0 = find(second_plat.begin(), second_plat.end(), j + 1);
                    if (it0 != second_plat.end()) {
                        sc1 += matrix[first_plat[i] - 1][j];
                    }
                    else {
                        sc1 -= matrix[first_plat[i] - 1][j];
                    }
                    //cout << sc1 << " ";
                }
                first_coefOfExtCom[i] = sc1;
            }

            for (int i = 0; i < second_plat.size(); i++) {
                sc1 = 0;
                for (int j = 0; j < N; j++) {
                    it0 = find(first_plat.begin(), first_plat.end(), j + 1);
                    if (it0 != first_plat.end()) {
                        sc1 += matrix[second_plat[i] - 1][j];
                    }
                    else {
                        sc1 -= matrix[second_plat[i] - 1][j];
                    }
                    //cout << sc1 << " ";
                }
                second_coefOfExtCom[i] = sc1;
            }

            cout << "Коэффициенты внешней связи:\n";
            for (int i = 0; i < first_coefOfExtCom.size(); i++) {
                cout << first_coefOfExtCom[i] << " ";
            }
            for (int i = 0; i < second_coefOfExtCom.size(); i++) {
                cout << second_coefOfExtCom[i] << " ";
            }
            cout << "\n";

            vector <vector <int>> p;
            vector <int> to_p;

            int perst;
            for (int i = 0; i < first_plat.size(); i++) {
                for (int j = 0; j < second_plat.size(); j++) {
                    perst = first_coefOfExtCom[i] + second_coefOfExtCom[j] - 2 * matrix[first_plat[i] - 1][second_plat[j] - 1];
                    to_p.push_back(perst);
                }
                p.push_back(to_p);
                to_p.clear();
            }

            int i_max=0, j_max=0;
            p_max = p[0][0];
            cout << "Матрица перестановок:\n";
            for (int i = 0; i < p.size(); i++) {
                for (int j = 0; j < p[i].size(); j++) {
                    cout << p[i][j] << " ";
                    if (p[i][j] > p_max) {
                        p_max = p[i][j];
                        i_max = i;
                        j_max = j;
                    }
                }
                cout << "\n";
            }
            
            if (p_max <= 0) {
                cout << "Дальнейшие перестановки не уменьшат число связей между матрицами\n";
                break;
            }

            int el_one = first_plat[i_max], el_two = second_plat[j_max];
            cout << "Максимальное значение: " << p_max << "; т.е. при перестановке " << el_one << " и " << el_two << " вершин количество связей между платами уменьшится на " << p_max;
            first_plat[i_max] = el_two; second_plat[j_max] = el_one;
            cout << "\nПлата1: ";
            for (it = first_plat.begin(); it != first_plat.end(); it++) {
                cout << *it << " ";
            }
            cout << "\nПлата2: ";
            for (it = second_plat.begin(); it != second_plat.end(); it++) {
                cout << *it << " ";
            }
            cout << "\n";
        }
        cout << "Количество связей между платами ныне минимально возможное; ";
        kol_sv = 0;
        for (int i = 0; i < first_plat.size(); i++) {
            for (int j = 0; j < second_plat.size(); j++) {
                kol_sv += matrix[first_plat[i] - 1][second_plat[j] - 1];
            }
        }
        cout << "равняется " << kol_sv;
    }
}



