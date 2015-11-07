 /* =====================================================================================
 *
 *       Filename:  modularquery.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 06 November 2015 07:09:08  IST
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

typedef long long LL;
#define PII       pair<int,int>
#define sz(c)     (int)c.size()
#define MOD       1000000007

LL calc[4000000];

typedef struct
{
	LL val;
	int digits;
}node;

vector<node> segtree(1000000);

vector<string> arr(100000);
node eNode;

LL cal(string a)
{
	LL ret =0;
	for(int i = 0; i < sz(a); i++)
		ret = (ret * 10 + a[i] - '0') % MOD;
	cerr << ret << endl;
	return ret;
}

void buildTree(int l , int r , int pos)
{
	if(l == r)
	{
		segtree[pos].digits = sz(arr[l - 1]);
		segtree[pos].val = cal(arr[l-1]);
		return ;
	}
	int mid = (l + r) / 2;
	buildTree(l , mid , 2*pos);
	buildTree(mid + 1 , r , 2*pos + 1);
	segtree[pos].digits = segtree[2 * pos].digits + segtree[2 * pos + 1].digits;
	segtree[pos].val = segtree[2 * pos].val * calc[segtree[2 * pos + 1].digits] + segtree[2 * pos + 1].val;
	segtree[pos].val %= MOD;
}

void update(int idx , int l , int r, int pos)
{
	if(l > idx or r < idx) return ;
	if(l == idx && r == idx)
	{
		segtree[pos].digits = sz(arr[l - 1]);
		segtree[pos].val = cal(arr[l-1]);
		return ;
	}
	int mid = (l + r) / 2;
	update(idx , l , mid , 2*pos);
	update(idx , mid + 1 , r , 2*pos + 1);
	segtree[pos].digits = segtree[2 * pos].digits + segtree[2 * pos + 1].digits;
	segtree[pos].val = segtree[2 * pos].val * calc[segtree[2 * pos + 1].digits] + segtree[2 * pos + 1].val;
	segtree[pos].val %= MOD;
}

node query(int lQ,int rQ,int l ,int r,int pos)
{
	if(l > r or l > rQ or r < lQ) return eNode;
	if(l >= lQ && r <= rQ) return segtree[pos];
	int mid = (l + r) / 2;
	node L = query(lQ,rQ,l,mid,2*pos);
	node R = query(lQ,rQ,mid+1,r,2*pos + 1);
	node ret;
	ret.digits = L.digits + R.digits;
	ret.val = L.val * calc[R.digits] + R.val;
	ret.val %= MOD;	
	return ret;
}

int main()
{
				calc[0] = 1;
				for(int i = 1;i < 4000000; i++) calc[i] = (calc[i-1] * 10) % MOD;
				eNode.digits = eNode.val = 0;
				int n;
				cin >> n;
				for(int i = 0; i < n; i++)
								cin >> arr[i];
				buildTree(1 , n , 1);
				int q;
				cin >> q;
				while(q--)
				{
								int type;
								cin >> type;
								if(type == 0)
								{
												int a , b;
												cin >> a >> b;
												cout << query(a,b,1,n,1).val << endl;
								}
								else
								{
												int pos ;
												string x;
												cin >> pos >> x;
												arr[pos-1] = x;
												update(pos , 1 , n , 1);
								}
				}
				return 0;
}
