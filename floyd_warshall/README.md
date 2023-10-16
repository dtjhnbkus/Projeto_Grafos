# Algoritimo Floyd Warshall

O Algoritmo Floyd Warshall tem a função de ser um algoritmo de busca de caminho mínimo dentre todos os vertices em um grafo.

## Compilação e execução

* Sistema Operacional: Ubuntu;
* Para compilar é necessário está no diretório ```floyd_Warshall``` e digitar ```ubuntu```;
* As entradas testadas estão no diretório ```floyd_Warshall/inputs/```;

## Entrada do algoritmo

```ubuntu
n m
v1 v2 p
. . .
. . .
. . .
vn vn pn
```

* n é o número de vertices;
* m é o número de arestas;
* O par de v's (v1 v2) são as arestas;
* p é o peso das arestas;
* Importante: para grafos não direcionados é preciso informar o arco de ida e volta!

## Saída do algoritmo

* O formato será em ``vértice``:``valor até chegar nele`` partindo do vértice informado pelo comando -i;
* Caso não seja informado o vértice pelo comando -i, o mesmo vai imprimir o caminho de todos os vertices no formato indicado acima.

## Exemplo de execução

No diretorio principal do projeto digite:

```ubuntu
./floyd_warshall.bin -f inputs/input-0.mtx -i 1
```

Saída no terminal:
```ubuntu
1:0 2:3 3:4 4:2 5:10 6:3 
```

Para salvar em um arquivo:

```ubuntu
./floyd_warshall.bin -f inputs/input-0.mtx -o saida.txt -i 1

```
