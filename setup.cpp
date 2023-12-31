#include<bits/stdc++.h>
using namespace std;
#define arr array
#define pb push_back
#define fi first
#define se second
#define I int
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll, ll>
#define tiii tuple<int,int,int>
#define vi vector<int>
#define vll vector<ll>
#define vii vector<pii>
#define vb vector<bool>
#define vc vector
#define L cout<<'\n';
#define all(x) x.begin(),x.end()
#define rep(i,a,b) for (int i=a; i<b; ++i)
#define rev(i,a,b) for (int i=a; i>b; --i)
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define setpr(x) cout<<setprecision(x)<<fixed
#define sz(v) ((int)(v).size())
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define sees(s,n) for(int i=0;i<n;i++){int x; cin>>x; s.insert(x);}
#define ms0(a) memset(a, 0, sizeof(a))


typedef int64_t int64;
typedef pair<int,int> ii;

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

//  neu truong hop ma ra kq co kha nang float thi nen xet can-1 > can +1 cho safe
// floor() l�m tr�n xu�ng, ceil() l�m tr�n l�n
// queue front, back, push, empty, pop
// stack top, back, push, empty, pop
// uoc chung lon nhat __gcd()
// set erase
// pair make_pair

bool snt[1000001];
void initSNT() {
    for(int i = 0; i <= 1e6;++i) {
        snt[i] = true;
    }
    snt[0] = false;
    snt[1] = false;
    for(int i = 2; i * i <= 1e6; ++i) {
         if(snt[i] == true) {
             for(int j = i * i; j <= 1e6; j += i)
                 snt[j] = false;
        }
    }
}

//bigInt
const int base = 1000000000;
const int base_digits = 9;
struct bigint {
    vector<int> a;
    int sign;

    bigint() :
        sign(1) {
    }

    bigint(long long v) {
        *this = v;
    }

    bigint(const string &s) {
        read(s);
    }

    void operator=(const bigint &v) {
        sign = v.sign;
        a = v.a;
    }

    void operator=(long long v) {
        sign = 1;
        if (v < 0)
            sign = -1, v = -v;
        for (; v > 0; v = v / base)
            a.push_back(v % base);
    }

