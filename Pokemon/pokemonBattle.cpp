/* Name: Bria Weisblat
Date: 12/02/2022
Section: 4
Assignment: Homework 7- Problem 2- Pokemon Battle
Due Date: 12/02/2022
About this project: This is a program that simulates a Pokemon battle based on information/statistics
stored in two files.
Assumptions: Assume the smaller chunks of information are tab seperated on each line and that each new
line represents a new chunk of information starting. Assume that a fainted Pokemon will not attack anymore.

All work below was performed by Bria Weisblat */


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Move
{
    char name[50];
    int moveDamage;
};

struct Pokemon
{
    char name[50];
    char type[50];
    int hitPoints, defenceRating;
    bool isAwake;
    char moveName[50];

};

int main() {

    ifstream pokemonFile;
    ifstream sessionFile;

    pokemonFile.open("pokemon.txt");
    sessionFile.open("session.txt");

    // Creates a variable for the number of moves
    int M;
    // Reads in the first number in the pokemon.txt file and assigns it to M
    pokemonFile >> M;
    // Ignores the newline after the number
    pokemonFile.ignore(1);

    // Creates a pointer of the move type and sets it equal to a dynamic array
    Move * movePtr = new Move [M];


    // For the total number of moves
    for (int i=0; i < M; i++){
        // Reads in the name of an attack until a tab character
        pokemonFile.getline(movePtr[i].name, 50, '\t');
        // Reads in move damage until a whitespace character
        pokemonFile >> movePtr[i].moveDamage;
        // Ignores the newline after the damage
        pokemonFile.ignore(1);
    }

    // Creates a variable for the number of Pokemon
    int N;
    // Reads in the nexy number in the pokemon.txt file and assigns it to N
    pokemonFile >> N;
    // Ignores the newline after the number
    pokemonFile.ignore(1);

    // All Pokemon are awake before the battle begins
    int numAwake = N;


    // Creates a pointer of the Pokemon type and sets it equal to a dynamic array
    Pokemon * pokemonPtr = new Pokemon [N];

    for (int i=0; i < N; i++){
        // Reads in the name of a Pokemon until a tab character
        pokemonFile.getline(pokemonPtr[i].name, 50, '\t');
        // Reads in the Pokemon type until a tab character
        pokemonFile.getline(pokemonPtr[i].type, 50, '\t');
        // Reads in hit points until a whitespace character
        pokemonFile >> pokemonPtr[i].hitPoints;
        // Ignores the tab after the damage
        pokemonFile.ignore(1);
        // Reads in the defence rating until a whitespace character
        pokemonFile >> pokemonPtr[i].defenceRating;
        // Ignores the tab after the defence rating
        pokemonFile.ignore(1);
        // Reads in the move name until a newline character
        pokemonFile.getline(pokemonPtr[i].moveName, 50, '\n');
        // Set isAwake true
        pokemonPtr[i].isAwake = true;
    }

    // Creates a variable for the number of attacks
    int K;
    // Reads in the first number in the session.txt file and assigns it to K
    sessionFile >> K;
    // Ignores the newline after the number
    sessionFile.ignore(1);


    for (int i=0; i < K; i++){
        char player1[50];
        char attackName[50];
        char player2[50];
        int attackRating;
        // Reads in the name of the first Pokemon until a tab character
        sessionFile.getline(player1, 50, '\t');
        // Reads in the attack name until a tab character
        sessionFile.getline(attackName, 50, '\t');
        // Reads in the name of the second Pokemon until a tab character
        sessionFile.getline(player2, 50, '\t');
        // Reads in the attack rating until a whitespace character
        sessionFile >> attackRating;
        // Ignores the tab after the attack rating
        sessionFile.ignore(1);

        int defenceRating;
        int defenderIndex;
        for (int j=0; j < N; j++) {
            // Find player 2 and their defence rating
            if ((strcmp(player2, pokemonPtr[j].name) ) == 0) {
                defenceRating = pokemonPtr[j].defenceRating;
                defenderIndex = j;
            }
        }

        int attackDamage;
        for (int j=0; j < M; j++) {
            // Find the attack damage of player 1
            if ((strcmp(attackName, movePtr[j].name) ) == 0)
                attackDamage = movePtr[j].moveDamage;
        }


        for (int j=0; j < N; j++) {
            // Check if the move used is the signature move of the pokemon using it
            // Check if the attack rating (player 1) is greater than or equal to the defence rating (player 2)
            if (  ((strcmp(attackName, pokemonPtr[j].moveName) ) == 0) && ((strcmp(player1, pokemonPtr[j].name) )== 0) && (attackRating >= defenceRating)){
                pokemonPtr[defenderIndex].hitPoints -= attackDamage;
                // If player 2's hit points drops below 0, it becomes unconscious
                if (pokemonPtr[defenderIndex].hitPoints < 0) {
                    pokemonPtr[defenderIndex].isAwake = false;
                    cout << player1 << " attacked " << player2 << " It was super effective." << endl;
                    numAwake--;
                }
            }

        }
    }

    ofstream healthyPokemon;

    healthyPokemon.open("healthy.txt");


   // Dynamic array that sorts the Pokemon
    Pokemon *sort = new Pokemon [numAwake];
    int a = 0;
    // Stores the pokemon that are awake
    for (int i=0; i < N; i++) {
        if (pokemonPtr[i].isAwake) {
            sort[a] = pokemonPtr[i];
            a++;
        }
    }

    // Sorts te conscious pokemon by the amount of hp they have left in descending order
    for (int i=1; i < numAwake; i++) {
        Pokemon x = sort[i];
        int j = i -1;
        while (j >= 0 && sort[j].hitPoints > x.hitPoints) {
            sort[j + 1] = sort[j];
            j -= 1;
        }
        sort[j+1] = x;
    }

    // Prints the array so that the pokemon display in ascending order based on their hp
    for (int i=numAwake-1; i >= 0; i--) {
        healthyPokemon << sort[i].name << '\t' << sort[i].hitPoints << endl;
    }


    healthyPokemon.close();
    pokemonFile.close();
    sessionFile.close();

    delete [] sort;
    delete [] movePtr;
    delete [] pokemonPtr;

    return 0;
}