/*
Zad 5
Gra - KOLKO I KRZYZYK
Mozliwosc zapisu i wczytania stanu gry.
Gra moze byc w dwoch wariantach:
- gra dwoch graczy
* - gracz gra z komputerem (nalezy napisac logike komputera jak najtrudniejsza)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

void odczyt(char plansza[][3])
{
    int i, j;
    FILE *plik;

    if((plik=fopen("zapis.txt", "rb")) == NULL)
    {
        printf("\nBlad przy odczycie!\n");
        exit(1);
    }

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            fread(&plansza[i][j], sizeof(char), 1, plik);

    printf("Laduje ostatni zapis");
    for(i=0; i<3; i++)
    {
        printf(".");
        Sleep(500);
    }

    fclose(plik);
}

void printtable(char plansza[][3])
{
    int i, j;

    system("@cls");

    for(i=0; i<3; i++)
    {
        printf("  %c | %c | %c\n", plansza[i][0], plansza[i][1], plansza[i][2]);
        if(i<2)
            printf("-------------\n");
    }
}

void cleartable(char plansza[][3])
{
    int i, j;

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
           plansza[i][j] = 32;
}

void zapis(char plansza[][3])
{
    int i, j;
    FILE *pliczek;

    pliczek = fopen("zapis.txt", "w");

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            putc(plansza[i][j], pliczek);

    fclose(pliczek);
}

void playermove(char plansza[][3])
{
    int x=0, y=0, ruch=1;
    FILE *save;
    printf("\nTwoj ruch!(wiersz kolumna, aby zapisac stan gry wpisz: 0 0): ");

    do
    {
        scanf("%d %d", &x, &y);
        if(x == 0 && y == 0)
        {
            printf("Zapisuje gre.");
            zapis(plansza);
            exit(78);
        }
        else if(plansza[x-1][y-1] != 32)
            printf("\nTo pole jest juz zajete! Wybierz jakies inne!: ");
        else
        {
            plansza[x-1][y-1] = 79;
            ruch--;
        }
    } while(ruch);
}

void randaimove(char plansza[][3])
{
    int x, y, ruch=1;
    do
    {
        x = rand()%3;
        y = rand()%3;
        if(plansza[x][y] == 32)
        {
            plansza[x][y] = 88;
            ruch--;
        }
    } while(ruch);
}

int remis(char plansza[][3])
{
    int i, j, flag=9;

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            if(plansza[i][j] != 32)
                    flag--;
    if(flag == 0)
        return 0;
    else
        return 1;
}

int winner(char plansza[][3])
{
    if((plansza[0][0] == 79 && plansza[0][1] == 79 && plansza [0][2] == 79) ||
       (plansza[1][0] == 79 && plansza[1][1] == 79 && plansza [1][2] == 79) ||
       (plansza[2][0] == 79 && plansza[2][1] == 79 && plansza [2][2] == 79) ||
       (plansza[0][0] == 79 && plansza[1][0] == 79 && plansza [2][0] == 79) ||
       (plansza[0][1] == 79 && plansza[1][1] == 79 && plansza [2][1] == 79) ||
       (plansza[0][2] == 79 && plansza[1][2] == 79 && plansza [2][2] == 79) ||
       (plansza[0][0] == 79 && plansza[1][1] == 79 && plansza [2][2] == 79) ||
       (plansza[0][2] == 79 && plansza[1][1] == 79 && plansza [2][0] == 79))
    {
        printtable(plansza);
        printf("\nBrawo! Pokonales mnie!\n");
        printf("\nDzieki za gre!\n");
        exit(146);
        return 0;
    }
    else if((plansza[0][0] == 88 && plansza[0][1] == 88 && plansza [0][2] == 88) ||
            (plansza[1][0] == 88 && plansza[1][1] == 88 && plansza [1][2] == 88) ||
            (plansza[2][0] == 88 && plansza[2][1] == 88 && plansza [2][2] == 88) ||
            (plansza[0][0] == 88 && plansza[1][0] == 88 && plansza [2][0] == 88) ||
            (plansza[0][1] == 88 && plansza[1][1] == 88 && plansza [2][1] == 88) ||
            (plansza[0][2] == 88 && plansza[1][2] == 88 && plansza [2][2] == 88) ||
            (plansza[0][0] == 88 && plansza[1][1] == 88 && plansza [2][2] == 88) ||
            (plansza[0][2] == 88 && plansza[1][1] == 88 && plansza [2][0] == 88))
    {
        printtable(plansza);
        printf("Tym razem to ja wygralem!\nSprobuj pokonac mnie nastepnym razem!\n");
        printf("\nDzieki za gre!\n");
        exit(161);
        return 0;
    }
    else
        return 1;
}
/*
int mmremis(int plansza[][3])
{
    int i, j, flag=9;

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            if(plansza[i][j] != 32)
                    flag--;
    if(flag == 0)
        return 0;
    else
        return 1;
}

int mmwinner(int plansza[][3],int player)
{
    if((plansza[0][0] == player && plansza[0][1] == player && plansza [0][2] == player) ||
       (plansza[1][0] == player && plansza[1][1] == player && plansza [1][2] == player) ||
       (plansza[2][0] == player && plansza[2][1] == player && plansza [2][2] == player) ||
       (plansza[0][0] == player && plansza[1][0] == player && plansza [2][0] == player) ||
       (plansza[0][1] == player && plansza[1][1] == player && plansza [2][1] == player) ||
       (plansza[0][2] == player && plansza[1][2] == player && plansza [2][2] == player) ||
       (plansza[0][0] == player && plansza[1][1] == player && plansza [2][2] == player) ||
       (plansza[0][2] == player && plansza[1][1] == player && plansza [2][0] == player))
        return 0;
    else
        return 1;
}

void minimaxmove(char plansza[][3])
{
    int i, j, max, move[2], score=0;
    int minimaxplansza[3][3];

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            minimaxplansza[i][j] = plansza[i][j];

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(minimaxplansza[i][j] == 32)
                minimaxplansza[i][j] = minimax(plansza, 88);

            if(max < minimaxplansza[i][j] && minimaxplansza[i][j] != 88 && minimaxplansza[i][j] != 79)
            {
                max = minimaxplansza[i][j];
                move[0] = i;
                move[1] = j;
            }
        }
    }

    plansza[move[0]][move[1]] = 88;
}

int minimax(int minimaxplansza[][3], int player)
{
    int i, j, score=0, result;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(minimaxplansza[i][j] == 32)
                minimaxplansza[i][j] == player;
            else if(mmwinner(minimaxplansza, player) == 0 && player == 88)
                return 10;
            else if(mmwinner(minimaxplansza, player) == 0 && player == 79)
                return -10;
            else if(mmremis(minimaxplansza) == 0)
                return 0;

            if(player == 88 && mmremis(minimaxplansza)){
                minimax(minimaxplansza, 79);
            }
            else if(player == 79 && mmremis(minimaxplansza)){
                minimax(minimaxplansza, 88);
            }
        }
    }
} */

