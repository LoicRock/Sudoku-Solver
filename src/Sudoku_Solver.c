#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




typedef struct
{
    char** value;
    int nbr;
    int nbc;
} Sudoku;

void display_sudoku(int nbc,int nbr,char s[nbc][nbr])
{
    int i,j;
    for (i=0; i<nbc; i++)
    {
        for(j=0; j<nbr; j++)
        {
            printf(" %c |",s[i][j]);
            if(j==nbc-1)
            {
                printf("\n");

            }
        }
    }
    printf("OK");


}

void init_sudoku(int nbc,int nbr,char s[nbc][nbr])
{

    int i,j;
    for (i=0; i<nbc; i++)
    {
        for(j=0; j<nbr; j++)
        {
            s[i][j]=' ';
        }
    }

}

/*Fonction sleep*/
void sleep(unsigned long int n)
{
    /* boucle vide parcourue (n * 100000) fois*/
    int i = 0;
    unsigned long int max = n * 100000;
    do
    {

        i++;
    }
    while(i <= max);
}


void lire_fichier(int nbc,int nbr,char s[nbc][nbr],char *filename)
{
    int i,j;
    FILE* fic=NULL;
    fic=fopen(filename,"r");
    char c;
    ;

    if(fic!=NULL)
    {


        for (i = 0; i < nbc; i++)
        {
            for (j = 0; j < nbr; j++)
            {

                fscanf(fic,"%c ",&s[i][j]);


            }

        }

        fclose(fic);
    }
}


void zero_to_space(int nbc,int nbr,char s[nbc][nbr])
{
    int i,j;
    for(i=0; i<nbc; i++)
    {
        for(j=0; j<nbr; j++)
        {
            if(s[i][j]=='0')
            {
                s[i][j]=' ';
            }
        }
    }
}

int countlines(char *filename)
{
    FILE *fp = fopen(filename,"r");
    int c=0;
    int lines=0;

    while((c=fgetc(fp)) != EOF)
    {
        if(c=='\n')
            lines++;
    }

    return lines;
}

int main()
{
    Sudoku s;

    char fnamer[100]="";
    printf("Entrez le nom du fichier [exemple.txt]: \n");
    scanf("%s",&fnamer);
    int nbline=countlines(fnamer);
    printf("%d",nbline);

    //init taille grille
    s.nbc=nbline;
    s.nbr=nbline;
    char tab[s.nbr][s.nbc];
    s.value=tab;


    init_sudoku(s.nbc,s.nbr,s.value);//Initialise la grille à 0
    display_sudoku(s.nbc,s.nbr,s.value);
    lire_fichier(s.nbc,s.nbr,s.value,fnamer); //Lit le fichier et remplis la grille
    printf("Aprés lecture \n");
    display_sudoku(s.nbc,s.nbr,s.value);
    printf("Aprés remplacement :\n");
    zero_to_space(s.nbc,s.nbr,s.value); //Remplace les zero par des espace
    display_sudoku(s.nbc,s.nbr,s.value);

    printf("Résolution : \n");
    estValide(s.nbc,s.nbr,s.value,0);
     display_sudoku(s.nbc,s.nbr,s.value);

    return 0;
}
