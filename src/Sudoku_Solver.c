#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

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

    switch(nbr)
    {
    case 4:
        printf("+------+------+\n");
        break;
    case 6:
        printf("+---------+---------+\n");
        break;
    case 9:
        printf("+---------+---------+---------+\n");
        break;
    case 12:
        printf("+------------+------------+------------+\n");
        break;
    case 16:
        printf("+------------+------------+------------+------------+\n");
        break;
    default:
        printf("Error separator");
        break;

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
                if((i==sizer-1 && sizer%sizec==0) || (i==(sizer*2)-1  && sizer%sizec==0) || (i==(sizer*3)-1 && sizer%sizec==0) || (i==(sizer*4)-1 && sizer%sizec==0))
                {
                    display_separator(nbc,nbr);

                }
                else if(i==sizec-1 ||i==(sizec*2)-1||i==(sizec*3)-1 || i==(sizec*4)-1)
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



void read_file(int nbc,int nbr,int s[nbc][nbr],char *filename)
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


//backtracking

bool notInColumn(int nbr,int nbc, int k,int s[nbr][nbc],int j)
{

    int i;
    for (i=0; i < nbc; i++)
    {
        if (s[i][j] == k)
            return false;
    }
    return true;
}

bool notInRow(int nbr,int nbc, int k,int s[nbr][nbc],int i)
{
    int j ;
    for (j=0; j < nbr; j++)
    {
        if (s[i][j] == k)
            return false;
    }
    return true;
}

bool notInCell (int nbr,int nbc,int s[nbc][nbr],int k, int i, int j,int sizer,int sizec)
{



    int i2 = i-(i%sizec);
    int j2 = j-(j%sizer);  // ou encore : _i = 3*(i/3), _j = 3*(j/3);
    for (i=i2; i < i2+sizec; i++)
        for (j=j2; j < j2+sizer; j++)
            if (s[i][j] == k)
                return false;
    return true;
}


bool isValid (int nbc,int nbr,int s[nbc][nbr], int position,int sizec,int sizer)
{

    if (position == nbc*nbr)
        return true;

    int i = position/nbc;
    int j = position%nbc;

    if (s[i][j] != 0)
    {
        return isValid(nbc,nbr,s,position+1,sizec,sizer);
    }


    int k;
    for (k=1; k<=nbc; k++)
    {

        if (notInColumn(nbr,nbc,k,s,j)==true && notInRow(nbr,nbc,k,s,i )==true && notInCell(nbr,nbc,s,k,i,j,sizec,sizer)==true)
        {

            s[i][j] = k;

            if (isValid(nbc,nbr,s, position+1,sizec,sizer))
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

    int choice =0;
    while (choice!=2)
    {
        Sudoku s;

        char fnamer[100]="";
        while (access(fnamer, R_OK ) == -1)
        {
            printf("Enter a name file [exemple.txt]: \n");
            scanf("%s",&fnamer);
        }
        int nbline=countlines(fnamer);

        //init grid size
        s.nbc=nbline;
        s.nbr=nbline;
        int tab[s.nbr][s.nbc];
        s.value=tab;
        //Get cell size
        s.size_cell_c=select_size_cell_c(nbline);
        s.size_cell_r=select_size_cell_r(nbline);

        init_sudoku(s.nbc,s.nbr,s.value);//init grid at 0
        read_file(s.nbc,s.nbr,s.value,fnamer); //read file and fill grid
        printf("Apres lecture du fichier \n");
        display_sudoku(s.nbc,s.nbr,s.value,s.size_cell_c,s.size_cell_r);

        printf("\n");
        printf("Resolution en cours...\n");
        printf("\n");

        clock_t begin, end;//start clock
        begin = clock();

        isValid(s.nbc,s.nbr,s.value,0,s.size_cell_c,s.size_cell_r);//Backtracking

        bool test=false;
        int i,j;
        for(i=0;i<s.nbc;i++){
            for(j=0;j<s.nbr;j++){
                if(tab[i][j]==0){
                printf("Il y a une erreur dans la grille rentré \n");
                test=false;
                exit(true);
                }else{
                test=true;
                }
            }
        }

        if(test==true){
            printf("Solution : \n");
            display_sudoku(s.nbc,s.nbr,s.value,s.size_cell_c,s.size_cell_r);

            double time_spent;
            end = clock(); //end clock
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Temps de resolution : \n");
            printf("%f s\n",time_spent);
            printf("%f ms\n",time_spent*1000);
            printf("\n");
        }

        printf("Load another file ? [1]\n");
        printf("Quit [2]\n");
        scanf("%d",&choice);

    }
    return 0;
}




