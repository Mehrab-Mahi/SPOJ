#include<bits/stdc++.h>
#define ll long long int
#define mx 100005

using namespace std;

ll tree[mx*4],lazy[mx*4];

ll merg(ll a , ll b){
    return a+b;
}

void relax(ll node,ll b ,ll e){
    tree[node] += (lazy[node]*(e-b+1));

    if(b!=e){
        lazy[2*node]+=lazy[node];
        lazy[2*node+1]+=lazy[node];
    }

    lazy[node]=0;
}



void updateRange(ll node,ll b,ll e,ll i,ll j,ll v){

    if(lazy[node])
        relax(node,b,e);

    if(i>e || j<b){
        return ;
    }

    if(b >= i && e <= j){
        lazy[node]+=v;
        relax(node,b,e);
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node+1;

    updateRange(left,b,mid,i,j,v);
    updateRange(right,mid+1,e,i,j,v);

    tree[node] = merg(tree[left],tree[right]);

}

void init(ll node,ll b,ll e){
    if(b==e){
        tree[node] = 0;
        lazy[node] = 0;
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node + 1;

    init(left,b,mid);
    init(right,mid+1,e);

    tree[left] = 0;
    lazy[left] = 0;
    tree[right] = 0;
    lazy[right] = 0;
    tree[node] = 0;
    lazy[node] = 0;
}


ll query(ll node,ll b,ll e,ll i,ll j){
    if(lazy[node]) relax(node, b, e);
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

int main()
{

    ll t,n,c;

    scanf("%lld",&t);

    while(t--){
        scanf("%lld %lld",&n,&c);

        init(1,1,n);

        ll cs,x,y;
        ll v;

        while(c--){

        scanf("%lld",&cs);

        if(cs==0){
            scanf("%lld %lld %lld",&x,&y,&v);
            updateRange(1,1,n,x,y,v);
        }
        else{
            scanf("%lld %lld",&x,&y);
            printf("%lld\n",query(1,1,n,x,y));
        }
        }

    }


}
