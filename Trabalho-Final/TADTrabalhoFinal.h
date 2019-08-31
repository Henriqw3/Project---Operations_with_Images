#ifndef TADTRABALHOFINAL_H_INCLUDED
#define TADTRABALHOFINAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcmp no main
#include "TADMatriz.h"
#include "TADPilha.h"
#include "ponto.h"


//Constantes de erro
#define SUCCESS 1
#define ERROR_INVALID_COMMAND -3
#define ERROR_INVALID_FILE_FORMAT -4
#define ERROR_OPEN_FILEIN -5
#define ERROR_OPEN_FILEOUT -8
#define ERROR_TAD_MAT -15
#define ERROR_TAD_FILLMAT -17
#define ERROR_MAZE_NOTFINAL -20
#define ERROR_IN_MAZEFUNC -22


/*Funções Principais (Descritas no roteiro do trabalho)*/

//print_file
//Abre uma imagem (formato texto) e mostra os valores dos pixels na tela
int print_file(char *fileIn);

//convert
//Converte uma imagem no formato file.txt para o formato file.imm
int convert(char *fileIn, char *fileOut);// -open

//segment
//Faz o thresholding (limiariza��o da imagem) com um valor thr da imagem file.imm
//e escreve o resultado em segfile.imm
int segment(int thr, char *fileIn, char *fileOut);

//related_component
//Detecta os componentes conexos de uma imagem e os rotula no arquivo de sa�da
int related_component(char *fileIn, char *fileOut);

//maze
//Mostra o caminho a ser percorrido em um labirinto em um arquivo.txt de sa�da
int maze(char *fileIn, char *fileOut); // -lab (Labirinto)


/*=============================================================================*/

/*Fun��es de Apoio*/

//calc_dim_fileMat
//Calcula dimens�o da matriz de um arquivo(.txt ou .imm)
int calc_dim_fileMat(char *fileIn, int *linha, int *coluna);

//write_tad_in_file
//Pega uma TAD Matriz e escreve em um arquivo de sa�da(.txt ou .imm)
int write_tad_in_file(char *fileOut, Matriz *m);

//open_file
//Abre um arquivo e coloca seu conte�do em uma TAD Matriz m (.txt ou .imm)
int open_file(char *fileIn, Matriz **m);

//identify_type_file
//Identifica o tipo do arquivo. Retorna 1 se for .txt, 2 se for.imm e 0 se o formato for desconhecido
int identify_type_file(char *fileIn);

#endif // TADTRABALHOFINAL_H_INCLUDED

