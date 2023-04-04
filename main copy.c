#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} tuple;

typedef struct set{
    tuple data;
    set* next;
} set;

// add
void add (set **head, tuple data) {
    set *newItem = malloc(sizeof(set));
    newItem->data = data;
    newItem->next = *head;
    (*head) = newItem;
}

// remove
void remove (set **head, tuple data) {
    // store head node
    set *temp = *head, *prev;

    // if head node contains data
    if (temp != NULL && temp->data.x == data.x && temp->data.y == data.y) {
        *head = temp->next;
        free(temp);
        return;
    }

    // search for data to be deleted
    while (temp != NULL && (temp->data.x != data.x || temp->data.y != data.y)) {
        prev = temp;
        temp = temp->next;
    }

    // if data not present in linked list
    if (temp == NULL)
        return;

    // unlink and free the node
    prev->next = temp->next;
    free(temp);
}

// search
set *search (set *head, tuple data) {
    set *current = head;
    while (current != NULL) {
        if (current->data.x == data.x && current->data.y == data.y) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// free linked list
void freeList (set *head) {
    set *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// applicable sets
int A[3] = {1, 2, 3};
tuple S[] = {{1, 1}, {1, 2}, {1, 3}, {2, 1}, {2, 2}, {2, 3}, {3, 1}, {3, 2}, {3, 3}};
bool V[2] = {true, false};
int P[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
tuple T[] = {{1, 1}, {1, 2}, {1, 3}};
tuple M[] = {{2, 1}, {2, 2}, {2, 3}};
tuple B[] = {{3, 1}, {3, 2}, {3, 3}};
tuple L[] = {{1, 1}, {2, 1}, {3, 1}};
tuple C[] = {{1, 2}, {2, 2}, {3, 2}};
tuple R[] = {{1, 3}, {2, 3}, {3, 3}};
set *F = NULL;

// system variables and initialization 
set *Occ = NULL;
set *Free = NULL;
set *One = NULL;
set *Two = NULL;
set *Three = NULL;
set *Four = NULL;
set *Five = NULL;
set *Six = NULL;
int Peg[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
set *W = NULL;
bool ok = false;
bool turn = true;
bool over = false;
bool next = false;

int main ()
{
    int i;
    int board[3][3];
    printf("2 players game\n");
    printf("whoever completes the magic square wins\n");
    printf("magic square = sum of every row is 15 and sum of every column is 16\n");
    printf("if a player completes a row or column and the sum is less than 15, the other player wins\n");
    for (int x = 0; x < 3; x++) {   // print board
        printf("%d", board[x]);
    }
    printf("peg: use integers 1 - 9\n");
    printf("pos: row, column (ex. `1, 1` or `2, 3` or `3, 1` etc)\n");

    while (1) {
        // system facts
        for (i = 0; i < 9; i++) {
        }

        for (int i = 0; i < SIZE; i++) {
            Free[i] = S[i] - Occ[i];
        }
        for (int i = 0; i < SIZE; i++) {
            Peg[i] = P[i] - One[i] - Two[i] - Three[i] - Four[i] - Five[i] - Six[i];
        }
        for (int i = 0; i < SIZE; i++) {
            W[i] = 0;
        }
        for (int i = 0; i < SIZE; i++) {
            W[i] = One[i];
        }
        for (int i = 0; i < SIZE; i++) {
            W[i] = Two[i];
        }
        for (int i = 0; i < SIZE; i++) {
            W[i] = Three[i];
        }
        for (int i = 0; i < SIZE; i++) {
            W[i] = Four[i];
        }
        for (int i = 0; i < SIZE; i++) {
            W[i] = Five[i];
        }
        for (int i = 0; i < SIZE; i++) {
            W[i] = Six[i];
        }

        bool first = false;
        bool second = true;
        for (int w = 0; w < SIZE; w++) {
            if (strlen(w) == 3 && sum(w) < 15) {
                first = true;
            }
        }
        for (int w = 0; w < SIZE; w++) {
            if (strlen(w) != 3 || sum(w) != 15) {
                second = false;
            }
        }
        over = first || (second && strlen(W) != 0);

        if (GameOver(over)) {
            return 0;
        }
        
        if (turn) printf("\nA TURN\n");
        else printf("\nB TURN\n");

        char peg = 'a';
        return 0;
    
    
    }
}