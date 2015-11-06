 /* =====================================================================================
 *
 *       Filename:  rangesumquery.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 06 November 2015 04:12:10  IST
 *       Compiler:  gcc
 *
 *         Author:  Gaurav Joshi , contactgaurav27@gmail.com
 *   Organization:  University of Hyderabad
 *   help        :  use shortcuts \if \im \ \isf \ii \io \cfr \cfu 
                    \csc for adding comment history
										\rc is for compiling code
										\rr is for running code for vim only
 *
 * =====================================================================================*/

#include <bits/stdc++.h>
using namespace std;

typedef struct
{
int mn;
int mx;
}node;

vector<node> Seg(1000000);
vector<int> arr(10000);

void buildTree(int l,int r,int pos);
node query(int lx,int rx,int l,int r,int pos);
node eNode;
void update(int,int,int,int);
int main()
{
				int n;
				cin  >>  n;

				for(int i=0;i<n;i++)
								cin  >>  arr[i];

				eNode.mn=100000;
				eNode.mx=-100000;
				buildTree(1,n,1);

				cout  <<  "out of build tree \n";
				int p,q;
				cin  >>  p  >>  q;
				node tmp=query(p,q,1,n,1);
        cout  <<"min: " << tmp.mn  <<  "max: " << tmp.mx  << endl ;
        int val;
				cin >>  p  >> val;
				arr[p-1]=val;
				cout  <<  "CAlinng update \n";
				update(p,1,n,1);
				cout  << "after udapte \n";
				cin  >>  p  >>  q;
				tmp=query(p,q,1,n,1);
        cout  <<"min: " << tmp.mn  <<  "max: " << tmp.mx  << endl ;
				return 0;

}

void buildTree(int l,int r,int pos)
{
				if(l == r)
				{
								cout  <<  "inside l==r check \n";
								Seg[pos].mn=arr[l-1];
								Seg[pos].mx=arr[l-1];
								return;
				}

				int mid = (l + r)/2;
				buildTree(l,mid,2*pos);
				buildTree(mid+1,r,2*pos + 1);
				Seg[pos].mn=min(Seg[2*pos].mn,Seg[2*pos+1].mn);
				Seg[pos].mx=max(Seg[2*pos].mx,Seg[2*pos+1].mx);
				return;

}

node query(int lx,int rx,int l,int r,int pos)
{				if(l > r or l > rx or r < lx) return eNode;

				if(lx <= l && rx >=r)
								return Seg[pos];

        int mid=(l+r)/2;
				node L=query(lx,rx,l,mid,2*pos);
				node R=query(lx,rx,mid+1,r,2*pos+1);

				node ret;

				ret.mn= min(L.mn,R.mn);
				ret.mx= max(L.mx,R.mx);

				return ret;
}

void update(int idx,int l,int r,int pos)
{
	if(l > idx || r < idx) return ;
				if(l==idx && r==idx)
				{
								Seg[pos].mn=arr[l-1];
								Seg[pos].mx=arr[l-1];
								return ;
				}

				int mid=(l+r)/2;
				update(idx,l,mid,2*pos);
				update(idx,mid+1,r,2*pos+1);
				Seg[pos].mn=min(Seg[2*pos].mn,Seg[2*pos+1].mn);
				Seg[pos].mx=max(Seg[2*pos].mx,Seg[2*pos+1].mx);
				return;
}

int min(int a,int b)
{
				return(a>b?b:a);
}
int max(int a,int b)
{
				return(a>b?a:b);
}
