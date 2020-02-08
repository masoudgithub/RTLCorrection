import random 
import argparse
from itertools import combinations
import sys
from datetime import timedelta
# help flag provides flag help
# store_true actions stores argument as True
def parsArgument():
    parser = argparse.ArgumentParser()
    parser.add_argument('--size', type = int, dest='size', required=True,
    help="size of the verilog file")
    parser.add_argument('--sim_time', type = int, dest='sim_time', required=True,
    help="simulation time of the verilog file")
    args = parser.parse_args()
    return args

def calc_runtime(args):
    """Calculte runtime for a patch."""
    bench_mark_size = args.size # lines
    max_number_of_errors = int(bench_mark_size / 1000)
    print(f"max num of errors {max_number_of_errors}")
    num_real_fixing_candidates = int( 7 * max_number_of_errors / 10 ) + 1
    number_error_candidare_lines = int(2 * bench_mark_size / 1000) # number of error candidate lines 
    max_number_of_fixing_type = 4
    if num_real_fixing_candidates > max_number_of_errors :
        print("Error: num_real_fixing_candidates can not be bigger than max_number_of_errors")
        sys.exit(-1)
    number_of_virtual_fixing_candidates = number_error_candidare_lines * max_number_of_fixing_type
    real_fix_set = set(range(num_real_fixing_candidates))
    line_nums = list(range(number_of_virtual_fixing_candidates))
    random.shuffle(line_nums)
    print(f"line_nums = {line_nums}")
    # comb_lines = list(combinations(line_nums, max_number_of_errors))
    # random.shuffle(comb_lines)
    print("real fix set", real_fix_set)
    # print("size possible fixes", len(comb_lines))
    cnt = 1
    one_exe_time = args.sim_time
    num_count_exam = 50
    one_can_simul_time = one_exe_time * num_count_exam
    runtime = 0
    for line in combinations(line_nums, max_number_of_errors):
        if  set(line) >= real_fix_set:
            print("fix found", line)
            # print("run", cnt, "of", len(comb_lines))
            runtime = one_can_simul_time * cnt
            print("run_time = ", str(timedelta(seconds=runtime)), "sec")
            break
        else:
            cnt = cnt + 1
    return runtime

if __name__ == "__main__":
    args = parsArgument()
    avg_time = 0
    num_run = 100
    for i in range(num_run):
        avg_time += calc_runtime(args)
    print(avg_time/num_run)
    print("avg_run_time = ", str(timedelta(seconds = (avg_time/num_run))), "sec")
    

