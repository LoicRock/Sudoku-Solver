#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




typedef struct
{
    int** value;
    int nbr;
    int nbc;
    int size_cell_c;
    int size_cell_r;
} Sudoku;

void display_separator(int nbc,int nbr)
{

    if(nbr==4)
    {
        printf("+------+------+\n");
    }
    else if(nbr==6)
    {
        printf("+---------+---------+\n");
    }
    else if(nbr==9)
    {
        printf("+---------+---------+---------+\n");
    }
    else if(nbr==16)
    {
        printf("+------------+------------+------------+------------+\n");
    }

}

void display_sudoku(int nbc,int nbr,int s[nbc][nbr],int sizer,int sizec)
{
    int i,j;

    display_separator(nbc,nbr);


    for (i=0; i<nbc; i++)
    {
        printf("|");
        for(j=0; j<nbr; j++)
        {

            if(j==sizer || j==sizer*2 || j==sizer*3)
            {
                printf("|");
            }
            if(s[i][j]==0)
            {
                printf(" . ");
            }
            else if(s[i][j]>9)
            {
                printf(" %d",s[i][j]);
            }
            else
            {
                printf(" %d ",s[i][j]);
            }


            if(j==nbc-1)
            {
                printf("|");
                printf("\n");
                if(i==sizer-1 && sizer%sizec==0 || i==(sizer*2)-1  && sizer%sizec==0|| i==(sizer*3)-1 && sizer%sizec==0 || i==(sizer*4)-1 && sizer%sizec==0)
                {
                    display_separator(nbc,nbr);

                }
                else if(i==sizec-1 ||i==(sizec*2)-1||i==(sizec*3)-1)
                {

                    display_separator(nbc,nbr);
                }
            }

        }

    }



}

void init_sudoku(int nbc,int nbr,int s[nbc][nbr])
{

    int i,j;
    for (i=0; i<nbc; i++)
    {
        for(j=0; j<nbr; j++)
        {
            s[i][j]=0;
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


void lire_fichier(int nbc,int nbr,int s[nbc][nbr],char *filename)
{
    int i,j;
    FILE* fic=NULL;
    fic=fopen(filename,"r");

    if(fic!=NULL)
    {


        for (i = 0; i < nbc; i++)
        {
            for (j = 0; j < nbr; j++)
            {

                fscanf(fic,"%d ",&s[i][j]);


            }

        }

        fclose(fic);
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


void print_bool(bool a)
{
    if (a==true)
    {

        printf("true");
    }
    else
    {
        printf("false");
    }

}

//backtracking

bool absentSurColonne(int nbr,int nbc, int k,int s[nbr][nbc],int j)
{

    int i;
    for (i=0; i < nbc; i++)
    {
        if (s[i][j] == k)
            return false;
    }
    return true;
}

bool absentSurLigne(int nbr,int nbc, int k,int s[nbr][nbc],int i)
{
    int j ;
    for (j=0; j < nbr; j++)
    {
        if (s[i][j] == k)
            return false;
    }
    return true;
}

bool absentSurBloc (int nbr,int nbc,int s[nbc][nbr],int k, int i, int j,int sizer,int sizec)
{



    int i2 = i-(i%sizec);
    int j2 = j-(j%sizer);  // ou encore : _i = 3*(i/3), _j = 3*(j/3);
    for (i=i2; i < i2+sizec; i++)
        for (j=j2; j < j2+sizer; j++)
            if (s[i][j] == k)
                return false;
    return true;
}


bool estValide (int nbc,int nbr,int s[nbc][nbr], int position,int sizec,int sizer)
{

    if (position == nbc*nbr)
        return true;

    int i = position/nbc;
    int j = position%nbc;

    if (s[i][j] != 0)
    {
        return estValide(nbc,nbr,s,position+1,sizec,sizer);
    }


    int k;
    for (k=1; k<=nbc; k++)
    {
        printf("k: %d \n",k);
        print_bool(absentSurColonne(nbr,nbc,k,s,j));
        print_bool(absentSurLigne(nbr,nbc,k,s,i ) );
        print_bool(absentSurBloc(nbr,nbc,s,k,i,j,sizec,sizer));
        printf("\n");

        if (absentSurColonne(nbr,nbc,k,s,j)==true && absentSurLigne(nbr,nbc,k,s,i )==true && absentSurBloc(nbr,nbc,s,k,i,j,sizec,sizer)==true)
        {

            s[i][j] = k;

            if (estValide (nbc,nbr,s, position+1,sizec,sizer))
                return true;
        }
    }
    s[i][j] = 0;

    return false;
}

int select_size_cell_r(int nbline)
{
    int size;

    switch(nbline)
    {
    case 4:
        size=2;

        break;
    case 6:
        size=2;
        break;
    case 9:
        size=3;
        break;
    case 12:
        size=3;
        break;
    case 16:
        size=4;
        break;
    default:
        size=0;
    }

    return size;
}

int select_size_cell_c(int nbline)
{
    printf("nbline : %d\n",nbline);

    int size;

    switch(nbline)
    {
    case 4:
        size=2;

        break;
    case 6:
        size=3;
        break;
    case 9:
        size=3;
        break;
    case 12:
        size=4;
        break;
    case 16:
        size=4;
        break;
    default:
        size=0;
    }

    return size;
}


int main()
{
    Sudoku s;

    char fnamer[100]="";
    printf("Enter a name file [exemple.txt]: \n");
    scanf("%s",&fnamer);
    int nbline=countlines(fnamer);



    //init taille grille
    s.nbc=nbline;
    s.nbr=nbline;
    int tab[s.nbr][s.nbc];
    s.value=tab;
    int sizec,sizer;
    s.size_cell_c=select_size_cell_c(nbline);
    s.size_cell_r=select_size_cell_r(nbline);
    printf("%d",s.size_cell_c);
    printf("%d",s.size_cell_r);



    init_sudoku(s.nbc,s.nbr,s.value);//Initialise la grille à 0
    lire_fichier(s.nbc,s.nbr,s.value,fnamer); //Lit le fichier et remplis la grille
    printf("Aprés lecture du fichier \n");
    display_sudoku(s.nbc,s.nbr,s.value,s.size_cell_c,s.size_cell_r);
    display_sudoku(s.nbc,s.nbr,s.value,s.size_cell_c,s.size_cell_r);

    printf("Résolution : \n");
    estValide(s.nbc,s.nbr,s.value,0,s.size_cell_c,s.size_cell_r);
    display_sudoku(s.nbc,s.nbr,s.value,s.size_cell_c,s.size_cell_r);

    return 0;
}
