// DSTRU MP Simplified
// wala na yung occ na set
// wala na yung one, two, three, four, five, six na set at ginawa na lang col-order traversal at row-order traversal
// wala na yung next na variable

#include <stdio.h>
#include <stdlib.h>
#define P_CARDINALITY 9
#define A_CARDINALITY 3

void printCells(int cells[])
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (cells[i] != 0)
            printf("║ %i ", cells[i]);
        else
            printf("║   ");
    }
    printf("║");
}

// Fancy Grid tiles (box-drawing characters) copied from wikipedia
// needs "chcp 65001" system command to show properly on windows cmd
// Gumamit ako ng ganito sa CCPROG1 MP
void printGrid(int cells[][A_CARDINALITY])
{
    printf("\n     0   1   2");
    printf("\n   ╔═══╦═══╦═══╗\n 0 ");
    printCells(cells[0]);
    printf("\n   ╠═══╬═══╬═══╣\n 1 ");
    printCells(cells[1]);
    printf("\n   ╠═══╬═══╬═══╣\n 2 ");
    printCells(cells[2]);
    printf("\n   ╚═══╩═══╩═══╝\n");
}

// int checkWin(xMove, oMove){}

// since 0 is not in set and you cannot directly delete array elements in C,
// just replace the value of the element to 0 and pretend zero does not exist
// in the universe of discourse
// (tamad vibes)
void splice(int nArr[], int nElement)
{
    int i;
    for (i = 0; i < P_CARDINALITY; i++)
    {
        if (nArr[i] == nElement)
            nArr[i] = 0;
    }
}

int arraySum(int nArr[])
{
    int sum = 0;
    int i;
    for (i = 0; i < A_CARDINALITY; i++)
    {
        if (nArr[i] > 0)
            sum += nArr[i];
    }
    return sum == 15;
}


// Over cond 1: there is a row/column with a size 3 and sum less than 15
int overCond1(int grid[][A_CARDINALITY])
{
    int isCondTrue = 0;

    // Row Order Check. salamat CCPROG2 exam dahil dun ko lang natutunan
    // kung ano yung row order at column order hahahah
    int i = 0, j = 0, nCount, nSum;
    while (i < A_CARDINALITY && !isCondTrue)
    {
        nCount = 0;
        nSum = 0;
        while (j < A_CARDINALITY)
        {
            if (grid[i][j] > 0)
            {
                nCount++;
                nSum += grid[i][j];
            }
            j++;
        }
        if (nCount == 3 && nSum < 15)
            isCondTrue = 1;
        i++;
    }


    if (!isCondTrue)
    {
        i = 0;
        j = 0;
        // Column Order Check
        while (j < A_CARDINALITY && !isCondTrue)
        {
            nCount = 0;
            nSum = 0;
            while (i < A_CARDINALITY)
            {
                if (grid[i][j] > 0)
                {
                    nCount++;
                    nSum += grid[i][j];
                }
                i++;
            }
            if (nCount == 3 && nSum < 15)
                isCondTrue = 1;
            j++;
        }
    }
    return isCondTrue;
}

// Over cond 2: all row/columns have a cardinality of 3 and sum of 15 
int overCond2(int grid[][A_CARDINALITY])
{
    int isCondTrue = 1;

    // Row Order Check. salamat CCPROG2 exam dahil dun ko lang natutunan
    // kung ano yung row order at column order hahahah
    int i = 0, j = 0, nCount, nSum;
    while (i < A_CARDINALITY && !isCondTrue)
    {
        nCount = 0;
        nSum = 0;
        while (j < A_CARDINALITY)
        {
            if (grid[i][j] > 0)
            {
                nCount++;
                nSum += grid[i][j];
            }
            j++;
        }
        if (nCount < 3 || nSum != 15)
            isCondTrue = 0;
        i++;
    }


    if (isCondTrue)
    {
        i = 0;
        j = 0;
        // Column Order Check
        while (j < A_CARDINALITY && !isCondTrue)
        {
            nCount = 0;
            nSum = 0;
            while (i < A_CARDINALITY)
            {
                if (grid[i][j] > 0)
                {
                    nCount++;
                    nSum += grid[i][j];
                }
                i++;
            }
            if (nCount < 3 || nSum != 15)
                isCondTrue = 0;
            j++;
        }
    }
    return isCondTrue;
}


// Check if any of the rows and columns are full/count to three
int over(int grid[][A_CARDINALITY])
{
    return ( overCond1(grid) || overCond2(grid) );
}

// di ko maintindihan to basta copy paste lang mula sa math
int ok(int nInputPeg, int nInputX, int nInputY, int Peg[], int free[][3])
{
    int cond1 = 0, cond2 = 0;
    int i;
    for (i = 0; i < P_CARDINALITY; i++)
    {
        if (Peg[i] == nInputPeg && nInputPeg > 0)
            cond1 = 1;
    }
    cond2 = (free[nInputX][nInputY] == 0);
    return cond1 && cond2;
}

// debugging
// void printarr(int arr []) {
//     for (int i = 0; i < A_CARDINALITY; i++)
//         printf("%d ", arr[i]);
//     printf("\n");
// }

int main()
{
    system("chcp 65001"); // for Fancy Grid
    int free[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    // int next = 0;
    int turn = 1; // 1 = A turn, 0 = B turn
    char players[] = {'B', 'A'};
    int peg[P_CARDINALITY] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int inputPeg;
    int nInputX, nInputY; // (x, y) Tuple
    printGrid(free);
    while (!over(free))
    {
        printf("%c Turn. Select X and Y Position: ", players[turn]);
        scanf("%d", &nInputX);
        scanf("%d", &nInputY);
        printf("Select Peg: ");
        scanf("%d", &inputPeg);
        if (ok(inputPeg, nInputX, nInputY, peg, free))
        {
            free[nInputX][nInputY] = inputPeg;
            splice(peg, inputPeg);
            turn = !turn;
            printGrid(free);
        }
        else
        {
            printf("Invalid Input!");
        }
    }
    // Gameover
    int nOverCond1 = overCond1(free);
    int nOverCond2 = overCond2(free);
    int result = -1; // 1 = A wins, 0 = B wins, -1 no winner
    if (nOverCond1)
    {
        if (turn)
            result = 0;
        else
            result = 1;        
    }
    else if (nOverCond2)
    {
        if (turn)
            result = 1;
        else
            result = 0; 
    }
    if (result == -1)
    {
        printf("No Winner!");
    }
    else
    {
        printf("%i Wins!", players[result]);
    }
    return 0;
}