                                                  //   Bismillahir Rahmanir Rahim      //
                                                 //     After hardship comes ease     //
                                                //         AUTHOR : iamarman         //

// pragmas
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx,avx2,fma")
// #pragma GCC optimization ("unroll-loops")
// #pragma GCC optimization ("strict-overflow")
 
#include<bits/stdc++.h>


using namespace std;

#ifndef __clang__
    #include <ext/pb_ds/tree_policy.hpp>
    #include <ext/pb_ds/assoc_container.hpp>
    using namespace __gnu_pbds;
#endif

                                                    ////       TEMPLATE       ////

//---------------------------------------------------------------------------------------------------------------------------------|


# define    el '\n'
# define    sp " "
# define    ff first
# define    ss second
# define    ll long long
# define    pb push_back
# define    mp make_pair
# define    yess1 cout<<1<<el 
# define    noo cout<<"NO"<<el
# define    yess cout<<"YES"<<el
# define    siz(x) (int)x.size()
# define    ull unsigned long long    
# define    all(v) v.begin(),v.end()
# define    allr(v) v.rbegin(),v.rend()
# define    torad(x) ((x) * ((2*acos(0))/180.0))
# define    todeg(x) ((x) * (180.0/(2*acos(0))))

constexpr ll mod=1000000000+7;
constexpr ll INF=LLONG_MAX;
const double PI= acos(-1);
constexpr double eps=1e-9;

# define mem(a,b) memset(a,b,sizeof(a))
# define sqr(a) ((a)*(a))
# define lcm(a,b) (a*b)/__gcd(a,b)

# define optimise   { ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
# define fraction(a) cout.unsetf(ios::floatfield); cout.precision(a); cout.setf(ios::fixed,ios::floatfield);
# define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>

// find_by_order() - Returns an iterator to the k-th largest element (counting from zero)
// order_of_key()  - The number of items in a set that are strictly smaller than our item 
// greater instead of less for descending order
// less_equal works as ordered multiset
// we can use pair<int,int> instead of int for pair of orderd set
// for multiset st.lower_bound(x) works as upper bound and st.upper_bound(x) works as lower bound

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

ll poww(ull a,ull b) { ull ans=1; if(!b) return 1; while(b>1) {  if(b&1) { ans=ans*a%mod; } a=a*a%mod; b/=2; }return a*ans%mod; }

int gcd(ll a,ll b) { ll rem; while(b%a!=0)  {  rem=b%a;  b=a;  a=rem; } return a; }

ll sqrtt(ll a){ long long x = sqrt(a) + 2; while (x * x > a) x--; return x;}

ll sqrt(ll n) {ll low=0,high=1e10; while(high-low>1){ ll mid=low+(high-low)/2; if(mid*mid<=n) low=mid; else high=mid; }return low; }

long double sqrtd(long double n){ long double low=0,high=n,mid; for(int i=0;i<100;i++) { mid=(low+high)/2; if(mid*mid<=n) low=mid; else high=mid;} return low;}

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

inline ll getrandom(ll a,ll b) { return uniform_int_distribution<ll>(a,b)(rng); }

 
int dx[]={-1, 1 , 0 , 0 , -1 ,-1, 1, 1};
int dy[]={ 0, 0 ,-1 , 1 , -1 , 1,-1, 1};

// up = { -1,0 } , down = { 1,0 } , right = { 0,1 } , left = { 0,-1 }
// up-right = { -1,1 } , up-left = { -1,-1 } , down-right = { 1,1 } , down-left = { 1,-1 }




                                                   ///  ____________CODE STARTS FROM HERE____________    ///


void solve()
{  
   int n;
   cin>>n;
   vector<int> vec(n+1);
   for(int i=1;i<=n;i++)
   {
	   cin>>vec[i];
   }
   
   for(int i=1;i<=n;i++)
   {
	   cout<<vec[i]<<sp;
   }
   cout<<el;
}
int main()
{ 
    optimise;
    #ifdef LOCAL
        auto start = chrono::high_resolution_clock::now();
    #endif
    
    int t=1;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
		#ifdef LOCAL
            cout <<"\tTest case " << i << endl;
        #endif
        
        solve();
    }
    #ifdef LOCAL
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cerr << "Time taken: " << duration.count() / 1000.0 << " ms" << endl;
    #endif
  
}

 



// run() {
// # Compile the file (uses the first argument $1)
//     g++ -o sol -Wall -Wextra -std=c++17 -O2 -DLOCAL "$1.cpp"
        
//     # If compilation is successful ($? -eq 0), run it
//     if [ $? -eq 0 ]; then
//         echo "Running with input.txt..."
//         time ./sol < input.txt
//     fi  
        
