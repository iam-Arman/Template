                                                  //   Bismillahir Rahmanir Rahim      //
                                                 //     After hardship comes ease     //
                                                //         AUTHOR : iamarman         //

// pragmas
#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("strict-overflow")
 

#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>


using namespace std;
using namespace __gnu_pbds;

                                                    ////       TEMPLATE       ////

//---------------------------------------------------------------------------------------------------------------------------------|

typedef     vector<int> vii;
typedef     vector<long long> vll;
typedef     vector<pair<int,int> > vpi;
typedef     vector<pair<long long,long long > > vpl;

# define    el '\n'
# define    ff first
# define    ss second
# define    R0 return 0
# define    ll long long
# define    noo1 cout<<-1<<el;  
# define    ull unsigned long long                                                                                                         
# define    rep(i,a,b) for(int i=a;i<b;i++)
# define    rep_n(i,a,b) for(int i=a;i<=b;i++)
# define    test int test; cin>>test; while(test--)
# define    rep_rev(i,a,b) for(int i=b;a>=1;i--)
# define    allr(v) v.rbegin(),v.rend()
# define    all(v) v.begin(),v.end()
# define    yess cout<<"YES"<<el
# define    siz(x) (int)x.size()
# define    noo cout<<"NO"<<el
# define     yess1 cout<<1<<el
# define    pb push_back
# define    mp make_pair
# define    sp " "


constexpr ll mod=1000000000+7;
constexpr ll INF=LLONG_MAX;
constexpr double PI= acos(-1);
constexpr double eps=1e-9;

# define mem(a,b) memset(a,b,sizeof(a))
# define sqr(a) ((a)*(a))
# define lcm(a,b) (a*b)/__gcd(a,b)

# define optimise   { ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); }
# define fraction(a) cout.unsetf(ios::floatfield); cout.precision(a); cout.setf(ios::fixed,ios::floatfield);
# define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

// find_by_order() - Returns an iterator to the k-th largest element (counting from zero)
// order_of_key()  - The number of items in a set that are strictly smaller than our item 
// greater instead of less for descending order
// less_equal works as ordered multiset
// we can use pair<int,int> instead of int for pair of orderd set
// for multiset st.lower_bound(x) works as upper bound and st.upper_bound(x) works as lower bound


typedef vector<int>::iterator vit;
typedef vector<ll>::iterator vlt;
typedef set<int>::iterator sit;
typedef map<int,int>::iterator mit;


//                                           -- Custom hash for unordered map and unordered set --

template <typename KeyType>  // use as unordered_map<int, int, custom_hash<int>> mp;  / unordered_map<pair<int,string>, int, custom_hash<pair<int,string>>> mp;
struct custom_hash {         // use as unordered_set<int, custom_hash<int>> s;
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

     // Specialization for int keys
    size_t operator()(int key) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(static_cast<uint64_t>(key) + FIXED_RANDOM);
    }

    // Specialization for std::string keys
    size_t operator()(const std::string& key) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(std::hash<std::string>{}(key) + FIXED_RANDOM);
    }

   
   //  Specialization for std::pair
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& key) const {
        size_t hash1 = operator()(key.first);
        size_t hash2 = operator()(key.second);
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }

    // Template specialization for other types
    template <typename T>
    size_t operator()(const T& key) const {
        static_assert(std::is_arithmetic<T>::value, "Unsupported key type");
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(static_cast<uint64_t>(key) + FIXED_RANDOM);
    }
  // // Specialization for std::set keys
    template <typename T>
    size_t operator()(const std::set<T>& key) const {
        size_t hash = 0;
        for (const T& element : key) {
            hash ^= operator()(element);
        }
        return hash;
    }

   // Specialization for std::vector keys
    template <typename T>
    size_t operator()(const std::vector<T>& key) const {
        size_t hash = 0;
        for (const T& element : key) {
            hash ^= operator()(element);
        }
        return hash;
    }

    // Specialization for std::map keys
    template <typename K, typename V>
    size_t operator()(const std::map<K, V>& key) const {
        size_t hash = 0;
        for (const auto& pair : key) {
            hash ^= operator()(pair.first) ^ operator()(pair.second); 
        }
        return hash;
    }

   
};



inline void file() {
 
#ifndef ONLINE_JUDGE
 
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
 
#endif // ONLINE_JUDGE

}

//----------------------------------------------------------------------------------------------------------------------------------|



                                                               // DEBUGGER //


//----------------------------------------------------------------------------------------------------------------------------------|

template < typename F, typename S > ostream& operator << ( ostream& os, const pair< F, S > & p ) { return os << "(" << p.first << ", " << p.second << ")"; }
 
template < typename T > ostream &operator << ( ostream & os, const vector< T > &v ) { os << "{"; for(auto it = v.begin(); it != v.end(); ++it) { if( it != v.begin() ) os << ", ";  os << *it; }  return os << "}";  }
 
template < typename T >  ostream &operator << ( ostream & os, const set< T > &v ) { os << "["; for(auto it = v.begin(); it != v.end(); ++it) { if( it != v.begin() ) os << ", "; os << *it;  } return os << "]"; }
 
template < typename T > ostream &operator << ( ostream & os, const multiset< T > &v ) { os << "["; for(auto it = v.begin(); it != v.end(); ++it) { if( it != v.begin() ) os << ", "; os << *it; } return os << "]"; }
 
template < typename F, typename S > ostream &operator << ( ostream & os, const map< F, S > &v ) { os << "["; for(auto it = v.begin(); it != v.end(); ++it) { if( it != v.begin() ) os << ", "; os << it -> first << " = " << it -> second ; } return os << "]";  }
 
#define dbg(args...) do {cerr << #args << " : "; iamarman(args); } while(0)
 
void iamarman () { cerr << endl; }
 
template <typename T> void iamarman( T a[], int n ) {   for(int i = 0; i < n; ++i) cerr << a[i] << ' '; cerr << endl;  }
 
template <typename T, typename ... hello>  void iamarman( T arg, const hello &... rest) {   cerr << arg << ' ';  iamarman(rest...);  }

//--------------------------------------------------------------------------------------------------------------------------------------|



  
                                                           /////    FUNCTIONS     /////



ll bigmod(ll base,ll power){ ll res=1; ll p=base%mod; while(power>0) { if(power%2==1) {  res=((res%mod)*(p%mod))%mod; }  power/=2; p=((p%mod)*(p%mod))%mod; } return res; }

ll inversemod(ll base) { return bigmod(base,mod-2); }

ll poww(ll a,ll b) { ll ans=1; if(!b) return 1; while(b>1) {  if(b&1) { ans=ans*a%mod; } a=a*a%mod; b/=2; }return a*ans%mod; }

int gcd(ll a,ll b) { ll rem; while(b%a!=0)  {  rem=b%a;  b=a;  a=rem; } return a; }


int dx[]={-1, 1 , 0 , 0 , -1 ,-1, 1, 1};
int dy[]={ 0, 0 ,-1 , 1 , -1 , 1,-1, 1};

// up = { -1,0 } , down = { 1,0 } , right = { 0,1 } , left = { 0,-1 }
// up-right = { -1,1 } , up-left = { -1,-1 } , down-right = { 1,1 } , down-left = { 1,-1 }




                                                   ///  ____________CODE STARTS FROM HERE____________    ///





void solve()
{
    

    
}

int main()
{
    optimise;
    file();
 
    clock_t q= clock();
   //test
    { 

      solve();
    }
 
    cerr << "Run Time : " <<((double)(clock() - q) / CLOCKS_PER_SEC)<<el;
  
}
