 /* =====================================================================================
 *
 *       Filename:  2vs3.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 06 November 2015 09:10:54  IST
 *       Compiler:  gcc
 *
 *         Author:  Gaurav Joshi , contactgaurav27@gmail.com
 *   Organization:  University of Hyderabad
 *   help        :  use shortcuts \if \im \ \isf \ii \io \cfr \cfu 
                    \csc for adding comment history
										\rc is for compiling code
										\rr is for running code for vim only
 *
 *
 *   Problem     : https://www.hackerearth.com/problem/algorithm/2-vs-3/
 * =====================================================================================*/


#include <bits/stdc++.h>
using namespace std;

#define MAX 1000005
typedef int ll;

ll arr[MAX];
ll Seg[4*MAX];
ll bin[MAX];
void buildTree(ll pos,ll l,ll r);
ll query(ll pos,ll l,ll r,ll lq,ll rq);
void update(ll pos,ll l,ll r,ll idx);

int main()
{
				bin[0]=1;
				for(ll j=1;j<=100000;j++)
								bin[j]=(bin[j-1]*2)%3;
				ll n;
				cin  >>  n;
				string s;
				cin  >>  s;
				for(ll i=0;i<n;i++)
				{
								arr[i]=s[i]-'0';
				}
				buildTree(1,0,n-1);
				ll q;
        cin  >> q;
				while(q-- > 0)
				{
								int type;
								cin >> type;
								if(type==0)
								{
												ll lq,rq;
												cin  >>  lq  >>  rq;
												ll ans=query(1,0,n-1,lq,rq);
												cout<<ans<< endl;
								}
								else
								{
												ll  indx=0;
												cin  >>  indx;
																arr[indx]=1;
																update(1,0,n-1,indx);

								}

				}
        return 0;
}

void buildTree(ll pos,ll l,ll r)
{
				if(l==r)
				{
								Seg[pos]=arr[l];
								return;
				}

				if(l>r)
								return ;

				ll mid=(l+r)/2;
				buildTree(2*pos,l,mid);
				buildTree(2*pos+1,mid+1,r);
		    ll temp=(r-mid);
        Seg[pos]=(Seg[2*pos]*bin[temp] + Seg[2*pos+1])%3;
				return;

}

ll query(ll pos,ll l,ll r,ll lq,ll rq)
{
	if(l > r || l > rq || r < lq) return 0;
     	if(l >= lq && r <=rq) return (Seg[pos]%3);

		ll mid=(l+r)/2;
		if(rq<=mid) return query(2*pos,l,mid,lq,rq);
		else if(mid+1<=lq) return query(2*pos+1,mid+1,r,lq,rq);
		else{
		ll L=query(2*pos,l,mid,lq,mid);
	  ll R=query(2*pos+1,mid+1,r,mid+1,rq);
		ll temp=bin[rq-mid];
    ll tmp=(L*temp + R)%3;
		return tmp;
		}
}


void update(ll pos,ll l,ll r,ll idx)
{
				if (l==r)
				{
								Seg[pos]=1;
								return ;
				}

				ll mid=(l+r)/2;
  		  if(l <= idx && idx<=mid)
								update(2*pos,l,mid,idx);    
				else    
								update(2*pos+1,mid+1,r,idx);    

				ll temp=(r-mid);
        Seg[pos]=(Seg[2*pos]*bin[temp]+ Seg[2*pos+1])%3;
				return;
}


