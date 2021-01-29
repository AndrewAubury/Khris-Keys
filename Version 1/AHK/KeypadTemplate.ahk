CapsLock::
	KeyWait, CapsLock
	If (A_PriorKey="CapsLock")
		SetCapsLockState, % GetKeyState("CapsLock","T") ? "Off" : "On"
Return

NumLock::
	KeyWait, NumLock
	If (A_PriorKey="NumLock")
		SetNumLockState, % GetKeyState("NumLock","T") ? "Off" : "On"
Return

ScrollLock::
	KeyWait, ScrollLock
	If (A_PriorKey="ScrollLock")
		SetScrollLockState, % GetKeyState("ScrollLock","T") ? "Off" : "On"
Return

#If, GetKeyState("CapsLock", "P") && GetKeyState("NumLock", "P") && GetKeyState("ScrollLock", "P") ;Layer 7
#+F1::Send, L7
#If, GetKeyState("NumLock", "P") && GetKeyState("ScrollLock", "P") ;Layer 6
#+F1::Send, L6
#If, GetKeyState("CapsLock", "P") && GetKeyState("ScrollLock", "P") ;Layer 5
#+F1::Send, L5
#If, GetKeyState("CapsLock", "P") && GetKeyState("NumLock", "P") ;Layer 4
#+F1::Send L4
#If, && GetKeyState("ScrollLock", "P") ;Layer 3
#+F1::Send, L3
#If, GetKeyState("NumLock", "P") ;Layer 2
#+F1::Send, L2
#If, GetKeyState("CapsLock", "P") ;Layer 1
#+F1::Send, L1
#If ;layer 0WS
#+F1::Send, L0