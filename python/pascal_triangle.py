#!/usr/bin/python

import sys

def main():
	if len(sys.argv) > 1:
		problem = sys.argv[1]
	else:
		problem = 10

	a = []
	rows = int(problem)
	for i in range(rows):
		a.append(0)
	for i in range(rows):
		print "row", i
		for j in range(i):
			if j == 0 or j == i-1:
				a[j] = 1
				l_aj = a[j]
				print('1')
			else:
				t_aj = a[j]
				a[j] += l_aj
				l_aj = t_aj
				print(a[j])
		print ""

if __name__ == "__main__":
	main()
