#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

/*  Estruturas  */
typedef struct {
	int id;
	float prior;  // 0 <= prior <= 900000
} ELEMENTO;

typedef struct {
	ELEMENTO A[4000];
	int maxElementos;  // inútil pois máximo de elementos já foi definido (4000)?
	int m;
} FILADEPRIORIDADE;






/*  Funções auxiliares  */
void maxHeapify(FILADEPRIORIDADE* f, int i) {  // auxiliar de buildMaxHeap(), atualiza a fila de prioridades de acordo à prioridade
	int maior = i;
	int indiceFilhoEsq = 2*i + 1;
	int indiceFilhoDir = 2*i + 2;
	
	if (indiceFilhoEsq < f->m && f->A[indiceFilhoEsq].prior > f->A[maior].prior) maior = indiceFilhoEsq;
	if (indiceFilhoEsq < f->m && f->A[indiceFilhoDir].prior > f->A[maior].prior) maior = indiceFilhoDir;

	if (maior != i) {  // condição é atendida apenas quando é necessário reorganizar heap
		ELEMENTO aux = f->A[i];
		f->A[i] = f->A[maior];
		f->A[maior] = aux;
		maxHeapify(f, maior);
	}
}

void buildMaxHeap(FILADEPRIORIDADE* f) {
	int comeco = (f->m / 2) - 1;  // índice do último nó não-folha
	for (int i = comeco; i >= 0; i--) {
		maxHeapify(f, i);  // atualiza fila de prioridades para cada i
	}
}

void heapIncreaseKey(FILADEPRIORIDADE* f, int i, float p) {  // altera prioridade de um elemento na posição i e atualiza a fila
	f->A[i].prior = p;
	buildMaxHeap(f);  // reordena heap após alterar prioridade de elemento
}






/*  Funções a serem implementadas para a parte 1 do trabalho 3  */
int heapMax(FILADEPRIORIDADE* f, ELEMENTO* local) {
	if (f->m != 0) {
		*local = f->A[0];  // copia elemento com prioridade máxima para o ponteiro informado pelos parâmetros
		return 1;
	}
	return 0;
	
}

int heapExtractMax(FILADEPRIORIDADE* f, ELEMENTO* local) {
	if (f->m == 0) return 0;

	ELEMENTO aux = f->A[0];
	*local = aux;  // copia elemento com prioridade máxima para o ponteiro informado pelos parâmetros

	f->A[0] = f->A[f->m - 1];  // copia último elemento para a primeira posição do arranjo
	f->m--;  // ignora última posição do arranjo
	buildMaxHeap(f);  // reorganiza arranjo

	return 1;
}

int heapInsert(FILADEPRIORIDADE* f, ELEMENTO e) {
	if (f->m >= f->maxElementos || e.prior < 0 || e.prior > 900000) return 0;  // casos em que é impossível a inserção

	if (f->m == 0) {  // caso heap esteja vazio
		f->A[0] = e;
		f->m++;
	} else {  // caso heap possua pelo menos um elemento
		f->A[f->m] = e;
		f->m++;
		buildMaxHeap(f);
	}
	return 1;
}

void heapPrint(FILADEPRIORIDADE* f) {
	printf("Fila de prioridade: [");
	for (int i = 0; i < f->m; i++) {
		if (i == f->m - 1) printf("%i(%.1f)", f->A[i].id, f->A[i].prior);  // caso seja último elemento do arranjo
		else printf("%i(%.1f), ", f->A[i].id, f->A[i].prior);  // caso contrário
	}
	printf("]\n");
}






/*  Input e Output  */
int main() {

	// fila solicitada pelo enunciado
	FILADEPRIORIDADE filaExecucao;
	filaExecucao.maxElementos = 4000;
	filaExecucao.m = 0;


	printf("\n#####################################\n");
	printf("Insira o numero de operacoes a serem executadas:\n");
	int numeroOperacoes;
	scanf("\n %i", &numeroOperacoes);

	for (int i = 0; i < numeroOperacoes; i++) {
		int operacaoAtual;
		printf("\nEscolha entre (1)-heapMax (2)-heapExtractMax (3)-heapInsert (4)-heapPrint:  ");
		scanf("\n %i", &operacaoAtual);

		if (operacaoAtual == 1) {
			ELEMENTO copiaHeap;
			int resultado = heapMax(&filaExecucao, &copiaHeap);
			if (resultado == 0) printf("-1 -1.0\n");
			else printf("%i %.1f\n", copiaHeap.id, copiaHeap.prior);

		} else if (operacaoAtual == 2) {
			ELEMENTO extracaoHeap;
			int resultado = heapExtractMax(&filaExecucao, &extracaoHeap);
			if (resultado == 0) printf("-1 -1.0\n");
			else printf("%i %.1f\n", extracaoHeap.id, extracaoHeap.prior);

		} else if (operacaoAtual == 3) {
			printf("Insira um valor inteiro para identificacao e um valor com ponto flutuante para prioridade (separados por espaco):  ");
			char linhaAtual[99];
			rewind(stdin);
			fgets(linhaAtual, 99, stdin);  // obtém string com input de inteiro de float

			char* valorInteiroChar = strtok(linhaAtual, " ");  // separa o input de inteiro
			char* valorFloatChar = strtok(NULL, " ");  // separa o input de float
			int valorInteiro = atoi(valorInteiroChar);  // converte string para inteiro
			float valorFloat = atof(valorFloatChar);  // converte string para float

			ELEMENTO insercaoHeap;
			insercaoHeap.id = valorInteiro;
			insercaoHeap.prior = valorFloat;
			
			int resultado = heapInsert(&filaExecucao, insercaoHeap);
			if (resultado == 0) printf("F\n");
			else printf("T\n");

		} else if (operacaoAtual == 4) {
			heapPrint(&filaExecucao);

		} else {
			printf("Nao foi possivel realizar a operacao escolhida. Tente novamente.\n");
			i--;
		}

		printf("\n");
	}

	printf("\n################ fim ################\n");
	return 0;
}