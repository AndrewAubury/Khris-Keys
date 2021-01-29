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

#If, !GetKeyState("CapsLock", "P") && !GetKeyState("NumLock", "P") && !GetKeyState("ScrollLock", "P") ;Layer 0 
#+F1::Run "C:\Program Files (x86)\VB\Voicemeeter\voicemeeter8x64.exe"
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#If, GetKeyState("CapsLock", "P") && !GetKeyState("NumLock", "P") && !GetKeyState("ScrollLock", "P") ;Layer 1
#+F1::Run "C:\Program Files\Locktime Software\NetLimiter 4\NLClientApp.exe
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#If, !GetKeyState("CapsLock", "P") && GetKeyState("NumLock", "P") && !GetKeyState("ScrollLock", "P") ;Layer 2
;#+F1::
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#If, !GetKeyState("CapsLock", "P") && !GetKeyState("NumLock", "P") && GetKeyState("ScrollLock", "P") ;Layer 3
;#+F1::
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#If, GetKeyState("CapsLock", "P") && GetKeyState("NumLock", "P") && !GetKeyState("ScrollLock", "P") ;Layer 4 
;#+F1::
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#If, !GetKeyState("CapsLock", "P") && GetKeyState("NumLock", "P") && GetKeyState("ScrollLock", "P") ;Layer 5
;#+F1::
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#If, GetKeyState("CapsLock", "P") && !GetKeyState("NumLock", "P") && GetKeyState("ScrollLock", "P") ;Layer 6
;#+F1::
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#If, GetKeyState("CapsLock", "P") && GetKeyState("NumLock", "P") && GetKeyState("ScrollLock", "P") ;Layer 7
;#+F1::
;#+F2::
;#+F3::
;#+F4::
;#+F5::
;#+F6::
;#+F7::
;#+F8::
;#+F9::
;#+F10::
;#+F11::
;#+F12::
;#+F13::
;#+F14::
;#+F15::
;#+F16::
#if
