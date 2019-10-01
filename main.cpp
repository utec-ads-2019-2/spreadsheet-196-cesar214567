#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

vector<char> abecedario={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

class punto{
    public:
    int x,y;
    punto(int x1,int y1):x(x1),y(y1){};
};
int get_letra(char letra){
    for (int i=0;i<abecedario.size();i++){
        if (abecedario[i]==letra){
            return i;
        }
    }
}

string get_palabra(string palabra,int &start, int end){
    int i=start;
    string temporal="";
    while(i<end && !isdigit(palabra[i])){
        temporal+=palabra[i];
        i++;
        
    }  
    start=i;
    return temporal;
}

int get_valor_de_palabra(string palabra,int end){
    int contador=0;
    for (int i=0;i<end;i++){
        contador+=get_letra(palabra[0])*pow(26,end-1-i);
    }
    return contador;
}

bool get_primeracosa(char palabra){
    return (palabra==61 || palabra==43);
}

int get_numero(string palabra,int &start, int end){
    int i=start;
    vector<int> temporal;
    int int_temporal;
    while(i<end && isdigit(palabra[i])){
        int_temporal=palabra[i]-'0';
        temporal.push_back(int_temporal);
        i++;
        
    }
    int_temporal=0;
    for (int j=0;j<temporal.size();j++){
        int_temporal=int_temporal+temporal[j]*pow(10,temporal.size()-1-j);
    }
    start=i;
    return int_temporal-1;
}

bool check_if_missing(vector<punto> matrix){
    if(matrix.empty()){
        return false;
    }
    return true;
}


int main(){
    int spreadsheets,Columns,Rows;
    cin>>spreadsheets;
    string palabra;
    vector<punto> missing_boxes;
    for (int i=0;i<spreadsheets;i++){
        cin>>Columns>>Rows;
        int **matrix=new int*[Rows];
        for (int l=0;l<Rows;l++){
            matrix[l]=new int[Columns];
        }
        string **matrix_string=new string*[Rows];
        for (int l=0;l<Rows;l++){
            matrix_string[l]=new string[Columns];
        }
        for(int j=0;j<Rows;j++){
            for (int k=0;k<Columns;k++){
                int temporal=0;
                cin>>palabra;
                if (isdigit(palabra[0]) || palabra[0]==45){
                    matrix[j][k]=stoi(palabra);
                    matrix_string[j][k]="0";
                }else{
                    matrix_string[j][k]=palabra;
                    matrix[j][k]=0;
                    missing_boxes.push_back(punto(j,k));
                }
                
            }
        }
        while(check_if_missing(missing_boxes)){
            for (int j=missing_boxes.size()-1;j>=0;j--){
                int k=missing_boxes[j].x;
                int l=missing_boxes[j].y;
                    if (matrix_string[k][l]!="0"){
                        string palabra=matrix_string[k][l];
                        bool dependencia=false;
                        int contador=0,posicion=0,x,y;
                        string temporal;
                        while(get_primeracosa(palabra[posicion])){
                            posicion+=1;
                            temporal=get_palabra(palabra,posicion,palabra.size());
                            y=get_valor_de_palabra(temporal,temporal.size());
                            x=get_numero(palabra,posicion,palabra.size());
                            if(matrix_string[x][y]=="0"){
                                contador+=matrix[x][y];
                            }else{
                                dependencia=true;
                                break;
                            }
                        }
                        if(!dependencia){
                            matrix[k][l]=contador;
                            matrix_string[k][l]="0";
                            missing_boxes.erase(missing_boxes.begin()+j);
                        }
                        
                    }
                
            }
        }


        for(int a=0;a<Rows;a++){
            for (int b=0;b<Columns;b++){
                if (b!=Columns-1){
                    cout<<matrix[a][b]<<" ";
                }else{
                    cout<<matrix[a][b];
                }
                
            }cout<<endl;
        }
        
        
        
    }
}
