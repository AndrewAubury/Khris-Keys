

#If, GetKeyState("F17") && GetKeyState("F18") && GetKeyState("F19") ;Layer 7
F20 & F1::Send, L7{Enter}
#If, GetKeyState("F17") && GetKeyState("F19") ;Layer 6, ID = 5
F20 & F1::Send, L6{Enter}
#If, GetKeyState("F18") && GetKeyState("F19") ;Layer 5, ID = 6
F20 & F1::Send, L5{Enter}
#If, GetKeyState("F17") && GetKeyState("F18") ;Layer 4, ID = 3
F20 & F1::Send L4{Enter}
#If, && GetKeyState("F19") ;Layer 3, ID = 4
F20 & F1::Send, L3{Enter}
#If, GetKeyState("F18") ;Layer 2, ID = 2
F20 & F1::Send, L2{Enter}
#If, GetKeyState("F17") ;Layer 1, ID= 1
F20 & F1::Send, L1{Enter}
#If ;Layer 0, ID = 0
F20 & F1::Send, L0{Enter}