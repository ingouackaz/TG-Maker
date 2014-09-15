#!/bin/sh
#TGMaker game installer
#Execute this script: it will spawn your game as a single executable.

game="./CannedShit"
echo "TGMaker Installer"
echo "-=-=-=-=-=-=-=-=-"
echo ""
echo "Requirements: SFML1.6 (w/ correct paths), /tmp dir, gcc, base64, gunzip, GNU tail, mktemp"
echo "Generating temporary file..."
tmpa=`mktemp /tmp/TGMaker.XXXXXXXX.b64`
tmpb=`mktemp /tmp/TGMaker.XXXXXXXX.gz`
tmpc=`mktemp /tmp/TGMaker.XXXXXXXX.cpp`
echo "Extracting game code..."

# made by benoit
tail $0 -n +`echo "\`grep -n \\\`echo -n GAME && echo CODE\\\` $0 | cut -d':' -f1\` + 1" | bc` >> $tmpa

echo "Decoding..."
base64 -di $tmpa >> $tmpb
echo "Ungzipping..."
gunzip -c $tmpb >> $tmpc
echo "Compiling..."
gcc -o $game $tmpc -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system
echo "Finalizing..."
chmod +x $game
echo "Cleaning up /tmp dir..."
rm -f /tmp/TGMaker*
echo "Script complete. Please check for errors."
echo "Your game is: $game"
exit

### #GAMECODE# ###
H4sIAAAAAAAAA61VbU/bMBD+nl9x2r4kUmkLWwGVgQSlMCQQiLCxSZMmk1xaT64d2Q6lmvjvOzsJ
TUumSWWRcmrv5bm7x7lz0HvDE/R68BlZitoEb8J5z2UiihThU3x2ddk71yyf8sR0p3l+1DByZaxG
NjsKgrfloxfG0uoF5IpLCyoDlueCJ8xyJYPa5YdGW2gJx0sb4BO3kKgUa6/Nq3CZZ4zLMAp+B0AP
pRxRfxa9GuZcpmruLSYbDm9REtP3XulKCp3yK09RXVE54X6/34Hdfj/qwDvHIsRTlqN5Fx0ENXhs
mbYwYTMEoVTu1fMpFwgh4XUvzHWOEtMwirypLKqKvdEqQWMAH1Fa82JxNYydCrw8eDE0cM/RemPo
ZQW+mqDuXiiDVd8w9FyvuPAMSpDu3SJHODxc5h8OfXAarQS4x5XgbWG0LO85aDY3Esg0mEQjymA1
jgxhTWHlfarZHHKNKWac6ALjiV6Jcy7+fPwhDIeX5Bhu0wG5d6/84cSg4zsYKaG0O+E0atTYBjTi
OhEY7rhoLzxOA+M7CqHmZaKG+kQU+C/sW0wskxOC/zCo4Xed8H8bYOeOp2iNlZOCixQYJIWxakYj
Ih/xqeRm5WvxyeBGicVEyWVBlaJ7nKY3biZDSrnl8i4ThzsD4otU7huv4UqLI2Jn34tml69AHaDD
XAfd92/U2Ri0rdLtvb4XUWcD0Ppo10FrsRHoVl3q/6x0qyZ1A05XxsqPEzAJqrDC/Zzz1E5fJY7R
XpcO985OY7UOxA17oOWTcUFeE0JMAaVX2SnW6K9wx97ljILCjAmDLT2XLlX20OoC11LfIyTUgLGE
AoUpE2aFTNzdYWgoZjO6Q6wCRna/pVMaQl+aevhF82fa2i2p+8uH4Ae17YCu1CNNsp/ffr/FHifM
jTrFtxhvlaV7KPw4aNt9ja38skeqwDX3My6p00UHUm5ywRaeD+0vMlqcmXZXERHSsnlPy4B6Z1f7
urqQx98u7n7GX0ajcRwfBM/BHwtB6A3GCAAA
