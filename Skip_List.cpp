
#include <cstdlib>
#include <ctime>
#define  max_level  3
#define chance 0.5 // chance de chave subir para o próx level = 1/2


// Estrutura do nó da Skip List
struct Node {
    int key;
    string title;
    Node* forward[max_level + 1]; // Array de ponteiros para os próximos nós

    // Construtor do nó para inicializar os ponteiros como nulos
    Node() {
        for (int i = 0; i <= max_level; ++i) {
            forward[i] = nullptr;
        }
    }
};

// Classe da Skip List
class SkipList {
public:
    Node* head;
    int current_level; // O nível mais alto atualmente na lista

    SkipList() {
        // O nó 'head' atua como um sentinela com chave mínima
        head = new Node();
        head->key = -1; // Ou qualquer valor que seja menor que todas as chaves possíveis
        head->title = "HEAD";
        current_level = 0; // A lista começa no nível 0
        // Semeia o gerador de números aleatórios
        srand(time(nullptr));
    }

    // Gera um nível aleatório para o novo nó
    int Random_Level() {
        int level = 0;
        // Continua incrementando o nível com base na 'chance' definida
        while ((static_cast<double>(rand()) / RAND_MAX) < chance && level < max_level) {
            level++;
        }
        return level;
    }


    void Insert(int new_key, string new_title) {
        Node* x = this->head;
        Node* update[max_level + 1]; // Array para guardar os predecessores do novo nó

        // # Encontra a posição correta do nó
        // Começa do nível mais alto da lista e desce até o nível 0
        for (int i = current_level; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < new_key) {
                x = x->forward[i];
            }
            update[i] = x; // Guarda o ponteiro para o nó predecessor no nível i
        }

        // # Aqui, x->forward[0] aponta para o local da inserção
        x = x->forward[0];

        // # Se a chave new_key já existe, atualiza seu valor (título)
        if (x != nullptr && x->key == new_key) {
            x->title = new_title;
        } else {
            // # se a chave não existe, insere
            int level = Random_Level(); // # sorteia número aleatório

            // # se o nível sorteado é maior que o atual da lista
            if (level > current_level) {
                // Atualiza o array 'update' para os novos níveis.
                // O predecessor para esses níveis será o 'head'.
                for (int i = current_level + 1; i <= level; i++) {
                    update[i] = this->head;
                }
                // Atualiza o nível da lista
                current_level = level;
            }

            // # Cria o novo nó
            Node* new_node = new Node();
            new_node->key = new_key;
            new_node->title = new_title;

            // # Insere o novo nó na lista, religando os ponteiros
            for (int i = 0; i <= level; i++) {
                // O 'forward' do novo nó aponta para onde o predecessor apontava
                new_node->forward[i] = update[i]->forward[i];
                // O 'forward' do predecessor agora aponta para o novo nó
                update[i]->forward[i] = new_node;
            }
        }
    }

    void Delete(int searchKey) {
        Node* update[max_level + 1];
        Node* x = head;

        // Encontra os nós predecessores do nó a ser removido em cada nível
        for (int i = current_level; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < searchKey) {
                x = x->forward[i];
            }
            update[i] = x;
        }

        // Aqui, x->forward[0] aponta para o nó a ser removido
        // Avança para o nó que pode ser o alvo da remoção
        x = x->forward[0];

        // Se o nó foi encontrado (chave corresponde), procede com a remoção
        if (x != nullptr && x->key == searchKey) {

            // Atualiza os ponteiros dos predecessores para pular o nó x
            for (int i = 0; i <= current_level; i++) {
                // Se o predecessor no nível i não aponta para x,
                // significa que x não existe nos níveis superiores, então para.
                if (update[i]->forward[i] != x) {
                    break;
                }
                // O predecessor agora aponta para o nó que x apontava
                update[i]->forward[i] = x->forward[i];
            }

            // # desaloca o nó x
            delete x;

            //  todo nível que estiver vazio, desconsidera
            // Atualiza o nível da lista, caso os níveis superiores tenham ficado vazios
            while (current_level > 0 && head->forward[current_level] == nullptr) {
                current_level--;
            }
        }
        // Se a chave não for encontrada, a função termina sem fazer nada.
    }

    Node* Search(int key) {
        cout << "\n===== Buscando pela chave: " << key << " =====" << endl;
        Node* x = head;

        // Começa a busca do nível mais alto
        for (int i = current_level; i >= 0; i--) {
            // Imprime o nó de partida da busca no nível atual
            cout << "Level " << i << ": ";
            if(x->key == -1) cout << "HEAD"; else cout << x->key;

            // Avança na lista enquanto a chave do próximo nó for menor que a chave buscada
            while (x->forward[i] != nullptr && x->forward[i]->key < key) {
                x = x->forward[i];
                cout << " -> " << x->key;
            }
            cout << endl; // Nova linha para separar a busca de cada nível
        }

        // # Aqui, estamos apontando para o antecessor da chave buscada
        // Avança para o nó que potencialmente contém a chave
        x = x->forward[0];

        cout << "--------------------------------------" << endl;

        // Verifica se o nó candidato realmente contém a chave buscada
        if (x != nullptr && x->key == key) {
            cout << "Resultado: Chave " << key << " ENCONTRADA!" << endl;
            cout << "  -> Dados: (" << x->key << ", \"" << x->title << "\")" << endl;
            return x;
        } else {
            cout << "Resultado: Chave " << key << " NAO ENCONTRADA." << endl;
            return nullptr;
        }
    }
    // Função para imprimir a lista (para verificação)
    void PrintList() {
        cout << "\n*****SKIP LIST*****" << endl;
        for (int i = current_level; i >= 0; i--) {
            Node* node = head->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->key << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }
};
