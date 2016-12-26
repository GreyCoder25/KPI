{$MODE TP}
uses crt;
type
	tfile = text;
var
	f,g:tfile;
procedure OpenFileError(var f:tfile; name:string);
	begin
		if IOResult <> 0 then
			begin
				clrscr;
				writeln('Ошибка открытия файла ',name);
				halt(0);
			end;
	end;
	
procedure IsEmpty(var f:tfile);
	begin
		if seekeof(f) then 
			begin
				clrscr;
				writeln('Исходный файл пуст');
				halt(0);
			end;
	end;
	
function readword(var f:tfile):string;
	var
		r:char;
		wordd:string;
	begin
		wordd:='';
		repeat 
			read(f,r);
			wordd:=wordd+r;
		until (r = ' ') or (eoln(f));
		
		if (length(wordd)>1) and (wordd[length(wordd)] = ' ') then
			delete(wordd,length(wordd),1);

		readword:=wordd;
	end;
	
procedure check(var f:tfile;var temp,str:string);
	begin
		temp:=' ';
		while temp = ' ' do
			begin
				temp:=readword(f);
			end;
		str:=temp;
	end;
	
procedure main(var f,g:tfile);
	var
		name,surname,patronymic,temp:string;
		space:char;
	begin
		{$I-}
		reset(f);
		{I+}
		OpenFileError(f,'f');
		IsEmpty(f);
		
		{$I-}
		rewrite(g);
		{I+}
		OpenFileError(g,'g');
		
		space:=' ';
		
		while not seekeof(f) do
			begin
				if seekeoln(f) then readln(f);
				
				check(f,temp,surname);
				check(f,temp,name);
				check(f,temp,patronymic);
				
				write(g,name,space);
				write(g,patronymic,space);
				writeln(g,surname);		
			end;
		close(g);
		close(f);
		
	end;
	
begin
	assign(f,'f.txt');
	assign(g,'g.txt');
	main(f,g);
end.
