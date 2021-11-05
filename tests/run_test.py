import argparse
import subprocess
import os
import filecmp

p = 0
f = 0

def compare(lhs, rhs, i):
    global p
    global f
    print("Test #" + str(i) + ":")
    if filecmp.cmp(lhs, rhs):
        print("\tpassed.")
        p += 1
    else:
        print("\tfailed.")
        f += 1

def test(prog, t_path):
    print("Run tests:")
    for i in range(1, 10):
        input  = os.path.join(t_path, "input_rand" + str(i) + ".in")
        output = os.path.join(t_path, "program_result"+ str(i) + ".out")
        stdout = str()
        subprocess.run([prog, input, output], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output_ver = os.path.join(t_path, "manual_check"+ str(i) + ".txt")
        compare(output, output_ver, i)
    print("\n")
    print("Tests passed = " + str(p))
    print("Tests failed = " + str(f))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', type=str)
    parser.add_argument('-f', type=str)
    args = parser.parse_args()
    test(os.path.normpath(args.p), os.path.normpath(args.f))

main()