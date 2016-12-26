{$MODE TP}
uses Crt;
type

	TTree = ^TNode;
	
	TNode = record
		Inf:integer;
		color:byte;
		Left:TTree;
		Right:TTree;
		level:word;
		BelowF:boolean;
		BelowL:boolean;
	end;
	
	SetPointer = procedure (Root:TTree;var P:TTree; X:integer);
	SetAtt = procedure (Root:TTree);
	
function Tree(n,h:word):TTree;
	var
		P:TTree;
		nl,nr,val:word;
	begin
		if n = 0 then P:=nil
		  else
			begin
				nl:=n div 2;
				nr:=n - nl - 1;
				val:=random(10);
				New(P);
				with P^ do
					begin
						Inf:=val;
						color:=white;
						BelowF:=FALSE;
						BelowL:=FALSE;
						level:=h;
						Left:=Tree(nl,h+1);
						Right:=Tree(nr,h+1);
					end;
			end;
		Tree:=P;
	end;
	
procedure PrintTree(Root:TTree; XPos,YPos,Shift:byte);
	begin
		if Root <> nil then
			begin
				GotoXY(XPos,YPos);
			
				TextColor(Root^.color);
				write(Root^.Inf);
				
				YPos:=WhereY+2;
				PrintTree(Root^.Left,XPos-Shift,YPos,Shift div 2);
				PrintTree(Root^.Right,XPos+Shift,YPos,Shift div 2);
				
				TextColor(white);

			end;
	end;
	
	
procedure PrintTreeInf(Root:TTree);
	begin
		if Root <> nil then
			with Root^ do
			  begin
				write(Inf,' ');
				
				if (Left <> nil) and (Right <> nil) and (Left^.Inf > Right^.Inf) then
					begin
						PrintTreeInf(Right);
						PrintTreeInf(Left);
					end
				else
					begin
						PrintTreeInf(Left);
						PrintTreeInf(Right);
					end;
			  end;
	end;
	
procedure SetPF(Root:TTree;var P:TTree; X:integer);
	begin
		if (P = nil) and (Root^.Inf = X) then
			P:=Root;
	end;

procedure SetPL(Root:TTree;var P:TTree; X:integer);
	begin
		if Root^.Inf = X then
			P:=Root;
	end;
	
procedure FindAndMark(Root:TTree; X:integer; var P:TTree; Action:SetPointer);
	begin
		if Root <> nil then
			  begin
				Action(Root,P,X);
				if (Root^.Left <> nil) and (Root^.Right <> nil) and (Root^.Left^.Inf > Root^.Right^.Inf) then
					begin
						FindAndMark(Root^.Right,X,P,Action);
						FindAndMark(Root^.Left,X,P,Action);
					end
				else
					begin
						FindAndMark(Root^.Left,X,P,Action);
						FindAndMark(Root^.Right,X,P,Action);
					end;
			  end;
	end;
	
procedure SetBF(Root:TTree);
	begin
		Root^.BelowF:=TRUE;
		Root^.color:=lightgreen;
	end;
	

procedure SetBL(Root:TTree);
	begin
		Root^.BelowL:=TRUE;
		Root^.color:=lightcyan;
	end;
	
procedure MarkNodesBelow(Root,P:TTree; Action:SetAtt);
	begin
		if (Root <> nil) and (P <> nil) then
			  begin
				if Root^.level > P^.level then Action(Root);
				if (Root^.Left <> nil) and (Root^.Right <> nil) and (Root^.Left^.Inf > Root^.Right^.Inf) then
					begin
						MarkNodesBelow(Root^.Right,P,Action);
						MarkNodesBelow(Root^.Left,P,Action);
					end
				else
					begin
						MarkNodesBelow(Root^.Left,P,Action);
						MarkNodesBelow(Root^.Right,P,Action);
					end;
			  end;
	end;
	
procedure TreeInput(var num:word);
	begin
	  repeat
		write('Enter number of the nodes: ');
		{$I-}
		readln(num);
		{$I+}
	  until (IOResult = 0) and (num >=15) and (num <= 31);
			
	end;
	
var
	T1,FEq,LEq:TTree;
	n,X:word;
	
BEGIN{main}
	randomize;
	TreeInput(n);
	clrscr;
	
	T1:=Tree(n,0);
	
	FEq:=nil;
	LEq:=nil;
	
	X:=random(10);
	
	FindAndMark(T1,X,FEq,SetPF);
	FindAndMark(T1,X,LEq,SetPL);
	
	
	//MarkNodesBelow(T1,FEq,SetBF);
	MarkNodesBelow(T1,LEq,SetBL);
	
	if FEq <> nil then FEq^.color:=red;
	if LEq <> nil then LEq^.color:=blue;
	
	PrintTree(T1,40,1,20);
	
	writeln;
	writeln;
	writeln;
	writeln('Search for the element ',X);
	
	PrintTreeInf(T1);
END.{main}