    bigint operator+(const bigint &v) const {
        if (sign == v.sign) {
            bigint res = v;

            for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int) res.a.size())
                    res.a.push_back(0);
                res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry)
                    res.a[i] -= base;
            }
            return res;
        }
        return *this - (-v);
    }

    bigint operator-(const bigint &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                bigint res = *this;
                for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry)
                        res.a[i] += base;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }

    void operator*=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size())
                a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / base);
            a[i] = (int) (cur % base);
            //asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
        }
        trim();
    }

    bigint operator*(int v) const {
        bigint res = *this;
        res *= v;
        return res;
    }

    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
        int norm = base / (b1.a.back() + 1);
        bigint a = a1.abs() * norm;
        bigint b = b1.abs() * norm;
        bigint q, r;
        q.a.resize(a.a.size());

        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long) base * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.a[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }

    bigint operator/(const bigint &v) const {
        return divmod(*this, v).first;
    }

    bigint operator%(const bigint &v) const {
        return divmod(*this, v).second;
    }

    void operator/=(int v) {
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = a[i] + rem * (long long) base;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }

    bigint operator/(int v) const {
        bigint res = *this;
        res /= v;
        return res;
    }

    int operator%(int v) const {
        if (v < 0)
            v = -v;
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i)
            m = (a[i] + m * (long long) base) % v;
        return m * sign;
    }

    void operator+=(const bigint &v) {
        *this = *this + v;
    }
    void operator-=(const bigint &v) {
        *this = *this - v;
    }
    void operator*=(const bigint &v) {
        *this = *this * v;
    }
    void operator/=(const bigint &v) {
        *this = *this / v;
    }

    bool operator<(const bigint &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }

    bool operator>(const bigint &v) const {
        return v < *this;
    }
    bool operator<=(const bigint &v) const {
        return !(v < *this);
    }
    bool operator>=(const bigint &v) const {
        return !(*this < v);
    }
    bool operator==(const bigint &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const bigint &v) const {
        return *this < v || v < *this;
    }

    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }

    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }

    bigint operator-() const {
        bigint res = *this;
        res.sign = -sign;
        return res;
    }

    bigint abs() const {
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    }

    long long longValue() const {
        long long res = 0;
        for (int i = a.size() - 1; i >= 0; i--)
            res = res * base + a[i];
        return res * sign;
    }

    friend bigint gcd(const bigint &a, const bigint &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend bigint lcm(const bigint &a, const bigint &b) {
        return a / gcd(a, b) * b;
    }

    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }

    friend istream& operator>>(istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator<<(ostream &stream, const bigint &v) {
        if (v.sign == -1)
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }

    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<long long> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) p.size(); i++)
            p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(int(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int) cur);
        while (!res.empty() && !res.back())
            res.pop_back();
        return res;
    }


    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }

        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());

        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);

        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];

        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int) a1b1.size(); i++)
            r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            r[i] -= a2b2[i];

        for (int i = 0; i < (int) r.size(); i++)
            res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            res[i + n] += a2b2[i];
        return res;
    }

    bigint operator*(const bigint &v) const {
        vector<int> a6 = convert_base(this->a, base_digits, 6);
        vector<int> b6 = convert_base(v.a, base_digits, 6);
        vll a(a6.begin(), a6.end());
        vll b(b6.begin(), b6.end());
        while (a.size() < b.size())
            a.push_back(0);
        while (b.size() < a.size())
            b.push_back(0);
        while (a.size() & (a.size() - 1))
            a.push_back(0), b.push_back(0);
        vll c = karatsubaMultiply(a, b);
        bigint res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int) c.size(); i++) {
            long long cur = c[i] + carry;
            res.a.push_back((int) (cur % 1000000));
            carry = (int) (cur / 1000000);
        }
        res.a = convert_base(res.a, 6, base_digits);
        res.trim();
        return res;
    }
};
/*
how to use
string A, B; cin >> A >> B;
bigint a(A);
bigint b(B);
end bigInt
*/

/*
string add(std::string a, std::string b) {
  while ((int) a.size() < (int) b.size()) {
    a = "0" + a;
  }
  while ((int) b.size() < (int) a.size()) {
    b = "0" + b;
  }
  std::string ret;
  ret.resize((int) a.size());
  int rem = 0;
  for (int i = (int) a.size() - 1; i >= 0; i--) {
    int sum = a[i] - '0' + b[i] - '0' + rem;
    int dig = sum % 10;
    rem = sum / 10;
    ret[i] = (char) (dig + '0');
  }
  if (rem == 1) {
    ret = "1" + ret;
  }
  return ret;
}
*/

//kruskal
/*
struct edge{
	int u, v;
	int w;
	edge(int canhdau, int canhcuoi, int trongso) : u(canhdau), v(canhcuoi), w(trongso){
	}
};

const int maxn = 1001;

int n, m;
int parent[maxn], size[maxn];

vector<edge> canh;

void make_set() {
	for(int i = 1; i <= n; i++) {
		parent[i] = i;
		size[i] = 1;
	}
}

int find(int v) {
	if(v == parent[v]) return v;
	return parent[v] = find(parent[v]);
}

bool Union(int a, int b) {
	int PA = find(a);
	int PB = find(b);
	if(PA != PB) {
		if(size[PA] < size[PB]) swap(PA, PB);
		parent[PB] = PA;
		size[PA] += size[PB];
		return true;
	}
	return false;
}

void input() {
	cin >> n >> m;
 	for(int i = 0; i < m; i++) {
 		int x, y, w; cin >> x >> y >> w;
 		edge e = edge(x, y, w);
 		canh.push_back(e);
	}
}

bool cmp(edge x, edge y) {
	return x.w < y.w;
}

void kruskal() {
//	tao cay khung cuc tieu rong
	vector<edge> mst;
	int d = 0;
//	sort cac canh theo chieu dai tang dan
	sort(canh.begin(), canh.end(), cmp);
//	lap cho den khi het cac canh hoac mst co n-1 phan tu
	for(int i = 0; i < m; i++) { // m la so canh
		if(mst.size() == n-1) break;
		edge e = canh[i];
		if(Union(e.u, e.v)) {
			mst.push_back(e);
			d += e.w;
		}
		else continue;
	}
	if(mst.size() != n-1) {
		cout<<"NO FIND WAY";
		return ;
	}
	else {
		cout<<"MST: "<<d<<endl;
		for(edge it : mst) {
			cout<<it.u<<" "<<it.v<<" "<<it.w<<endl;
		}
	}
}

import 3 line below to handle kruskal
input();
make_set();
kruskal();
*/

