//
//  main.cpp
//  tareaintegradora
//
//  Created by Jose Antonio on 14/11/17.
//  Copyright © 2017 Jose Antonio. All rights reserved.
//

#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <string>
/*
 juego que selecciona casilla y depende la direccion que se le de se mueve a e=dos casillas en esa direccion si
 esta libre ese espacio y justo una casilla de la seleccionada en la direccion hay otra ficha
 */
using namespace std;
//Funcion para ver si gano, regresa true si gano, flase si no
bool gano(char mat[4][4])
{
    int cont = 0;
    // for para recorrer el arreglo y contar el numero de $
    for(int row =0 ; row < 4 ; row ++)
    {
        for(int col = 0 ; col < 4 ; col ++)
        {
            if(mat[row][col] == '$')
                cont ++;
        }
    }
    if(cont <= 1 ) //Si es menor o igual a 1, significa que gano por que no se encontraron mas de un $
    {
        return true;
    }
    else //De lo contrario perdio, regresar false
    {
        return false;
    }
}
bool mover(char mat[4][4],char donde,int row, int col)
{
    switch(donde) //Switch para ver a donde se desea mover
    {
        case 'a': //Izquierda
            if((mat[row][col - 1] == '$') && (mat[row][col - 2] == ' '))
            {
                mat[row][col] = ' ';
                mat[row][col - 1] = ' ';
                mat[row][col - 2] = '$';
                return true;
            }
            else if((col - 1) >= 0 && mat[row][col -1] == ' ')
            {
                mat[row][col] = ' ';
                mat[row][col -1] = '$';
                return true;
            }
            else
                return false;
            break;
        case 'd': //Derecha
            if((mat[row][col + 1] == '$') && (mat[row][col + 2] == ' '))
            {
                mat[row][col] = ' ';
                mat[row][col + 1] = ' ';
                mat[row][col + 2] = '$';
                return true;
            }
            else if((col + 1) <= 4 && mat[row][col + 1] == ' ')
            {
                mat[row][col] = ' ';
                mat[row][col +1] = '$';
                return true;
            }
            else
                return false;
            break;
        case 's': //Abajo
            if((mat[row +1][col] == '$') && (mat[row + 2][col] == ' '))
            {
                mat[row][col] = ' ';
                mat[row+1][col] = ' ';
                mat[row+2][col] = '$';
                return true;
            }
            else if((row + 1) <= 4 && mat[row+1][col] == ' ')
            {
                mat[row][col] = ' ';
                mat[row+1][col] = '$';
                return true;
            }
            else
                return false;
            break;
            
        case 'w': // Arriba
            if((mat[row - 1][col] == '$') && (mat[row - 2][col] == ' '))
            {
                mat[row][col] = ' ';
                mat[row-1][col] = ' ';
                mat[row-2][col] = '$';
                return true;
            }
            else if((row - 1) >= 0 && mat[row-1][col] == ' ')
            {
                mat[row][col] = ' ';
                mat[row-1][col] = '$';
                return true;
            }
            else
                return false;
            break;
    }
    return false;
}

//Desplegar mat
void desplegarMat(char mat[4][4])
{
    int cont = 1;
    //Recorrer toda la matriz y desplegarla con el contador de casilla que es cont
    for(int row = 0; row < 4; row ++)
    {
        for(int col = 0 ; col < 4; col ++)
        {
            cout << cont << "[" << mat[row][col] << "]\t";
            cont ++;
        }
        cout << endl;
    }
}
//Funcion para llenar meatrix random
void llenarMat(char mat[4][4])
{
    //Llenar con espacios
    for(int row = 0; row < 4; row ++)
    {
        for(int col = 0; col < 4; col ++)
        {
            mat[row][col] = ' ';
        }
    }
    int col = 0, row = 0;
    //For para recorrer y llenar la matriz con $ random
    srand(time(NULL));
    for(int i = 0; i < 13 ; i ++)
    {
        col = rand() % 4;
        row = rand() % 4;
        if(mat[row][col] == '$')
        {
            i --;
        }
        else
        {
            mat[row][col] = '$';
        }
        
    }
}
int main()
{
    //Declaracion de variables
    char mat[4][4];
    char seguir, donde;
    int casilla ;
    //Declarar matriz con cordenadas de matrix con datos
    int pos[16][2] =
    {
        {0,0},
        {0,1},
        {0,2},
        {0,3},
        {1,0},
        {1,1},
        {1,2},
        {1,3},
        {2,0},
        {2,1},
        {2,2},
        {2,3},
        {3,0},
        {3,1},
        {3,2},
        {3,3},
    };
    //llenar la matriz
    llenarMat(mat);
    //Desplegar matriz llamando a la funcion
    desplegarMat(mat);
    do //Do para no salir, amenos que el usuario lo quiera o que se gane el juego
    {
        //Preguntar siguinte movimiento
        cout << "Casilla-> " ;
        cin >> casilla;
        if(casilla < 17 && casilla > 0 && mat[pos[casilla - 1][0]][pos[casilla - 1][1]] == '$') //Condicion para verificar que la casilla es valida y que no tenga un $
        {
            cout << "(a - iz; s - aba; w -arr; d - der)"; //Desplegar mensaje
            cin >> donde;
            donde = tolower(donde); //Pasar a minusculas por si se puso una mayuscula
            if(!mover(mat,donde,pos[casilla - 1][0],pos[casilla - 1][1])) // condicion, si la funcion de mover regresa false, no se puede mover
            {
                cout << "Error" << endl;
            }
            if(gano(mat)){ // se llama a la funcion ganar para ver si se gano la partida
                cout << "Ganaste!!!" << endl;
                break;
            }
        }
        else //Si no entra la condicion, despliega que no existe
        {
            cout << "Error, la casilla no existe o no tiene valor para mover" << endl;
        }
        desplegarMat(mat); //Llamar funcion para desplegar matriz
        cout << "Seguir (s/n) -> " ; //Preguntar si se quiere seguir
        cin >> seguir;
        seguir = tolower(seguir); //Pasar a minusculas por si se puso una mayuscula
    }
    while(seguir != 'n');
    return 0;
}
