#include <iostream>

# include <string>
using namespace std;
# include "Skip_List.cpp"
void preencheSkipList(SkipList &list) {
    list.Insert(101, "Algoritmos e Estruturas de Dados");
    list.Insert(29, "Inteligência Artificial");
    list.Insert(203, "Machine Learning Avançado");
    list.Insert(88, "Programação em Python");
    list.Insert(175, "Redes Neurais e Deep Learning");
    list.Insert(256, "Sistemas Distribuídos");
    list.Insert(191, "Visão Computacional");
    list.Insert(317, "Lógica Matemática");
    list.Insert(125, "Banco de Dados");
    list.Insert(297, "Sistemas Operacionais");
    list.Insert(410, "Redes de Computadores");
    list.Insert(281, "Compiladores");
    list.Insert(373, "Matemática Discreta");
    list.Insert(182, "Processamento Digital de Imagens");
    list.Insert(299, "Projeto e Análise de Algoritmos");
    list.Insert(437, "Engenharia de Software");
}

int main() {
    srand(time(0));

    SkipList L;
    preencheSkipList(L);
    L.PrintList();

    L.Insert(408, "Processamento de Linguagem Neural");
    L.Delete(203);

    cout << "Após inserção e remoção:" << endl;
    L.PrintList();

    L.Search(373);
    L.Search(400);


    return 0;
}
