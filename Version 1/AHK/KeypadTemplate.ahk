Home::
	KeyWait, Home
	If (A_PriorKey="Home")
		Send {Home}
Return
End::
	KeyWait, End
	If (A_PriorKey="End")
		Send {End}
Return
Insert::
	KeyWait, Insert
	If (A_PriorKey="Insert")
		Send {Insert}
Return

#If, GetKeyState("Home") && GetKeyState("End") && GetKeyState("Insert") ;Layer 7
#+F1::Send, L7
#If, GetKeyState("End") && GetKeyState("Insert") ;Layer 6
#+F1::Send, L6
#If, GetKeyState("Home") && GetKeyState("Insert") ;Layer 5
#+F1::Send, L5
#If, GetKeyState("Home") && GetKeyState("End") ;Layer 4
#+F1::Send L4
#If, && GetKeyState("Insert") ;Layer 3
#+F1::Send, L3
#If, GetKeyState("End") ;Layer 2
#+F1::Send, L2
#If, GetKeyState("Home") ;Layer 1
#+F1::Send, L1
#If ;layer 0WS
#+F1::Send, L0