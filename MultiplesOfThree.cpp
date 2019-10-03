#include<bits/stdc++.h>
#define ll long long int
#define mx 100005

using namespace std;

ll tree[mx*4],one[mx*4],zero[mx*4],lazy[mx*4],two[mx*4];

ll merg(ll a , ll b){
    return a+b;
}

void relax(ll node,ll b ,ll e){

    swap(one[node],two[node]);
    swap(one[node],zero[node]);

    if(b!=e){
        lazy[2*node]++;
        lazy[2*node+1]++;

    }

    lazy[node]--;

    if(lazy[node]%3){
        relax(node,b,e);
    }
    else{
        lazy[node]=0;
    }
}



void updateRange(ll node,ll b,ll e,ll i,ll j){

    if(lazy[node]%3==0){
        lazy[node]=0;
    }
    else{
        relax(node,b,e);
    }

    if(i>e || j<b){
        return ;
    }

    if(b >= i && e <= j){
        lazy[node]++;
        if(lazy[node]==3){
            lazy[node] = 0;
        }
        else{
            relax(node,b,e);
        }

        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node+1;

    updateRange(left,b,mid,i,j);
    updateRange(right,mid+1,e,i,j);

    zero[node] = zero[left]+zero[right];
    one[node] = one[left]+one[right];
    two[node] = two[left]+two[right];

}

void init(ll node,ll b,ll e){
    if(b==e){
        zero[node] = 1;
        one[node] = 0;
        two[node] = 0;
        return;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node + 1;

    init(left,b,mid);
    init(right,mid+1,e);

    zero[node] = merg(zero[left],zero[right]);
    one[node] = merg(one[left],one[right]);
    two[node] = merg(two[left],two[right]);
}


ll query(ll node,ll b,ll e,ll i,ll j){
    if(lazy[node]%3==0){
        lazy[node] = 0;
    }
    else{
        relax(node, b, e);
    }
    if(i>e || j<b){
        return 0;
    }

    if(b >= i && e <= j){
        return zero[node];
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

//    for(int i = 1; i < 8 ;i++)
//        cout<<zero[i]<<" "<<one[i]<<" "<<two[i]<<endl;

    ll cs,x,y;
    ll v;

    while(q--){

    scanf("%lld %lld %lld",&cs,&x,&y);

    if(cs==0){
        x++;
        y++;
        updateRange(1,1,n,x,y);
    }
    else{
        x++;
        y++;
        printf("%lld\n",query(1,1,n,x,y));
    }
    }

}
