# define the name of the installer
Outfile "LotsOfLines.exe"

# Set program files as install directory
InstallDir $PROGRAMFILES\LotsOfLines

# default section
Section
 
# define the output path for this file
SetOutPath $INSTDIR
 
# define what to install and place it in the output path
File bin\release\LotsOfLinesApp.exe
File /r data

# define uninstaller name
WriteUninstaller $INSTDIR\uninstaller.exe
 
SectionEnd

Section "Uninstall"
 
# Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe
 
# now delete installed files
Delete $INSTDIR\LotsOfLinesApp.exe
RMDir /r $INSTDIR\data
 
SectionEnd
