//
//  main.cpp
//  Prueba
//
//  Created by Mike Grimaldo
//

//#include <windows.h>
#include <windows.h>
#include <GL/glut.h>

#include <stdlib.h>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"


#include <iostream>


//variables globales
    int fin;
    char caracter;

    Deck d;     //se inicializa el deck
    Hand dealer;//se inicializa la mano del dealer
    Hand player;//se inicializa la mano del jugador

void elegir(char x);

void deal();
void hit();
void stand();

//void inicializa(Card ha);
//void inicializaDeck(Deck ha);

int main()
{
    fin = 0;
    caracter ='a';
    using namespace std;

    cout << "Bienvenido al Blackjack" << endl;

    // mientras no se presiona ESC o q, el juego continuera. La primera mano siempre se juega

   while(fin == 0)
   {
    cout << "Presiona:   D-Deal   H-Hit     S-Stand  Esc-Salir" << endl;
    cin >> caracter;

    //metodo elegir controla los inputs del jugador
    elegir(caracter);

    }


    cout << "Buen juego" << endl;


    return 0;

}

void elegir(char key)
{

    switch (key)
    {
        case 27 : break;
        case 'Q':
            fin = 1;
           // exit(0);
            break;
        case 'D':
            deal();
            break;
        case 'H':
            hit();
            break;

        case 'S':
            stand();
            break;
        default:
            break;

        }
}

/*
void inicializaDeck(Deck ha)
{
    for(int i = 0; i < 52; i++){
        //ha[i] = Card('z','z');
    }
}

void inicializa(Card ha)
{
        ha.setSuit('z');
        ha.setValue('z');

}
*/

void deal()
{

    //Se reinicializa cada vez que se presione 'D'
    //inicializaDeck(d);

    d.shuffle();                      //se shufflea el deck

    // el jugador recibe 2 Cards y suma el valor de sus Cards
    player.addCard(d.dealCard());
    player.countHand(1);            // el 1 significa que si la Card es As, puede elegir entre 1 u 11
    player.addCard(d.dealCard());
    player.countHand(1);

    // el dealer recibe  2 Cards y suma el valor de sus Cards
    dealer.addCard(d.dealCard());
    dealer.countHand(0);            // el 0 significa que si la Card es As, solo vale 11
    dealer.addCard(d.dealCard());
    dealer.countHand(0);
                                    // Se despliega informacion
    cout << "Información del jugador" << endl;
    cout << player.str() << " : Puntos totales: "<< player.getCountHand() << endl;
    cout << "Información del dealer" << endl;
    cout << dealer.str() << " : Puntos totales: "<< dealer.getCountHand() << endl;

}
void hit()
{
            if(player.getCountHand() < 21)      // Si el Player no tiene mas de 21 puntos, pide una nueva Card
            {
                player.addCard(d.dealCard());
                player.countHand(1);
                cout << "Información del jugador" << endl;
                cout << player.str() << " : Puntos totales: "<< player.getCountHand() << endl;

            }else
            {
                cout << "Tu score  " << player.getCountHand() << " es mayor a 21, PERDISTE" << endl;
            }
}
void stand()
{
    if(player.getCountHand() < 21)      // Si el Player no tiene mas de 21 puntos, el Dealer pide una nueva Card
    {
    while (dealer.getCountHand() < 17)
        {      // si el Dealer tiene menos puntos que el Player Y sus puntos son menores a 17
            dealer.addCard(d.dealCard());
            dealer.countHand(0);
            cout << "Información del dealer" << endl;
            cout << dealer.str() << " : Puntos totales: "<< dealer.getCountHand() << endl;
        }

    if(dealer.getCountHand() > 21)
        {           //si los puntos del dealer sobrepasa 21, player gana
            cout << "El score  del Dealer es " << dealer.getCountHand() << ", GANASTE!" << endl;
        }
    else if(player.getCountHand() <= dealer.getCountHand())
        {           //si los puntos del dealer  sobrepasan a los puntos del player, dealer gana
            cout << "El dealer tiene " << dealer.getCountHand() << ", PERDISTE!" << endl;
        }
    else
    {           // si los puntos del player sobrepasan los puntos del dealer, player gana
            cout << "Tu score es " << player.getCountHand() << ", GANASTE!" << endl;
    }

    }
    else
    {
        cout << "Tu score  " << player.getCountHand() << " es mayor a 21, PERDISTE" << endl;
    }
}

