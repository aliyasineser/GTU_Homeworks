/*************************************************************
 *                                                           *
 * HW07 Part3                                                *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 10/04/2015                                  *
 *                                                           *
 *************************************************************/

 /*
    Onemli bir nokta belirtilmeli ki dosyadan okuma yapilacagindan
    onceden size(boyut) ogrenmek ekstra uzun islemler gerektirecektir.
    Bu program makrolara gore hareket etmekte ve matrisleri buna gore
    doldurmaktadir. Buyuk boyutlu labirentlerde cok kez denendi ve
    makroyu tanimladiginiz surece beklediginiz ciktilari elde
    edebileceksiniz.
 */



/*Kutuphane ve makro tanimlamalari*/
#include <stdio.h>
#define COL_SIZE 5
#define ROW_SIZE 5
#define FIRST 0
#define NONSUCCESS 0
#define SUCCESS 1
#define SUB 1
#define ADDONE 1

/*Tip tanimlamalari, Dogru/Yanlis ve gidilecek yonler icin*/
typedef enum {FALSE, TRUE} Bool;
typedef enum {notavailable,available,right_down} Grid_t;

/*Fonksiyonlarin prototipleri*/
void read_table(FILE *input_file, Grid_t table[][COL_SIZE]);
void print_path(char path[][COL_SIZE], int n);
Bool find_path(Grid_t table[][COL_SIZE], char path[][COL_SIZE],
int size, int location_x, int location_y);

int
main()
{
    int i, j, is_success=NONSUCCESS;/*Counter ve basari durumu*/
    FILE *iptr; /*Matrise atilacak bilgileri barindiran dosya icin*/
    Grid_t table[ROW_SIZE][COL_SIZE];   /*Durum icin matris*/
    char path[ROW_SIZE][COL_SIZE];  /*Yolun cizilecegi matris*/

    read_table( iptr, table );  /*Tablo dosyadan doldurulur*/

    printf("This is our maze:\n\n");
    /* Tablonun konsola yazdirilmasi */
    for( i=FIRST; i < ROW_SIZE; i++)
    {
        for( j=FIRST; j < COL_SIZE; j++)
        {
            printf("%d  ", table[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    /*Sacma ciktilari onlemek icin yol matrisine atama yapiliyor*/
    for( i=FIRST; i < ROW_SIZE; i++)
    {
        for( j=FIRST; j < COL_SIZE; j++)
        {
            path[i][j] = '|';
        }
    }

    printf("We can't go to 0, if we go to the 1 or 2:\n");
    printf("1---> We can go down or right\n");
    printf("2---> We can go down and right together\n\n");
    printf("If we know what is that, now i can tell you");
    printf(" is there a path for getting out of maze.\n");
    printf("I looked and...\n\n");

    /*Fonksiyonun cagirillip yolu kontrol etmesi, yol bulmasi*/
    is_success = find_path( table , path, ROW_SIZE, FIRST, FIRST );
    /*Dogruysa yolu yazdirir ve mesaj verir, yanlis ise bilgi verir*/
    if( is_success == SUCCESS )
        {
            printf( "This is the path for the getting out of maze:\n\n" );
            printf("I marked the path with \'*\' and the others \'|\'.\n");
            printf("So, here's the way:\n\n");
            print_path( path, ROW_SIZE );
        }
    else
        printf("There isn't any path for getting out of maze.\n\n");

    printf("\n\n");
    return 0;
}

/*Dosyadan matrise okuma yapan fonksiyon*/
void read_table(FILE *input_file, Grid_t table[][COL_SIZE])
{
    int i,j;
    int table_int[ROW_SIZE][COL_SIZE];  /*Gecici integer matris*/

    input_file=fopen("table.txt","r");
/*Tum degerler okunur,cast edilerek matristen diger matrise atilir*/
    for( i=FIRST; i < ROW_SIZE; i++)
    {
        for( j=FIRST; j < COL_SIZE; j++)
        {
            fscanf(input_file, "%d", &table_int[i][j]);
            table[i][j] = (Grid_t)table_int[i][j];
        }
    }
}

/*Yolu yazdiran fonksyion*/
void print_path(char path[][COL_SIZE], int n)
{
    int i,j;

    for( i=FIRST; i<n;i++ )
    {
        for( j=FIRST; j<n; j++ )
        {
            printf( "%c ", path[i][j] );
        }
            printf("\n");
    }
}

/*Yolu bulan ozyineli fonksiyon*/
Bool find_path(Grid_t table[][COL_SIZE], char path[][COL_SIZE],
int size, int location_x, int location_y)
{
    Bool cond=FALSE;
/*Eger matrisin sonundaysa yol bulunmustur*/
    if( location_x == size-SUB && location_y == COL_SIZE-SUB )
    {
        cond=TRUE;
        path[location_x][location_y] = '*';
        path[size-SUB][COL_SIZE-SUB] = '*';
    }
    /*Saga ve asagi gidemezse yanlis yol diyecek*/
    if( table[location_x][location_y+ADDONE] == notavailable  &&
        table[location_x + ADDONE][location_y] == notavailable
        && table[location_x + ADDONE][location_y+ADDONE] == notavailable )
            {cond =  FALSE;}
    /*Eger bulundugu konum sag-asagi gitmeye izin veriyorsa*/
    else if ( table[location_x][location_y] == right_down )
    {
        /*Eger capraz yol cikisa gidiyor ve caprazda gidilecek yer varsa*/
        if( table[location_x+ADDONE][location_y+ADDONE] != notavailable &&
            find_path(table, path, size,
            location_x+ADDONE, location_y+ADDONE) == TRUE)
                {
                cond = TRUE;
                path[location_x][location_y] = '*';
                }

        /*Eger sag taraf cikisa gidiyor ve sagda yer varsa*/
        else if( table[location_x][location_y+ADDONE] != notavailable &&
            find_path(table, path, size,
            location_x, location_y+ADDONE) == TRUE)
                {
                cond = TRUE;
                path[location_x][location_y] = '*';
                }

        /*Eger asagi taraf cikisa gidiyor ve sagda yer varsa*/
        else if( table[location_x+ADDONE][location_y] != notavailable &&
            find_path(table, path, size,
            location_x+ADDONE, location_y) == TRUE)
                {
                cond = TRUE;
                path[location_x][location_y] = '*';
                }
    }
    /*Eger bulunulan konum sadece saga veya asagi gitmeye izin veriyorsa*/
    else if ( table[location_x][location_y] == available )
    {
        /*Eger asagi taraf cikisa gidiyor ve sagda yer varsa*/
        if( table[location_x+ADDONE][location_y] != notavailable &&
            find_path(table, path, size,
            location_x+ADDONE, location_y) == TRUE)
                {
                cond = TRUE;
                path[location_x][location_y] = '*';
                }

        /*Eger sag taraf cikisa gidiyor ve sagda yer varsa*/
        else if( table[location_x][location_y+ADDONE] != notavailable &&
            find_path(table, path, size,
            location_x, location_y+ADDONE) == TRUE)
                {
                cond = TRUE;
                path[location_x][location_y] = '*';
                }
    }
    return cond;
}
/****************************************************************************
 * 						End of HW07 Part3                     				*
 ****************************************************************************/
