const
	m1 = 3; n1 = 9;
	m2 = 6; n2 = 5;
	m3 = 5; n3 = 7;
type
	TMatr1 = array [1..m1,1..n1] of byte;
	TMatr2 = array [1..m2,1..n2] of byte;
	TMatr3 = array [1..m3,1..n3] of byte;
	
	P_TMatr1 = ^TMatr1;
	P_TMatr2 = ^TMatr2;
	P_TMatr3 = ^TMatr3;

var
	A:P_TMatr1;
	B:P_TMatr2;
	C:P_TMatr3;
	
procedure MatrInput(P:Pointer; m,n:byte; ch:char);
	const
		RandLim = 10;
	var
		i,j:byte;
	begin
		randomize;
		
		case ch of
			'A':
				begin
					for i:=1 to m do
						for j:=1 to n do
							P_TMatr1(P)^[i,j]:=random(RandLim);
				end;
			'B':
				begin
					for i:=1 to m do
						for j:=1 to n do
							P_TMatr2(P)^[i,j]:=random(RandLim);
				end;
			'C':
				begin
					for i:=1 to m do
						for j:=1 to n do
							P_TMatr3(P)^[i,j]:=random(RandLim);
				end;
		end;
	end;
	
procedure MatrOutput(P:Pointer; m,n:byte; ch:char);
	var
		i,j:byte;
	begin

		writeln('Matrix ',ch,'[',m,',',n,']:');
		
		case ch of
			'A':
				begin
					for i:=1 to m do
						begin
							for j:=1 to n do
								write(P_TMatr1(P)^[i,j],' ');
							writeln;
						end;
				end;
			'B':
				begin
					for i:=1 to m do
						begin
							for j:=1 to n do
								write(P_TMatr2(P)^[i,j],' ');
							writeln;
						end;
				end;
			'C':
				begin
					for i:=1 to m do
						begin
							for j:=1 to n do
								write(P_TMatr3(P)^[i,j],' ');
							writeln;
						end;
				end;
		end;
	end;
	
function RowSum(const V:array of byte):word;
	var
		i:byte;
		S:word;
	begin
		S:=0;
		for i:=0 to High(V) do
			S:=S+V[i];
			
		RowSum:=S;
	end;
	
procedure MatrRowSums(P:Pointer; m,n:byte; ch:char);
	var
		i:byte;
	begin
		writeln;
		case ch of
			'A':
				begin
					for i:=1 to m do
							writeln('Sum of elements in row № ',i,': ',RowSum(P_TMatr1(P)^[i]));
				end;
			'B':
				begin
					for i:=1 to m do
							writeln('Sum of elements in row № ',i,': ',RowSum(P_TMatr2(P)^[i]));
				end;
			'C':
				begin
					for i:=1 to m do
							writeln('Sum of elements in row № ',i,': ',RowSum(P_TMatr3(P)^[i]));
				end;
		end;
		writeln;
	end;

procedure MatrixProcessing(var P:pointer; m,n:byte; ch:char);
	begin
		case ch of
			'A':
				begin
					New(P_TMatr1(P));
					MatrInput(P_TMatr1(P),m1,n1,'A');
					MatrOutput(P_TMatr1(P),m1,n1,'A');
					MatrRowSums(P_TMatr1(P),m1,n1,'A');
					Dispose(P_TMatr1(P));
				end;
			'B':
				begin
					New(P_TMatr2(P));
					MatrInput(P_TMatr2(P),m2,n2,'B');
					MatrOutput(P_TMatr2(P),m2,n2,'B');
					MatrRowSums(P_TMatr2(P),m2,n2,'B');
					Dispose(P_TMatr2(P));
				end;
			'C':
				begin
					New(P_TMatr3(P));
					MatrInput(P_TMatr3(P),m3,n3,'C');
					MatrOutput(P_TMatr3(P),m3,n3,'C');
					MatrRowSums(P_TMatr3(P),m3,n3,'C');
					Dispose(P_TMatr3(P));
				end;
		end;

	end;
	
BEGIN
	MatrixProcessing(A,m1,n1,'A');
	MatrixProcessing(B,m2,n2,'B');
	MatrixProcessing(C,m3,n3,'C');
END.
