#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;
int totalScore=0;                          //total score of the current/last game      
int highest=0;                             //highest total overall
bool wonStatus=false;                      //tells whether the recent game was won or not

bool over(int arr[][4]);
int completition(int arr[][4]);
void display(int arr[][4]);
void adder(int arr[][4]);
void addRight(int arr[][4]);
void moveRight(int arr[][4]);
void Right(int arr[][4]);
void addLeft(int arr[][4]);
void moveLeft(int arr[][4]);
void Left(int arr[][4]);
void addUp(int arr[][4]);
void moveUp(int arr[][4]);
void Up(int arr[][4]);
void addDown(int arr[][4]);
void moveDown(int arr[][4]);
void Down(int arr[][4]);
void game(int arr[][4]);

int main(){
    srand(time(0));
    int choice=0;                          //choice in menu

    cout<<"Hello there!\nWelcome to 2048!\nA Game Specially designed for math nerds, JK!"<<endl;   
    while (choice!=3){                     //main loop, keeps repeating itself unless quit is selected
        cout<<"\n\n1. Play\n2. Instructions\n3. Quit\n";
        cin>>choice;
        if (choice==1){                    //initiates the game
            int arr[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
            totalScore=0;
            wonStatus=false;
            game(arr);
        }
        else if(choice==2){                //displays instructions/rules
            system("cls");
            cout<<"Rules & Instructions:\n1- Press Up, Down, Left, or Right to move the board\n2- Board will move in the respected direction. \n3- Same numbers will add up, increasing your overall score!!\n4- Goal is to hit 2048 before getting stuck.\n5- You can also try to beat your overall highest score!"<<endl;
            cout<<endl<<"Pro-tip:\n**Keep the largest value in corner**"<<endl;
        }
        else if (choice==3){}              //exits the code
        else{               
            cout<<"Invalid input! Select one of the above options!";
        }
    }

    return 0;
}

void game (int arr[4][4]){                 //handles the game's controls
    int result=1;
    adder(arr);
    adder(arr);
    display(arr);
    while(result!=0){      //loop exits if game is over, game is over when result=0, game continues while result=1
        
        int key = 0;
        
        key=getch();
        switch (key){
            case 72:                      // up arrow key and board movement
                Up(arr);                  // up function is called, handles all the up commands
                break;

            case 80:                      // down arrow key and board movement
                Down(arr);                // down function is called, handles all the down commands
                break;
                
            case 77:                      // right arrow key and board movement
                Right(arr);               // right function is called, handles all the right commands
                break;
                
            case 75:                      // left arrow key and board movement
                Left(arr);                // left function is called, handles all the left commands
                break;
                
            default:
                continue;
        }
        result=completition(arr);         //completition function keeps track of whether the game is won, over, or still in progress
        cout<<"Total: "<<totalScore<<endl;//Displaying the current total of the game
        if (totalScore>highest){
            highest=totalScore;           //high score updated if nessesary
        }
        cout<<"Highest Score: "<<highest<<endl;
    }


    cout<<endl<<endl;
    
    if(wonStatus==true){
        cout<<"WoW, gratzz"<<endl;           //If game won
    }else if (wonStatus==false){
        cout<<"Better luck next time-"<<endl;//If game lost
    }else{}

    cout<<"Total Score of this game: "<<totalScore<<endl;         //Total of the last game
    if (totalScore>highest){
        highest=totalScore;                                       //high score updated if nessesary
    }else{
        cout<<"Highest Score overall: "<<highest<<endl;;          //Highest total overall
    }
}

void adder(int arr[4][4]){            //adds 2 or 4 if a random title, if title available
    int r=(rand()%4);                 //generates a random row number
    int c=(rand()%4);                 //generates a random coloumn number
    int count=0;                      //counter for free/0 tiles
    for (int i=0; i<4; i++){          //checks if any free tile available
        for (int j=0; j<4; j++){
            if (arr[i][j]==0){
                count++;
            }
        }
    }
    if (count>0){                    //if free/0 tiles available
        while (arr[r][c]!=0){        //But current tile is not free/0
            r=(rand()%4);            //will keep generating tiles untill free/0 one has been spotted
            c=(rand()%4);
        }
        arr[r][c]=((rand()%2)+1)*2;  //adds 2 or 4 to the free tile 
    }else{}                          //pass if no free tile

}

void display(int arr[4][4]){         //displaying the board
    cout<<endl;
    system("cls");                   //clearing the screen
    cout<<endl;
    for(int i=0; i<4; i++){
        cout<<"---------------------------------"<<endl;        //generating border for start and end of each row
        for (int j=0; j<4; j++){
            cout<<"| "<<arr[i][j]<<"\t";                        //Displaying the value of each tile, "|" for border between columns
        }
        cout<<"|";
        cout<<endl;
    }
    cout<<"---------------------------------"<<endl;
}

int completition(int arr[4][4]){             //checks if the game is over or not
    int o=over(arr);                         //over function tells if any possible combinations(addition) between tiles are possible
    int f=0;
    int count=0;
    for(int i=0; i<4; i++){
        for (int j=0; j<4;j++){
            if (arr[i][j]==2048){            //checks of game is won
                wonStatus=true;              //won

            }else if((arr[i][j]!=0)&&(o==0)){
                count++;                     //keeping track of number of tiles taht are not free and with no possible combinations and additions on either side
                if (count==16){              //when counter hits 16, game is over!
                    f=0;
                    return f;
                }
            }else if(arr[i][j]==0||o==1){    //either combination still possible or there's 0 somewhere in matrix
                f=1;
                return f;
            }
            
        }
    }
    return f;
}

bool over(int arr[4][4]){                  //over function tells if any possible combinations(addition) between tiles are possible
    bool ret=false;
    int count=0;
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            if((j<3)&&(i<3)){              //checks if combinations possible for the values of the first 3 rows and columns
                if ((arr[i][j]==arr[i][j+1])||(arr[i][j]==arr[i+1][j])){
                    count++;
                }
            }
            if ((i==3)&&(j!=3)){           //checks if combinations possible between values of the last row
                if ((arr[i][j]==arr[i-1][j])||(arr[i][j]==arr[i][j+1])){
                    count++;
                }
            }
            if ((i!=3)&&(j==3)){           //checks if combinations possible between values of the last row
                if ((arr[i][j]==arr[i][j-1])||(arr[i][j]==arr[i+1][j])){
                    count++;
                }
            }
            if((i==3)&&(j==3)){            //checks if combinations possible between value the last column of the last row
                if ((arr[i][j]==arr[i][j-1])||(arr[i][j]==arr[i-1][j])){
                    count++;
                }
            }
        }
    }
    if(count>0){
        ret= true;                         //returns true if possible combinations
    }else if (count==0){
        ret= false;                        //false if not
    }
    return ret;
}

