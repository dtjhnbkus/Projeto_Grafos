#include <bits/stdc++.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

using namespace std;

const int INF = INT_MAX;

void floydWarshall(vector<vector<int>> &dist) {
    int n = dist.size();
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    int init = 0, arq_in = 0, arq_out = 0;
    bool set_arq = false, set_init = false, output = false;
    ifstream arquivo;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-f")) {
            set_arq = true;
            arq_in = i + 1;
        }

        if (!strcmp(argv[i], "-i"))
            set_init = true;

        if (!strcmp(argv[i], "-o")) {
            arq_out = i + 1;
            output = true;
        }

        if (!strcmp(argv[i], "-h")) {
            cout << CYAN << "\n\t<---------------- HELP ---------------->" << endl;
            cout << GREEN << "\n-o <arquivo> : redireciona a saída para o arquivo" << endl;
            cout << GREEN << "-f <arquivo> : indica o arquivo que contém a entrada" << endl;
            cout << GREEN << "-s : mostra a solução (em ordem crescente), caso não informado o custo será mostrado!" << endl;
        }
    }

    if (set_arq)
        arquivo.open(argv[arq_in]);

    if (arquivo.fail() == 1) {
        cout << "O arquivo não foi encontrado, digite o nome do arquivo após o -f!\n\nExemplo: ./bin -f arquivo.txt\n\n";
        return 1;
    }

    int n, m;
    arquivo >> n >> m;

    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int v, w, p;

        arquivo >> v >> w >> p;

        dist[v - 1][w - 1] = p;
        dist[w - 1][v - 1] = p;
    }

    arquivo.close();

    floydWarshall(dist);

    if (set_init) {
        int j;
        for (j = 0; j < argc; j++) {
            int i, neg = 0;
            for (i = 0; i < strlen(argv[j]); i++) {
                if (argv[j][i] >= 48 && argv[j][i] <= 57 || argv[j][i] == '-') {
                    if (argv[j][i] == '-') {
                        neg = 1;
                    } else {
                        init = init * 10 + argv[j][i] - '0';
                    }
                } else {
                    init = 0;
                    break;
                }
            }
            if (neg)
                init *= (-1);
            if (i == strlen(argv[j])) {
                init -= 1;
                break;
            }
        }
    }
    if (init >= n || init < 0) {
        cout << "Vertice informado pelo -i não pertence ao grafo!\n";
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (dist[init][i] == INF) {
            cout << i + 1 << ":-1 ";
        } else {
            cout << i + 1 << ":" << dist[init][i] << " ";
        }
    }

    cout << endl;

    if (output) {
        ofstream out_file;
        out_file.open(argv[arq_out]);

        if (out_file.fail() == 1) {
            cout << "Erro ao criar o arquivo, digite o nome do arquivo após -o!\n\nExemplo: ./bin -o arquivo.txt\n\n";
            return 1;
        }
        for (int i = 0; i < n; i++) {
            if (dist[init][i] == INF) {
                out_file << i + 1 << ":-1 ";
            } else {
                out_file << i + 1 << ":" << dist[init][i] << " ";
            }
        }
        out_file << endl;
    }

    return 0;
}