void mikoai(char plansza[][3])
{
    int x, y, ruch=1;

    if(plansza[1][1] == 32)
        plansza[1][1] = 88;

    else if(plansza[1][1] == 88 && plansza[0][0] == 88 && plansza[2][2] == 32)
        plansza[2][2] = 88;
    else if(plansza[1][1] == 88 && plansza[0][1] == 88 && plansza[2][1] == 32)
        plansza[2][1] = 88;
    else if(plansza[1][1] == 88 && plansza[0][2] == 88 && plansza[2][0] == 32)
        plansza[2][0] = 88;
    else if(plansza[1][1] == 88 && plansza[1][0] == 88 && plansza[1][2] == 32)
        plansza[1][2] = 88;
    else if(plansza[1][1] == 88 && plansza[1][2] == 88 && plansza[1][0] == 32)
        plansza[1][0] = 88;
    else if(plansza[1][1] == 88 && plansza[2][0] == 88 && plansza[0][2] == 32)
        plansza[0][2] = 88;
    else if(plansza[1][1] == 88 && plansza[2][1] == 88 && plansza[0][1] == 32)
        plansza[0][1] = 88;
    else if(plansza[1][1] == 88 && plansza[2][2] == 88 && plansza[0][0] == 32)
        plansza[0][0] = 88;


    else if(plansza[0][0] == 88 && plansza[0][2] == 88 && plansza[0][1] == 32)
        plansza[0][1] = 88;
    else if(plansza[0][0] == 88 && plansza[0][1] == 88 && plansza[0][2] == 32)
        plansza[0][2] = 88;
    else if(plansza[0][1] == 88 && plansza[0][2] == 88 && plansza[0][0] == 32)
        plansza[0][0] = 88;
    else if(plansza[0][0] == 88 && plansza[2][0] == 88 && plansza[1][0] == 32)
        plansza[1][0] = 88;
    else if(plansza[0][0] == 88 && plansza[1][0] == 88 && plansza[2][0] == 32)
        plansza[2][0] = 88;
    else if(plansza[2][0] == 88 && plansza[1][0] == 88 && plansza[0][0] == 32)
        plansza[0][0] = 88;
    else if(plansza[0][2] == 88 && plansza[1][2] == 88 && plansza[2][2] == 32)
        plansza[2][2] = 88;
    else if(plansza[0][2] == 88 && plansza[2][2] == 88 && plansza[1][2] == 32)
        plansza[1][2] = 88;
    else if(plansza[1][2] == 88 && plansza[2][2] == 88 && plansza[0][2] == 32)
        plansza[0][2] = 88;
    else if(plansza[2][0] == 88 && plansza[2][1] == 88 && plansza[2][2] == 32)
        plansza[2][2] = 88;
    else if(plansza[2][0] == 88 && plansza[2][2] == 88 && plansza[2][1] == 32)
        plansza[2][1] = 88;
    else if(plansza[2][2] == 88 && plansza[2][1] == 88 && plansza[2][0] == 32)
        plansza[2][0] = 88;

    else if(plansza[1][1] == 79 && plansza[0][0] == 79 && plansza[2][2] == 32)
        plansza[2][2] = 88;
    else if(plansza[1][1] == 79 && plansza[0][1] == 79 && plansza[2][1] == 32)
        plansza[2][1] = 88;
    else if(plansza[1][1] == 79 && plansza[0][2] == 79 && plansza[2][0] == 32)
        plansza[2][0] = 88;
    else if(plansza[1][1] == 79 && plansza[1][0] == 79 && plansza[1][2] == 32)
        plansza[1][2] = 88;
    else if(plansza[1][1] == 79 && plansza[1][2] == 79 && plansza[1][0] == 32)
        plansza[1][0] = 88;
    else if(plansza[1][1] == 79 && plansza[2][0] == 79 && plansza[0][2] == 32)
        plansza[0][2] = 88;
    else if(plansza[1][1] == 79 && plansza[2][1] == 79 && plansza[0][1] == 32)
        plansza[0][1] = 88;
    else if(plansza[1][1] == 79 && plansza[2][2] == 79 && plansza[0][0] == 32)
        plansza[0][0] = 88;


    else if(plansza[0][0] == 79 && plansza[0][2] == 79 && plansza[0][1] == 32)
        plansza[0][1] = 88;
    else if(plansza[0][0] == 79 && plansza[0][1] == 79 && plansza[0][2] == 32)
        plansza[0][2] = 88;
    else if(plansza[0][1] == 79 && plansza[0][2] == 79 && plansza[0][0] == 32)
        plansza[0][0] = 88;
    else if(plansza[0][0] == 79 && plansza[2][0] == 79 && plansza[1][0] == 32)
        plansza[1][0] = 88;
    else if(plansza[0][0] == 79 && plansza[1][0] == 79 && plansza[2][0] == 32)
        plansza[2][0] = 88;
    else if(plansza[2][0] == 79 && plansza[1][0] == 79 && plansza[0][0] == 32)
        plansza[0][0] = 88;
    else if(plansza[0][2] == 79 && plansza[1][2] == 79 && plansza[2][2] == 32)
        plansza[2][2] = 88;
    else if(plansza[0][2] == 79 && plansza[2][2] == 79 && plansza[1][2] == 32)
        plansza[1][2] = 88;
    else if(plansza[1][2] == 79 && plansza[2][2] == 79 && plansza[0][2] == 32)
        plansza[0][2] = 88;
    else if(plansza[2][0] == 79 && plansza[2][1] == 79 && plansza[2][2] == 32)
        plansza[2][2] = 88;
    else if(plansza[2][0] == 79 && plansza[2][2] == 79 && plansza[2][1] == 32)
        plansza[2][1] = 88;
    else if(plansza[2][2] == 79 && plansza[2][1] == 79 && plansza[2][0] == 32)
        plansza[2][0] = 88;

    else if(plansza[0][0] == 32)
        plansza[0][0] = 88;
    else if(plansza[0][2] == 32)
        plansza[0][2] = 88;
    else if(plansza[2][0] == 32)
        plansza[2][0] = 88;
    else if(plansza[2][2] == 32)
        plansza[2][2] = 88;

    else
    {
        do
        {
            x = rand()%3;
            y = rand()%3;
            if(plansza[x][y] == 32)
            {
                plansza[x][y] = 88;
                ruch--;
            }
        } while(ruch);
    }
}

