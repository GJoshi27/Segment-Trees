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
int val;
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

				eNode.val=0;
				buildTree(0,n-1,1);

				cout  <<  "out of build tree \n";
				int p,q;
				cin  >>  p  >>  q;
        cout  <<  "sum between given range: "  <<  query(p,q,0,n-1,1).val  << endl;
        int val;
				cin >>  p  >> val;
				arr[p]=val;
				cout  <<  "CAlinng update \n";
				update(p,0,n-1,1);
				cout  << "after udapte \n";
				cin  >>  p  >>  q;
        cout  <<  "Getsum after update : "  <<  query(p,q,0,n-1,1).val;
				return 0;

}

void buildTree(int l,int r,int pos)
{
				if(l == r)
				{
								cout  <<  "inside l==r check \n";
								Seg[pos].val=arr[l];
								return;
				}

				int mid = (l + r)/2;
				buildTree(l,mid,2*pos);
				buildTree(mid+1,r,2*pos + 1);
				Seg[pos].val=Seg[2*pos].val + Seg[2*pos+1].val;
				return;

}

node query(int lx,int rx,int l,int r,int pos)
{				if(l > r or l > rx or r < lx) return eNode;

				if(lx <= l && rx >=r)
								return Seg[pos];

        int mid=(l+r)/2;
				if(rx <= mid)
				return query(lx,rx,l,mid,2*pos);
				else if(l > mid)
				return query(lx,rx,mid+1,r,2*pos+1);
				else{

				node L=query(lx,rx,l,mid,2*pos);
				node R=query(lx,rx,mid+1,r,2*pos+1);
				node ret;
				ret.val= L.val + R.val;
				return ret;
				}
}

void update(int idx,int l,int r,int pos)
{
				if(l > idx || r < idx) return ;

				if(l==idx && r==idx)
				{
								Seg[pos].val=arr[l];
								return ;
				}

				int mid=(l+r)/2;
				if(idx <=mid)
								update(idx,l,mid,2*pos);
				else
								update(idx,mid+1,r,2*pos+1);
				Seg[pos].val=Seg[2*pos].val + Seg[2*pos+1].val;
				return;


}
