#!/usr/bin/env python
#
# MIPS assembler
# Author: Zachary Yedidia
#
# Usage:
#    python assembler.py [asm file]

import sys, re

def bin_to_hex(x):
    y = hex(int(x,2))[2:]
    if len(y) < 8:
        y = (8-len(y))*"0" + y
    return y

def dec_to_bin(value, nbits):
  value = int(value)
  fill = "0"
  if value < 0:
    value = (abs(value) ^ 0xffffffff) + 1
    fill = "1"

  value = bin(value)[2:]
  if len(value) < nbits:
    value = (nbits-len(value))*fill + value
  if len(value) > nbits:
    value = value[-nbits:]
  return value

rtypes = {
    "add": 32,
    "sub": 34,
    "and": 36,
    "or": 37,
    "xor": 38,
    "nor": 39,
    "sll": 0,
    "sra": 3,
    "srl": 2,
    "slt": 42,
    "jr": 8,
	"mul": 2,
}

op_codes = {
    "add": 0,
    "sub": 0,
    "and": 0,
    "or": 0,
    "xor": 0,
    "nor": 0,
    "sll": 0,
    "sra": 0,
    "srl": 0,
    "slt": 0,
    "jr": 0,
    "jal": 3,
    "beq": 4,
    "bne": 5,
    "addi": 8,
    "andi": 12,
    "lw": 35,
    "sw": 43,
    "xori": 14,
    "j": 2,
    "slti": 10,
    "ori": 13,
	"mul": 28
}
registers = {
    # Direct numbers
    '$0' :  0,
    '$1' :  1,
    '$2' :  2,
    '$3' :  3,
    '$4' :  4,
    '$5' :  5,
    '$6' :  6,
    '$7' :  7,
    '$8' :  8,
    '$9' :  9,
    '$10' : 10,
    '$11' : 11,
    '$12' : 12,
    '$13' : 13,
    '$14' : 14,
    '$15' : 15,
    '$16' : 16,
    '$17' : 17,
    '$18' : 18,
    '$19' : 19,
    '$20' : 20,
    '$21' : 21,
    '$22' : 22,
    '$23' : 23,
    '$24' : 24,
    '$25' : 25,
    '$26' : 26,
    '$27' : 27,
    '$28' : 28,
    '$29' : 29,
    '$30' : 30,
    '$31' : 31,

    # Names
    '$zero' : 0,
    '$at': 1,
    '$v0': 2,
    '$v1': 3,
    '$a0': 4,
    '$a1': 5,
    '$a2': 6,
    '$a3': 7,
    '$t0': 8,
    '$t1': 9,
    '$t2': 10,
    '$t3': 11,
    '$t4': 12,
    '$t5': 13,
    '$t6': 14,
    '$t7': 15,
    '$s0': 16,
    '$s1': 17,
    '$s2': 18,
    '$s3': 19,
    '$s4': 20,
    '$s5': 21,
    '$s6': 22,
    '$s7': 23,
    '$t8': 24,
    '$t9': 25,
    '$k0': 26,
    '$k1': 27,
    '$gp': 28,
    '$sp': 29,
    '$fp': 30,
    '$ra': 31,
}

def find_label_relative(parsed_lines, line, label):
    for l in parsed_lines:
        if l['label'] == label:
            imm = l['line_number'] - line['line_number'] - 1
            return dec_to_bin(imm, 16)

def find_label_absolute(parsed_lines, label):
    for l in parsed_lines:
        if l['label'] == label:
            imm = l['line_number']*4 + 0x400000
            return dec_to_bin(imm, 32)[4:30]

def main():
    me, fname = sys.argv

    f = open(fname, "r")
    labels = {}        # Map from label to its address.
    parsed_lines = []  # List of parsed instructions.
    address = 0        # Track the current address of the instruction.
    line_count = 0     # Number of lines.
    for line in f:

        # Stores attributes about the current line of code, like its label, line
        # number, instruction, and arguments.
        line_attr = {}

        # Handle comments, whitespace.
        line = line.strip()

        if line:
            label = ""
            if "#" in line:
                line = line.split("#")[0].strip()
                if not line:
                    continue

            if ":" in line:
                elems = line.split(":")
                label = elems[0].strip()
                labels[label] = 0x400000 + line_count * 4
                line = elems[1].strip()

            sp = re.split(r"\s+", line, 1)
            cmd = sp[0]
            args = ""
            if len(sp) > 1:
                args = sp[1].split(',')

            line_attr['line_number'] = line_count

            # Handle labels
            # Parse the rest of the instruction and its register arguments.
            line_attr["instruction"] = cmd
            line_attr["label"] = label
            line_attr["args"] = args

            # Finally, add this dict to the complete list of instructions.
            parsed_lines.append(line_attr)

            line_count = line_count + 1
    f.close()

    machine = ""  # Current machine code word.

    for line in parsed_lines:
        if line['instruction'] == 'nop':
            machine = 8*'0'
        elif line['instruction'] in rtypes:
            # Encode an R-type instruction.
            args = line['args']

            if line['instruction'] == "jr":
                rs = dec_to_bin(registers[args[0].strip()], 5)
                machine = 6*'0' + rs + 15*'0' + dec_to_bin(rtypes['jr'], 6)
            elif line['instruction'] == 'mul':
                rd = dec_to_bin(registers[args[0].strip()], 5)
                rs = dec_to_bin(registers[args[1].strip()], 5)
                rt = dec_to_bin(registers[args[2].strip()], 5)
                machine = '011100' + rs + rt + rd + '00000000010'
            else:
                rs = dec_to_bin(registers[args[1].strip()], 5)
                if '$' in args[2]:
                    rt = dec_to_bin(registers[args[2].strip()], 5)
                    shamt = 5*'0'
                else:
                    shamt = dec_to_bin(args[2].strip(), 5)
                    rt = rs
                    rs = 5*'0'

                rd = dec_to_bin(registers[args[0].strip()], 5)
                funct = dec_to_bin(rtypes[line['instruction']], 6)

                machine = 6*'0' + rs + rt + rd + shamt + funct
        else:
            # Encode a non-R-type instruction.
            args = line['args']
            op = dec_to_bin(op_codes[line['instruction']], 6)
            if line['instruction'] == 'jal':
                addr = find_label_absolute(parsed_lines, args[0].strip())
                machine = op + addr
            elif line['instruction'] == 'j':
                addr = find_label_absolute(parsed_lines, args[0].strip())
                machine = op + addr
            else:
                rt = dec_to_bin(registers[args[0].strip()], 5)
                if line['instruction'].endswith('i'):
                    rs = dec_to_bin(registers[args[1].strip()], 5)
                    imm = dec_to_bin(int(args[2].strip()), 16)
                elif line['instruction'].endswith('w'):
                    arg2 = args[1].strip()
                    matchObj = re.match(r'(-?\d+)\((.+?)\)', arg2)
                    imm = dec_to_bin(matchObj.group(1), 16)
                    rs = dec_to_bin(registers[matchObj.group(2)], 5)
                elif line['instruction'].startswith('b'):
                    rt = dec_to_bin(registers[args[1].strip()], 5)
                    rs = dec_to_bin(registers[args[0].strip()], 5)

                    imm = find_label_relative(parsed_lines, line, args[2].strip())

                machine = op + rs + rt + imm

        print (bin_to_hex(machine))

if __name__ == "__main__":
    main()
