/*Ioannis Bozionelos
AM:2022202300157
dit23157@uop.gr

Ioannis Vasiligiannis
AM:2022202300133
dit23133@uop.gr
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>



#define MAX 20							 // Megisto megethos dwmatiou


typedef struct Node {
    int x, y;              				 // Suntetagmenes
    int g, h, f;          				 // g:pragmatikh apostash, h:Manhattan, f:sunolikh ektimhsh
    struct Node* previous; 			   	 // Deikths prohgoumenou kombou
} Node;


typedef struct {						 //Oura proteraiothtas
    Node* nodes[MAX * MAX];
    int size;
} PriorityQueue;



void Queue(PriorityQueue* queue);
void queueInsert(PriorityQueue* queue, Node* node);
Node* queueExtract(PriorityQueue* queue);
int manhattanDistance(int x1, int y1, int x2, int y2);
void generateRoom(int room[MAX][MAX], int width, int height, int obstaclePercentage);
void printRoom(int room[MAX][MAX], int width, int height);
void aStar(int room[MAX][MAX], int width, int height);



int main(void) {

	printf("\n*****************************************\n");	
    printf("*      Welcome to the A* Algorithm      *\n");
    printf("*****************************************\n");
    printf("This program finds the optimal path from the entrance to the exit of a room, avoiding obstacles. \n\n");
    printf("In the map:\n");
    printf("- '.' represents free space.\n");
    printf("- '*' represents obstacles.\n");
    printf("- 'r' represents the robot's path.\n\n");
    printf("Enjoy exploring the pathfinding process!\n\n");

	srand(time(NULL));

    int room[MAX][MAX], size, width, height, obstaclePercentage;
	size= 10+rand()%11;											// To megethos tou dwmatiou PREPEI na anhkei sto diasthma [10x10,20x20]!
    width = size;
	height = size;

	obstaclePercentage =  10 + rand() % 81;						// To pososto twn empodiwn PREPEI na anhkei sto diasthma [10,90]!

    generateRoom(room, width, height, obstaclePercentage);

    aStar(room, width, height);

	printf("\n*********************************************************************\n");
	printf("*          Thank you for using the A* Pathfinding Program!          *\n");
	printf("*********************************************************************\n");
	printf("*       We hope you enjoyed exploring the optimal pathfinding       *\n");
	printf("*   Feel free to try again with different room sizes or obstacles   *\n");
	printf("*********************************************************************\n");
	printf("*                         Have a great day!                         *\n");
	printf("*********************************************************************\n");
	
    return 0;
}



void generateRoom(int room[MAX][MAX], int width, int height, int obstaclePercentage) {					// Dhmiourgia dwmatiou me empodia
    int i,j;
	for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
			if (rand() % 100 < obstaclePercentage) {
				room[i][j] = 1; 
			} else {
				room[i][j] = 0; 
			}
        }
    }
    room[0][0] = 0; 
    room[height - 1][width - 1] = 0;
}



void printRoom(int room[MAX][MAX], int width, int height) {												// Ektupwsh dwmatiou
	int i,j;
	for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (room[i][j] == 1)  			// Empodia
                printf("* ");
            else if (room[i][j] == 'r')  	// Monopati
                printf("r ");
            else  							// Kena diasthmata
                printf(". ");
        }
        printf("\n");
    }
}



void aStar(int room[MAX][MAX], int width, int height) { 												// Algorithmos A*
    PriorityQueue openSet;
    Queue(&openSet);

    bool closedSet[MAX][MAX] = {false};

    int initialRoom[MAX][MAX], i, j; 								// Dhmiourgia arxikou pinaka
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            initialRoom[i][j] = room[i][j];
        }
    }

    int examinedRoom[MAX][MAX]; 							// Dhmiourgia pinaka me exetasmenous kombous
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            examinedRoom[i][j] = room[i][j];
        }
    }

    Node* start = malloc(sizeof(Node)); 					// Dhmiourgia kai arxikopoihsh afethrias
    start->x = 0;
    start->y = 0;
    start->g = 0;
    start->h = manhattanDistance(0, 0, width - 1, height - 1);
    start->f = start->g + start->h;
    start->previous = NULL;

    queueInsert(&openSet, start);

    printf("Initial Room:\n");
    printRoom(initialRoom, width, height);					// Emfanisi arxikou pinaka
    printf("\nPress Enter to continue...\n");
    getchar(); 												// Perimenei eisodo xristi(enter)

    while (openSet.size > 0) { 								// Oso h oura proteraiothtas den einai adeia sunexizei
        Node* current = queueExtract(&openSet); 			// O kombos me elaxisth timh f exagetai kai mpainei sto current

        examinedRoom[current->y][current->x] = 'r'; 		// Shmadevei tous exetasmenous kombous

        system("clear");
        printf("Examined Room (so far):\n");
        printRoom(examinedRoom, width, height);				 // Emfanisi pinaka me exetasmenous kombous
        printf("\nPress Enter to continue...\n");
        getchar();

        if (current->x == width - 1 && current->y == height - 1) { // Elegxos gia ton an o current einai sthn exodo
            printf("\nPath found!\n");

            int pathRoom[MAX][MAX]; 						// Pinakas gia to teliko monopati
            for (i = 0; i < height; i++) {
                for (j = 0; j < width; j++) {
                    pathRoom[i][j] = room[i][j];
                }
            }

            Node* temp = current;
            while (temp) {
                pathRoom[temp->y][temp->x] = 'r'; 			// Shmadeuei thn diadromh me r
				system("clear");
				printf("\nBuilding OPTIMAL path (step-by-step!):\n");
				printRoom(pathRoom, width, height);
				printf("\nPress Enter to continue...\n");
				getchar();
                temp = temp->previous;
            }

            system("clear");
			printf("\nFinal OPTIMAL Path:\n");
			printRoom(pathRoom, width, height);
			printf("\nPress Enter to exit...\n");
			getchar();

            return;
        }

        closedSet[current->y][current->x] = true; 			// Mpainoun sto closedSet gia na mhn epanexetastoun

        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (i = 0; i < 4; i++) {
            int nx = current->x + directions[i][0];
            int ny = current->y + directions[i][1];

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && room[ny][nx] == 0 && !closedSet[ny][nx]) {
                Node* neighbor = malloc(sizeof(Node)); 		// Dhmiourgia neou kombou geitona
                neighbor->x = nx;
                neighbor->y = ny;
                neighbor->g = current->g + 1;
                neighbor->h = manhattanDistance(nx, ny, width - 1, height - 1);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->previous = current;

                queueInsert(&openSet, neighbor);
            }
        }
    }
    printf("\nFailure: There is no visible path!\n");
    printf("\nPress Enter to exit...\n");
    getchar();
}

   

void Queue(PriorityQueue* queue) {																		// Dhmiourgia swrou
    queue->size = 0;
}



int manhattanDistance(int x1, int y1, int x2, int y2) {													// Ypologismos Manhattan apostashs
    return abs(x1 - x2) + abs(y1 - y2);
}



Node* queueExtract(PriorityQueue* queue) {																// Eksagwgh kombou
    Node* min = queue->nodes[0];						//apothikeuetai o kombos ths ouras me to mikrotero f(tha epistrafei sto telos)
    Node* last = queue->nodes[--queue->size];			//apothikeuetai proswrina o teleutaios kombos ws riza, epishs meiwnei to megethos ths ouras afou enas kombos tha afairethei
    
	int i = 0, child;								
    while ((child = 2 * i + 1) < queue->size) {			//o gonikos kombos i prepei na exei mikroterh h ish f apo ta paidia tou
        if (child + 1 < queue->size && queue->nodes[child + 1]->f < queue->nodes[child]->f) {
            child++;
        }
        if (last->f <= queue->nodes[child]->f) break;
        queue->nodes[i] = queue->nodes[child];			//metakinhsh paidiou sth thesh gonea
        i = child;
    }
    queue->nodes[i] = last;
    return min;
}



void queueInsert(PriorityQueue* queue, Node* node) {													// Eisagwgh kombou
    int i = queue->size++;										//auxhsh megethous ouras
    while (i && node->f < queue->nodes[(i - 1) / 2]->f) {		//timh f kombou<timh f gonikou kombou
        queue->nodes[i] = queue->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->nodes[i] = node;										//topothethsh kombou sth swsth thesh
}