/* prim toi uu chua setup het
int parent[maxn], d[maxn];
void primWithPriorityQueue(int u) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	vector<canh> MST;
	int res = 0;
	Q.push({0, u});
	while(!Q.empty()) {
		pair<int, int> top = Q.top(); Q.pop();
		int x = top.second;
		int w = top.first;
		if(visited[x]) continue;
		res += w;
		visited[x] = true;
		if(u != x) {
			MST.push_back({x, parent[x], w});
		}
		for(auto it : adj[x]) {
			if(!visited[it.first] && it.second < d[it.first]) {
				Q.push({it.second, it.first});
				d[it.first] = it.second;
				parent[it.first] = x;
			}
		}
	}
	cout<<res<<endl;
	for(canh e : MST) {
		cout<<e.x<<" "<<e.y<<" " <<e.w << endl;
	}
}

*/

// dijkstra
/*
const int maxn = 200001;

int n, m, q;
vector<pll> adj[maxn];

void nhap() {
	cin >> n >> m >> q;
	for(int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w;
		adj[x].push_back({y, w});
		adj[y].push_back({x, w});
	}
}
// tim tu dinh s den moi dinh
void dijkstra(int s) {
	vector<ll> d(n+1, 1e18);
	vector<bool> visited(n+1, 0);
	priority_queue <pll, vector<pll>, greater<pll>> Q;
	d[s] = 0;
	Q.push({0, s});
	while(!Q.empty()) {
		pll x = Q.top();
		Q.pop();
		if(visited[x.se]) continue;
		for(pll tmp : adj[x.se]) {
			if(d[tmp.fi] > d[x.se] + tmp.se) {
				d[tmp.fi] = d[x.se] + tmp.se;
				Q.push({d[tmp.fi], tmp.fi});
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		cout<<d[i]<<" ";
	}
}
dijkstra(1);
*/

/*
floydWarshall tim duong di giua moi cap dinh
neu ton tai nhieu canh co cung x y hoac y x thi xet cost cua canh = min cua cost cu vs cost moi
void init_trace(vector<vector<int>> &trace) {
    int n = trace.size();
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            trace[u][v] = u;
        }
    }
}

void floydWarshall(int n, vector<vector<long long>> &w, vector<vector<long long>> &D, vector<vector<int>> &trace) {
    D = w;
    init_trace(trace); // n?u c?n d? ��?ng �i

    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (D[u][v] > D[u][k] + D[k][v]) {
                    D[u][v] = D[u][k] + D[k][v];
                    trace[u][v] = trace[k][v];
                }
            }
        }
    }
}
vector<int> trace_path(vector<vector<int>> &trace, int u, int v) {
    vector<int> path;
    while (v != u) { // truy v?t ng�?c t? v v? u
        path.push_back(v);
        v = trace[u][v];
    }
    path.push_back(u);

    reverse(path.begin(), path.end()); // c?n reverse v? ��?ng �i t? v ng�?c v? u

    return path;
}
*/

