#include <iostream>
#define inf 999999999

using namespace std;


//Tic Tac Toe implementation with minimax algorithm

class XOGame{
private:
    char grid[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}  };
private:
    void afisareGrid(){

        for(int r=0;r<3;r++){
            cout<<" ";
            for(int i=1;i<=3;i++)cout<<"--- ";
            cout<<'\n';
            cout<<"| ";
            for(int i=0;i<3;i++){
                //            afisarea numerelor;
//            if(grid[r][i] != ' ')cout<<grid[r][i]<<" | ";
//            else cout<<r*3+i+1<<" | ";

                cout<<grid[r][i]<<" | ";
            }

            cout<<'\n';
        }
        for(int i=1;i<=3;i++)cout<<" ---";
        cout<<'\n';
    }

    void gridClear(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                grid[i][j] = ' ';
        }
    };

    bool isOver(){

        //verificam daca mai exista spatii libere;
        int c=0;
        for(int i=0;i<3 && c==0;i++){
            for(int j=0;j<3;j++)
                if(grid[i][j] == ' ')c++;
        }

        if(c==0) return true;



        //verificam daca a castigat 0, pe linii
        for(int i=0;i<3;i++){
            if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != ' ')return true;
        }

        //apoi pe coloane
        for(int i=0;i<3;i++){
            if(grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != ' ')return true;
        }

        //si ulterior pe diagonale
        if((grid[0][0] == grid[1][1] && grid[2][2] == grid[0][0] && grid[0][0] != ' ') || (grid[2][0] == grid[1][1] && grid[0][2] == grid[1][1] && grid[1][1] != ' ') )return true;



        return false;


    }

    int getLine(char c){
        int n = c - '0';
        return (n-1)/3;
    }

    int getColumn(char c){
        int n = c - '0';
        return (n-1)%3;
    }

    int isOk(char move){
        //codificari erori:
        // 1 - pozitia nu este pe tabela
        // 2- pozitia este deja ocupata

        if(move >'9' || move < '1')return 1;

        if(grid[getLine(move)][getColumn(move)] != ' ') return 2;



        return 0;
    }

    char winner(){
        //0 = tie, 1 = x, -1 = O
        int win = 0;
        char w = ' ';

        for(int i=0;i<3;i++){
            if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] )w = grid[i][2];
        }

        for(int i=0;i<3;i++){
            if(grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != ' ')w = grid[2][i];
        }


        if((grid[0][0] == grid[1][1] && grid[2][2] == grid[0][0] && grid[0][0] != ' ') || (grid[2][0] == grid[1][1] && grid[0][2] == grid[1][1] && grid[1][1] != ' ') )w= grid[1][1];


        return w;

    }

    void place(char c, char m){
        grid[getLine(m)][getColumn(m)] = c;
    }

    int minimax( int depth, bool isO, int alpha, int beta){
        if(isOver()){
            if(winner() == ' ') return 0;
            else
            if(winner() == 'X' ) return -10+depth;
            else return 10-depth;
        }

        //O vrea sa maximizeze, X sa minimizeze
        int eval, e;
        if(isO){
            eval = -1 * inf;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(grid[i][j] == ' '){
                        grid[i][j] = 'O';
                        e= minimax( depth+1, false, alpha, beta);
                        grid[i][j] = ' ';

                        eval = max( eval, e );
                        alpha = max(alpha, e);
                        if(beta<= alpha) return eval;


                    }
                }
            }
        }else{
            eval = inf;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(grid[i][j] == ' '){
                        grid[i][j] = 'X';
                        e= minimax( depth+1, true, alpha, beta);
                        grid[i][j] = ' ';
                        eval = min( eval, e );
                        alpha = max(alpha, e);
                        if(beta<= alpha) return eval;


                    }
                }
            }
        }

        return eval;


    }

public:
    XOGame() = default;


    void startGame(){
        cout<<"\nSalut! Bun venit la jocul de X si O!\nVei juca cu X si vei face prima mutare.\n";
        cout<<"Tabela de joc este numerotata dupa modelul urmator:\n";
        afisareGrid();
        cout<<"Pentru a incepe alege un o pozitie in care doresti sa plasezi un X: ";

        gridClear();
        char move;

        char turn = 'X';

        while(!isOver()) {
            cin >> move;

            while (isOk(move) != 0) {
                cout << "Aceasta mutare nu este posibila. Cititi alta:";
                cin >> move;
            }

            place('X', move);
            afisareGrid();

            //mutarea calculatorului
            if (!isOver()) {
                //calculam valoarea minmax pentru toate mutarile posibile de la un anumit moment si o aplicam pe cea mai buna dintre acestea
                //tinem cont ca O vrea sa maximizeze
                int maxim = -1 * inf, ipoz = 0, jpoz = 0;

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (grid[i][j] == ' ') {
                            grid[i][j] = 'O';

                            if (maxim < minimax( 0, false, -1 * inf, inf)) {
                                maxim = minimax( 0, false, -1 * inf, inf);
                                ipoz = i;
                                jpoz = j;
                            }
                            grid[i][j] = ' ';
                        }
                    }
                }

                grid[ipoz][jpoz] = 'O';

            }

            cout<<"Buna mutare! Eu am ales asta: \n";
            afisareGrid();


        }
        if(winner() == ' ') cout<<"Amandoi suntem foarte buni, nimeni nu a castigat!";
        else{
            cout<<"Castigator: "<< winner();
        }

    }

};


int main() {
    XOGame x;
    x.startGame();


}