int main()
{
    int i, choice, lvl;
    char plansza[3][3];

    srand(time(NULL));

    cleartable(plansza);

    printf("Witaj w grze!\nCo chcesz zrobic?\n");
    do
    {
    printf("1. Nowa gra\n2. Wczytaj gre\n");
    scanf("%d", &choice);
    if(choice>2 || choice<1)
        printf("Wybacz, nie zrozumialem. Wybierz jeszcze raz\n");
    else if(choice == 2)
        odczyt(plansza);

    } while(choice != 1 && choice != 2);

    system("@cls");
    printf("Wybierz poziom trudnosci:\n");
    do
    {
        printf("1. Latwy\n2. Sredni\n");
        scanf("%d", &lvl);
        if(lvl>2 || lvl<1)
            printf("Wybacz, nie zrozumialem. Wybierz jeszcze raz\n");
        else if(lvl == 2)
        {
            system("@cls");
            do
            {
                printtable(plansza);
                playermove(plansza);
                printtable(plansza);
                if(remis(plansza) && winner(plansza))
                {
                    for(i=0; i<3; i++){
                        printf(".");
                        Sleep(350);
                    }
                    mikoai(plansza);
                }
            } while(remis(plansza) && winner(plansza));
            if(remis(plansza) == 0)
            {
                printtable(plansza);
                printf("To jest remis!\nNacisnij dowonly przycisk aby kontynuowac...");
                _getch();
                exit(375);
            }
            else if(winner(plansza))
            {
               printtable(plansza);
                winner(plansza);
                exit(426);
            }

        }
    }while(choice != 1 && choice != 2);

    system("@cls");
    do
    {
        printtable(plansza);
        playermove(plansza);
        printtable(plansza);
        if(remis(plansza) && winner(plansza))
        {
            for(i=0; i<3; i++){
                printf(".");
                Sleep(350);
            }
            randaimove(plansza);
        }
    } while(remis(plansza) && winner(plansza));

    printf("\nDzieki za gre!\n");

    return 0;
}
