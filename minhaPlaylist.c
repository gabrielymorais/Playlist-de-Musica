#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar cada música
typedef struct Musica {
    char titulo[100];
    char artista[100];
    int duracao;  // duração em segundos
    struct Musica* prev;
    struct Musica* next;
} Musica;

// Estrutura para a playlist
typedef struct {
    Musica* inicio;
    Musica* fim;
    Musica* atual;
    int totalMusicas;
    int duracaoTotal;
} Playlist;

// Função para inicializar a playlist
void inicializarPlaylist(Playlist* playlist) {
    playlist->inicio = NULL;
    playlist->fim = NULL;
    playlist->atual = NULL;
    playlist->totalMusicas = 0;
    playlist->duracaoTotal = 0;
}

// Função para adicionar música no fim da playlist
void adicionarMusica(Playlist* playlist) {
    Musica* nova = (Musica*)malloc(sizeof(Musica));

    // Solicita os dados da música ao usuário
    printf("Digite o título da música: ");
    scanf(" %[^\n]", nova->titulo);
    printf("Digite o nome do artista: ");
    scanf(" %[^\n]", nova->artista);
    printf("Digite a duração da música (em segundos): ");
    scanf("%d", &nova->duracao);

    nova->next = NULL;
    nova->prev = NULL;

    // Insere a música no fim da playlist
    if (playlist->inicio == NULL) {
        playlist->inicio = nova;
        playlist->fim = nova;
        playlist->atual = nova;
    } else {
        playlist->fim->next = nova;
        nova->prev = playlist->fim;
        playlist->fim = nova;
    }

    playlist->totalMusicas++;
    playlist->duracaoTotal += nova->duracao;
    printf("\n");
    printf("| MÚSICA ADICIONADA COM SUCESSO |\n");
}

// Função para remover música pelo título
void removerMusica(Playlist* playlist, char* titulo) {
    Musica* temp = playlist->inicio;

    while (temp != NULL) {
        if (strcmp(temp->titulo, titulo) == 0) {
            // Caso seja o único nó
            if (temp->prev == NULL && temp->next == NULL) {
                playlist->inicio = NULL;
                playlist->fim = NULL;
            }
            // Caso seja o primeiro nó
            else if (temp->prev == NULL) {
                playlist->inicio = temp->next;
                playlist->inicio->prev = NULL;
            }
            // Caso seja o último nó
            else if (temp->next == NULL) {
                playlist->fim = temp->prev;
                playlist->fim->next = NULL;
            }
            // Caso esteja no meio
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            free(temp);
            playlist->totalMusicas--;
            printf("\n");
            printf("| MÚSICA REMOVIDA COM SUCESSO |\n");
            return;
        }
        temp = temp->next;
    }

    printf("| MÚSICA NAO ENCONTRADA |\n");
}

// Função para mostrar a playlist completa
void mostrarPlaylist(Playlist* playlist) {
    Musica* temp = playlist->inicio;

    if (temp == NULL) {
        printf("| A PLAYLIST ESTÁ VAZIA |\n");
        return;
    }

    printf("Playlist completa:\n");
    while (temp != NULL) {
        printf("\n");
        printf("Título: %s | Artista: %s | Duração: %d segundos\n", temp->titulo, temp->artista, temp->duracao);
        printf("\n");

        temp = temp->next;
    }

    printf("\n");
    printf("Total de músicas: %d\n", playlist->totalMusicas);
    printf("Duração total: %d segundos\n", playlist->duracaoTotal);
    printf("\n");

}

// Função para avançar para a próxima música
void proximaMusica(Playlist* playlist) {
    if (playlist->atual != NULL && playlist->atual->next != NULL) {
        playlist->atual = playlist->atual->next;
        printf("\n");
        printf("Tocando agora: %s - %s\n", playlist->atual->titulo, playlist->atual->artista);
        printf("\n");

    } else {
        printf("\n");
        printf("| NAO HA PROXIMA MUSICA |\n");
    }
}

// Função para voltar para a música anterior
void musicaAnterior(Playlist* playlist) {
    if (playlist->atual != NULL && playlist->atual->prev != NULL) {
        playlist->atual = playlist->atual->prev;
        printf("Tocando agora: %s - %s\n", playlist->atual->titulo, playlist->atual->artista);
    } else {
        printf("\n");
        printf("| NAO HA MUSICA ANTERIOR |\n");
    }
}

// Função principal com o menu de opções
int main() {
    Playlist minhaPlaylist;
    inicializarPlaylist(&minhaPlaylist);
    
    int opcao;
    char titulo[100];

    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar Música\n");
        printf("2. Remover Música\n");
        printf("3. Mostrar Playlist\n");
        printf("4. Avançar para a próxima música\n");
        printf("5. Voltar para a música anterior\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
     

        switch(opcao) {
            case 1:
                adicionarMusica(&minhaPlaylist);
                break;
            case 2:
                printf("Digite o título da música a ser removida: ");
                scanf(" %[^\n]", titulo);
                removerMusica(&minhaPlaylist, titulo);
                break;
            case 3:
                mostrarPlaylist(&minhaPlaylist);
                break;
            case 4:
                proximaMusica(&minhaPlaylist);
                break;
            case 5:
                musicaAnterior(&minhaPlaylist);
                break;
            case 0:
                printf("Saindo --> \n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
