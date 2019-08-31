#include "TADTrabalhoFinal.h"


int print_file(char *fileIn)//recebe argumento que é o nome do arquivo
{
    Matriz *m;//Cria matriz
    int aux;

    aux = open_file(fileIn, &m);//Abre o arquivo
    if(!aux)
        return ERROR_OPEN_FILEIN;//Se a função open retorou erro a função print retorna erro

    m_tad_print(m);
    m_free(m);
    return SUCCESS;
}

int convert(char *fileIn, char *fileOut)
{
    Matriz *m;

    open_file(fileIn, &m);
    write_tad_in_file(fileOut, m);

    return SUCCESS;
}

int segment(int thr, char *fileIn, char *fileOut)
{
    Matriz *m;
    int nLin, nCol;
    int val;

    open_file(fileIn, &m);
    m_get_lin_col(m, &nLin, &nCol);

    //faz thresholding
    for(int i = 0; i < nLin; i++)
    {
        for(int j = 0; j < nCol; j++)
        {
            m_select_int(m, i, j , &val);
            if(val >= thr)
                m_insert_int(m, i, j, 1);
            else
                m_insert_int(m, i, j, 0);
        }
    }

    write_tad_in_file(fileOut, m);

    m_free(m);
    return SUCCESS;
}

int related_component(char *fileIn, char *fileOut)
{
    Stack *st;
    Matriz *img;
    Matriz *img_rot;
    Ponto vetp[4];
    Ponto base;
    int nLin, nCol;
    int valA, valB;
    int rotulo = 0;

    open_file(fileIn, &img);

    m_get_lin_col(img, &nLin, &nCol);
    img_rot = m_create(nLin, nCol);
    m_fill(img_rot, 0);

    st = stack_create();

    //Rotina de rotular TAD Matriz img_rot
    for(int i = 0; i < nLin; i++)
    {
        for(int j = 0; j < nCol; j++)
        {
            m_select_int(img, i, j, &valA);
            m_select_int(img_rot, i, j, &valB);

            if(valA == 1 && valB == 0)//Gatilho que inicia o rotulamento de um objeto ao encontrar o seu primeiro elemento
            {
                rotulo++;

                m_insert_int(img_rot, i, j, rotulo);//Rotula o primeiro ponto encontrado de um objeto

                base.x = i;
                base.y = j;

                stack_push(st, base);

                while(stack_size(st) > 0)
                {
                    vetp[0].x= base.x;
                    vetp[0].y= base.y-1;
                    vetp[1].x= base.x-1;
                    vetp[1].y= base.y;
                    vetp[2].x= base.x;
                    vetp[2].y= base.y+1;
                    vetp[3].x= base.x+1;
                    vetp[3].y= base.y;

                    for(int k = 0; k < 4; k++)
                    {
                        m_select_int(img, vetp[k].x, vetp[k].y, &valA);
                        m_select_int(img_rot, vetp[k].x, vetp[k].y, &valB);
                        if(valA == 1 && valB == 0)
                        {
                            m_insert_int(img_rot, vetp[k].x, vetp[k].y, rotulo);
                            stack_push(st, vetp[k]); 
                            base = vetp[k];
                            break;
                        }
                        else
                        {
                            if(k == 3)
                            {
                                stack_pop(st);
                                stack_top(st, &base);
                            }

                            if(stack_size(st) == 1 && k == 3)
                                stack_pop(st);
                        }
                    }
                }
            }
        }
    }

    write_tad_in_file(fileOut, img_rot);

    m_free(img);
    m_free(img_rot);
    stack_free(st);

    return SUCCESS;
}