void addRight(int arr[4][4]){              //adds values in the right direction, if they are same
    for (int i=0; i<4; i++){
        for (int j=3; j>0; j--){           //since we are moving left to right, rows iterate normally while columns iterate backwards
            if((arr[i][j])==(arr[i][j-1])){//checks if values are same
                arr[i][j]=arr[i][j]*2;     //doubles the value in the current tile
                arr[i][j-1]=0;             //Zero replaced as the value to the tile the current tile was compared to
                totalScore+=arr[i][j];     //value added to total score
            }else {}
        }
    }
}

void moveRight(int arr[4][4]){             //moves board in the right direction, clearing any zeros inbetween values
    int n=0;
    while(n<3){
        for (int i=0; i<4; i++){
            for (int j=3; j>0; j--){       //since we are moving left to right, rows iterate normally while columns iterate backwards
                if(arr[i][j]==0){
                    arr[i][j]=arr[i][j-1];
                    arr[i][j-1]=0;
                }else if(arr[i][j]!=0){}
            }
        }
        n++;                               //repeated 3 times, every value moves once in the respected direction each time its executed, hence repeated thrice
    }
}

void Right(int arr[4][4]){                 //executed when right key is pressed
    moveRight(arr);                        //clears zeros between values
    addRight(arr);                         //adds same values in right directin
    moveRight(arr);                        //clears zeroes between values again
    adder(arr);                            //adds a random 2 or 4 to a random tile if possible
    display(arr);                          //displays the board again
}


