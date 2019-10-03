#include<bits/stdc++.h>
#define mx 100005
#define optimize  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int tree[mx*3],arr[mx];

map<string,int>mp;
map<int,int>pos;

int result(int a,int b){
    //cout<<a<<" "<<b<<endl;
    return (a+b);
}

void init(int node,int b,int e){
    if(b==e){
        tree[node]=arr[b];
        return ;
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node + 1;

    //cout<<"Calling ("<<left<<","<<b<<","<<mid<<")  ("<<right<<","<<mid+1<<","<<e<<")"<<endl;


    init(left,b,mid);
    init(right,mid+1,e);

    tree[node] = tree[left]+tree[right];
    //cout<<tree[left]<<" "<<tree[right]<<" "<<tree[node]<<endl;
}


int query(int node,int b,int e,int i,int j){
    if(i>e || j<b){
        return 0;
    }

    if(i<=b && e<=j){
        return tree[node];
    }


    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node+1;

    int q1 = query(left,b,mid,i,j);
    int q2 = query(right,mid+1,e,i,j);

    //cout<<node<<" "<<node+1<<endl;

    return result(q1,q2);
}

void update(int node,int b,int e,int i,int value){
    if(i<b || i>e){
        return;
    }
    if(i<=b && i>=e){
        tree[node] += value;
        return;
    }

    int mid = (b+e)/2;
    int left = 2*node;
    int right = 2*node + 1;

    update(left,b,mid,i,value);
    update(right,mid+1,e,i,value);

    tree[node] = result(tree[left],tree[right]);

}


int main(){
    optimize;
    int n,q,t,x,y;


//    for(int i = 1 ; i<10;i++){
//        cout<<tree[i]<<" ";
//    } cout<<endl;

    cin>>t;

    while(t--){
        mp.clear();
        pos.clear();

        cin>>n;
        string right[n+2],wrong[n+2];

        for(int i = 1;i<=n;i++)
            cin>>wrong[i];

        for(int i = 1;i<=n;i++)
            cin>>right[i];

        //cout<<"   "<<wrong<<endl<<"   "<<right<<endl;

        string s = "";
        int x = 1;
        for(int i = 1;i<=n;i++){
            mp[right[i]]=x;
            x++;
        }

        x=1;


        for(int i = 1;i<=n;i++){
            pos[mp[wrong[i]]]= x;
            x++;
        }

        long long int ans = 0;

        init(1,1,n);

        for(int i = 1;i<=n;i++){
            update(1,1,n,pos[i],1);

            if(pos[i]+1<=n)
                ans+=query(1,1,n,pos[i]+1,n);
        }
        cout<<ans<<endl;


    }

}
