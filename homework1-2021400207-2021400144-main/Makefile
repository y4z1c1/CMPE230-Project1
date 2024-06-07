default:
	@gcc -o ringmaster src/main.c src/func.c

clean:
	@rm -f ringmaster

grade:
	python3 test/grader.py ./ringmaster test-cases
