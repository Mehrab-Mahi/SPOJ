#include<bits/stdc++.h>
#define ll long long int
#define pb push_back
#define mx 100005

using namespace std;

int tree[mx*4],arr[mx*4],fnl[mx*4];


int merg(int a , int b){
    return a+b;
}



void init(int node,int b,int e){
    if(b==e){
        tree[node] = fnl[b];
        return;
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node + 1;

    init(left,b,mid);
    init(right,mid+1,e);

    tree[node]= merg(tree[left],tree[right]);
}


int query(int node,int b,int e,int i,int j){

    if(i>e || j<b){
        return 0;
    }

    if(b >= i && e <= j){

        return tree[node];
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node + 1;

    int p = query(left,b,mid,i,j);
    int q = query(right,mid+1,e,i,j);

    return merg(p,q);

}

int main()
{
    int n,q,x,y;

    scanf("%d",&n);

    map<int,int>mp;

    for(int i = 1;i<=n;i++)
        scanf("%d",&arr[i]);

    for(int i = 1;i<=n;i++){
        if(mp[arr[i]]==0){
            mp[arr[i]] = i;
            fnl[i] = 1;
        }
        else{
            fnl[mp[arr[i]]] = 0;
            fnl[i]  = 1;
            mp[arr[i]] = i;
        }
    }

    init(1,1,n);


//    for(int i = 1;i<=9;i++)
//        cout<<tree[i]<<" ";

    scanf("%d",&q);

    while(q--){

        scanf("%d %d",&x,&y);

        if(x==y)
            printf("1\n");
        else
            printf("%d\n",query(1,1,n,x,y));

    }

}
