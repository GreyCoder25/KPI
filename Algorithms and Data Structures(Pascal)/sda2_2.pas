const
	m = 7;
	n = 8;
type
	matrix = array [1..m,1..n+1] of integer;
	vector = array [0..n] of integer;
var
	A:matrix;
procedure backord_input(var A:matrix);
	var
		i,j:byte;
		num:integer;
	begin
		num:=1;
		for i:=1 to m do
			for j:=1 to n do
				begin
					A[i,j]:=num;
					inc(num);
				end;
	end;
procedure ord_input(var A:matrix);
	var
		i,j:byte;
		num:integer;
	begin
		num:=m*n;
		for i:=1 to m do
			for j:=1 to n do 
				begin
					A[i,j]:=num;
					dec(num);
				end;
	end;
procedure rand_input(var A:matrix);
	var
		i,j:byte;
	begin
		randomize;
		for i:=1 to m do
			for j:=1 to n do
				A[i,j]:=random(10);
	end;
procedure output(const A:matrix);
	var
		i,j:byte;
	begin
		for i:=1 to m do 
			begin
					for j:=1 to n do
					write(A[i,j]:3);
				writeln;
			end;
			writeln('--------------------');
	end;
procedure insert3_sort(var A:vector);
	var
		i,j:byte;
	begin
		for i:=2 to n do 
			begin
				A[0]:=A[i];
				j:=i;
				while (A[j-1] < A[0]) do 
					begin
						A[j]:=A[j-1];
						dec(j);
					end;
				A[j]:=A[0];
			end;
	end;
procedure main;
	var
		i:byte;
	begin
		rand_input(A);
		writeln('Initial matrix:');
		output(A);
		
		for i:=1 to m do
			insert3_sort(A[i]);
			
		writeln('Sorted matrix:');
		output(A);
	end;
begin
	main;
end.
