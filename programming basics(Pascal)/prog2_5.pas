{$MODE TP}
const
	PrAcc = 0.001; //задана точність
type
	TFunc = function(x:real):real;
	
	function integrand(x:real):real;
		begin
			integrand:=exp(ln(exp(1))*(x*arctan(x)+ln(x))); //підінтегральна функція
		end;{integrand}	
	
var
	f:TFunc;
	n0:longint;
	err,theta,a,b:real;
	Sn,S2n:real;
	
function integral(f:TFunc; a,b:real; N:longint):real; //функція наближеного обчислення інтеграла
	var
		i:word;
		h,S,x:real;
	begin
		h:=(b-a)/N; //обчислюємо значення кроку
		S:=0;		//встановлюємо початкове значення інтегральної суми
		
				for i:=0 to N-1 do //в циклі виконується додавання тільки-що
								   //порахованої площі прямокутника до загальної суми	
					begin
						x:=a+(i+0.5)*h;
						S:=S+h*f(x);
					end;
			
		integral:=S;
	end;{integral}
	
BEGIN
	n0:=10; //початкова кількість кроків
	theta:=1/3;
	err:=PrAcc+1; //для того,щоб на початку точність точно була меншою, ніж задана
	a:=0; //нижня межа інтегрування
	b:=3; //верхня межа інтегрування

	f:=integrand; //присвоюємо функції-параметру f задану підінтегральну функцію
	
	
	S2n:=integral(f,a,b,n0); //вираховуємо значення функції для початкової
							 //кількості кроків	
	
	while (err > PrAcc) do	 //виконуємо дії в циклі поки похибка більша заданої
		begin
			writeln('n0 = ',n0);
			
			Sn:=S2n; //значення функції для поточної кількості кроків дорівнює
					 //значенню функції для подвоєної кількості кроків на попередній ітерації
			writeln('Sn = ',Sn);
			
			n0:=2*n0; //подвоюємо кількість кроків
			S2n:=integral(f,a,b,n0);
			writeln('S2n = ',S2n);
			
			err:=theta * abs(Sn - S2n); //обчислюємо похибку
			writeln('err = ',err);
			
		end;
		
writeln;
writeln('I = ',S2n);	
	
END.{main}