void addLeft(int arr[4][4]){               //adds values in the left direction, if they are same
    for (int i=0; i<4; i++){
        for (int j=0; j<3; j++){           //since we are moving right to left, rows iterate normally while columns iterate backwards
            if((arr[i][j])==(arr[i][j+1])){//checks if values are same
                arr[i][j]=arr[i][j]*2;     //doubles the value in the current tile
                arr[i][j+1]=0;             //Zero replaced as the value to the tile the current tile was compared to
                totalScore+=arr[i][j];     //value added to total score
            }else {}
        }
    }
}

void moveLeft(int arr[4][4]){             //moves board in the left direction, clearing any zeros inbetween values
    int n=0;
    while(n<3){
        for (int i=0; i<4; i++){
            for (int j=0; j<3; j++){      //since we are moving right to left, rows iterate normally while columns iterate backwards
                if(arr[i][j]==0){
                    arr[i][j]=arr[i][j+1];
                    arr[i][j+1]=0;
                }else if(arr[i][j]!=0){}
            }
        }
        n++;                              //repeated 3 times, every value moves once in the respected direction each time its executed, hence repeated thrice
    }
}

void Left(int arr[4][4]){                 //executed when left key is pressed
    moveLeft(arr);                        //clears zeros between values
    addLeft(arr);                         //adds same values in left directin
    moveLeft(arr);                        //clears zeroes between values again
    adder(arr);                           //adds a random 2 or 4 to a random tile if possible
    display(arr);                         //displays the board again
}

void addUp(int arr[4][4]){                 //adds values in the upwards direction, if they are same
    for (int i=0; i<3; i++){
        for (int j=0; j<4; j++){           //since we are moving up to down, columns iterate normally while rows iterate backwards
            if((arr[i][j])==(arr[i+1][j])){//checks if values are same
                arr[i][j]=arr[i][j]*2;     //doubles the value in the current tile
                arr[i+1][j]=0;             //Zero replaced as the value to the tile the current tile was compared to
                totalScore+=arr[i][j];     //value added to total score
            }else {}
        }
    }
}

void moveUp(int arr[4][4]){                //moves board in the upwards direction, clearing any zeros inbetween values
    int n=0;
    while(n<3){
        for (int i=0; i<3; i++){           //since we are moving up to down, columns iterate normally while rows iterate backwards
            for (int j=0; j<4; j++){
                if(arr[i][j]==0){
                    arr[i][j]=arr[i+1][j];
                    arr[i+1][j]=0;
                }else if(arr[i][j]!=0){}
            }
        }
        n++;                               //repeated 3 times, every value moves once in the respected direction each time its executed, hence repeated thrice
    }
}

void Up(int arr[4][4]){                 //executed when up key is pressed
    moveUp(arr);                        //clears zeros between values
    addUp(arr);                         //adds same values in upward directin
    moveUp(arr);                        //clears zeroes between values again
    adder(arr);                         //adds a random 2 or 4 to a random tile if possible
    display(arr);                       //displays the board again
}

void addDown(int arr[4][4]){               //adds values in the downwards direction, if they are same
    for (int i=3; i>0; i--){
        for (int j=0; j<4; j++){           //since we are moving down to up, columns iterate normally while rows iterate backwards
            if((arr[i][j])==(arr[i-1][j])){//checks if values are same
                arr[i][j]=arr[i][j]*2;     //doubles the value in the current tile
                arr[i-1][j]=0;             //Zero replaced as the value to the tile the current tile was compared to
                totalScore+=arr[i][j];     //value added to total score
            }else {}
        }
    }
}

void moveDown(int arr[4][4]){             //moves board in the downwards direction, clearing any zeros inbetween values
    int n=0;
    while(n<3){
        for (int i=3; i>0; i--){          //since we are moving down to up, columns iterate normally while rows iterate backwards
            for (int j=0; j<4; j++){
                if(arr[i][j]==0){
                    arr[i][j]=arr[i-1][j];
                    arr[i-1][j]=0;
                }else if(arr[i][j]!=0){}
            }
        }
        n++;                              //repeated 3 times, every value moves once in the respected direction each time its executed, hence repeated thrice
    }
}

void Down(int arr[4][4]){                 //executed when down key is pressed
    moveDown(arr);                        //clears zeros between values
    addDown(arr);                         //adds same values in downward directin
    moveDown(arr);                        //clears zeroes between values again
    adder(arr);                           //adds a random 2 or 4 to a random tile if possible
    display(arr);                         //displays the board again
}