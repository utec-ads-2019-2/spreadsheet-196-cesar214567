#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

vector<char> abecedario={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
typedef int sizess ;
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

bool check_if_missing(string **matrix,int rows, int cols){
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            if (matrix[i][j]!="0"){
                return true;
            }
        }
    }
    return false;
}


int main(){
    int spreadsheets,Columns,Rows;
    cin>>spreadsheets;
    string palabra;
    
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
                }
                /*if (isdigit(palabra[0]) || palabra[0]==45){
                    matrix[j][k]=stoi(palabra);
                }else{
                    int contador=0,posicion=0,x,y;
                    string temporal;
                    while(get_primeracosa(palabra[posicion])){
                        posicion+=1;
                        temporal=get_palabra(palabra,posicion,palabra.size());
                        x=get_valor_de_palabra(temporal,temporal.size());
                        y=get_numero(palabra,posicion,palabra.size());
                        cout<<" X ES "<<x<<"   Y ES "<<y;
                        contador+=matrix[x][y];
                        cout<<"   "<<matrix[x][y]<<endl;
                    }
                    matrix[j][k]=contador;
                }*/
            }
        }
        while(check_if_missing(matrix_string,Rows,Columns)){
            for (int j=0;j<Rows;j++){
                for (int k=0;k<Columns;k++){
                    if (matrix_string[j][k]!="0"){
                        string palabra=matrix_string[j][k];
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
                            matrix[j][k]=contador;
                            matrix_string[j][k]="0";
                        }
                        
                    }
                }
            }
        }


        for(int j=0;j<Rows;j++){
            for (int k=0;k<Columns;k++){
                if (k!=Columns-1){
                    cout<<matrix[j][k]<<" ";
                }else{
                    cout<<matrix[j][k];
                }
                
            }cout<<endl;
        }
        
    }
}
