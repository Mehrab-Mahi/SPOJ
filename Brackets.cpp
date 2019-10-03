#include<bits/stdc++.h>
#define ll long long int
#define mx 100005

using namespace std;

int tree[mx*4],lazy[mx*4],arr[mx*4];

int merg(int a , int b){
    return min(a,b);
}

void relax(int node,int b ,int e){
    tree[node] += lazy[node];

    if(b!=e){
        lazy[2*node]+=lazy[node];
        lazy[2*node+1]+= lazy[node];

    }

    lazy[node]=0;
}



void updateRange(int node,int b,int e,int i,int j,int value){

    if(lazy[node])
        relax(node,b,e);

    if(i>e || j<b){
        return ;
    }

    if(b >= i && e <= j){
        lazy[node]+=value;
        relax(node,b,e);
        return;
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node+1;

    updateRange(left,b,mid,i,j,value);
    updateRange(right,mid+1,e,i,j,value);

    tree[node]=merg(tree[left],tree[right]);

}

void init(int node,int b,int e){
    if(b==e){
        tree[node] = arr[b];
        return;
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node + 1;

    init(left,b,mid);
    init(right,mid+1,e);

    tree[node] = merg(tree[left],tree[right]);
}


int query(int node,int b,int e,int i,int j){
    if(lazy[node]) relax(node, b, e);
    if(i>e || j<b){
        return INT_MAX;
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

    int t=10,n,q,tst=1;

    while(t--){

    fill(arr,arr+(mx*4),0);
    fill(tree,tree+(mx*4),0);
    fill(lazy,lazy+(mx*4),0);

    char s[300005];

    scanf("%d ",&n);

    scanf("%s",&s);
    for(int i = 0; i<n;i++){
        if(s[i]=='('){
            arr[i+1]=arr[i]+1;
        }
        else if(s[i]==')'){
            arr[i+1]=arr[i]-1;
        }
    }

    init(1,1,n);

    int cs,x,y;
    scanf("%d",&q);
    printf("Test %d:\n",tst++);
    while(q--){
        scanf("%d",&x);

        if(x==0){
            //cout<<query(1,1,n,1,n)<<" "<<query(1,1,n,n,n)<<" gsffg"<<endl;
            if(query(1,1,n,1,n)>=0 && query(1,1,n,n,n)==0 ){
                printf("YES\n");
            }
            else{
                printf("NO\n");
            }
        }
        else{
            if(s[x-1]=='('){
                s[x-1] = ')';
                updateRange(1,1,n,x,n,-2);
//
//                for(int i= 1;i<=7;i++)
//                    cout<<tree[i]<<" ";
//                cout<<endl;

            }
            else{
                s[x-1] = '(';
                updateRange(1,1,n,x,n,2);
            }
        }
    }
    }

}

