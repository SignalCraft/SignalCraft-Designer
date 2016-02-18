; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "SignalCraft"

; The file to write
OutFile "Install SignalCraft.exe"

; The default installation directory
InstallDir $PROGRAMFILES\SignalCraft

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\SignalCraft" "InstallDir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "SignalCraft"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "build\release\SignalCraft.exe"
  File "build\release\Qt5Core.dll"
  File "build\release\Qt5Gui.dll"
  File "build\release\Qt5Widgets.dll"
  File "blocks.json"
  SetOutPath $INSTDIR\blocks
  File /r "blocks\*.h"
  SetOutPath $INSTDIR\platforms
  File /r "build\release\platforms\*.dll"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\SignalCraft "InstallDir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SignalCraft" "DisplayName" "SignalCraft"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SignalCraft" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SignalCraft" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SignalCraft" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\SignalCraft"
  CreateShortcut "$SMPROGRAMS\SignalCraft\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\SignalCraft\SignalCraft.lnk" "$INSTDIR\SignalCraft.exe" "" "$INSTDIR\SignalCraft.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\SignalCraft"
  DeleteRegKey HKLM SOFTWARE\SignalCraft

  ; Remove files and uninstaller
  Delete $INSTDIR\SignalCraft.exe
  Delete $INSTDIR\Qt5Core.dll
  Delete $INSTDIR\Qt5Gui.dll
  Delete $INSTDIR\Qt5Widgets.dll
  Delete $INSTDIR\blocks.json
  RMDir /r $INSTDIR\blocks
  RMDir /r $INSTDIR\platforms
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\SignalCraft\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\SignalCraft"
  RMDir "$INSTDIR"

SectionEnd
