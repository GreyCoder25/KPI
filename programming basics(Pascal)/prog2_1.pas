uses crt;
const
	numM = 'e';
type
	mult = set of char;
	mults = array ['a'..'e'] of mult;
var
	M:mults;
	X:mult;
	str:string;
procedure init(var a:mult);
	var
		i:byte;
	begin
		for i:=1 to random(10) do
			a:=a+[chr( 97+random(10) )];
	end;
	
procedure input(var M:mults);
	var
		i:char;
	begin
		for i:='a' to numM do
			init(M[i]);
	end;
	
procedure output(const M:mults);
	var
		i:char;
		j:byte;
	begin
		for i:='a' to numM do begin
			for j:=97 to 106 do 
				if chr(j) in M[i] then write(chr(j),' ');
			writeln;
		end;
	end;
procedure outX(X:mult);
	var
		j:byte;
	begin
		write('X = { ');
		for j:=97 to 106 do
			if chr(j) in X then write(chr(j),' ');
		write('}');
	end;
	
procedure prog1;
	begin
		randomize;
		input(M);
		output(M);
		if ( M['d'] <= ((M['e']*M['a']) + (M['b']*M['c'])) ) then
			X:=M['a']+M['b']*M['c']-M['d']*M['e']
		else
			X:=M['a']-M['b']*M['c']*M['d']-M['e'];
		outX(X);
	end;
	
{procedure input2(var str:string);
	begin
		write('Enter the text: ');
		readln;
		readln(str);
	end;
}
{procedure output(const str:string);
	begin
		writeln(str);
	end;
}	
{procedure prog2(var str:string);
	var
		i:word;
	begin
		input2(str);
		i:=1;
		while (i <= length(str)) do begin
			if (str[i] in ['0'..'9']) then begin
				delete(str,i,1);
				dec(i);
			end
			else if (str[i] in ['+','-']) then begin
				insert(str[i],str,i);
				inc(i);
			end;
			inc(i);
		end;
		output(str);
	end;
}

procedure prog2;
	var
		ch:char;
	begin
		write('Enter the text you want to correct: ');
		ch:=readkey;
		while (ch <> '.') do begin
			if (not (ch in ['0'..'9'])) then
				write(ch);
			if (ch in ['+','-']) then
				write(ch);
			ch:=readkey;
		end;
			
	end;

procedure main;
	var
		action:byte;
	begin
		writeln('1 - prog1, 2 - prog2');
		write('Enter the number of thing you want to do: ');
		read(action);
		case action of
			1:prog1;
			2:prog2;
		end;
	end;

begin
	main;
end.
