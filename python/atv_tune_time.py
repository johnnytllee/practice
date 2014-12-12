#!/usr/bin/python

import sys
import re

def main():
	if len(sys.argv) > 1:
		problem = sys.argv[1]
	else:
		problem = "atv_tune_input.txt"
	print ("Processing " + problem)

	input_file = open(problem, 'r')
	print input_file

	print "Frequency, Time"
	count = 0
	acc = 0
	for line in input_file:
		m = re.search(r"start:(\d+)", line)
		if (m):
			f = m.group(1)
			m = re.search(r"(\d+)(\.)(\d+)", line)
			if (m):
				start = m.group(0)
		else:
			m = re.search(r"(\d+)(\.)(\d+)", line)
			if (m):
				end = m.group(0)
				t = float(end) - float(start)
				if (t < 0):
					t = (60 + float(end)) - float(start)
				acc += t
				count += 1
				print f, ",", t
	print "Average Time =", acc/count

if __name__ == "__main__":
	main()
