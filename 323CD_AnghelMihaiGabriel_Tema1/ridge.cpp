#include <bits/stdc++.h>
using namespace std;

class Ridge {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    unsigned long long int h[1000001];
    unsigned long long int c[1000001];

    void read_input() {
        ifstream fin("ridge.in");
        fin >> n;
        for (int i = 0; i < n; i++) {
            fin >> h[i] >> c[i];
        }
        fin.close();
    }

    unsigned long long int get_result() {
        unsigned long long int result = ULLONG_MAX;
        unsigned long long int **cost_min = new unsigned long long int *[n + 1];
        for (int i = 0; i <= n + 1; i++) {
            cost_min[i] = new unsigned long long int[3];
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
               cost_min[i][j] = 0;
            }
        }

        // muntele ramane nesapat
        cost_min[0][0] = 0;

        // muntele este sapat cu o unitate
        cost_min[0][1] = c[0];

        // muntele este sapat cu 2 unitat
        cost_min[0][2] = 2 * c[0];

        for (int i = 1; i < n; i++) {
            // se fac permutarile posibilitatilor de a obtine costul minim
            // pentru a sapa in muntii adiacenti
            for (int j = 0; j < 3; j++) {
                unsigned long long int minim = ULLONG_MAX;
                // pentru fiecare sapatura trebuie sa ma asigur ca nivelul nu
                // scade sub 0
                // identarea if-urilor este asa pentru a nu depasi lungimea
                // maxima pe coloana
                if ((h[i] - j != h[i - 1])
                    && (h[i] - j >= 0)) {
                    minim = min(minim, cost_min[i - 1][0]);
                }

                if ((h[i] - j != h[i - 1] - 1)
                    && (h[i - 1] - 1 >= 0)
                    && (h[i] - j >= 0)) {
                    minim = min(minim, cost_min[i - 1][1]);
                }

                if ((h[i] - j != h[i - 1] - 2)
                    && (h[i - 1] - 2 >= 0)
                    && (h[i] - j >= 0)) {
                    minim = min(minim, cost_min[i - 1][2]);
                }

                // fac update la costul minim partial
                cost_min[i][j] = j * c[i] + minim;

                // in final extrag costul minim total
                if (i == n - 1) {
                    result = min(result, cost_min[i][j]);
                }
            }
        }

        return result;
    }

    void print_output(unsigned long long int result) {
        ofstream fout("ridge.out");
        fout << result;
        fout.close();
    }
};

int main() {
    // * se aloca un obiect Ridge pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (std::nothrow) Ridge();
    if (!task) {
        std::cerr << "ERROR!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
