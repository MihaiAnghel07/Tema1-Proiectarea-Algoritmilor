#include <bits/stdc++.h>
using namespace std;

struct my_pair {
    unsigned int p;
    unsigned int u;
};

class Crypto {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, B;
    struct my_pair update[1000001];

    void read_input() {
        ifstream fin("crypto.in");
        fin >> n >> B;
        for (int i = 0; i < n; i++) {
            fin >> update[i].p >> update[i].u;
        }
        fin.close();
    }

    static bool my_cmp(struct my_pair A, struct my_pair B) {
    	return (A.p < B.p);
    }

    int get_result() {
    	// sortez perechile in functie de capacitatea de productie
    	sort(update, update + n, my_cmp);

        int s = update[0].u, result = update[0].p, dif;
        for (int i = 1; i < n && B > 0; i++) {
            if (update[i].p == update[i - 1].p) {
            	// creez o singura entitate avand capacitatea egala cu
            	// suma capacitatilor tuturor calculatoarelor cu aceeasi
            	// capacitate de productie
                s += update[i].u;
            } else {
            	// fac update la entitatea creata anterior
                dif = update[i].p - update[i - 1].p;
                while (dif != 0 && B > 0) {
                	dif--;
                	B -= s;
                	result++;
                }

                if (B == 0) {
                	return result;
                }

                if (B < 0) {
                	return result - 1;
                }

                s += update[i].u;
            }
        }

        // daca mai sunt bani, se face update pana se cheltuiesc toti
        while (B > 0) {
        	B -= s;
        	result++;
        }

        if (B == 0) {
            return result;
        }

        if (B < 0) {
          	return result - 1;
        }

        return result;
    }

    void print_output(int result) {
        ofstream fout("crypto.out");
        fout << result;
        fout.close();
    }
};

int main() {
    // * se aloca un obiect Crypto pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (std::nothrow) Crypto();
    if (!task) {
        std::cerr << "ERROR\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
