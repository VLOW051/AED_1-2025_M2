#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// layout da memória

#define TAM_NOME 50
#define TAM_EMAIL 50
#define MAX_PESSOAS 10

#define TAM_INT sizeof(int)
#define TAM_CHAR sizeof(char)

#define TAM_REGISTRO ( (TAM_NOME * TAM_CHAR) + TAM_INT + (TAM_EMAIL * TAM_CHAR) )

#define OFFSET_PCOUNT (TAM_INT)
#define OFFSET_PI     (2 * TAM_INT)
#define OFFSET_PJ     (3 * TAM_INT)
#define OFFSET_PFOUND (4 * TAM_INT)
#define OFFSET_PSEARCH (5 * TAM_INT)

#define OFFSET_AGENDA ( (5 * TAM_INT) + (TAM_NOME * TAM_CHAR) )

// tamanho buffer completo

#define TAMANHO_BUFFER ( OFFSET_AGENDA + (MAX_PESSOAS * TAM_REGISTRO) )

//Retorna o ponteiro para o NOME da pessoa no índice *pIndex
 
char* getNome(void* pAgendaBase, int* pIndex) {
    return (char*)(pAgendaBase + (*pIndex * TAM_REGISTRO));
}

// Retorna o ponteiro para a IDADE da pessoa no índice *pIndex
 
int* getIdade(void* pAgendaBase, int* pIndex) {
    return (int*)(pAgendaBase + (*pIndex * TAM_REGISTRO) + (TAM_NOME * TAM_CHAR));
}

 // Retorna o ponteiro para o EMAIL da pessoa no índice *pIndex
  
char* getEmail(void* pAgendaBase, int* pIndex) {
    return (char*)(pAgendaBase + (*pIndex * TAM_REGISTRO) + (TAM_NOME * TAM_CHAR) + TAM_INT);
}


void limparBufferEntrada(int* pScratch) {
    while ((*pScratch = getchar()) != '\n' && *pScratch != EOF);
}


void removerNewline(char* pString) {
    pString[strcspn(pString, "\n")] = '\0';
}

int main() {
    
    void* pBuffer = NULL;

    int* pChoice;
    int* pCount;
    int* pI;
    int* pJ;
    int* pFound;
    char* pSearch;
    void* pAgenda;

    pBuffer = malloc(TAMANHO_BUFFER);
    if (pBuffer == NULL) {
        printf("Erro fatal: Falha ao alocar buffer de memoria.\n");
        exit(1);
    }

    pChoice = (int*)(pBuffer);
    pCount  = (int*)(pBuffer + OFFSET_PCOUNT);
    pI      = (int*)(pBuffer + OFFSET_PI);
    pJ      = (int*)(pBuffer + OFFSET_PJ);
    pFound  = (int*)(pBuffer + OFFSET_PFOUND);
    pSearch = (char*)(pBuffer + OFFSET_PSEARCH);
    pAgenda = (void*)(pBuffer + OFFSET_AGENDA);

    *pCount = 0;
    *pChoice = 0;

    do {
        printf("\n--- Agenda ---\n");
        printf("Pessoas cadastradas: %d / %d\n", *pCount, MAX_PESSOAS);
        printf("-------------------------------------\n");
        printf("1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4. Listar todos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", pChoice);
        limparBufferEntrada(pI); 

        switch (*pChoice) {
            
            case 1: {
                if (*pCount >= MAX_PESSOAS) {
                    printf("Agenda cheia! Nao e possivel adicionar.\n");
                } else {
                    *pI = *pCount; 
                    
                    printf("--- Adicionando Pessoa (ID: %d) ---\n", *pI);

                    char* pNewNome = getNome(pAgenda, pI);
                    int* pNewIdade = getIdade(pAgenda, pI);
                    char* pNewEmail = getEmail(pAgenda, pI);

                    printf("Nome: ");
                    fgets(pNewNome, TAM_NOME, stdin);
                    
                    printf("Email: ");
                    fgets(pNewEmail, TAM_EMAIL, stdin);

                    printf("Idade: ");
                    scanf("%d", pNewIdade);
                    limparBufferEntrada(pI); 

                    removerNewline(pNewNome);
                    removerNewline(pNewEmail);

                    (*pCount)++; 
                    printf("Pessoa adicionada com sucesso!\n");
                }
                break;
            }

            case 2: {
                if (*pCount == 0) {
                    printf("Agenda vazia. Nada para remover.\n");
                    break;
                }

                printf("--- Remover Pessoa ---\n");
                printf("Digite o nome a remover: ");
                fgets(pSearch, TAM_NOME, stdin);
                removerNewline(pSearch);

                *pFound = -1; 
                
                for (*pI = 0; *pI < *pCount; (*pI)++) {
                    if (strcmp(pSearch, getNome(pAgenda, pI)) == 0) {
                        *pFound = *pI; 
                        break;
                    }
                }

                if (*pFound == -1) {
                    printf("Pessoa '%s' nao encontrada.\n", pSearch);
                } else {
                    printf("Pessoa '%s' encontrada. Removendo...\n", pSearch);

                    for (*pJ = *pFound; *pJ < (*pCount - 1); (*pJ)++) {
                        
                        *pI = *pJ + 1; 

                        void* pDest = (void*)getNome(pAgenda, pJ);
                        void* pSrc = (void*)getNome(pAgenda, pI);

                        memcpy(pDest, pSrc, TAM_REGISTRO);
                    }

                    (*pCount)--; 
                    printf("Removido com sucesso.\n");
                }
                break;
            }

            case 3: {
                if (*pCount == 0) {
                    printf("Agenda vazia. Nada para buscar.\n");
                    break;
                }

                printf("--- Buscar Pessoa ---\n");
                printf("Digite o nome a buscar: ");
                fgets(pSearch, TAM_NOME, stdin);
                removerNewline(pSearch);

                *pFound = -1; 

                for (*pI = 0; *pI < *pCount; (*pI)++) {
                    if (strcmp(pSearch, getNome(pAgenda, pI)) == 0) {
                        *pFound = *pI;
                        break;
                    }
                }

                if (*pFound == -1) {
                    printf("Pessoa '%s' nao encontrada.\n", pSearch);
                } else {
                    *pI = *pFound;
                    printf("--- Pessoa Encontrada (ID: %d) ---\n", *pI);
                    printf("Nome: %s\n", getNome(pAgenda, pI));
                    printf("Idade: %d\n", *getIdade(pAgenda, pI));
                    printf("Email: %s\n", getEmail(pAgenda, pI));
                }
                break;
            }

            case 4: {
                printf("--- Listando Todas as Pessoas (%d) ---\n", *pCount);
                if (*pCount == 0) {
                    printf("Agenda vazia.\n");
                } else {
                    for (*pI = 0; *pI < *pCount; (*pI)++) {
                        printf("\n--- [Registro ID: %d] ---\n", *pI);
                        printf("  Nome: %s\n", getNome(pAgenda, pI));
                        printf("  Idade: %d\n", *getIdade(pAgenda, pI));
                        printf("  Email: %s\n", getEmail(pAgenda, pI));
                    }
                }
                break;
            }

            case 5: {
                printf("Saindo e liberando memoria...\n");
                break;
            }

            default: {
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }
        } 

    } while (*pChoice != 5);

    free(pBuffer);
    pBuffer = NULL;

    return 0;
}