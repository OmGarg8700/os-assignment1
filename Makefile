om_2021481:
	gcc cat.c -o cat
	gcc date.c -o date
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm

	gcc main.c

clean:
	rm -rf cat date ls mkdir rm