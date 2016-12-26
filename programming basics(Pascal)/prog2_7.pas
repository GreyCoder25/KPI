uses SLL,GeomFig;

var
	ListObj:SLList;
	PObj:Point;
	LineObj:Line;
	elem:integer;
	i:byte;

BEGIN{main}
	{ListObj.CreateList;}
	ListObj.LPInit;
	writeln(ListObj.GetHeadId);
	writeln(ListObj.GetTailId);
	
	{ListObj.PrintList;
	for i:=1 to 10 do
		ListObj.PushBack(i);
	ListObj.PrintList;
	ListObj.PopBack(elem);
	ListObj.PrintList;
	
	PObj.Init(1,1);
	PObj.PrintPoint;
	
	LineObj.Init(8,7);
	LineObj.PrintLine;}
END.{main}
