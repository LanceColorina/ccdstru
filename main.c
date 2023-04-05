#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} tuple;

void printboard(int board[][3])
{
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 3; j++) 
            printf("[%d]", board[i][j]);
        printf("\n");
    }
}

tuple map (int num)
{
    tuple cell;
    if (num == 1) {
        cell.x = 0;
        cell.y = 0;
    } else if (num == 2) {
        cell.x = 0;
        cell.y = 1;
    } else if (num == 3) {
        cell.x = 0;
        cell.y = 2;
    } else if (num == 4) {
        cell.x = 1;
        cell.y = 0;
    } else if (num == 5) {
        cell.x = 1;
        cell.y = 1;
    } else if (num == 6) {
        cell.x = 1;
        cell.y = 2;
    } else if (num == 7) {
        cell.x = 2;
        cell.y = 0;
    } else if (num == 8) {
        cell.x = 2;
        cell.y = 1;
    } else if (num == 9) {
        cell.x = 2;
        cell.y = 2;
    }
    return cell;
}

int main()
{
    srand(time(NULL));

    // use of sets A, S, T, M, B, L, C, R, all of this represents a 3x3 grid
    // S = all the cells on the 3x3 grid (A x A)
    // T, M, B = coordinates of the rows 
    // L, C, R = coordinates of the columns
    // One, Two, Three, Four, Five, Six represents the pegs in each row/column (One, Two, Three, Four, Five, Six ⊆ P)
    // One = pegs in row T (1st row)
    // Two = pegs in row M (2nd row)
    // Three = pegs in row B (3rd row)
    // Four = pegs in column L (1st column)
    // Five = pegs in column C (2nd column)
    // Six = pegs in column R (3rd column)
    // Occ and Free are also represented by game board, you can SEE which spaces are occupied and free
    // All of this can be represented by the game board
    int board[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};    // One, Two, Three, Four, Five, Six are initalized to empty set aka nothing in the game board
    bool turn = true;                                       // turn is an element of set V which is {true, false}, initialized to true
    int peg = 0, takenPegLen = 0, i, takenPosLen = 0;
    tuple pos;
    bool valid = true, over1 = false, over2 = false; // over = over1 || over2, separating into 2 just makes it easier to determine which over condition was met
    int takenPeg[9];
    tuple takenPos[9];

    int given[][3] = {{1, 6, 8}, {2, 4, 9}, {3, 5, 7}, {9, 5, 6}, {4, 8, 7}, {3, 7, 6}}; // possible given values

    // set F = any 3 cells on grid excluding diagonals
    // used for given values (like in sudoku)
    int rand1, rand2, rand3;
    do {
        rand1 = rand() % 9 + 1;
        do {
            rand2 = rand() % 9 + 1; 
        } while(rand2 == rand1);
        do {
            rand3 = rand() % 9 + 1;
        } while (rand3 == rand2 || rand3 == rand1); 
    } while ((rand1 % 2 == 1 && rand2 % 2 == 1 && rand3 % 2 == 1) && 
            (((abs(rand1-rand2) == 8 ? 4 : abs(rand1-rand2)) == 4 && (abs(rand1-rand3) == 8 ? 4 : abs(rand1-rand3)) == 4 && (abs(rand2-rand3) == 8 ? 4 : abs(rand2-rand3)) == 4) ||
            ((abs(rand1-rand2) == 4 ? 2 : abs(rand1-rand2)) == 2 && (abs(rand1-rand3) == 4 ? 2 : abs(rand1-rand3)) == 2 && (abs(rand2-rand3) == 4 ? 2 : abs(rand2-rand3)) == 2)));

    int givenIndex = rand() % 6;
    board[map(rand1).x][map(rand1).y] = given[givenIndex][0];
    board[map(rand2).x][map(rand2).y] = given[givenIndex][1];
    board[map(rand3).x][map(rand3).y] = given[givenIndex][2];
    takenPeg[0] = rand1;    // takenPeg represents which pegs are already on the game board
    takenPeg[1] = rand2;
    takenPeg[2] = rand3;
    takenPegLen += 3;
    takenPos[0] = map(rand1);   // takenPos represents which cells are already taken on the game board
    takenPos[1] = map(rand2);
    takenPos[2] = map(rand3);
    takenPosLen += 3;

    // game loop
    while (1) {
        system("cls");
        printf("Magic Squre: 2 player game\n");
        printf("Whoever completes the magic square wins\n");
        printf("Magic square = sum of every row is 15 and sum of every column is 15\n");
        printf("If a player completes a row or column and the sum is less than 15, the other player wins\n");
        printf("Choose from integers 1-9, no duplicates allowed\n\n");
        printboard(board);

        if (turn) printf("\nA TURN\n");
        else printf("\nB TURN\n");

        // get peg
        do {
            fflush(stdin);
            valid = true;
            printf("Enter peg (1-9): ");    // P set is all pegs (pegs are integers from 1-9)
            scanf("%d", &peg);              // Peg = P − (One ∪ Two ∪ Three ∪ Four ∪ Five ∪ Six) means that Peg is the set of all pegs that aren't on the game board yet 
            for (i = 0; i < takenPegLen; i++) // and peg is an element of Peg, user inputs what peg they wanna place on the board
                if (peg == takenPeg[i])
                    valid = false;
        } while (!valid || peg < 1 || peg > 9);
        takenPeg[takenPegLen] = peg;
        takenPegLen++;

        // get pos
        do {
            fflush(stdin);
            valid = true;
            printf("Enter row (1-3): ");
            scanf("%d", &pos.x);
            fflush(stdin);
            printf("Enter column (1-3): "); 
            scanf("%d", &pos.y);
            for (i = 0; i < takenPosLen; i++)
                if (takenPos[i].x == pos.x && takenPos[i].y == pos.y)
                    valid = false;
        } while (!valid || pos.x < 1 || pos.x > 3 || pos.y < 1 || pos.y > 3); // pos is a subset of S meaning it should be a valid position on the game board
        takenPos[takenPosLen] = pos;
        takenPosLen++;

        board[pos.x-1][pos.y-1] = peg;  // add to board
        // NextPlayerMove = an overcomplicated way of adding pegs to the board
        // The contents can be summarized without the use of a separate function
        // Basically if peg is a valid peg from 1-9 (peg ∈ Peg) and the position the user inputted is a free space (pos ∈ Free),
        // add the peg to the respective row and column (One, Two, Three, etc.) and add the position to the set of occupied spaces (Occ) 
        // ok = flag to determine if peg and pos is valid
        // next = flag to determine if we can add to the columns
        // the purposes of both ok and next are already taken care of in the input handling

        // over biconditional : conditions for a game over
        // set W used here, each element w in W represents the pegs in a row/column (W = {One} ∪ {Two} ∪ {Three} ∪ {Four} ∪ {Five} ∪ {Six})
        // if any row sum < 15 or if any column sum < 15 and all spaces in line are filled
        for (i = 0; i < 3; i++)
            if ((board[i][0] + board[i][1] + board[i][2] < 15 && board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) ||
            (board[0][i] + board[1][i] + board[2][i] < 15 && board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0))
                over1 = true;
        // if each row == 15 and each column == 15 and all spaces filled
        for (i = 0; i < 3; i++)
            if ((board[i][1] + board[i][2] + board[i][3] == 15 && board[i][1] != 0 && board[i][2] != 0 && board[i][3] != 0) &&
            (board[0][i] + board[1][i] + board[2][i] == 15 && board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0))
                over2 = true;
        // over1 and over2 make it easier to determine which condition was met 

        // GameOver(over) function is simplified
        if (over1 && turn) 
            printf("\nB wins\n");
        if (over1 && !turn)
            printf("\nA wins\n");
        if (over2 && turn)
            printf("\nA wins\n");
        if (over2 && !turn)
            printf("\nB wins\n");
        if (over1 || over2) // over = over1 || over2
            return 0;

        // if not over
        turn = !turn;   
    }
}
