#include<bits/stdc++.h>
using namespace std;
typedef long double lb;

struct layer{
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

void forw(vector<layer> &nn){
    int n=nn.size();
    for(int i=0;i<n-1;i++){
        vector<lb> in_for_next;
        int sz=nn[i].b.size();
        //cout<<sz<<'\n';
        for(int j=0;j<sz;j++){
            in_for_next.push_back(activ(h(nn[i].x,nn[i].w[j],nn[i].b[j])));
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
    int n;
    cout<<"Numero de capas"<<'\n';
    cin>>n;
    vector<layer> nn(n);
    nn[0].x=X[0];
    
    for(int i=0;i<n;i++){
        cout<<"Numero de neuronas en la "<<i<<" capa"<<'\n';
        int sz;
        cin>>sz;
        for(int j=0;j<sz;j++){
            int tam;
            if(i==0) tam=X[0].size();
            else tam=nn[i-1].b.size();
            vector<lb> w(tam);
            for(int k=0;k<tam;k++) w[k]=rand()%1000;
            nn[i].w.push_back(w);
            nn[i].b.push_back(rand()%1000);
        }
    }
}