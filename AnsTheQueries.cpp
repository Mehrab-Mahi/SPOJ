#include<bits/stdc++.h>
#define ll long long int
#define mx 100005

using namespace std;


ll arr[mx*4];


struct str{
     int prefix ,suffix ,sum ,max_sum ;

};

str merg(str a,str b)
{
    str ret ;

    ret.sum = a.sum + b.sum ;

    ret.max_sum = max( max( a.max_sum , b.max_sum ) , (a.suffix + b.prefix ) ) ;

    ret.prefix = max( a.prefix , a.sum + b.prefix );

    ret.suffix = max( b.suffix , b.sum + a.suffix );

    return ret ;
}

str tree[mx*4];


void init(ll node,ll b,ll e){
    if(b==e){
        tree[node].prefix = tree[node].suffix = tree[node].sum = tree[node].max_sum = arr[b] ;
        return ;
    }

    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node + 1;



    init(left,b,mid);
    init(right,mid+1,e);

    tree[ node ] = merg( tree[left] , tree[right] );
}


str query(ll node,ll b,ll e,ll i,ll j){

    if(i==b && e==j){
        return tree[node];
    }


    ll mid = (b+e)/2;
    ll left = 2*node;
    ll right = 2*node+1;

    if(j <= mid)
        return query(left,b,mid,i,j);

    else if(i > mid)
        return query(right,mid+1,e,i,j) ;

    else
    {
        return merg( query(left,b,mid,i,mid) , query(right,mid+1,e,mid+1,j)) ;
    }


}


int main(){
    ll n,q,x,y;

    scanf("%lld",&n);

    for(int i = 1;i<=n;i++)
        scanf("%lld",&arr[i]);

    init(1,1,n);


    scanf("%lld",&q);

    while(q--){


        scanf("%lld %lld",&x,&y);
        printf("%lld\n",query(1,1,n,x,y).max_sum );

    }
}
