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

 
run() {
    # 1. Safety Check: Does file exist?
    if [ ! -f "$1.cpp" ]; then
        echo "\033[1;31m❌ Error: File '$1.cpp' not found.\033[0m"
        return
    fi

    # 2. Compile (Standard CP flags + LOCAL defined)
    # Added '-I std_lib' in case you use precompiled headers later
    echo "\033[1;34m🔨 Compiling $1.cpp...\033[0m"
    g++ -o sol -Wall -Wextra -std=c++17 -O2 -DLOCAL -I std_lib "$1.cpp"

    if [ $? -eq 0 ]; then
        # 3. GRANDMASTER TWEAK: Unlimited Stack
        # Fixes "Segmentation Fault" on Mac for deep DFS/Recursion
        ulimit -s unlimited

        # 4. Python Wrapper for Execution, Timing, and Safety
        python3 -c "
import sys, subprocess, os, resource

# Check for Interactive Mode (pass 'int' as 2nd arg)
interactive = '$2' == 'int'

try:
    infile = None
    # Setup Input
    if not interactive:
        if os.path.exists('input.txt'):
            infile = open('input.txt', 'r')
            print('\033[1;32m✅ Running with input.txt...\033[0m')
        else:
            print('\033[1;33m⚠️  input.txt not found. (Type manual input)...\033[0m')
    else:
        print('\033[1;35m🗣️  INTERACTIVE MODE ACTIVE (Manual Input)...\033[0m')

    print('---------------------------------------------------')

    # Start Timing (CPU Children)
    usage_start = resource.getrusage(resource.RUSAGE_CHILDREN)

    # Run Process
    # We pipe stdout so we can truncate it if it floods the terminal
    process = subprocess.Popen(
        ['./sol'], 
        stdin=infile, 
        stdout=subprocess.PIPE, 
        stderr=subprocess.PIPE,
        text=True,
        bufsize=1 # Line buffered for live output
    )

    # GRANDMASTER TWEAK: Output Flood Protection
    # Read line by line. If lines > 1000, kill it to save terminal.
    line_count = 0
    try:
        while True:
            output = process.stdout.readline()
            if output == '' and process.poll() is not None:
                break
            if output:
                sys.stdout.write(output)
                line_count += 1
                if line_count > 1000:
                    print('\n\033[1;41m 🛑 EMERGENCY STOP: Output Limit Exceeded (>1000 lines) \033[0m')
                    process.kill()
                    break
    except KeyboardInterrupt:
        print('\n\033[1;31m🛑 Manual Stop.\033[0m')
    
    # Wait for finish
    process.wait()
    
    # End Timing
    usage_end = resource.getrusage(resource.RUSAGE_CHILDREN)
    if infile: infile.close()

    # Calculate Pure CPU Time (User + System)
    cpu_time_ms = ((usage_end.ru_utime - usage_start.ru_utime) + 
                   (usage_end.ru_stime - usage_start.ru_stime)) * 1000

    print('\n---------------------------------------------------')
    if cpu_time_ms > 1000:
        print(f'\033[1;31m⏱️  Judge Time: {cpu_time_ms:.3f} ms (TLE Risk ⚠️)\033[0m')
    else:
        print(f'\033[1;36m⏱️  Judge Time: {cpu_time_ms:.3f} ms\033[0m')

except Exception as e:
    print(f'\n\033[1;31m❌ Runtime Error: {e}\033[0m')
"
    else
        echo "\033[1;31m❌ Compilation Failed!\033[0m"
    fi
}

