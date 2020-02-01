import random 
import argparse
from itertools import combinations
import sys
from datetime import timedelta
# help flag provides flag help
# store_true actions stores argument as True
def parsArgument():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', dest='patchfile', required=True,
    help="path to patch file")
    args = parser.parse_args()
    return args

def calc_runtime(patchfile):
    """Calculte runtime for a patch."""
    patch_file = open(patchfile, "r")
    real_fixing_candidates = patch_file.readlines()
    max_number_of_errors = 5
    number_of_virtual_fixing_line = 10
    max_number_of_fixing_type = 4
    if len(real_fixing_candidates) > max_number_of_errors :
        print("Error: real_fixing_candidates can not be bigger than max_number_of_errors")
        sys.exit(-1)
    number_of_virtual_fixing_candidates = number_of_virtual_fixing_line * max_number_of_fixing_type
    real_fix_set = set(range(len(real_fixing_candidates)))
    line_nums = range(number_of_virtual_fixing_candidates)
    print(line_nums)
    # random.shuffle(lines)
    # print ("Reshuffled line : ",  lines)
    comb_lines = list(combinations(line_nums, max_number_of_errors))
    random.shuffle(comb_lines)
    print("real fix set", real_fix_set)
    print("size possible fixes", len(comb_lines))
    cnt = 1
    one_exe_time = 0.01
    num_count_exam = 50
    one_can_simul_time = one_exe_time * num_count_exam
    runtime = 0
    for line in comb_lines:
        if  set(line) >= real_fix_set:
            print("fix found", line)
            print("run", cnt, "of", len(comb_lines))
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
        avg_time += calc_runtime(args.patchfile)
    print(avg_time/num_run)
    print("avg_run_time = ", str(timedelta(seconds = (avg_time/num_run))), "sec")
    
    
    
    
    
    
    
        # parsArgument()

