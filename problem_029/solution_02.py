
numbers = {};
base = 2;
power = 2;
combo_cnt = 0;
duplicate_cnt = 0;
while (base <= 100):
	power=2;
	while (power <= 100):
		combo_cnt += 1;
		n = base**power;
		if (numbers.has_key(n)):
			numbers[n].append((base,power));
			#print "%d; %d" % (power, base)
			duplicate_cnt += 1;
		else:
			numbers[n] = [(base,power)];
		power = power + 1;
	base = base + 1;

print "Duplicates:",duplicate_cnt
print "Combinations:",combo_cnt
print "Count:", len(numbers.keys())

