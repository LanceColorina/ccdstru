import itertools
import random
import os

def powerset(S):
    """
    Returns the power set of set S.
    """
    return itertools.chain.from_iterable(
        itertools.combinations(S, r) for r in range(len(S)+1))


# applicable sets
A = {x for x in range(1, 4)}
S = {(x, y) for x in A for y in A}
V = {True, False}
P = {x for x in range(1, 10)}

T = {(1, y) for y in A}
M = {(2, y) for y in A}
B = {(3, y) for y in A}

L = {(x, 1) for x in A}
C = {(x, 2) for x in A}
R = {(x, 3) for x in A}

F = {frozenset(x) for x in powerset(S) if len(x)==3}
F.remove(frozenset({(1, 1), (2, 2), (3, 3)}))
F.remove(frozenset({(1, 3), (2, 2), (3, 1)}))

# system initialization
ok = False
next = False
turn = True
One = set()
Two = set()
Three = set()
Four = set()
Five = set()
Six = set()
Peg = P

# system variables
Occ = set()
Free = S.difference(Occ)
W = set()
over = False

board = [
    [" ", " ", " "], 
    [" ", " ", " "], 
    [" ", " ", " "]
]

def NextPlayerMove(peg, pos):
    global ok
    global next

    if peg in Peg and pos in Free:
        Occ.add(pos)
        ok = not ok
        board[pos[0]-1][pos[1]-1] = str(peg)

    if ok and pos in T:
        One.add(peg)
        next = not next

    if ok and pos in M:
        Two.add(peg)
        next = not next

    if ok and pos in B:
        Three.add(peg)
        next  = not next

    if ok and next and pos in L: 
        Four.add(peg)
        next = not next
        ok = not ok
    
    if ok and next and pos in C:
        Five.add(peg)
        next = not next
        ok = not ok

    if ok and next and pos in R:
        Six.add(peg)
        next = not next
        ok = not ok

def GameOver(over):
    global turn
    result = ("B wins", "A wins")
    cond1 = True
    cond2 = True

    if over and turn: 
        for w in W:
            if len(w)==3 and sum(w)<15: print(result[0])

    if over and not turn: 
        for w in W:
            if len(w)==3 and sum(w)<15: print(result[1])

    if over and turn: 
        for w in W:
            if len(w)!=3 or sum(w)!=15: 
                cond1 = False
                break
        if cond1 == True:
            print(result[1])

    if over and not turn: 
        for w in W:
            if len(w)!=3 or sum(w)!=15: 
                cond2 = False
                break
        if cond2 == True:
            print(result[0])

    if not over: 
        turn = not turn
        return 0
    return 1

def main():
    global Free
    global Peg
    global W
    global over
    global turn

    given = [[1, 6, 8], [2, 4, 9], [3, 5, 7], [9, 5, 6], [4, 8, 7], [3, 7, 6]]
    f = random.choice(tuple(F))
    a, *_ = f
    _, b, *_ = f
    *_, c = f
    g = random.choice(given)
    NextPlayerMove(g[0], a)
    NextPlayerMove(g[1], b)
    NextPlayerMove(g[2], c)

    while (1):
        os.system("cls")
        print("Magic Square: 2 player game")
        print("Whoever completes the magic square wins")
        print("Magic square = sum of every row is 15 and sum of every column is 15")
        print("If a player completes a row or column and the sum is less than 15, the other player wins\n")
        print("For pegs, use integers 1-9, no duplicates allowed on the board")
        print("For pos, use format `row, column`, ex. 1, 1 = first row, first column")
        
        # system facts
        Free = S.difference(Occ)
        Peg = P.difference(One.union(Two, Three, Four, Five, Six))
        W.clear()
        W.add(frozenset(One))
        W.add(frozenset(Two))
        W.add(frozenset(Three))
        W.add(frozenset(Four))
        W.add(frozenset(Five))
        W.add(frozenset(Six))

        # print board
        print()
        for x in board:
            print(x)

        first = False
        second = True
        for w in W: 
            if len(w)==3 and sum(w)<15:
                first = True
        for w in W:
            if len(w)!=3 or sum(w)!=15:
                second = False
        over = first or (second and len(W) != 0)

        if(GameOver(over)):
            return
        
        if turn: print("\nA TURN")
        else: print("\nB TURN")

        peg = 'a'
        # user input peg
        while (peg not in Peg):
            peg = 'a'
            while (peg.isdigit()==False or len(peg)!=1):
                peg = input("Enput peg (1-9): ")
            peg = int(peg)

        pos = (0, 0)
        # user input pos
        while (pos not in Free):
            pos = 'a'
            while(len(pos)!=4 or not pos[0].isdigit() or pos[1]!=',' or pos[2]!=' ' or not pos[3].isdigit()):
                pos = input("Enter pos (row, column): ")
            pos = (int(pos[0]), int(pos[3]))

        NextPlayerMove(peg, pos)      

if __name__ == "__main__":
    main()