int maze(char *fileIn, char *fileOut)
{
    Stack *st;//Pilha
    Matriz *img;//Matriz original
    Matriz *img_rot;//Matriz Destino
    Ponto inicio;//(x, y)
    Ponto atual;//(x, y)
    Ponto vetp[4];//Especial para vizinhos(x, y)
    int nLin, nCol;
    int val, valA, valB;
    int x, y;

    open_file(fileIn, &img);//Abre o arquivo com o Binário

    m_get_lin_col(img, &nLin, &nCol);//Passa para as variáveis de linha e coluna seus respectivos tamanhos
    img_rot = m_create(nLin, nCol);//Cria imagem de contrução com as mesmas proporções da original
    m_fill(img_rot, 0);//Preenche a imagem root com zeros

    st = stack_create();

    //Pega posição do nicio do labirinto na TAD Matriz img
    for(int i = 0; i < nLin; i++)
    {
        m_select_int(img, i, 0, &val);
        if(val == 1)
        {
            inicio.x = i;
            inicio.y = 0;
            break;
        }
    }

    stack_push(st, inicio);
    m_insert_int(img_rot, inicio.x, inicio.y, 2);//rotula de 2 a posi��o de in�cio


    atual.x = inicio.x;
    atual.y = inicio.y + 1;
    m_insert_int(img_rot, atual.x, atual.y, 2);//Necess�rio, sem ele o segundo ponto do caminho n�o ser� rotulado de 2

    while(atual.y != nCol-1)//Enquanto nã chegar no final(última coluna)
    {
        //Set posições vizinhas
        vetp[0].x= atual.x ;//meio x
        vetp[0].y= atual.y-1;//oeste
        vetp[1].x= atual.x-1;//norte
        vetp[1].y= atual.y;//meio y
        vetp[2].x= atual.x;//
        vetp[2].y= atual.y+1;//leste
        vetp[3].x= atual.x+1;//sul
        vetp[3].y= atual.y;//

        //Percorre e rotula a partir da terceira pozição do caminho
        for(int i = 0; i < 4; i++)
        {
            x = vetp[i].x;//faz a rotação x
            y = vetp[i].y;//faz a rotação y

            m_select_int(img, x, y, &valA);//Pega um valor na matriz original
            m_select_int(img_rot, x, y, &valB);//	Pega o mesmo valor na mesma pos da em contrução

            if(valA == 1 && valB == 0)//Se houver um caminho válido(1), rotula e anda no primeiro que achar
            {
                stack_push(st, vetp[i]);//Empilha sua posição
                m_insert_int(img_rot, x, y, 2);//Insere dois na matriz
                atual = vetp[i];//Atual recebe o checkpoint
                break;
            }
            else
            { 
                if(i == 3)//significa que não há nenhum caminho a ser percorrido, volta um ponto para trás
                {//Fez a rotulação completa 

                    m_insert_int(img_rot, atual.x, atual.y, 1);//insere na matriz em contrução as posições atuais
                    stack_pop(st);//posições salvas são retiradas da pilha
                    stack_top(st, &atual);//e é consultado e passado para o atual um novo valor que é a última posição da pilha
                }
            }
        }
    }

    //Remove os caminhos sem fim rotulados de 1. Atribui a essas posições o valor 0;
    for(int i = 0; i < nLin; i++){
        for(int j = 0; j < nCol; j++){

            m_select_int(img_rot, i, j, &val);//Pega um valor na posição 
            if(val != 2 && val != 0)//se ele for dois limpa ele
                m_insert_int(img_rot, i, j, 0);//inserindo 0
        }
    }

    write_tad_in_file(fileOut, img_rot);

    m_free(img);
    m_free(img_rot);
    stack_free(st);
    return SUCCESS;
}

////////////////////////////////    Fun��es de Apoio    //////////////////////////////////////
int calc_dim_fileMat(char *fileIn, int *linha, int *coluna)//recebe nome do arquivo e duas variáveis por referencia para passar valores para elas
{//
    FILE *f;
    int nLin = 0;
    int nCol = 0;
    int val = 0;
    int elem = 0;
    char cAtual, cAnterior;
    int fileType = 0;

    fileType = identify_type_file(fileIn);//Identifica se o arquivo é semelhante a txt ou imm

    switch(fileType)
    {
        case 1:
            f = fopen (fileIn, "r");
            if(f == NULL)
                return ERROR_OPEN_FILEIN;

            //Percorrendo matriz do arquivo para calcular sua dimens�o.
            fscanf(f, "%d%c", &val, &cAtual);
            elem++;

            while(1)//Enquanto não for final de arquivo 
            {
                cAnterior = cAtual;
                elem++;

                fscanf(f, "%d", &val);
                if(feof(f))//condição do final de arquivo
                    break;
                fscanf(f, "%c", &cAtual);
                if(feof(f))//condição do final de arquivo
                    break;

                if(cAtual == '\n')
                    nLin++;
            }

            elem++;//Pra compensar o lado onde o feof para antes de ler o ultimo elemento da matriz;

            if(feof(f))//Testa se depois do ultimo elemento da matriz tem \n, se nao tiver, conta mais uma linha
            {
                if(cAnterior != '\n')
                nLin++;
            }

            nCol = elem / nLin;

            *linha = nLin;
            *coluna = nCol;
            fclose(f);
            return SUCCESS;

        case 2:
            f = fopen(fileIn, "rb");
            if(f == NULL)
                return ERROR_OPEN_FILEIN;

            fread(&linha, sizeof(int), 1, f);
            fread(&coluna, sizeof(int), 1, f);

            fclose(f);
            return SUCCESS;

        default:
            return ERROR_INVALID_FILE_FORMAT;
    }

}

