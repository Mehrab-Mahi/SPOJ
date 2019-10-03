#include<bits/stdc++.h>
#define ll long long int
#define mx 100005

using namespace std;

ll tree[mx*4],lazySet[mx*4],lazySquare[mx*4],arr[mx*4];

ll merg(ll a , ll b){
    return a + b;
}

void relaxSet(ll node , ll b , ll e){
    tree[node] = (e-b+1)*(lazySet[node]*lazySet[node]);

    if(b!=e){
        lazySet[2*node] = lazySet[node];
        lazySet[2*node+1] = lazySet[node];
    }
    lazySet[node] = 0;
}


void updateSet(int node,int b,int e,int i,int j,int value){

    if(lazySet[node])
        relaxSet(node,b,e);

    if(i>e || j<b){
        return;
    }

    if(i<=b && j>=e){
        lazySet[node]=value;
        relaxSet(node,b,e);
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node+1;

    updateSet(left,b,mid,i,j,value);
    updateSet(right,mid+1,e,i,j,value);

    tree[node] = merg(tree[left],tree[right]);

}



void updateSquare(ll node,ll b,ll e,ll i,ll j,ll value){

    if(lazySet[node])
        relaxSet(node,b,e);

    if(i>e || j<b)
        return;

    if(b==e){
        tree[node] = sqrt(tree[node]);
        tree[node]+=value;
        tree[node]= tree[node]*tree[node];
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node + 1;

    updateSquare(left,b,mid,i,j,value);
    updateSquare(right,mid+1,e,i,j,value);

    tree[node] = merg(tree[left],tree[right]);


}

ll query(ll node,ll b,ll e,ll i,ll j){

    if(lazySet[node])
        relaxSet(node,b,e);

    if(i>e || j<b){
        return 0;
    }

    if(b >= i && e <= j){
        return tree[node];
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node + 1;

    ll p = query(left,b,mid,i,j);
    ll q = query(right,mid+1,e,i,j);

    return merg(p,q);
}


void init(ll node,ll b,ll e){
    if(b==e){
        tree[node] = arr[b]*arr[b];
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node + 1;

    init(left,b,mid);
    init(right,mid+1,e);

    tree[node] = merg(tree[left],tree[right]);
}


int main()
{
    ll t,n,q,cs,x,y,xx,tst=1;

    scanf("%lld",&t);

    while(t--){
        scanf("%lld %lld",&n,&q);

        for(int i = 1;i<=n;i++)
            scanf("%lld",&arr[i]);

        init(1,1,n);

//        for(int i = 1;i<=7;i++)
//            cout<<tree[i]<<" ";
//        cout<<endl;

        printf("Case %lld:\n",tst++);
        while(q--){
            scanf("%lld",&cs);

            if(cs==0){
                scanf("%lld %lld %lld",&x,&y,&xx);
                updateSet(1,1,n,x,y,xx);
            }
            else if(cs==1){
                scanf("%lld %lld %lld",&x,&y,&xx);
                updateSquare(1,1,n,x,y,xx);
            }
            else{
                scanf("%lld %lld",&x,&y);
                printf("%lld\n",query(1,1,n,x,y));
            }
        }


    }

}
