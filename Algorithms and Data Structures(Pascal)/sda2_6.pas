type
	TPtr = ^TNode;
	
	TNode = record
		Inf:integer;
		Left:TPtr;
		Right:TPtr;
	end;
	
var
	Beg2L,End2L:TPtr;
	result:longint;
	
procedure CreateDList(var Head,Tail:TPtr);
	const
		rand = 3;
	var
		P:TPtr;
		i:word;
		n:word;
	begin
		repeat
			write('Enter number of elements in the list: ');
			{$I-}
			readln(n);
			{$I+}
			if (IOResult = 0) and (n>0) then
				Break
			else
				writeln('Not correct input or number of elements is too big');
		until (FALSE);
		
		randomize;

		New(P);
		P^.Inf:=random(rand);
		P^.Left:=nil;
		Head:=P;
		Tail:=P;
					
		for i:=2 to n do
			begin
				New(P);
				P^.Inf:=random(rand);
				P^.Left:=Tail;
				Tail^.Right:=P;
				Tail:=P;
			end;
		
		Tail^.Right:=nil;	
	
	end;{CreateDList}
	
function IsEmpty(Head:TPtr):boolean;
	begin
		if Head = nil then
			IsEmpty:=TRUE
		else
			IsEmpty:=FALSE;
	end;{IsEmpty}
	
procedure PrintList(Head:TPtr);
	var
		P:TPtr;
	begin
		writeln;
	
		P:=Head;
		
		if IsEmpty(P) then
			writeln('List is empty')
		else
			begin
				writeln('List:');
				while P <> nil do
					begin
						write(P^.Inf,' ');
						P:=P^.Right;
					end;
			end;
			
		writeln;
	end;{PrintList}
	
procedure Processing12(Head,Tail:TPtr; var res:longint);
	var
		Pb,Pe:TPtr;
	begin
		if Head = Tail then
			writeln('Operation is not possible because number of elements is too small')
		else
			begin
				writeln;
			
				Pb:=Head;
				Pe:=Tail;
				res:=1;
				
				while Pb <> Tail do
					begin
						res:=res*(Pb^.Inf + Pb^.Right^.Inf + 2*Pe^.Inf);
						write('(',Pb^.Inf,' + ',Pb^.Right^.Inf,' + 2*',Pe^.Inf,')');
						Pb:=Pb^.Right;
						Pe:=Pe^.Left;
					end;
				write(' = ',res);
				
				writeln;
				writeln;
			end;
			
		writeln('Result = ',res);
	end;{Processing12}
	
procedure ListFree(var Head,Tail:TPtr);
	var
		P:TPtr;
	begin
		P:=Head;
		while P <> nil do
			begin
				Head:=Head^.Right;
				Dispose(P);
				P:=Head;
			end;
		Tail:=nil;
	end;{ListFree}
	
BEGIN{main}
	CreateDList(Beg2L,End2L);
	PrintList(Beg2L);
	Processing12(Beg2L,End2L,result);
	ListFree(Beg2L,End2L);
END.{main}
