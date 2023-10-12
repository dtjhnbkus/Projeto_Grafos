#include <bits/stdc++.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

using namespace std;

struct Aresta {
    int vertice1;
    int vertice2;
    int peso;
};
int encontrar(int u, vector<int> &pai) {
    return (pai[u] != u) ? encontrar(pai[u], pai) : pai[u];
}
void unirArvore(int u, int v, vector<int> &pai, vector<int> &rank) {
    int origem = encontrar(u, pai);
    int destino = encontrar(v, pai);

    if (rank[origem] >= rank[destino])
    {
        pai[destino] = origem;

        if (rank[origem] == rank[destino])
        {
            rank[origem]++;
        }
    }
    else
    {
        pai[origem] = destino;
    }
}
void criarConjunto(int u, vector<int> &pai, vector<int> &rank) {
    pai[u] = u;
    rank[u] = 0;
}
static bool compararPeso(const Aresta &a1, const Aresta &a2) {
    return a1.peso < a2.peso;
}
static bool compararAGM(const Aresta &a1, const Aresta &a2) {
    return (a1.vertice1 == a2.vertice1) ? a1.vertice2 < a2.vertice2 : a1.vertice1 < a2.vertice1;
}

vector<Aresta> kruskal(vector<vector<pair<int, int>>> &grafo, int n, int m, int &soma) {
    vector<Aresta> arestas;
    for (int i = 0; i < n; i++) {
        for (auto aresta : grafo[i]) {
            if (aresta.first < i)
                continue;
            Aresta a;
            a.vertice1 = i;
            a.vertice2 = aresta.first;
            a.peso = aresta.second;
            arestas.push_back(a);
        }
    }

    sort(arestas.begin(), arestas.end(), compararPeso);

    vector<int> pai(n);
    vector<int> rank(n, 0);
    vector<Aresta> agm;

    for (int i = 0; i < n; i++) {
        criarConjunto(i, pai, rank);
    }
    for (int i = 0; i < m; i++) {
        int origem = arestas[i].vertice1;
        int destino = arestas[i].vertice2;
        if (encontrar(origem, pai) != encontrar(destino, pai)) {
            unirArvore(origem, destino, pai, rank);
            agm.push_back(arestas[i]);
        }
    }
    for (auto aresta : agm)
        soma += aresta.peso;

    return agm;
}
int main(int argc, char **argv) {
    int arquivoEntrada = 0, arquivoSaida = 0;
    bool ordenarAGM = false, definirArquivo = false, output = false;
    ifstream arquivo;

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-f")) {
            definirArquivo = true;
            arquivoEntrada = i + 1;
        }
        if (!strcmp(argv[i], "-s"))
            ordenarAGM = true;
        if (!strcmp(argv[i], "-o")) {
            arquivoSaida = i + 1;
            output = true;
        }
        if (!strcmp(argv[i], "-h")) {
            cout << CYAN << "\n\t<---------------- HELP ---------------->" << endl;
            cout << GREEN << "\n-o <arquivo> : redireciona a saída para o arquivo" << endl;
            cout << GREEN << "-f <arquivo> : indica o arquivo que contém a entrada" << endl;
            cout << GREEN << "-s : mostra a solução (em ordem crescente), caso não informado o custo será mostrado!" << endl;
        }
    }
    if (definirArquivo)
        arquivo.open(argv[arquivoEntrada]);

    if (arquivo.fail() == 1) {
        cout << "O arquivo não foi encontrado, digite o nome do arquivo após o -f!\n\nExemplo: ./bin -f arquivo.txt\n\n";
        return 1;
    }
    int n, m;
    arquivo >> n >> m;

    vector<vector<pair<int, int>>> grafo(n);

    for (int i = 0; i < m; i++) {
        int vertice1, vertice2, p;

        arquivo >> vertice1 >> vertice2 >> p;

        grafo[vertice1 - 1].push_back({vertice2 - 1, p});
        grafo[vertice2 - 1].push_back({vertice1 - 1, p});
    }
    arquivo.close();
    int soma = 0;
    vector<Aresta> agm = kruskal(grafo, n, m, soma);
    if (ordenarAGM) {
        sort(agm.begin(), agm.end(), compararAGM);

        for (auto aresta : agm)
            cout << "(" << aresta.vertice1 + 1 << "," << aresta.vertice2 + 1 << ") ";    

        cout << endl;
    }
    else {
        cout << soma << endl;
    }
    if (output) {
        ofstream out_file;
        out_file.open(argv[arquivoSaida]);

        if (out_file.fail() == 1) {
            cout << "Erro ao criar o arquivo, digite o nome do arquivo após -o!\n\nExemplo: ./bin -o arquivo.txt\n\n";
            return 1;
        }
        out_file << "AGM: ";
        for (auto aresta : agm)
            out_file << "(" << aresta.vertice1 + 1 << "," << aresta.vertice2 + 1 << ") "; 
        out_file << endl << "Custo: " << soma << endl;
    }
    return 0;
}
