#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

vector<string> abecedario={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};


int get_letra(string letra){
    for (int i=0;i<abecedario.size();i++){
        if (abecedario[i]==letra){
            //cout<<i<<endl;
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
    string temporal;
    for (int i=0;i<end;i++){
        temporal=palabra[i];
        contador+=((get_letra(temporal)+1)*pow(26,end-1-i));
        //cout<<get_letra(temporal)<<endl;
    }
    //cout<<contador<<endl;
    return contador-1;
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

int funcion(string **&matrix_string,int **&matrix,int x,int y){
    if (matrix_string[x][y]=="0"){
        return matrix[x][y];
    }
    string palabra=matrix_string[x][y];
    int contador=0,posicion=0,x1,y1;
    string temporal;
    while(get_primeracosa(palabra[posicion])){
        posicion+=1;
        temporal=get_palabra(palabra,posicion,palabra.size());
        //cout<<temporal<<endl;
        y1=get_valor_de_palabra(temporal,temporal.size());
        //cout<<"Y1 es "<<y1<<endl;
        x1=get_numero(palabra,posicion,palabra.size());
        contador+=funcion(matrix_string,matrix,x1,y1);
    }
    matrix[x][y]=contador;
    matrix_string[x][y]="0";
    return contador;
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
                
            }
        }
        for(int j=0;j<Rows;j++){
            for (int k=0;k<Columns;k++){
                if (matrix_string[j][k]!="0"){
                    matrix[j][k]=funcion(matrix_string,matrix,j,k);
                    
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
