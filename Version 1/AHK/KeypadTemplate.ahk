

#If, GetKeyState("F17") && GetKeyState("F18") && GetKeyState("F19") ;Layer 7
#+F1::Send, L7
#If, GetKeyState("F17") && GetKeyState("F19") ;Layer 6
#+F1::Send, L6
#If, GetKeyState("F18") && GetKeyState("F19") ;Layer 5
#+F1::Send, L5
#If, GetKeyState("F17") && GetKeyState("F18") ;Layer 4
#+F1::Send L4
#If, && GetKeyState("F19") ;Layer 3
#+F1::Send, L3
#If, GetKeyState("F18") ;Layer 2
#+F1::Send, L2
#If, GetKeyState("F17") ;Layer 1
#+F1::Send, L1
#If ;layer 0WS
#+F1::Send, L0