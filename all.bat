call g++ -o cts.exe cts.cpp
call cts --input test0.in --output test0.out
cmd /c start python eval.py --input test0.in --output test0.out --plot true
call cts --input test1.in --output test1.out
cmd /c start python eval.py --input test1.in --output test1.out --plot true
call cts --input test2.in --output test2.out
cmd /c start python eval.py --input test2.in --output test2.out --plot true
call cts --input test3.in --output test3.out
cmd /c start python eval.py --input test3.in --output test3.out --plot true
call cts --input test4.in --output test4.out
cmd /c start python eval.py --input test4.in --output test4.out --plot true
call cts --input test5.in --output test5.out
cmd /c start python eval.py --input test5.in --output test5.out --plot true
call cts --input test6.in --output test6.out
cmd /c start python eval.py --input test6.in --output test6.out --plot true
call cts --input test7.in --output test7.out
cmd /c start python eval.py --input test7.in --output test7.out --plot true
pause