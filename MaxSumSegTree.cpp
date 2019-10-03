#include<bits/stdc++.h>
#define mx 100005

using namespace std;


int tree[mx*4],tree1[mx*4],arr[mx],p,q;


int sum(int a,int b){
    int ar[4];
    ar[0] = a;
    ar[1] =b;
    ar[2] = p;
    ar[3] = q;
    sort(ar,ar+4);
    //cout<<ar[3]<<" "<<ar[2]<<endl;
    p = ar[3];
    q = ar[2];
}

void result(int a,int b,int c,int d,int node){
    int ar[4];
    ar[0] = a;
    ar[1] =b;
    ar[2] = c;
    ar[3] = d;
    sort(ar,ar+4);
    tree[node] = ar[3];
    tree1[node] = ar[2];
}

void init(int node,int b,int e){
    if(b==e){
        tree[node]=arr[b];
        tree1[node] = 0;
        return ;
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node + 1;

    //cout<<"Calling ("<<left<<","<<b<<","<<mid<<")  ("<<right<<","<<mid+1<<","<<e<<")"<<endl;


    init(left,b,mid);
    init(right,mid+1,e);

    result(tree[left],tree1[left],tree[right],tree1[right],node);
    //cout<<tree[left]<<" "<<tree[right]<<" "<<tree[node]<<endl;
}


int query(int node,int b,int e,int i,int j){
    if(i>e || j<b){
        return 0;
    }

    if(i<=b && e<=j){
        //cout<<"gdf   "<<node<<"   "<<tree[node]<<"  "<<tree1[node]<<endl;
        return sum( tree[node],tree1[node]);
    }


    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node+1;

    query(left,b,mid,i,j);
    query(right,mid+1,e,i,j);

    //cout<<q1<<" "<<q2<<endl;

    //return sum(tree[left],tree1[left],tree[right],tree1[right]);
}

void update(int node,int b,int e,int i,int value){
    if(i<b || i>e){
        return;
    }
    if(i<=b && i>=e){
        tree[node] = value;
        return;
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node + 1;

    update(left,b,mid,i,value);
    update(right,mid+1,e,i,value);

    result(tree[left],tree1[left],tree[right],tree1[right],node);

}


int main(){
    int n,qq,t,x,y;
        scanf("%d",&n);

        for(int i = 1 ;i<=n ; i++)
            scanf("%d",&arr[i]);

        init(1,1,n);

//    for(int i = 1 ; i<10;i++){
//        cout<<tree[i]<<" "<<tree1[i]<<endl;;
//    } cout<<endl;

        scanf("%d",&qq);
        char c;

        while(qq--){
        scanf(" %c",&c);

        scanf("%d %d",&x,&y);

        if(c=='U'){

            update(1,1,n,x,y);
        }
        else{
            p = 0,q = 0;
            query(1,1,n,x,y);

            printf("%d\n",p+q);
        }

        }
}



