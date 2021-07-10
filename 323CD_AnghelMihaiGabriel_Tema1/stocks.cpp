#include <bits/stdc++.h>
using namespace std;

struct share {
    int currentValue;
    int minValue;
    int maxValue;
};

class Stocks {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, b, l;
    struct share shares[101];

    void read_input() {
        ifstream fin("stocks.in");
        fin >> n >> b >> l;
        for (int i = 1; i <= n; i++) {
            fin >> shares[i].currentValue
                >> shares[i].minValue
                >> shares[i].maxValue;
        }
        fin.close();
    }

    int get_result() {
        int ***profit_max = new int**[n + 1];
        for (int i = 0; i <= n + 1; i++) {
            profit_max[i] = new int*[b + 1];
            for (int j = 0; j <= b + 1; j++) {
                profit_max[i][j] = new int[l + 1];
            }
        }

        // ma asigur ca tot tabloul are valoare 0
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= b; j++) {
                for (int k = 0; k <= l; k++) {
                    profit_max[i][j][k] = 0;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= b; j++) {
                for (int k = 0; k <= l; k++) {
                    // folosesc rezultatul obtinut la pasii anteriori in cazul
                    // in care nu voi folosi actiunea 'i'
                    profit_max[i][j][k] = profit_max[i - 1][j][k];

                    // verific restrictiile si daca se respecta, calculez
                    // profitul maxim
                    // pentru a avea linii sub 80 de coloane substitui numele
                    // unor variabile
                    int cV = shares[i].currentValue;
                    int minV = shares[i].minValue;
                    int maxV = shares[i].maxValue;
                    int pierdere = cV - minV;
                    int profit = maxV - cV;
                    if ((j - cV >= 0) && (k - pierdere >= 0)) {
                        int sol = profit_max[i-1][j-cV][k-pierdere] + profit;
                        profit_max[i][j][k] = max(profit_max[i][j][k], sol);
                    }
                }
            }
        }

        return profit_max[n][b][l];
    }

    void print_output(int result) {
        ofstream fout("stocks.out");
        fout << result;
        fout.close();
    }
};

int main() {
    // * se aloca un obiect Stocks pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (std::nothrow) Stocks();
    if (!task) {
        std::cerr << "ERROR\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
