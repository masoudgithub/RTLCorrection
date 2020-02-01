import random 
import argparse
from itertools import combinations
import sys
# help flag provides flag help
# store_true actions stores argument as True
def parsArgument():
    parser = argparse.ArgumentParser()
    parser.add_argument('-o', dest='output',  action='store_true', 
    help="shows output")
    args = parser.parse_args()
    if args.output:
        print( args.output)

if __name__ == "__main__":
    patch_file = open("patch.pch", "r")
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
    one_exe_time = 1.22
    num_count_exam = 50
    one_can_simul_time = one_exe_time * num_count_exam
    for line in comb_lines:
        if  set(line) >= real_fix_set:
            print("fix found", line)
            print("run", cnt, "of", len(comb_lines))
            print("run_time = ", one_can_simul_time * cnt, "sec")
            sys.exit(0)
        else:
            cnt = cnt + 1
    # parsArgument()

