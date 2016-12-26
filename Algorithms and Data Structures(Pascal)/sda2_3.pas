var
	n:integer;
function loop(n:byte):real;  {циклический вариант работы программы}
	var
		i:byte;
		S,F:real;
	begin
		F:=1;
		S:=1;
		for i:=2 to n do
			begin
				F:=ln(F+3) + sqrt(i);
				S:=S+F;
			end;
		loop:=S;
	end;
											{вычисление члена ряда и суммы}
											{на рекурсивном возврате      }
function sum_up(i:byte; var f:real):real;
	var
		temp:real;
	begin
		if (i > 1) then
			begin
				temp:=sum_up(i-1,f);
				f:=ln(f+3) + sqrt(i);
				sum_up:=temp+f;
			end
		else
			begin
				f:=1;
				sum_up:=1;
			end;
	end;
	
function calc_series(n:byte):real;
	var
		f:real;
	begin
		calc_series:=sum_up(n,f);
	end;

function sum_down(s,f:real; i,n:byte):real;	{вычисление члена ряда и суммы}
	begin									{на рекурсивном спуске     }
		if (i <= n) then
			begin
				f:=ln(f + 3) + sqrt(i);
				sum_down:=sum_down(s+f,f,i+1,n);
			end
		else
			sum_down:=s;
	end;
	
function sum_up_down(f:real; i,n:byte):real;  {вычисление члена ряда на рекурсивном   }
	begin									{спуске, а суммы на рекурсивном возврате}
		if (i > 1) then
			begin
				f:=ln(f+3) + sqrt(n-i+2);
				sum_up_down:=sum_up_down(f,i-1,n) + f;
			end
		else
			sum_up_down:=1;
	end;
	
begin
	write('Введите натуральное n: ');
	{$I-}
	readln(n);
	{I+}
	if (ioresult <> 0) or (n<=0) then
		writeln('Вы ввели слишком большое число или ввели его некорректно')
	else if (n > 254) then
		writeln('Недостаточно памяти для проведения операции, введите число меньше')
	else
		begin
			writeln('loop(n) = ', loop(n));
			writeln('sum_up(n) = ',calc_series(n));
			writeln('sum_down(n) = ', sum_down(1,1,2,n));
			writeln('sum_up_down(n) = ', sum_up_down(1,n,n));
		end;
end.
