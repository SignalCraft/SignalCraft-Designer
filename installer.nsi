; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install example2.nsi into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "UnnamedCompany UnnamedSoftware"

; The file to write
OutFile "unnamedsoftware.exe"

; The default installation directory
InstallDir $PROGRAMFILES\UnnamedCompany\UnnamedSoftware

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\UnnamedCompany\UnnamedSoftware" "installPath"

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
Section "UnnamedSoftware (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "unnamedsoftware.exe"
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\UnnamedCompany\UnnamedSoftware "installPath" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\UnnamedSoftware" "DisplayName" "Unnamed Software"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\UnnamedSoftware" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\UnnamedSoftware" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\UnnamedSoftware" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\UnnamedCompany\UnnamedSoftware"
  CreateShortcut "$SMPROGRAMS\UnnamedCompany\UnnamedSoftware\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortcut "$SMPROGRAMS\UnnamedCompany\UnnamedSoftware\UnnamedSoftware.lnk" "$INSTDIR\unnamedsoftware.exe" "" "$INSTDIR\unnamedsoftware.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\UnnamedSoftware"
  DeleteRegKey HKLM SOFTWARE\UnnamedCompany\UnnamedSoftware

  ; Remove files and uninstaller
  Delete $INSTDIR\unnamedsoftware.exe
  Delete $INSTDIR\uninstall.exe

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\UnnamedCompany\UnnamedSoftware\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\UnnamedCompany\UnnamedSoftware"
  RMDir "$INSTDIR"

SectionEnd
