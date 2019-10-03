#include<bits/stdc++.h>
#define ll long long int
#define mx 100005

using namespace std;

ll tree[mx*4],one[mx*4],zero[mx*4],lazy[mx*4],two[mx*4];

ll merg(ll a , ll b){
    return a+b;
}

void relax(ll node,ll b ,ll e){
    swap(one[node],zero[node]);

    if(b!=e){
        lazy[2*node]++;
        lazy[2*node+1]++;

    }

    lazy[node]=0;
}



void updateRange(ll node,ll b,ll e,ll i,ll j){

    if(lazy[node]%2)
        relax(node,b,e);

    if(i>e || j<b){
        return ;
    }

    if(b >= i && e <= j){
        lazy[node]++;
        relax(node,b,e);
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node+1;

    updateRange(left,b,mid,i,j);
    updateRange(right,mid+1,e,i,j);

    one[node] = one[left]+one[right];
    zero[node] = zero[left]+zero[right];

}

void init(ll node,ll b,ll e){
    if(b==e){
        one[node] = 0;
        zero[node] = 1;
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node + 1;

    init(left,b,mid);
    init(right,mid+1,e);

    one[node] = merg(one[left],one[right]);
    zero[node] = merg(zero[left],zero[right]);
}


ll query(ll node,ll b,ll e,ll i,ll j){
    if(lazy[node]%2) relax(node, b, e);
    if(i>e || j<b){
        return 0;
    }

    if(b >= i && e <= j){
        return one[node];
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

    ll t,n,q;

    scanf("%lld %lld",&n,&q);

    init(1,1,n);

    ll cs,x,y;
    ll v;

    while(q--){

    scanf("%lld %lld %lld",&cs,&x,&y);

    if(cs==0){
        updateRange(1,1,n,x,y);
    }
    else{
        printf("%lld\n",query(1,1,n,x,y));
    }
    }

}
