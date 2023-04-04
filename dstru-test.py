import itertools

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
Free = set()
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

    # print board
    print()
    for x in board:
        print(x)

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
    print("2 player game")
    print("whoever completes the magic square wins")
    print("magic square = sum of every row is 15 and sum of every column is 15")
    print("if a player completes a row or column and the sum is less than 15, the other player wins")
    # print board
    for x in board:
        print(x)
    print("peg: use integers 1 - 9")
    print("pos: row, column (ex. `1, 1` or `2, 3` or `3, 1` etc)")

    while (1):
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
        while (peg not in P):
            while (peg.isdigit()==False or len(peg)!=1):
                peg = input("input peg: ")
            peg = int(peg)

        pos = (0, 0)
        # user input pos
        while (pos not in S):
            pos = 'a'
            while(len(pos)!=4 or not pos[0].isdigit() or pos[1]!=',' or pos[2]!=' ' or not pos[3].isdigit()):
                pos = input("input pos: ")
            pos = (int(pos[0]), int(pos[3]))

        NextPlayerMove(peg, pos)

if __name__ == "__main__":
    main()