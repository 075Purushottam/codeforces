#include <bits/stdc++.h>
using namespace std;

void build(int ind,int low,int high,int arr[],int seg[]){
  if(low == high){
    seg[ind] = arr[low];
  }else{
    int mid = (low+high)/2;
    build(ind*2+1,low,mid,arr,seg);
    build(ind*2+2,mid+1,high,arr,seg);

    seg[ind] = min(seg[ind*2+1],seg[ind*2+2]);
  }
}

int query(int ind,int low,int high,int l,int r,int seg[]){
    // [low high l r] [l r low high]
    if(high<l || r<low) return INT_MAX;
    
    // complete overlap [ l low high r ]
    
    else if(low >= l && r >= high) return seg[ind];
    // partial overlap
    else{
        int mid = (low+high)/2;
        int left = query(ind*2+1,low,mid,l,r,seg);
        int right = query(ind*2+2,mid+1,high,l,r,seg);
        return min(left,right);
    }
}

void pointUpdate(int ind,int i,int val,int low,int high,int seg[]){
    if(low == high){ 
        seg[ind] = val;
        return;
    }
    
        int mid = (low+high)/2;
        if(i<=mid) pointUpdate(2*ind+1,i,val,low,mid,seg);
        else pointUpdate(2*ind+2,i,val,mid+1,high,seg);
        seg[ind] = min(seg[2*ind+1],seg[2*ind+2]); 
}

int main() {
  int n;
  cin>>n;
  int arr[n];
  int seg[4*n];
  for(int i=0;i<n;i++) cin>>arr[i];
  build(0,0,n-1,arr,seg);
  
  for(int i=0;i<9;i++) cout<<seg[i]<<" ";
  cout<<endl;
  
  int l,r;
  cin>>l>>r;
  cout<<query(0,0,n-1,l,r,seg)<<endl;
  
  int i,val;
  cin>>i>>val;
  pointUpdate(0,i,val,0,n-1,seg);
  
  cin>>l>>r;
  cout<<query(0,0,n-1,l,r,seg);
  
  return 0;
}