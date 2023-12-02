#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define struct Node at the top
struct Node {
    int ibp[3][3];
    int father[3][3];
    int ga;
    double fa;
    struct Node* next;
};

// Function prototypes
void updateParent(struct Node* CLOSED, struct Node* OPEN, int newParent[3][3], int parent[3][3], int gtemp);
struct Node* heuristic(struct Node* open, int moves[4][9], int goal[3][3], int gtemp, int initial[3][3], struct Node* closed);

struct Node* createNode(int initial[3][3], int movepos[3][3], double ftemp, int gtemp) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp->ibp[i][j] = initial[i][j];
            temp->father[i][j] = movepos[i][j];
        }
    }
    temp->ga = gtemp;
    temp->fa = ftemp;
    temp->next = NULL;
    return temp;
}

struct Node* insertNode(struct Node* node, int initial[3][3], int movepos[3][3], double ftemp, int gtemp) {
    struct Node* temp = createNode(initial, movepos, ftemp, gtemp);
    if (node == NULL) {
        node = temp;
        node->next = NULL;
    }
    else if (node->fa >= ftemp) {
        temp->next = node;
        node = temp;
    }
    else {
        struct Node* start = node;
        while (start->next != NULL && start->next->fa < ftemp) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
    return node;
}

struct Node* insertClosed(struct Node* node, int initial[3][3], int movepos[3][3], double ftemp, int gtemp) {
    struct Node* temp = createNode(initial, movepos, ftemp, gtemp);
    if (node == NULL) {
        node = temp;
        node->next = NULL;
    }
    else {
        struct Node* start = node;
        while (start->next != NULL) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
    return node;
}

void updateParent(struct Node* CLOSED, struct Node* OPEN, int newParent[3][3], int parent[3][3], int gtemp) {
    struct Node* temp = CLOSED;
    struct Node* temp1 = OPEN;
    while (temp != NULL) {
        if (isEqual(temp->ibp, parent)) {
            while (temp1 != NULL) {
                temp1->fa = temp1->fa - temp1->ga + gtemp + 1;
                temp1->ga = gtemp + 1;
                temp1 = temp1->next;
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    temp->ibp[i][j] = newParent[i][j];
                }
            }
            temp->fa = temp->fa - temp->ga + gtemp;
            temp->ga = gtemp;
        }
        temp = temp->next;
    }
}

double findHeuristicValue(int goal[3][3], int boardpos[3][3]) {
    double heuristicval = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            heuristicval += pow(goal[i][j] - boardpos[i][j], 2);
        }
    }
    return sqrt(heuristicval);
}

struct Node* heuristic(struct Node* open, int moves[4][9], int goal[3][3], int gtemp, int initial[3][3], struct Node* closed) {
    int di = 0;
    while (di < 4) {
        int dj = 0;
        int arr[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                arr[i][j] = moves[di][dj];
                dj++;
            }
        }
        double ftemp = findHeuristicValue(goal, arr) + gtemp;
        int check = 0;
        struct Node* temp = open;
        struct Node* temp1 = closed;
        if (temp == NULL && temp1 == NULL) {
            open = insertNode(open, initial, arr, ftemp, gtemp);
        }
        else {
            while (temp != NULL) {
                if (isEqual(temp->father, arr) == 1) {
                    if (temp->fa > ftemp) {
                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                temp->ibp[i][j] = initial[i][j];
                            }
                        }
                        temp->fa = ftemp;
                        temp->ga = gtemp;
                    }
                    check = 1;
                    break;
                }
                temp = temp->next;
            }
            if (check == 0) {
                while (temp1 != NULL) {
                    if (isEqual(temp1->father, arr) == 1) {
                        updateParent(closed, open, initial, temp1->ibp, gtemp);
                        check = 1;
                        break;
                    }
                    temp1 = temp1->next;
                }
            }
            if (check == 0) {
                open = insertNode(open, initial, arr, ftemp, gtemp);
            }
        }
        di++;
    }
    return open;
}

void findPosition(int i, int j, int arr[4][2]) {
    int k = 0;
    if ((3 > (i - 1) && i - 1 >= 0) && (3 > j && j >= 0)) {
        arr[k][0] = i - 1;
        arr[k][1] = j;
        k++;
    }
    if (3 > i + 1 && i + 1 >= 0 && 3 > j && j >= 0) {
        arr[k][0] = i + 1;
        arr[k][1] = j;
        k++;
    }
    if ((3 > i && i >= 0) && (3 > (j + 1) && j + 1 >= 0)) {
        arr[k][0] = i;
        arr[k][1] = j + 1;
        k++;
    }
    if ((3 > i && i >= 0) && (3 > j - 1 && j - 1 >= 0)) {
        arr[k][0] = i;
        arr[k][1] = j - 1;
        k++;
    }
}

void printQueue(struct Node* node) {
    if (node == NULL) {
        printf("\nList is empty");
        return;
    }
    struct Node* ptr = node;
    while (ptr != NULL) {
        printf("\nf(A): %lf", ptr->fa);
        printf("\tg(A): %d", ptr->ga);
        printf("\nParent Node\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", ptr->ibp[i][j]);
            }
            printf("\n");
        }
        printf("Child Node\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", ptr->father[i][j]);
            }
            printf("\n");
        }
        ptr = ptr->next;
    }
}

void printPath(struct Node* CLOSED, int initial[3][3], int goal[3][3]) {
    if (isEqual(initial, goal) == 1) {
        printf("Initial Node: f(A): %lf and g(A): %d\n", CLOSED->fa, CLOSED->ga);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", initial[i][j]);
            }
            printf("\n");
        }
        return;
    }
    struct Node* temp = CLOSED;
    while (temp != NULL && temp->next != NULL && isEqual(temp->father, goal) == 0) {
        temp = temp->next;
    }
    if (temp != NULL) {
        printf("Node: f(A): %lf and g(A): %d\n", temp->fa, temp->ga);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", temp->father[i][j]);
            }
            printf("\n");
        }
        printPath(CLOSED, initial, temp->ibp);
    }
}

int main() {
    int board[3][3], goal[3][3], x = 0, y = 0, ga = 0;
    printf("Enter Initial state: \n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }
    printf("Enter Goal state: \n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &goal[i][j]);
        }
    }
    struct Node* OPEN = NULL;
    int a[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
    OPEN = insertNode(OPEN, a, board, findHeuristicValue(goal, board) + ga, ga);
    struct Node* CLOSED = NULL;
    int arr[4][2];
    int flag = 0;
    while (OPEN != NULL) {
        struct Node* current = OPEN;
        OPEN = OPEN->next;
        current->next = NULL;
        CLOSED = insertClosed(CLOSED, current->ibp, current->father, current->fa, current->ga);
        if (current->fa - current->ga == 0) {
            flag = 1;
            break;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->father[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }
        storePosition(x, y, arr, current->father);
        OPEN = heuristic(OPEN, arr, goal, current->ga + 1, current->father, CLOSED);
    }
    if (flag == 0) {
        printf("Goal state can not be reached!\n");
    }
    else {
        printf("\nOPEN Linked List\n");
        printQueue(OPEN);
        printf("\nCLOSED Linked List\n");
        printQueue(CLOSED);
        printf("\nPath {from goal to initial state}\n");
        printPath(CLOSED, CLOSED->father, goal);
    }

    return 0;
}
