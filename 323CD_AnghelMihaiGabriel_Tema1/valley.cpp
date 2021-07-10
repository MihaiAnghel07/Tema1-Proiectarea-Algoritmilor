#include <bits/stdc++.h>
using namespace std;


class Valley {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    unsigned int h[1000001];

    void read_input() {
        ifstream fin("valley.in");
        fin >> n;
        for (int i = 0; i < n; i++) {
            fin >> h[i];
        }
        fin.close();
    }

    unsigned long long int get_result() {
        unsigned long long int result = 0;
        // am calculat separat cazul in care n = 3
        if (n == 3) {
            if (h[0] == h[1] && h[0]== h[2]) {
                return 0;
            }

            if (h[2] == 1) {
                return 0;
            }

            if (h[0] > h[2] && h[1] > h[2]) {
                result = h[1] - h[2];

            } else {
                while (h[0] <= h[2] && h[1] > h[0]) {
                    result = h[1] - h[0];
                }
            }

            return result;
        }

        // de asemenea, am luat separat cazul in care array-ul este in
        // intregime crescator sau descrescator
        int cresc = 1, desc = 1;
        for (int i = 0; i < n - 1; i++) {
            if (h[i] > h[i + 1]) {
                cresc = 0;
            }
            if (h[i] < h[i + 1]) {
                desc = 0;
            }
        }

        if (cresc == 1) {
            return h[1] - h[0];
        }

        if (desc == 1) {
            if (h[n - 2] > h[n - 1])
                return h[n - 2] - h[n - 1];
        }

        int i = 0, j = n - 1;
        unsigned long long int referinta = h[i++];
        unsigned long long int referinta2 = h[j--];
        while (i <= j) {
            // in functie de nivelul referintelor, se face parcurgerea si
            // saparea in munte de la un capat sau altul
            if (referinta > referinta2) {
                while ((i <= j) && (h[i] <= referinta
                    || referinta > referinta2)) {
                    if (h[i] > referinta) {
                        result += h[i] - referinta;
                        h[i++] = referinta;
                    } else {
                        referinta = h[i++];
                    }
                }

            } else {
                while ((i <= j) && (h[j] <= referinta2
                    || referinta2 >= referinta)) {
                    if (h[j] > referinta2) {
                        result += h[j] - referinta2;
                        h[j--] = referinta2;
                    } else {
                        referinta2 = h[j--];
                    }
                }
            }
        }

        return result;
    }

    void print_output(unsigned long long int result) {
        ofstream fout("valley.out");
        fout << result;
        fout.close();
    }
};

int main() {
    // * se aloca un obiect Valley pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (std::nothrow) Valley();
    if (!task) {
        std::cerr << "ERROR!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