int write_tad_in_file(char *fileOut, Matriz *m)
{
    FILE *f;
    int nLin, nCol;
    int val;
    int fileType = 0;

    m_get_lin_col(m, &nLin, &nCol);

    fileType = identify_type_file(fileOut);

    switch(fileType)
    {
        case 1:
            f = fopen(fileOut, "w");
            if(f == NULL)
                return ERROR_OPEN_FILEOUT;

            //Escreve matriz da TAD no arquivo
            for(int i = 0; i < nLin; i++)
            {
                for(int j = 0; j < nCol; j++)
                {
                    m_select_int(m, i, j, &val);
                    fprintf(f, "%d", val);
                    if(j == nCol-1)
                    {
                        fprintf(f, "\n");
                    }
                    else
                    {
                        fprintf(f, " ");
                    }
                }
            }
            fclose(f);
            return SUCCESS;

        case 2:
            f = fopen(fileOut, "wb");
            if(f == NULL)
                return ERROR_OPEN_FILEOUT;

            fwrite(&nLin, sizeof(int), 1, f);
            fwrite(&nCol, sizeof(int), 1, f);

            for(int i = 0; i < nLin; i++)
            {
                for(int j = 0; j < nCol; j++)
                {
                    m_select_int(m, i, j, &val);
                    fwrite(&val, sizeof(int), 1, f);
                }
            }
            fclose(f);
            return SUCCESS;

        default:
            return ERROR_INVALID_FILE_FORMAT;
    }
}

int open_file(char *fileIn, Matriz **m)/// recebe o argumento que é o nome do arquivo alem de pp para matriz
{
    FILE *f;
    int nLin = 0, nCol = 0;//Caso a imagem seja txt vai precisar recolher o  passa 
    int val = 0;
    int fileType = 0;

    fileType = identify_type_file(fileIn);//chama a idenficação para saber se é txt ou imm

    switch(fileType)
    {
        case 1: //Caso arquivo seja .txt
            if(calc_dim_fileMat(fileIn, &nLin, &nCol) != 1)
                return ERROR_OPEN_FILEIN;

            *m = m_create(nLin, nCol);

            f = fopen (fileIn, "r");//Abre o arquivo para leitura
            if(f == NULL)//Se for vazia 
                return ERROR_OPEN_FILEIN;//error
						//Caso contrário 
            for(int i = 0; i < nLin; i++)
            {
                for(int j = 0; j < nCol; j++)
                {
                    fscanf(f, "%d", &val);
                    m_insert_int(*m, i, j, val);
                }
            }

            fclose(f);
            return SUCCESS;

        case 2: //Caso de arquivo ser .imm
            f = fopen(fileIn, "rb");
            if(f == NULL)
                return ERROR_OPEN_FILEIN;

            //Pegando dimens�o da matriz
            fread(&nLin, sizeof(int), 1, f);//n�mero de linhas
            fread(&nCol, sizeof(int), 1, f);//n�mero de colunas

            *m = m_create(nLin, nCol);

            //Pega matriz do arquivo e coloca na TAD
            for(int i = 0; i < nLin; i++)
            {
                for(int j = 0; j < nCol; j++)
                {
                    fread(&val, sizeof(int), 1, f);
                    m_insert_int(*m, i, j, val);
                }
            }

            fclose(f);
            return SUCCESS;

        default://Caso de formato desconhecido
            return ERROR_INVALID_FILE_FORMAT;

    }
}

int identify_type_file(char *fileIn)//recebe o nome do arquivo e vai identificar se é...
{

    int i = strlen(fileIn);//i recebe o tamanho da string recebida, para verificar cada char

    if(fileIn[i-4] == '.' && fileIn[i-3] == 't' && fileIn[i-2] == 'x' && fileIn[i-1] == 't')
    {//Verifica caracter por caracter da string e neste caso verifica se é ".txt"
        return 1;//Se for arquivo txt retorna 1
    }
    else
    {
        if(fileIn[i-4] == '.' && fileIn[i-3] == 'i' && fileIn[i-2] == 'm' && fileIn[i-1] == 'm')
        {//se for arquivo tipo .imm retorna 2
            return 2;
        }

        return 0;//nenhum dos dois retorna 0
    }
}
