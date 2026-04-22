#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BOOKS    100
#define MAX_TITLE    100
#define MAX_AUTHOR    80
#define MAX_GENRE     50
#define HASH_SIZE     53   
#define MAX_GENRES    10
#define STACK_MAX     20
#define QUEUE_MAX     20
typedef struct {
    int   id;
    char  title[MAX_TITLE];
    char  author[MAX_AUTHOR];
    float price;
    char  genre[MAX_GENRE];
    int   available;   /* 1 = available, 0 = issued */
} Book;
char categories[MAX_GENRES][MAX_GENRE] = {
    "Fiction",     "Non-Fiction", "Science",  "Technology",
    "History",     "Biography",   "Mystery",  "Romance",
    "Fantasy",     "Self-Help"
};
void displayCategories(void) {
    printf("\n╔══ Book Categories (Array) ══════════╗\n");
    for (int i = 0; i < MAX_GENRES; i++)
        printf("  %2d. %s\n", i + 1, categories[i]);
    printf("╚═════════════════════════════════════╝\n");
}
typedef struct SNode {
    Book         book;
    struct SNode *next;
} SNode;
SNode *bookList = NULL;
void SLL_add(Book b) {
    SNode *n = (SNode *)malloc(sizeof(SNode));
    n->book = b;
    n->next = bookList;
    bookList = n;
    printf("  [SLL] Book '%s' (ID:%d) added.\n", b.title, b.id);
}
void SLL_delete(int id) {
    SNode *cur = bookList, *prev = NULL;
    while (cur) {
        if (cur->book.id == id) {
            if (prev) prev->next = cur->next;
            else      bookList   = cur->next;
            free(cur);
            printf("  [SLL] Book ID %d removed.\n", id);
            return;
        }
        prev = cur; cur = cur->next;
    }
    printf("  [SLL] Book ID %d not found.\n", id);
}
void SLL_display(void) {
    SNode *cur = bookList;
    if (!cur) { printf("  Library is empty.\n"); return; }
    printf("\n  %-5s %-32s %-22s %-12s %-8s %s\n",
           "ID","Title","Author","Genre","Price","Status");
    printf("  %-5s %-32s %-22s %-12s %-8s %s\n",
           "----","-----","------","-----","-----","------");
    while (cur) {
        printf("  %-5d %-32s %-22s %-12s %-8.2f %s\n",
               cur->book.id, cur->book.title, cur->book.author,
               cur->book.genre, cur->book.price,
               cur->book.available ? "Available" : "Issued");
        cur = cur->next;
    }
}
typedef struct DNode {
    Book         book;
    struct DNode *prev;
    struct DNode *next;
} DNode;
DNode *dHead = NULL;
void DLL_add(Book b) {
    DNode *n = (DNode *)malloc(sizeof(DNode));
    n->book = b;
    n->prev = NULL;
    n->next = dHead;
    if (dHead) dHead->prev = n;
    dHead = n;
}
void DLL_browse(void) {
    DNode *cur = dHead;
    if (!cur) { printf("  No books to browse.\n"); return; }
    char ch;
    printf("\n  [Browser] Commands: f=forward  b=backward  q=quit\n");
    printf("  ─────────────────────────────────────────────────\n");
    while (1) {
        printf("  ID: %-5d | Title: %-30s | Author: %s\n",
               cur->book.id, cur->book.title, cur->book.author);
        printf("  Navigate [f/b/q]: ");
        scanf(" %c", &ch);
        if      (ch == 'f') { if (cur->next) cur = cur->next; else printf("  (End of list)\n"); }
        else if (ch == 'b') { if (cur->prev) cur = cur->prev; else printf("  (Start of list)\n"); }
        else break;
    }
}
typedef struct {
    int ids[STACK_MAX];
    int top;
} Stack;
Stack recentStack = { .top = -1 };
int  Stack_isEmpty(Stack *s) { return s->top == -1; }
int  Stack_isFull (Stack *s) { return s->top == STACK_MAX - 1; }
void Stack_push(Stack *s, int id) {
    if (Stack_isFull(s)) {           /* circular shift to make room */
        for (int i = 0; i < STACK_MAX - 1; i++) s->ids[i] = s->ids[i + 1];
        s->ids[s->top] = id;
    } else {
        s->ids[++(s->top)] = id;
    }
    printf("  [Stack] Book ID %d pushed (recently viewed).\n", id);
}
int Stack_pop(Stack *s) {
    if (Stack_isEmpty(s)) { printf("  Stack underflow: empty.\n"); return -1; }
    return s->ids[(s->top)--];
}
int Stack_peek(Stack *s) {
    return Stack_isEmpty(s) ? -1 : s->ids[s->top];
}
void Stack_display(Stack *s) {
    if (Stack_isEmpty(s)) { printf("  Recently viewed: (empty)\n"); return; }
    printf("  Recently viewed (TOP → BOTTOM): ");
    for (int i = s->top; i >= 0; i--) printf("[%d] ", s->ids[i]);
    printf("\n");
}
void Stack_reverseString(char *str) {
    int   n = (int)strlen(str);
    char  stk[256];
    int   top = -1;
    for (int i = 0; i < n; i++)  stk[++top] = str[i];
    printf("  Original : %s\n  Reversed : ", str);
    while (top >= 0) printf("%c", stk[top--]);
    printf("\n");
}
int Stack_evalPostfix(char *expr) {
    int stk[128], top = -1;
    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        if (c >= '0' && c <= '9') {
            stk[++top] = c - '0';
        } else if (c == ' ') {
            continue;
        } else {
            if (top < 1) { printf("  Invalid expression.\n"); return 0; }
            int b = stk[top--], a = stk[top--];
            if      (c == '+') stk[++top] = a + b;
            else if (c == '-') stk[++top] = a - b;
            else if (c == '*') stk[++top] = a * b;
            else if (c == '/') stk[++top] = (b != 0) ? a / b : 0;
        }
    }
    return stk[top];
}
typedef struct {
    int data[QUEUE_MAX];
    int front, rear, size;
} Queue;
Queue waitlist = { .front = 0, .rear = -1, .size = 0 };
int  Queue_isEmpty(Queue *q) { return q->size == 0; }
int  Queue_isFull (Queue *q) { return q->size == QUEUE_MAX; }
void Queue_enqueue(Queue *q, int memberId) {
    if (Queue_isFull(q)) { printf("  Waitlist is full!\n"); return; }
    q->rear          = (q->rear + 1) % QUEUE_MAX;
    q->data[q->rear] = memberId;
    q->size++;
    printf("  [Queue] Member %d added to waitlist.\n", memberId);
}
int Queue_dequeue(Queue *q) {
    if (Queue_isEmpty(q)) { printf("  Waitlist is empty.\n"); return -1; }
    int val  = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_MAX;
    q->size--;
    return val;
}
void Queue_display(Queue *q) {
    if (Queue_isEmpty(q)) { printf("  Waitlist: (empty)\n"); return; }
    printf("  Waitlist (FRONT → REAR): ");
    int i = q->front, cnt = q->size;
    while (cnt--) { printf("[%d] ", q->data[i]); i = (i + 1) % QUEUE_MAX; }
    printf("\n");
}
typedef struct BSTNode {
    Book           book;
    struct BSTNode *left, *right;
} BSTNode;
BSTNode *bstRoot = NULL;
BSTNode *BST_insert(BSTNode *root, Book b) {
    if (!root) {
        BSTNode *n = (BSTNode *)malloc(sizeof(BSTNode));
        n->book = b; n->left = n->right = NULL;
        return n;
    }
    if      (b.id < root->book.id) root->left  = BST_insert(root->left,  b);
    else if (b.id > root->book.id) root->right = BST_insert(root->right, b);
    return root;
}
BSTNode *BST_search(BSTNode *root, int id) {
    if (!root || root->book.id == id) return root;
    return (id < root->book.id)
           ? BST_search(root->left,  id)
           : BST_search(root->right, id);
}
void BST_inorder  (BSTNode *r) { if (!r) return; BST_inorder(r->left);   printf("  [%d] %s\n", r->book.id, r->book.title); BST_inorder(r->right);  }
void BST_preorder (BSTNode *r) { if (!r) return; printf("  [%d] %s\n", r->book.id, r->book.title); BST_preorder(r->left);  BST_preorder(r->right); }
void BST_postorder(BSTNode *r) { if (!r) return; BST_postorder(r->left); BST_postorder(r->right); printf("  [%d] %s\n", r->book.id, r->book.title); }
typedef struct HashNode {
    char             key[MAX_TITLE];
    int              bookId;
    struct HashNode *next;        /* chaining */
} HashNode;
HashNode *hashTable[HASH_SIZE];
int hash_fn(const char *key) {
    unsigned long h = 0;
    for (int i = 0; key[i]; i++) h = (h * 31 + (unsigned char)key[i]) % HASH_SIZE;
    return (int)h;
}
void Hash_insert(const char *title, int id) {
    int idx          = hash_fn(title);
    HashNode *n      = (HashNode *)malloc(sizeof(HashNode));
    strncpy(n->key, title, MAX_TITLE - 1);
    n->bookId        = id;
    n->next          = hashTable[idx];
    hashTable[idx]   = n;
}
int Hash_search(const char *title) {
    int idx       = hash_fn(title);
    HashNode *cur = hashTable[idx];
    while (cur) {
        if (strcmp(cur->key, title) == 0) return cur->bookId;
        cur = cur->next;
    }
    return -1;   /* not found */
}
int  copyToArray(Book arr[], int max) {
    SNode *cur = bookList; int n = 0;
    while (cur && n < max) { arr[n++] = cur->book; cur = cur->next; }
    return n;
}
void printBookArray(Book arr[], int n) {
    printf("  %-5s %-32s %-22s\n", "ID", "Title", "Author");
    printf("  %-5s %-32s %-22s\n", "----", "-----", "------");
    for (int i = 0; i < n; i++)
        printf("  %-5d %-32s %-22s\n", arr[i].id, arr[i].title, arr[i].author);
}
static inline void swapBook(Book *a, Book *b) { Book t = *a; *a = *b; *b = t; }
void bubbleSort(Book arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].id > arr[j + 1].id) swapBook(&arr[j], &arr[j + 1]);
}
void selectionSort(Book arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int mn = i;
        for (int j = i + 1; j < n; j++) if (arr[j].id < arr[mn].id) mn = j;
        swapBook(&arr[i], &arr[mn]);
    }
}
void insertionSort(Book arr[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = arr[i]; int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) { arr[j + 1] = arr[j]; j--; }
        arr[j + 1] = key;
    }
}
int partition(Book arr[], int lo, int hi) {
    int pivot = arr[hi].id, i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (arr[j].id <= pivot) { i++; swapBook(&arr[i], &arr[j]); }
    swapBook(&arr[i + 1], &arr[hi]);
    return i + 1;
}
void quickSort(Book arr[], int lo, int hi) {
    if (lo < hi) { int p = partition(arr, lo, hi); quickSort(arr, lo, p - 1); quickSort(arr, p + 1, hi); }
}
void merge(Book arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Book *L = malloc(n1 * sizeof(Book)), *R = malloc(n2 * sizeof(Book));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i].id <= R[j].id) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}
void mergeSort(Book arr[], int l, int r) {
    if (l < r) { int m = (l + r) / 2; mergeSort(arr, l, m); mergeSort(arr, m + 1, r); merge(arr, l, m, r); }
}
void heapify(Book arr[], int n, int i) {
    int lg = i, l = 2*i+1, r = 2*i+2;
    if (l < n && arr[l].id > arr[lg].id) lg = l;
    if (r < n && arr[r].id > arr[lg].id) lg = r;
    if (lg != i) { swapBook(&arr[i], &arr[lg]); heapify(arr, n, lg); }
}
void heapSort(Book arr[], int n) {
    for (int i = n/2-1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n-1;   i > 0;  i--) { swapBook(&arr[0], &arr[i]); heapify(arr, i, 0); }
}
int linearSearch(Book arr[], int n, int id) {
    for (int i = 0; i < n; i++) if (arr[i].id == id) return i;
    return -1;
}
int binarySearch(Book arr[], int n, int id) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if      (arr[mid].id == id) return mid;
        else if (arr[mid].id <  id) lo = mid + 1;
        else                        hi = mid - 1;
    }
    return -1;
}
int adjMatrix[MAX_GENRES][MAX_GENRES];
int gVisited [MAX_GENRES];
void Graph_addEdge(int u, int v) { adjMatrix[u][v] = adjMatrix[v][u] = 1; }
void Graph_DFS(int v, int n) {
    gVisited[v] = 1;
    printf("  → %s\n", categories[v]);
    for (int i = 0; i < n; i++)
        if (adjMatrix[v][i] && !gVisited[i]) Graph_DFS(i, n);
}
void Graph_BFS(int start, int n) {
    int q[MAX_GENRES], vis[MAX_GENRES] = {0};
    int front = 0, rear = -1;
    q[++rear] = start; vis[start] = 1;
    printf("  BFS Genre Traversal:\n");
    while (front <= rear) {
        int v = q[front++];
        printf("  → %s\n", categories[v]);
        for (int i = 0; i < n; i++)
            if (adjMatrix[v][i] && !vis[i]) { vis[i] = 1; q[++rear] = i; }
    }
}
void Graph_setup(void) {
    memset(adjMatrix, 0, sizeof(adjMatrix));
    Graph_addEdge(0, 6);   
    Graph_addEdge(0, 8);
    Graph_addEdge(6, 7);  
    Graph_addEdge(2, 3);  
    Graph_addEdge(4, 5); 
    Graph_addEdge(1, 4);  
    Graph_addEdge(1, 9);   
    Graph_addEdge(9, 5);   
}
Book sampleBooks[] = {
    {101, "The Great Gatsby",           "F. Scott Fitzgerald",  299.0f, "Fiction",     1},
    {102, "Clean Code",                 "Robert C. Martin",     599.0f, "Technology",  1},
    {103, "Sapiens",                    "Yuval Noah Harari",    499.0f, "History",     1},
    {104, "Murder on the Orient Express","Agatha Christie",      349.0f, "Mystery",     0},
    {105, "Harry Potter & Sorcerer's Stone","J.K. Rowling",     399.0f, "Fantasy",     1},
    {106, "A Brief History of Time",    "Stephen Hawking",      450.0f, "Science",     1},
    {107, "Atomic Habits",              "James Clear",          379.0f, "Self-Help",   1},
};
void loadSampleData(void) {
    int n = (int)(sizeof(sampleBooks) / sizeof(Book));
    for (int i = 0; i < n; i++) {
        SLL_add(sampleBooks[i]);
        DLL_add(sampleBooks[i]);
        bstRoot = BST_insert(bstRoot, sampleBooks[i]);
        Hash_insert(sampleBooks[i].title, sampleBooks[i].id);
    }
    Graph_setup();
    printf("\n  %d sample books loaded.\n", n);
}
void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void printBanner(void) {
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════╗\n");
    printf("  ║         LIBRARY BOOK MANAGEMENT SYSTEM              ║\n");
    printf("  ║     Mini Project — Data Structures & Algorithms     ║\n");
    printf("  ╚══════════════════════════════════════════════════════╝\n");
}
void printMenu(void) {
    printf("\n  ┌─────────────────────────── MENU ───────────────────────────┐\n");
    printf("  │  1.  Add Book                (Linked List + BST + Hash)    │\n");
    printf("  │  2.  Delete Book             (Linked List)                 │\n");
    printf("  │  3.  Display All Books       (Singly Linked List)          │\n");
    printf("  │  4.  Browse Books            (Doubly Linked List)          │\n");
    printf("  │  5.  Search by ID            (Binary Search Tree)          │\n");
    printf("  │  6.  Search by Title         (Hash Table)                  │\n");
    printf("  │  7.  Recently Viewed Books   (Stack ADT)                   │\n");
    printf("  │  8.  Waitlist Management     (Queue ADT)                   │\n");
    printf("  │  9.  Sort Books              (6 Sorting Algorithms)        │\n");
    printf("  │  10. Search by ID            (Linear / Binary Search)      │\n");
    printf("  │  11. BST Traversals          (Recursion)                   │\n");
    printf("  │  12. Genre Recommendations   (Graph DFS / BFS)             │\n");
    printf("  │  13. Stack Applications      (String Reverse / Postfix)    │\n");
    printf("  │  14. Display Categories      (Array)                       │\n");
    printf("  │   0. Exit                                                  │\n");
    printf("  └────────────────────────────────────────────────────────────┘\n");
    printf("  Choice: ");
}
int main(void) {
    memset(hashTable, 0, sizeof(hashTable));
    printBanner();
    printf("\n  Loading sample data ...\n");
    loadSampleData();
    int choice;
    do {
        printMenu();
        if (scanf("%d", &choice) != 1) { clearInput(); continue; }
        clearInput();
        switch (choice) {
        case 1: {
            Book b;
            printf("  Book ID   : "); scanf("%d", &b.id); clearInput();
            printf("  Title     : "); fgets(b.title,  MAX_TITLE,  stdin); b.title [strcspn(b.title,  "\n")] = '\0';
            printf("  Author    : "); fgets(b.author, MAX_AUTHOR, stdin); b.author[strcspn(b.author, "\n")] = '\0';
            printf("  Genre     : "); fgets(b.genre,  MAX_GENRE,  stdin); b.genre [strcspn(b.genre,  "\n")] = '\0';
            printf("  Price     : "); scanf("%f", &b.price); clearInput();
            b.available = 1;
            SLL_add(b);
            DLL_add(b);
            bstRoot = BST_insert(bstRoot, b);
            Hash_insert(b.title, b.id);
            break;
        }
        case 2: {
            int id;
            printf("  Book ID to delete: "); scanf("%d", &id);
            SLL_delete(id);
            break;
        }
        case 3:
            SLL_display();
            break;
        case 4:
            DLL_browse();
            break;
        case 5: {
            int id;
            printf("  Enter Book ID to search (BST): "); scanf("%d", &id);
            BSTNode *res = BST_search(bstRoot, id);
            if (res) {
                printf("\n  ✔ Found:\n");
                printf("  ID: %d | Title: %s | Author: %s | Genre: %s | Available: %s\n",
                       res->book.id, res->book.title, res->book.author,
                       res->book.genre, res->book.available ? "Yes" : "No");
                Stack_push(&recentStack, id);
            } else {
                printf("  ✘ Book ID %d not found in BST.\n", id);
            }
            break;
        }
        case 6: {
            char title[MAX_TITLE];
            printf("  Enter exact book title: "); fgets(title, MAX_TITLE, stdin); title[strcspn(title, "\n")] = '\0';
            int id = Hash_search(title);
            if (id != -1) printf("  ✔ Hash found: '%s' → Book ID: %d\n", title, id);
            else          printf("  ✘ Title '%s' not found in hash table.\n", title);
            break;
        }
        case 7: {
            Stack_display(&recentStack);
            printf("  1. Peek (last viewed)   2. Pop from stack\n");
            printf("  Choice: ");
            int sub; scanf("%d", &sub);
            if      (sub == 1) { int id = Stack_peek(&recentStack); if (id != -1) printf("  Last viewed Book ID: %d\n", id); }
            else if (sub == 2) { int id = Stack_pop (&recentStack); if (id != -1) printf("  Popped Book ID: %d\n", id); }
            break;
        }
        case 8: {
            Queue_display(&waitlist);
            printf("  1. Enqueue (add to waitlist)   2. Dequeue (serve next member)\n");
            printf("  Choice: ");
            int sub; scanf("%d", &sub);
            if (sub == 1) {
                int mid; printf("  Member ID: "); scanf("%d", &mid);
                Queue_enqueue(&waitlist, mid);
            } else if (sub == 2) {
                int mid = Queue_dequeue(&waitlist);
                if (mid != -1) printf("  Serving Member ID: %d\n", mid);
            }
            break;
        }
        case 9: {
            Book arr[MAX_BOOKS];
            int  n = copyToArray(arr, MAX_BOOKS);
            if (n == 0) { printf("  No books to sort.\n"); break; }
            printf("\n  Sorting Algorithms:\n");
            printf("  1. Bubble Sort     O(n²)\n");
            printf("  2. Selection Sort  O(n²)\n");
            printf("  3. Insertion Sort  O(n²)\n");
            printf("  4. Quick Sort      O(n log n) avg\n");
            printf("  5. Merge Sort      O(n log n)\n");
            printf("  6. Heap Sort       O(n log n)\n");
            printf("  Choice: ");
            int sub; scanf("%d", &sub);
            const char *name = "Sort";
            switch (sub) {
                case 1: bubbleSort    (arr, n);      name = "Bubble Sort";    break;
                case 2: selectionSort (arr, n);      name = "Selection Sort"; break;
                case 3: insertionSort (arr, n);      name = "Insertion Sort"; break;
                case 4: quickSort     (arr, 0, n-1); name = "Quick Sort";     break;
                case 5: mergeSort     (arr, 0, n-1); name = "Merge Sort";     break;
                case 6: heapSort      (arr, n);      name = "Heap Sort";      break;
                default: printf("  Invalid.\n"); break;
            }
            if (sub >= 1 && sub <= 6) {
                printf("\n  [Result: %s — sorted by Book ID ascending]\n", name);
                printBookArray(arr, n);
            }
            break;
        }
        case 10: {
            Book arr[MAX_BOOKS];
            int  n = copyToArray(arr, MAX_BOOKS);
            if (n == 0) { printf("  No books.\n"); break; }
            int id;
            printf("  Enter Book ID to search: "); scanf("%d", &id);

            /* Linear Search */
            int idx = linearSearch(arr, n, id);
            printf("\n  Linear Search  → ");
            if (idx != -1) printf("Found at index %d: %s\n", idx, arr[idx].title);
            else           printf("Not found.\n");

            /* Sort before Binary Search */
            bubbleSort(arr, n);
            idx = binarySearch(arr, n, id);
            printf("  Binary Search  → ");
            if (idx != -1) printf("Found at index %d: %s\n", idx, arr[idx].title);
            else           printf("Not found.\n");
            break;
        }
        case 11: {
            if (!bstRoot) { printf("  BST is empty.\n"); break; }
            printf("\n  Inorder Traversal  (Sorted by ID):\n");  BST_inorder  (bstRoot);
            printf("\n  Preorder Traversal (Root First):\n");    BST_preorder (bstRoot);
            printf("\n  Postorder Traversal (Root Last):\n");    BST_postorder(bstRoot);
            break;
        }
        case 12: {
            displayCategories();
            printf("  Choose a start genre (0-%d): ", MAX_GENRES - 1);
            int g; scanf("%d", &g);
            if (g < 0 || g >= MAX_GENRES) { printf("  Invalid.\n"); break; }
            memset(gVisited, 0, sizeof(gVisited));
            printf("\n  DFS from '%s':\n", categories[g]);
            Graph_DFS(g, MAX_GENRES);
            printf("\n");
            Graph_BFS(g, MAX_GENRES);
            break;
        }
        case 13: {
            printf("\n  Stack Applications:\n");
            printf("  1. Reverse a string\n");
            printf("  2. Evaluate postfix expression (single-digit operands)\n");
            printf("  Choice: ");
            int sub; scanf("%d", &sub); clearInput();
            if (sub == 1) {
                char str[256];
                printf("  Enter string: "); fgets(str, 256, stdin); str[strcspn(str, "\n")] = '\0';
                Stack_reverseString(str);
            } else if (sub == 2) {
                char expr[256];
                printf("  Enter postfix (e.g. 3 4 + 2 *): "); fgets(expr, 256, stdin); expr[strcspn(expr, "\n")] = '\0';
                printf("  Result = %d\n", Stack_evalPostfix(expr));
            }
            break;
        }
        case 14:
            displayCategories();
            break;
        case 0:
            printf("\n  Thank you for using Library Management System. Goodbye!\n\n");
            break;
        default:
            printf("  Invalid option. Please try again.\n");
        }
    } while (choice != 0);
    return 0;
}
