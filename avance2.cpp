#include<bits/stdc++.h>
using namespace std;
typedef long double lb;

void barra(){
    cout<<"-------------------------"<<'\n';
}

struct layer{
    int n;
    vector<lb> x;
    vector<vector<lb>> w;
    vector<lb> b;  
    layer()=default;
};

lb h(vector<lb> &x,vector<lb> &w,lb &b){
    lb ans=b;
    for(int i=0;i<x.size();i++) ans=ans+x[i]*w[i];
    return ans;
}

lb activ(lb val){
    return 1/(1 +exp(-val));
}

lb activ(lb net, string tipo){
    lb resultado;
    if(tipo == "sigmoide"){
        resultado = 1 / (1 + exp(-net));
    } else if(tipo == "tanh"){
        resultado = tanh(net);
    } else if(tipo == "relu"){
        resultado = net > 0 ? net : 0;
    }
    return resultado;
}

vector<lb> softmax(vector<lb> vect){
    vector<lb> sol;
    lb suma = 0;
    for(int i=0; i<vect.size(); ++i) suma += exp(vect[i]);

    for(int i=0; i<vect.size(); ++i){
        lb temp = exp(vect[i]) / suma;
        sol.push_back(temp);
    }
    return sol;
}

void forw(vector<layer> &nn,int &n){
    for(int i=0;i<n-1;i++){
        vector<lb> in_for_next;
        for(int j=0;j<nn[i+1].n;j++){
            cout<<nn[i].x.size()<<' '<<nn[i+1].w[j].size()<<' '<<nn[i+1].b[j]<<'\n';
            barra();
            in_for_next.push_back(activ(h(nn[i].x,nn[i+1].w[j],nn[i+1].b[j])));
        }
        nn[i+1].x=in_for_next;
    }
    cout<<"here"<<'\n';
}


int main(){
    ifstream read_file("sign_mnist_train.csv");
    string reader;
    vector<vector<lb>> X;
    vector<lb> Y;
    while(getline(read_file,reader)){
        string guard="";
        vector<lb> temp;
        bool pri=1;
        for(int i=0;i<reader.size();i++){
            if(reader[i]==','){
                if(pri==1){
                    Y.push_back(stof(guard));
                    pri=0;
                }
                else temp.push_back(stof(guard));
                guard="";
            }
            else guard=guard+reader[i]; 
        }
        temp.push_back(stof(guard));
        X.push_back(temp);
    }
    cout<<X.size()<<' '<<X[0].size()<<'\n';
    cout<<Y.size()<<'\n';
    
    int n;
    cout<<"Numero de capas"<<'\n';
    cin>>n;
    vector<layer> nn(n);
    nn[0].x=X[0];
    nn[0].n=X[0].size();
    
    cout<<"Numero de neuronas en las capas ocultas y cantidad de capas"<<'\n';

    int sz_n,num_hidden;
    cin>>sz_n>>num_hidden;
    for(int i=1;i<1+num_hidden;i++){
        nn[i].n=sz_n;
        for(int j=0;j<sz_n;j++){
            int tam=nn[i-1].n;
            vector<lb> w(tam);
            for(int k=0;k<tam;k++) w[k]=rand()%100;
            nn[i].w.push_back(w);
            nn[i].b.push_back(rand()%100);
        }
    }
 
    for(int i=0;i<n;i++){
        cout<<"Capa "<<i<<'\n';
        cout<<nn[i].n<<'\n';
        cout<<nn[i].x.size()<<'\n';
        cout<<nn[i].w.size()<<'\n';
        cout<<nn[i].b.size()<<'\n';
        barra();
    }
    forw(nn,n);
}