/* base segmentTree
const int maxn = 100000;
int n;
int a[maxn];
int t[4*maxn];

void build(int v, int l, int r) {
	if(l > r) return;
	if(l == r) {
		t[v] = a[l];
		return;
	}else {
		int mid = (l+r) / 2;
		build(v*2, l, mid);
		build(v*2+1, mid+1, r);
		// caculator sum
		t[v] = t[v*2] + t[v*2+1];
		// caculator min
		t[v] = min(t[v*2], t[v*2+1]);
	}
}

// query sum a[l, r]
int sum(int v, int tl, int tr, int l, int r) {
	if(l == tl && r == tr) {
		return t[v];
	}
	if(l >= tl && r <= tr) return t[v];
	else {
		int mid = (tl+tr) / 2;
		return sum(v*2, tl, mid, l, min(mid, r)) + sum(v*2+1, mid+1, tr, max(mid+1, l) , r);
	}
}

// query min a[l, r]
int MIN(int v, int tl, int tr, int l, int r) {
	if(l > tr || r < tl) return INT_MAX;
	if(l == r) {
		return t[v];
	}
	//cmt duoi nen test
//	if(l >= tl && r <= tr) return t[v];
	else {
		int mid = (l+r) / 2;
		return min(MIN(2*v, l, mid, l, min(r, mid)), MIN(2*v+1, mid+1, r, max(l, mid+1), r));
	}
}
// update l -> r

void update2(int v, int tl, int tr, int l, int r, int val) {
	if(l > tr || r < tl) return;
	if(l == r) {
		t[v] += val;
		return;
	}
	int mid = (l+r) / 2;
	update2(2*v, tl, mid, l, r, val);
	update2(2*v+1, mid+1, tr, l, r, val);
	t[v] = min(t[v*2], t[2*v+1]);
}


// update a[post] = val

void update(int v, int l, int r, int pos, int val) {
	if(l == r) {
		t[v] = val;
	}
	else {
		int mid = (l+r) /2;
		if(pos <= mid) update(v*2, l, mid, pos, val);
		else update(v*2+1, mid+1, r, pos, val);
		t[v] = t[v*2] + t[v*2+1];
	}
}
*/

//convert number to string
//string stri = to_string(value);

//convert string to number
// stoi(value), stoll()
// a << b tuong duong a*2^b

//define int int64_t la int co 64 bit tuong duong long long
//define int int32_t la int co 32 bit

/*
mang thua (sparse table)
LG l� so lon nhat thoa man 2^LG < N
v� du: N = 10^5 thi LG = 16 vi 2^16 = 65536
int a[N], st[LG + 1][N];
void preprocess() {
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];
    for (int j = 1; j <= LG; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i)
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}
int queryMin(int l, int r) {
    int k = __lg(r - l + 1);
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}
*/

/*
string s;
getline(cin, s); de lay cac cum tu

int countWords(string str)
{
    // Breaking input into word
    // using string stream

    // Used for breaking words
    stringstream s(str);

    // To store individual words
    string word;

    int count = 0;
    while (s >> word)
        count++;
    return count;
}
*/
// next_permutation(s.begin(), s.end())
// priority_queue<int> pq; la tao mang se theo chieu giam dan
// priority_queue <int, vector<int>, greater<int>> gq; la tao mang theo chieu tang dan
// priority_queue <pair<int,int>, vector<int, int>, greater<int, int>> gq; la tao mang tang dan theo x.first
// multiset<lli, greater<int>> tickets; tao multiset giam dan
// accumulate(all(v),0LL); tinh tong tu begin -> end dau vao init = 0
/*
f = 3.1
n = 4
cout << setprecision(n) << fixed << f;// lay so thap phan f=3.1000
*/
// dung BFS tim duong di ngan nhat tu 1 dinh den dinh can tim
// A65 Z90 a97 z122 0.48 9.57 ascii
// s1.find(s2) != string::npos kiem tra xem chuoi s2 co phai la chuoi con s1 ko

const int maxn = 1e5+1;
const int MOD = 1e9+7;

int main() {
	IOS;
//	freopen("SETUP.inp", "r", stdin);
//  freopen("SETUP.out", "w", stdout);
   	return 0;
}