// }

// TIMEFMT=$'\nReal:\t%E\nUser:\t%U\nSys:\t%S'

// match() {
//     # 1. Compile (NO -DLOCAL, so output is clean for checking)
//     g++ -o sol -Wall -Wextra -std=c++17 -O2 "$1.cpp"

//     if [ $? -eq 0 ]; then
//         echo "--- Running $1 vs expected.txt ---"

//         # 2. Run code and measure time
//         # We capture the start/end time to warn if it's too slow (Time Limit Exceeded)
//         start=$(date +%s.%N)
//         ./sol < input.txt > my_output.txt
//         end=$(date +%s.%N)
//         runtime=$( echo "$end - $start" | bc -l )

//         # 3. Smart Python Checker
//         if [ -f "expected.txt" ]; then
//             python3 -c "
// import sys

// def is_float(s):
//     try:
//         float(s)
//         return True
//     except ValueError:
//         return False

// try:
//     with open('my_output.txt') as f1, open('expected.txt') as f2:
//         out = [line.strip() for line in f1 if line.strip()]
//         exp = [line.strip() for line in f2 if line.strip()]
// except:
//     print('Error reading files.')
//     sys.exit(1)
// passed_count = 0
// total_cases = max(len(out), len(exp))

// for i in range(total_cases):
//     val_out = out[i] if i < len(out) else '(missing)'
//     val_exp = exp[i] if i < len(exp) else '(missing)'

//     match = False

//     # Check 1: Exact String Match
//     if val_out == val_exp:
//         match = True
//     # Check 2: Floating Point Match (Precision 1e-6)
//     elif is_float(val_out) and is_float(val_exp):
//         if abs(float(val_out) - float(val_exp)) < 1e-6:
//             match = True

//     if match:
//         print(f'\033[1;32m✅ OK (Test Case {i+1})\033[0m')
//         passed_count += 1
//     else:
//         print(f'\033[1;31m❌ Test Case {i+1} Failed!\033[0m')
//         print(f'   Your Output: \033[1m{val_out}\033[0m')
//         print(f'   Expected:    \033[1m{val_exp}\033[0m')
//         print('-' * 30)

// # 4. Final Summary
// print('\n' + '='*30)
// if passed_count == total_cases:
//     print(f'\033[1;32m🎉 ACCEPTED ({passed_count}/{total_cases})\033[0m')
// else:
//     print(f'\033[1;31m💀 WRONG ANSWER ({passed_count}/{total_cases} passed)\033[0m')
// print('='*30)
// "
//             # 5. TLE Warning (if slower than 1.0s)
//             if (( $(echo "$runtime > 1.0" |bc -l) )); then
//                 echo "\033[1;33m⚠️  WARNING: Slow Runtime (${runtime}s)\033[0m"
//             else
//                 echo "\033[1;30mRuntime: ${runtime}s\033[0m"
//             fi

//         else
//             echo "No 'expected.txt' found."
//             cat my_output.txt
//         fi

//         rm my_output.txt
//     fi
// }


// debug() {
//     # 1. Automatically silence the Mac "Nano Zone" warning
//     export MallocNanoZone=0

//     echo "\n\033[1;34m🛠️  [DEBUG MODE] Compiling $1.cpp...\033[0m"

//     # 2. Compile with Clang (Best for Mac)
//     # -g        : Adds line numbers to error messages
//     # -O0       : Disables optimization so variables are easy to track
//     # -fsanitize: Turns on the "Crash Catcher" (Address + Undefined Behavior)
//     clang++ -o sol -std=c++17 -g -O0 -fsanitize=address,undefined -DLOCAL "$1.cpp"

//     if [ $? -ne 0 ]; then
//         echo "\033[1;31m❌ Compilation Failed!\033[0m"
//         return
//     fi

//     echo "\033[1;32m✅ Compilation Successful. Running...\033[0m"
//     echo "==================================================="

//     # 3. Run with extra checks (Catch stack errors)
//     # We capture the exit code ($?) to check if it crashed
//     ASAN_OPTIONS=detect_stack_use_after_return=1 ./sol < input.txt
//     EXIT_CODE=$?

//     echo "\n==================================================="
//  # 4. Final Verdict
//     if [ $EXIT_CODE -eq 0 ]; then
//         echo "\033[1;32m✨ CLEAN RUN: No crashes or memory errors detected.\033[0m"
//     else
//         echo "\033[1;31m💀 CRASH DETECTED! (Exit Code: $EXIT_CODE)\033[0m"
//         echo "Scroll up ⬆️  to see the red error report and line number."
//     fi
// }
    


