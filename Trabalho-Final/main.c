#include "TADTrabalhoFinal.h"
#include "TADMatriz.h"

void error_msg(int n);  //Função que imprime na tela a mensagem detalhada do erro.

int main(int argc, char *argv[])
{
    int aux;


    //Seleciona qual função deve ser chamada de acordo com a tag argv[1]
		//Compara com a string -open o segundo argumento passado para a main
		//Se strcmp for == 0 signica que a string chamada foi de fato -open
    if(strcmp(argv[1], "-open") == 0 && argc == 3)
    {
        aux = print_file(argv[2]);//chama a print_file e passa o nome do arquivo segundo argumento
        if(!aux)//Se retornou algum erro
            error_msg(aux);//MSG erro
    }else if(strcmp(argv[1], "-convert") == 0 && argc == 4)//compara as duas strings 
    {
        aux = convert(argv[2], argv[3]);
        if(!aux)
            error_msg(aux);
    }else if(strcmp(argv[1], "-segment") == 0 && argc == 5)
    {
        int thr = atoi(argv[2]);
        aux = segment(thr, argv[3], argv[4]);
        if(!aux)
            error_msg(aux);
    }else if(strcmp(argv[1], "-cc") == 0 && argc == 4)
    {
        aux = related_component(argv[2], argv[3]);
        if(!aux)
            error_msg(aux);
    }else if(strcmp(argv[1], "-lab") == 0  && argc == 4)
    {
        aux = maze(argv[2], argv[3]);
        if(!aux)
            error_msg(aux);
    }else
        error_msg(ERROR_INVALID_COMMAND);


    return 0;
}

void error_msg(int n)
{
    switch(n)
    {
        case ERROR_INVALID_COMMAND: printf("\nErro: Comando invalido\n"); break;

        case ERROR_INVALID_FILE_FORMAT: printf("\nErro: Formato de arquivo de entrada desconhecido\n"); break;

        case ERROR_OPEN_FILEIN: printf("\nErro: Falha na abertura de arquivo de entrada\n");  break;

        case ERROR_OPEN_FILEOUT: printf("\nErro: Falha na abertura de arquivo de saida\n"); break;

        case ERROR_TAD_MAT: printf("\nErro: Falha na alocação de TAD Matriz\n"); break;

        case ERROR_TAD_FILLMAT: printf("\nErro: Operação de popular TAD Matriz com 0 falhou\n");

        case ERROR_MAZE_NOTFINAL: printf("\nErro: Fim do labirinto não encontrado\n"); break;

        case ERROR_IN_MAZEFUNC: printf("\nErro: Falha na alocação de pilha\n"); break;

        default: printf("\nErro: Natureza desconhecida\n");
    }
}
