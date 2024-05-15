typedef struct elemento *Lista;

Lista *criarLista();
int inserirOrdenado(Lista *, struct carta);
int acessarIndice(Lista *, int, struct carta *);
int removerIndice(Lista *, int);
int exibirLista(Lista *);
int quantidade(Lista *);
int destruirLista(Lista *, int);