// TIMEFMT=$'\nReal:\t%E\nUser:\t%U\nSys:\t%S'
match() {
    # 1. Compile Solution
    g++ -o sol -Wall -Wextra -std=c++17 -O2 "$1.cpp"

    if [ $? -eq 0 ]; then
        echo "--- Running $1 vs expected.txt ---"

        # 2. Python Script with Resource Usage Tracking
        python3 -c "
import sys
import subprocess
import os
import resource  # <--- This is the magic tool

# --- STEP 1: RUN YOUR CODE & MEASURE CPU USAGE ---
try:
    if os.path.exists('input.txt'):
        infile = open('input.txt', 'r')
    else:
        infile = None

    # Snapshot of CPU time used by children BEFORE running
    usage_start = resource.getrusage(resource.RUSAGE_CHILDREN)
    
    # Run the solution
    result = subprocess.run(['./sol'], stdin=infile, capture_output=True, text=True)
    
    # Snapshot of CPU time used by children AFTER running
    usage_end = resource.getrusage(resource.RUSAGE_CHILDREN)
    
    if infile: infile.close()

    # Calculate PURE CPU Time (User Time + System Time)
    # This ignores 'waiting' time and only counts 'working' time
    cpu_time_s = (usage_end.ru_utime - usage_start.ru_utime) + (usage_end.ru_stime - usage_start.ru_stime)
    cpu_time_ms = cpu_time_s * 1000
    
    my_output = result.stdout.strip().splitlines()
    
except Exception as e:
    print(f'\033[1;31m❌ Execution Error: {e}\033[0m')
    sys.exit(1)

# --- STEP 2: COMPARE OUTPUT ---
try:
    with open('expected.txt', 'r') as f:
        expected = [line.strip() for line in f if line.strip()]
    my_output = [line.strip() for line in my_output if line.strip()]
except FileNotFoundError:
    print('\033[1;33m⚠️  No expected.txt found. Showing output:\033[0m')
    print('\n'.join(my_output))
    sys.exit(0)

# Helper for float comparison
def is_float(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

passed_count = 0
total_cases = max(len(my_output), len(expected))

for i in range(total_cases):
    val_out = my_output[i] if i < len(my_output) else '(missing)'
    val_exp = expected[i] if i < len(expected) else '(missing)'

    match = False
    if val_out == val_exp:
        match = True
    elif is_float(val_out) and is_float(val_exp):
        if abs(float(val_out) - float(val_exp)) < 1e-6:
            match = True

    if match:
        print(f'\033[1;32m✅ OK (Test Case {i+1})\033[0m')
        passed_count += 1
    else:
        print(f'\033[1;31m❌ Test Case {i+1} Failed!\033[0m')
        print(f'   Your Output: \033[1m{val_out}\033[0m')
        print(f'   Expected:    \033[1m{val_exp}\033[0m')
        print('-' * 30)

# --- STEP 3: SUMMARY ---
print('\n' + '='*30)
if passed_count == total_cases:
    print(f'\033[1;32m🎉 ACCEPTED ({passed_count}/{total_cases})\033[0m')
else:
    print(f'\033[1;31m💀 WRONG ANSWER ({passed_count}/{total_cases} passed)\033[0m')
print('='*30)

# --- STEP 4: JUDGE TIME DISPLAY ---
if cpu_time_ms > 1000:
    print(f'\033[1;31m⚠️  SLOW: {cpu_time_ms:.3f} ms (TLE Risk)\033[0m')
elif cpu_time_ms > 500:
    print(f'\033[1;33m⚠️  WARNING: {cpu_time_ms:.3f} ms\033[0m')
else:
    # Bright Blue for CPU time
    print(f'\033[1;36m⏱️  Judge Time: {cpu_time_ms:.3f} ms\033[0m')
"
    fi
}

debug() {
    # 1. Automatically silence the Mac "Nano Zone" warning
    export MallocNanoZone=0

    echo "\n\033[1;34m🛠️  [DEBUG MODE] Compiling $1.cpp...\033[0m"

    # 2. Compile with Clang (Best for Mac)
    # -g        : Adds line numbers to error messages
    # -O0       : Disables optimization so variables are easy to track
    # -fsanitize: Turns on the "Crash Catcher" (Address + Undefined Behavior)
    clang++ -o sol -std=c++17 -g -O0 -fsanitize=address,undefined -DLOCAL "$1.cpp"

    if [ $? -ne 0 ]; then
        echo "\033[1;31m❌ Compilation Failed!\033[0m"
        return
    fi

    echo "\033[1;32m✅ Compilation Successful. Running...\033[0m"
    echo "==================================================="

    # 3. Run with extra checks (Catch stack errors)
    # We capture the exit code ($?) to check if it crashed
    ASAN_OPTIONS=detect_stack_use_after_return=1 ./sol < input.txt
    EXIT_CODE=$?

    echo "\n==================================================="
 # 4. Final Verdict
    if [ $EXIT_CODE -eq 0 ]; then
        echo "\033[1;32m✨ CLEAN RUN: No crashes or memory errors detected.\033[0m"
    else
        echo "\033[1;31m💀 CRASH DETECTED! (Exit Code: $EXIT_CODE)\033[0m"
        echo "Scroll up ⬆️  to see the red error report and line number."
    fi
}


precompile() {
    echo "\033[1;33m⏳ Precompiling bits/stdc++.h (This takes ~5 seconds)...\033[0m"
    
    # 1. Create a dedicated folder for the header
    mkdir -p std_lib
    
    # 2. Compile the header with your specific flags (-O2, -std=c++17)
    # The output file MUST be named 'stdc++.h.gch' for GCC to find it
    g++ -x c++-header -O2 -std=c++17 -DLOCAL /usr/local/include/bits/stdc++.h -o std_lib/stdc++.h.gch
    
    if [ $? -eq 0 ]; then
        echo "\033[1;32m✅ Done! Compilation will now be instant.\033[0m"
    else
        echo "\033[1;31m❌ Failed. Make sure you have bits/stdc++.h installed.\033[0m"
    fi
}

clean() {
    echo "\033[1;34m🧹 Cleaning up garbage files...\033[0m"
    # Removes executable 'sol', 'gen', 'brute', and temp txt files
    rm -f sol gen brute *.o *.out my_output.txt output.txt input.txt expected.txt stdc++.h.gch
    
    # Optional: Removes compiled header if you want to reset 'precompile'
    # rm -rf std_lib 
    
    echo "\033[1;32m✨ Clean.\033[0m"
}


stress() {
    # 1. Check if required files exist
    if [[ ! -f "$1.cpp" ]] || [[ ! -f "brute.cpp" ]] || [[ ! -f "gen.cpp" ]]; then
        echo "\033[1;31m❌ Error: You need $1.cpp, brute.cpp, and gen.cpp in this folder.\033[0m"
        return
    fi

    echo "\033[1;34m🔨 Compiling $1.cpp, brute.cpp, and gen.cpp...\033[0m"
    
    # 2. Compile Everything
    # We use -O2 for speed. brute.cpp also needs to be compiled.
    g++ -o sol -Wall -Wextra -std=c++17 -O2 "$1.cpp"
    g++ -o brute -std=c++17 -O2 brute.cpp
    g++ -o gen -std=c++17 -O2 gen.cpp

    if [ $? -ne 0 ]; then
        echo "\033[1;31m❌ Compilation Failed!\033[0m"
        return
    fi

    # 3. Increase Stack Size (Prevents Mac DFS crashes)
    ulimit -s unlimited

    echo "\033[1;32m✅ Compilation Done. Starting Stress Test...\033[0m"
    echo "---------------------------------------------------"

    # 4. Python Loop for High Speed Testing
    python3 -c "
import sys, subprocess, os

i = 1
while True:
    # A. Generate Input
    with open('input.txt', 'w') as f_in:
        subprocess.run(['./gen'], stdout=f_in)

    # B. Run Your Solution
    with open('input.txt', 'r') as f_in, open('my_out.txt', 'w') as f_out:
        subprocess.run(['./sol'], stdin=f_in, stdout=f_out)

    # C. Run Brute Force
    with open('input.txt', 'r') as f_in, open('brute_out.txt', 'w') as f_out:
        subprocess.run(['./brute'], stdin=f_in, stdout=f_out)

    # D. Compare (Strip whitespace for fairness)
    with open('my_out.txt') as f1, open('brute_out.txt') as f2:
        out = [l.strip() for l in f1 if l.strip()]
        ans = [l.strip() for l in f2 if l.strip()]

    if out == ans:
        # Print progress on the same line (\r)
        sys.stdout.write(f'\r\033[1;32m✅ Passed Test {i}\033[0m')
        sys.stdout.flush()
        i += 1
    else:
        print(f'\n\n\033[1;31m❌ FOUND FAILING TEST CASE ({i})!\033[0m')
        print('---------------------------------------------------')
        
        print('\033[1;33m[ INPUT ]\033[0m')
        with open('input.txt') as f: print(f.read().strip())
        
        print('\n\033[1;33m[ YOUR OUTPUT ]\033[0m')
        with open('my_out.txt') as f: print(f.read().strip())
        
        print('\n\033[1;33m[ CORRECT OUTPUT ]\033[0m')
        with open('brute_out.txt') as f: print(f.read().strip())
        
        print('---------------------------------------------------')
        break # Stop the loop
"
}


