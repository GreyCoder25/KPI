uses ptcGraph,ptcCrt;

const
	num = 1600; {!}
	//tmin = -80; {!}
	//tmax = 80;  {!}
	tmin = 0;
	tmax = 20;
	xbeg = 1; ybeg = 1;
	xend = 480; yend = 480; 
	x0 = 240; y0 = 240;
	k = 20;
type
	ValArr = array [1..num] of double;
	ValPixArr = array [1..num] of word;
	
var
	x,y:ValArr;
	scrx,scry:ValPixArr;
	Driver,Mode:integer;
	mx,my:real;
	
procedure GraphInit(var Driver,Mode:integer);//инициализация графического режима
	begin
		Driver:=VGA;   //адаптер VGA
		Mode:=VGAHi;   //режим 640*480 пикс.*16 цветов
	
		writeln('Драйвер: ', Driver, ', Графический режим: ', Mode);
		InitGraph(Driver, Mode,'');
		WriteLn('Разрешение: ', GetMaxX+1,'x',GetMaxY+1, ', Цветов: ', GetMaxColor+1);
	end;{GraphInit}

function dt(min,max:real; num:word):real;
	begin
		dt:=(max - min)/(num -1);
	end;{dt}
	
function max(const A:ValArr; size:word):real;
	var
		i:word;
		maxel:real;
	begin
		maxel:=A[1];
		
		for i:= 2 to size do
			if A[i] > maxel then
				maxel:=A[i];
				
		max:=maxel;
			
	end;{max}
	
function min(const A:ValArr; size:word):real;
	var
		i:word;
		minel:real;
	begin
		minel:=A[1];
		
		for i:= 2 to size do
			if A[i] < minel then
				minel:=A[i];
				
		min:=minel;
			
	end;{min}
	
procedure CoordArrCalc(var Ax,Ay:ValArr; tmin,tmax:real; a,b:real; size:word);
	var
		i:word;
		t,step:real;
	begin
		t:=tmin; i:=1;
		step:=dt(tmin,tmax,size);
		
		for i:=1 to num do
			begin
				//Ax[i]:=3*a*t/(t*t*t+1);
				//Ay[i]:=3*a*t*t/(t*t*t+1);
				Ax[i]:=(a+b)*cos(t) - a*cos((a+b)*t/a);
				Ay[i]:=(a+b)*sin(t) - a*sin((a+b)*t/a);
				
				t:=t+step;
				//if (t >=-1.5) and (t<=-0.5) then t:=-0.5;
			end;
		
	end;{CoordArrCalc}
	
procedure mcalc(x1,y1,x2,y2:word; const Ax,Ay:ValArr; size:word; var mx,my:real; m:byte);
	begin
	
		mx:=(x2 - x1)/m;{(max(Ax,size) - min(Ax,size));}
		my:=(y2 - y1)/m;{(max(Ay,size) - min(Ay,size));}
	end;{mcalc}
	
procedure ScrCoordCalc(var Ascrx,Ascry:ValPixArr; const Ax,Ay:ValArr; mx,my:real; size:word; x0,y0:word);
	var
		i:word;
	begin
	
		for i:=1 to size do
			begin
				Ascrx[i]:=x0 + round(Ax[i]*mx);
				Ascry[i]:=y0 - round(Ay[i]*my);

				
			end;
	end;{ScrCoordCalc}
	
procedure PrintArr(const A:ValArr; size:word);
	var
		i:word;
	begin
		writeln;
	
		for i:=1 to size do	
			write(A[i]:8:4);
			
		writeln;
	end;{PrintArr}
	
procedure GraphicDraw(const Ascrx,Ascry:ValPixArr; size:word);
	var
		i:word;
	begin
		SetColor(white);
		i:=0;
		
		{repeat
			i:=i+1;
			Line(Ascrx[i],Ascry[i],Ascrx[i+1],Ascry[i+1]);
		until(Ascry[i+2]-220 < 0);
		
		inc(i);
			
		repeat
			i:=i+1;
			Line(Ascrx[i],Ascry[i],Ascrx[i+1],Ascry[i+1]);	
		until(i = num-1);}
		repeat
			i:=i+1;
			Line(Ascrx[i],Ascry[i],Ascrx[i+1],Ascry[i+1]);	
		until(i = num-1);
			
	
	end;{GraphicDraw}
	
procedure CoordMarcDraw(x0,y0:word; m:byte);
	var
		l:word;
		i:byte;
		dig:string;
	begin
		Line(x0,0,x0,yend); Line(x0,0,x0+5,5); Line(x0,0,x0-5,5); OutTextXY(x0+7,0,'Y');
		Line(0,y0,xend,y0); Line(xend,y0,xend-5,y0+5); Line(xend,y0,xend-5,y0-5); OutTextXY(xend,y0+7,'X');
		
		for i:=1 to m-1 do
			begin
				l:=i*round((xend-xbeg)/m);
				Line(l,y0+5,l,y0-5);
				str(i-(m div 2),dig);
				OutTextXY(l+3,y0+8,dig)
			end;
			
		for i:=m-1 downto (m div 2 +1) do
			begin
				l:=(m-i)*round((yend-ybeg)/m);
				Line(x0+5,l,x0-5,l);
				str(i-(m div 2),dig);
				OutTextXY(x0+5,l,dig)
			end;
			
		for i:=(m div 2 - 1) downto 1 do
			begin
				l:=(m-i)*round((yend-ybeg)/m);
				Line(x0+5,l,x0-5,l);
				str(i-(m div 2),dig);
				OutTextXY(x0+5,l,dig)
			end;
	end;{CoordMarcDraw}
	
procedure signature;
	begin
		OutTextXY(xend-30,y0 div 2,'Made by: Serhiy Latyuk');
		OutTextXY(xend-30,y0 div 2 + 15,'y = 3at^2/(t^3+1);');
		OutTextXY(xend-30,y0 div 2 + 30,'x = 3at/(t^3+1);');
		
	end;

BEGIN{main}
	GraphInit(Driver,Mode);
	CoordArrCalc(x,y,tmin,tmax,3,2,num);
	
	mcalc(xbeg,ybeg,xend,yend,x,y,num,mx,my,k);

	ScrCoordCalc(scrx,scry,x,y,mx,my,num,x0,y0);
	
	CoordMarcDraw(x0,y0,k);
	GraphicDraw(scrx,scry,num);
	signature;
	
	readkey;
	CloseGraph;
END.{main}
