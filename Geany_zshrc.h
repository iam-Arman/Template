run() {
    # 1. Safety Check: Does file exist?
    if [ ! -f "$1.cpp" ]; then
        echo "\033[1;31m❌ Error: File '$1.cpp' not found.\033[0m"
        return
    fi

    # 2. Compile (Standard CP flags + LOCAL defined)
    echo "\033[1;34m🔨 Compiling $1.cpp...\033[0m"
    g++ -o sol -Wall -Wextra -std=c++17 -O2 -DLOCAL -I std_lib "$1.cpp"

    if [ $? -eq 0 ]; then
        # 3. GRANDMASTER TWEAK: Unlimited Stack
        ulimit -s unlimited

        # 4. Python Wrapper for Execution with Memory & Time
        python3 -c "
import sys, subprocess, os, resource, re, platform

interactive = '$2' == 'int'

try:
    infile_path = 'input.txt'
    if not interactive:
        if os.path.exists(infile_path):
            infile = open(infile_path, 'r')
            print('\033[1;32m✅ Running with input.txt...\033[0m')
        else:
            print('\033[1;33m⚠️  input.txt not found. (Type manual input)...\033[0m')
            infile = None
    else:
        print('\033[1;35m🗣️  INTERACTIVE MODE ACTIVE (Manual Input)...\033[0m')
        infile = None

    print('---------------------------------------------------')

    usage_start = resource.getrusage(resource.RUSAGE_CHILDREN)

    process = subprocess.Popen(
        ['./sol'], 
        stdin=infile, 
        stdout=subprocess.PIPE, 
        stderr=subprocess.PIPE,
        text=True,
        bufsize=1
    )

    line_count = 0
    try:
        while True:
            output = process.stdout.readline()
            if output == '' and process.poll() is not None:
                break
            if output:
                # COLORFUL HEADERS LOGIC
                if re.search(r'Test case \d+', output, re.IGNORECASE):
                    colored_output = re.sub(r'(Test case \d+)', r'\033[1;32m✅ \1\033[0m', output, flags=re.IGNORECASE)
                    sys.stdout.write(colored_output)
                else:
                    sys.stdout.write(output)
                
                line_count += 1
                if line_count > 1000:
                    print('\n\033[1;41m 🛑 EMERGENCY STOP: Output Limit Exceeded (>1000 lines) \033[0m')
                    process.kill()
                    break
    except KeyboardInterrupt:
        print('\n\033[1;31m🛑 Manual Stop.\033[0m')
    
    process.wait()
    usage_end = resource.getrusage(resource.RUSAGE_CHILDREN)
    if infile: infile.close()

    # --- TIME CALCULATION ---
    cpu_time_ms = ((usage_end.ru_utime - usage_start.ru_utime) + 
                   (usage_end.ru_stime - usage_start.ru_stime)) * 1000

    # --- MEMORY CALCULATION (MacOS Specific) ---
    # macOS reports ru_maxrss in Bytes. Linux reports in Kilobytes.
    # We auto-detect system to be safe.
    mem_bytes = usage_end.ru_maxrss
    if platform.system() == 'Linux':
        mem_bytes = mem_bytes * 1024 # Convert KB to Bytes for Linux
    
    mem_mb = mem_bytes / (1024 * 1024)

    print('\n---------------------------------------------------')
    
    # Time Output
    if cpu_time_ms > 1000:
        print(f'\033[1;31m⏱️  Judge Time: {cpu_time_ms:.3f} ms (TLE Risk ⚠️)\033[0m')
    elif cpu_time_ms > 500:
        print(f'\033[1;33m⏱️  Judge Time: {cpu_time_ms:.3f} ms (Warning)\033[0m')
    else:
        print(f'\033[1;36m⏱️  Judge Time: {cpu_time_ms:.3f} ms\033[0m')

    # Memory Output
    if mem_mb > 256: 
        print(f'\033[1;31m💾 Memory: {mem_mb:.2f} MB (MLE Risk ⚠️)\033[0m')
    else:
        print(f'\033[1;35m💾 Memory: {mem_mb:.2f} MB\033[0m')

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
    # 1. Silence Mac Warning
    export MallocNanoZone=0

    # 2. Input Safety Check
    if [ ! -s "input.txt" ]; then
        echo "\033[1;33m⚠️  Warning: 'input.txt' is empty or missing!\033[0m"
    fi

    echo "\n\033[1;35m🛠️  [DEBUG MODE] Compiling with Static Analysis & Strict Checks...\033[0m"

    # 3. Compile with EVERYTHING (Sanitizers + Hardening + Static Analysis)
    clang++ -o sol -std=c++17 -g -O0 \
    -fsanitize=address,undefined \
    -DLOCAL \
    -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG \
    -D_LIBCPP_DEBUG=1 \
    -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion -Wuninitialized -Wparentheses \
    "$1.cpp"

    if [ $? -ne 0 ]; then
        echo "\033[1;31m❌ Compilation Failed!\033[0m"
        return
    fi

    echo "\033[1;32m✅ Ready. Running...\033[0m"
    echo "---------------------------------------------------"

    # 4. Run safely and CAPTURE errors
    ASAN_OPTIONS=detect_stack_use_after_return=1:handle_abort=1 UBSAN_OPTIONS=print_stacktrace=1 \
    ./sol < input.txt 2> .debug_log

    EXIT_CODE=$?

    # Show output
    cat .debug_log

    echo "\n---------------------------------------------------"
    if [ $EXIT_CODE -eq 0 ]; then
        echo "\033[1;32m✨ CLEAN RUN: No errors found.\033[0m"
    else
        echo "\033[1;31m💀 CRASH DETECTED! (Exit Code: $EXIT_CODE)\033[0m"
        
        # 5. AUTOMATICALLY EXTRACT LINE NUMBER
        CRASH_INFO=$(grep -o "$1.cpp:[0-9]*" .debug_log | head -n 1)

        if [ -n "$CRASH_INFO" ]; then
            LINE_NUM=$(echo "$CRASH_INFO" | cut -d: -f2)
            
            # MATH: Calculate range (Line-2 to Line+2)
            START_LINE=$((LINE_NUM - 2))
            if [ $START_LINE -lt 1 ]; then START_LINE=1; fi
            END_LINE=$((LINE_NUM + 2))

            echo "\n\033[1;33m🎯 BUG FOUND AT: \033[1;4;31m $CRASH_INFO \033[0m \033[1;30m(Showing Context)\033[0m"
            echo "\033[0m----------------------------------------"
            
            # Print the snippet with line numbers
            # We use 'awk' to print lines and highlight the crash line with '>>'
            awk -v target="$LINE_NUM" -v start="$START_LINE" -v end="$END_LINE" '
                NR >= start && NR <= end { 
                    if (NR == target) printf "\033[1;31m>> %d | %s\033[0m\n", NR, $0; 
                    else              printf "\033[1;30m   %d | %s\033[0m\n", NR, $0; 
                }
            ' "$1.cpp"
            
            echo "----------------------------------------"
        else
            echo "Scroll up ⬆️  to see the error details."
        fi
    fi
    
    rm -f .debug_log
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

